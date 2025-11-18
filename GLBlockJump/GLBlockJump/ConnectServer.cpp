#include "ConnectServer.h"
#include <iostream>
#include "ParticleSendRecv.h"

#include "GameState.h"


PacketParam staticObjParam; // 고정 객체를 전송할 패킷들의 총 정보
float staticObjectPosition[3]; // 고정된 객체들의 각 좌표를 넣어서 그 개수만큼 반복

PacketParam dynamicObjParam; // 움직이는 객체를 전송할 패킷들의 총 정보
float dynamicObjectPosition[3]; // 움직이는 객체들의 각 좌표를 넣어서 그 개수만큼

SOCKET InitSocket(const char* SERVERIP)
{
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        err_display("WSAStartup()");
        return INVALID_SOCKET;
    }

    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        err_display("socket()");
        WSACleanup();
        return INVALID_SOCKET;
    }

    struct sockaddr_in serveraddr;
    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(SERVERPORT);

    int retval = inet_pton(AF_INET, SERVERIP, &serveraddr.sin_addr);
    if (retval <= 0) {
        if (retval == 0)
            printf("[오류] 잘못된 IP 주소 형식: %s\n", SERVERIP);
        else
            err_display("inet_pton()");
        closesocket(sock);
        WSACleanup();
        return INVALID_SOCKET;
    }

    if (connect(sock, (struct sockaddr*)&serveraddr, sizeof(serveraddr)) == SOCKET_ERROR) {
        err_display("connect()");
        closesocket(sock);
        WSACleanup();
        return INVALID_SOCKET;
    }

    return sock;
}

void CleanupSocket(SOCKET sock)
{
    closesocket(sock);
    WSACleanup();
}

void RecvInitPlayers(SOCKET sock, UINT &MyID)
{
    PacketParam header{};
    int pkType = 0;
    int retval = recv(sock, (char*)&pkType, sizeof(int), MSG_WAITALL);
    std::cout << "연결 종료\n\n";
    if (retval <= 0) return;

    header.type = (PacketType)pkType;

    retval = recv(sock, (char*)&header.size, sizeof(header.size), MSG_WAITALL);
    if (retval <= 0) return;

    if (header.type != PACK_INIT_PLAYERS) return;

    int bodySize = header.size / sizeof(PacketParam);
    if (bodySize <= 0 || bodySize > 1024) return;


  

    std::vector<uint8_t> buffer(sizeof(PktInitPlayers));
    retval = recv(sock, (char*)buffer.data(), buffer.size() * sizeof(uint8_t), MSG_WAITALL);
    if (retval <= 0) return;

    PktInitPlayers pkt;
    pkt.Deserialize(buffer.data(), buffer.size());
    MyID = pkt.myPlayerId;

    for (int i = 0; i < 3; ++i) {
        const std::array<float, 3> pos = {
            pkt.players[i].spawnPos[0],
            pkt.players[i].spawnPos[1],
            pkt.players[i].spawnPos[2]
        };
        players[i].Init(pos, pkt.players[i].playerId);
    }
}

void RecvInitWorldStatic(SOCKET sock)
{
    PacketParam header{};
    int pkType = 0;
    int retval = recv(sock, (char*)&pkType, sizeof(int), MSG_WAITALL);
    if (retval <= 0) return;

    header.type = (PacketType)pkType;

    if (header.type != PACK_INIT_WORLD_STATIC)
        return;

    size_t hsize = 0;
    retval = recv(sock, (char*)&hsize, sizeof(size_t), MSG_WAITALL);
    if (retval <= 0) return;

    header.size = ntohl(hsize);



    int bodySize = header.size * 3;
    if (bodySize <= 0) return;

    // 버퍼 안에는 초기 정점들을 넣음
    // 정점은 3개의 float로 구성이 되어 있고
    // 우리가 서버로부터 받은 size는 "정점"의 개수
    // 버퍼는 모든 "float"를 저장해야 하니까 정점을 풀어서 저장해야 해
    std::vector<float> buffer(header.size * 3);
    retval = recv_all(sock, (char*)buffer.data(), buffer.size() * 4);
    if (retval == SOCKET_ERROR) 
        err_quit("recv()");


    int objectCount = bodySize / 3;
    staticObjects.resize(objectCount);

    for (int i = 0; i < objectCount; ++i)
    {
        std::array<float, 3> pos = {
            buffer[i * 3 + 0],
            buffer[i * 3 + 1],
            buffer[i * 3 + 2]
        };
        staticObjects[i].Init(pos);
    }

    count_block = staticObjects.size();
}
void RecvInitWorldDynamic(SOCKET sock)
{
    PacketParam header{};
    int pkType = 0;
    int retval = recv(sock, (char*)&pkType, sizeof(int), MSG_WAITALL);
    if (retval <= 0) return;

    header.type = (PacketType)pkType;

    if (header.type != PACK_INIT_WORLD_DYNAMIC)
        return;

    size_t hsize = 0;
    retval = recv(sock, (char*)&hsize, sizeof(size_t), MSG_WAITALL);
    if (retval <= 0) return;

    header.size = ntohl(hsize);


    int bodySize = header.size * 3;
    if (bodySize <= 0) return;

    std::vector<float> buffer(header.size * 3);
    retval = recv(sock, (char*)buffer.data(), buffer.size() * 4, MSG_WAITALL);
    if (retval == SOCKET_ERROR) err_display("recv()");

    int objectCount = bodySize / 3;
    MoveObjects.resize(objectCount);

    for (int i = 0; i < objectCount; ++i)
    {
        std::array<float, 3> pos = {
            buffer[i * 3 + 0],
            buffer[i * 3 + 1],
            buffer[i * 3 + 2]
        };
        MoveObjects[i].Init(pos, {0, 0, 0});
    }

    count_moving_block = MoveObjects.size();
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
    int pkType = 0;

    int retval = recv(sock, (char*)&pkType, sizeof(int), MSG_WAITALL);
    if (retval <= 0) return;

    header.type = (PacketType)pkType;
    if (header.type != PACK_FRAME_STATE) return;

    retval = recv(sock, (char*)&header.size, sizeof(header.size), MSG_WAITALL);
    if (retval <= 0) return;

    std::vector<uint8_t> buffer(header.size);
    retval = recv(sock, (char*)buffer.data(), (int)buffer.size(), MSG_WAITALL);
    if (retval <= 0) return;

    PktFrameState pkt;
    pkt.Deserialize(buffer.data(), (int)buffer.size());

    EnterCriticalSection(&FrameCS);

    for (int i = 0; i < 3; ++i)
    {
        players[i].SetPosX(pkt.players[i].position[0]);
        players[i].SetPosY(pkt.players[i].position[1]);
        players[i].SetPosZ(pkt.players[i].position[2]);

        players[i].SetRotationX(pkt.players[i].rotation[0]);
        players[i].SetRotationY(pkt.players[i].rotation[1]);
        // rotation[2]는 setter가 없으니 일단 무시
    }

    if (pkt.move_block_size > 0 &&
        pkt.move_block_size <= (int)MoveObjects.size())
    {
        for (int i = 0; i < pkt.move_block_size; ++i)
        {
            std::array<float, 3> pos = {
                pkt.DynObjPos[0][i],
                pkt.DynObjPos[1][i],
                pkt.DynObjPos[2][i]
            };

            //클라에서 방향은 의미 없음. 000으로 대체
            std::array<int, 3> dirArr = { 0,0,0 };
            MoveObjects[i].Init(pos, dirArr);
        }
    }
    LeaveCriticalSection(&FrameCS);
}
