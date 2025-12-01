#include "ServerProcess.h"
#include "SocketError.h"

PktFrameState Fs;
volatile int winnerId = -1;
PlayerInputs pi[MAX_CLIENTS];

bool clientQuitFlags[MAX_CLIENTS] = { false };
bool clientRestartFlags[MAX_CLIENTS] = { false };

void SendWorld(ThreadParam* param)
{
    // 월드의 정보를 패킷에 담아 전송한다.

    PacketParam pkHeader;

    pkHeader.type = PACK_FRAME_STATE;
	// 전송할 패킷의 크기를 계산한다
    
    std::vector<uint8_t> tempData = Fs.Serialize();
	pkHeader.size = tempData.size();

	// 패킷 헤더 전송
    send(param->sock, (char*)&pkHeader, sizeof(PacketParam), 0);
    // 패킷 본문 전송
    std::vector<uint8_t> serializedData = Fs.Serialize();
	send(param->sock, (char*)serializedData.data(), serializedData.size(), 0);
}

bool RecvInputChange(SOCKET sock, uint32_t clientId);


DWORD WINAPI ServerProcess(LPVOID arg)
{
    // ThreadParam으로 변환
    ThreadParam* param = (ThreadParam*)arg;
    
    uint32_t clientId = param->id;
    SOCKET clientSock = param->sock;

    DWORD optval = 1;
    setsockopt(clientSock, IPPROTO_TCP, TCP_NODELAY, (const char*)&optval, sizeof(optval));


  //  if (param->id != 0)
  //  {
		//SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL);
  //  }

    while (1)
    {
        // 매 틱마다 월드 정보를 전송
        SendWorld(param);

        bool br = false;

        // 클라이언트로부터 입력 정보 수신
        clientQuitFlags[clientId] = RecvInputChange(clientSock, clientId);


        if (clientQuitFlags[clientId]) {
            // 종료 메시지를 출력함
            printf("[ServerProcess] Client %d quit.\n", clientId);
            break;
        }

    }

    closesocket(clientSock);
    return 0;
}

bool RecvInputChange(SOCKET sock, uint32_t clientId)
{

    // PacketParam 헤더 수신
    PacketParam header{};
    int retval = recv(sock, reinterpret_cast<char*>(&header), sizeof(header), MSG_WAITALL);
    if (retval <= 0) {
        err_display("recv() - Header");
        return false;
    }

    // 헤더 타입 확인
    if (header.type != PACK_INPUT_COMMAND) {
        printf("[RecvInputChange] Unexpected packet type: %d\n", header.type);
        return false;
    }

    // 헤더에 명시된 크기 확인
    if (header.size != sizeof(PlayerInputs)) {
        printf("[RecvInputChange] Unexpected packet size: %d\n", header.size);
        return false;
    }




    // 입력 데이터 수신
    PlayerInputs input{};
    retval = recv(sock, reinterpret_cast<char*>(&input), sizeof(input), MSG_WAITALL);
    if (retval <= 0) {
        err_display("recv() - Body");
        return false;
    }

	// 승자가 정해졌다면 다른 클라이언트의 입력은 quit, restart만 받는다.  
	// 승자가 정해지지 않았거나, 혹은 승자라면  모든 입력을 읽어들인다.
    if (winnerId != -1 && winnerId != clientId)
    {
        EnterCriticalSection(&players[clientId].pInputCS);
        players[clientId].inputs.quit = input.quit;
		players[clientId].inputs.restart = input.restart;
        LeaveCriticalSection(&players[clientId].pInputCS);
    }
    else {
        // 입력 데이터 처리
        EnterCriticalSection(&players[clientId].pInputCS);
        players[clientId].inputs = input;
        LeaveCriticalSection(&players[clientId].pInputCS);

        // 치트 쓴다면 알려야 한다
        //if (input.jumpCheat)
        //{
        //    std::cout << "Player " << clientId << "using cheat!!!.\n";
        //}
    }

    if (players[clientId].inputs.restart && Fs.gameState == GAME_STATE_FINISHED)
    {

        clientRestartFlags[clientId] = true;
    }

    // 디버그용 출력
    //if (input.playerid != 0) {
    //    printf("[RecvInputChange] Client %d Input Accepted: up=%d, rl=%d, jump=%d, dx=%.2f, dy=%.2f, quit=%d\n",
    //        input.playerid, input.updown, input.rightleft, input.jump,
    //        input.deltax, input.deltay, input.quit);
    //}

    return input.quit;
}