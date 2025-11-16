#include "ServerProcess.h"


PktFrameState Fs;
PlayerInputs pi[MAX_CLIENTS];

void SendWorld(ThreadParam* param)
{
    // 월드의 정보를 패킷에 담아 전송한다.

    
}


DWORD WINAPI ServerProcess(LPVOID arg)
{
    // ThreadParam으로 변환
    ThreadParam* param = (ThreadParam*)arg;
    
    uint32_t clientId = param->id;
    SOCKET clientSock = param->sock;


    while (1)
    {
        SendWorld(param);
    }

    return 0;
}
