#include "ClientProcess.h"
#include "Object.h"
#include "Player.h"


DWORD WINAPI ClientProcess(LPVOID arg)
{
    extern UINT MyID;
	//월드 정보를 수신, 입력 정보를 송신

    // LPVOID는 void*임 값이 아니라 포인터를 가지고 있음
    SOCKET param = *((SOCKET*)arg);

    while (1)
    {
        RecvWorld(param);
        SendInputChange(param, players[MyID].inputs);
    }

	return 0;
}

void SendInputChange(SOCKET sock, const PlayerInputs& input)
{
    PacketParam header{};
    header.type = PACK_INPUT_COMMAND;
    header.size = sizeof(PacketParam) + sizeof(PlayerInputs);

    int retval = send(sock, reinterpret_cast<const char*>(&header), sizeof(header), 0);
    if (retval == SOCKET_ERROR) return;

    EnterCriticalSection(&InputCS);
    retval = send(sock, reinterpret_cast<const char*>(&input), sizeof(input), 0);
    if (retval == SOCKET_ERROR) return;
    LeaveCriticalSection(&InputCS);

    // 디버그용
    printf("[SendInputChange] playerid=%d jump=%d updown=%d rightleft=%d dx=%.2f dy=%.2f\n",
        input.playerid, input.jump, input.updown, input.rightleft, input.deltax, input.deltay);
}

void RecvWorld(SOCKET sock)
{
    PacketParam header{};
    int retval = recv(sock, reinterpret_cast<char*>(&header), sizeof(header), MSG_WAITALL);
    if (retval <= 0) {
        err_display("recv() - Header");
        return;
    }
    // 헤더 타입 확인
    if (header.type != PACK_FRAME_STATE) {
        printf("[RecvWorld] Unexpected packet type: %d\n", header.type);
        return;
    }

    // 헤더에 명시된 크기만큼 버퍼를 준비
    std::vector<uint8_t> buffer(header.size);
    retval = recv(sock, reinterpret_cast<char*>(buffer.data()), static_cast<int>(buffer.size()), MSG_WAITALL);
    if (retval <= 0) {
        err_display("recv() - Body");
        return;
    }

    // PktFrameState 데이터 역직렬화
    PktFrameState pkt;
    pkt.DynObjPos = new float[MoveObjects.size()][3];
    pkt.Deserialize(buffer.data(), buffer.size());

    // 플레이어 데이터 업데이트
    for (int i = 0; i < 3; ++i) {
        players[i].SetPosX(pkt.players[i].position[0]);
        players[i].SetPosY(pkt.players[i].position[1]);
        players[i].SetPosZ(pkt.players[i].position[2]);

        players[i].SetRotationX(pkt.players[i].rotation[0]);
        players[i].SetRotationY(pkt.players[i].rotation[1]);
        // rotation[2]는 setter가 없으므로 무시
    }

    // 움직이는 객체 데이터 업데이트
    if (pkt.move_block_size > 0 && pkt.move_block_size <= static_cast<int>(MoveObjects.size())) {
        for (int i = 0; i < pkt.move_block_size; ++i) {
            std::array<float, 3> pos = {
                pkt.DynObjPos[0][i],
                pkt.DynObjPos[1][i],
                pkt.DynObjPos[2][i]
            };

            // 클라이언트에서는 방향 정보가 필요 없으므로 {0, 0, 0}으로 대체
            std::array<int, 3> dirArr = { 0, 0, 0 };
            MoveObjects[i].Init(pos, dirArr);
        }
    }

	delete[] pkt.DynObjPos;
}
