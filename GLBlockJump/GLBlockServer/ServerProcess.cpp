#include "ServerProcess.h"


PktFrameState Fs;
PlayerInputs pi[MAX_CLIENTS];

void SendWorld(ThreadParam* param)
{
    // 월드의 정보를 패킷에 담아 전송한다.

    
}

bool RecvInputChange(SOCKET sock, uint32_t clientId);
DWORD WINAPI ServerProcess(LPVOID arg)
{
    // ThreadParam으로 변환
    ThreadParam* param = (ThreadParam*)arg;
    
    uint32_t clientId = param->id;
    SOCKET clientSock = param->sock;


    while (1)
    {
        SendWorld(param);
        bool br = RecvInputChange(clientSock, clientId);
		if (br) break;
    }

    return 0;
}

bool RecvInputChange(SOCKET sock, uint32_t clientId)
{
    PacketType pktType;
    int retval = recv(sock, (char*)&pktType, sizeof(pktType), MSG_WAITALL);
    if (retval <= 0) return false;
    if (pktType != PACK_INPUT_COMMAND) return false;

    size_t bodySize = 0;
    retval = recv(sock, (char*)&bodySize, sizeof(bodySize), MSG_WAITALL);
    if (retval <= 0) return false;
    if (bodySize != sizeof(PlayerInputs)) return false;
    
    PlayerInputs input{};
    retval = recv(sock, (char*)&input, sizeof(PlayerInputs), MSG_WAITALL);
    if (retval <= 0) return false;
    
	bool quit = input.quit;

    EnterCriticalSection(&InputCS);

    players[clientId].inputs = input;

    LeaveCriticalSection(&InputCS);

    // 디버그용
    printf("[RecvInputChange] 클라이언트 %d 입력 수신: up=%d, rl=%d, jump=%d, dx=%.2f, dy=%.2f, quit=%d\n",
        input.playerid, input.updown, input.rightleft, input.jump,
        input.deltax, input.deltay, input.quit);

    return quit;
}