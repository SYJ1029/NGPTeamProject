#include "ClientProcess.h"
#include "ConnectServer.h"
#include "Object.h"
#include "Player.h"


DWORD WINAPI ClientProcess(LPVOID arg)
{
    extern UINT MyID;
	//월드 정보를 수신, 입력 정보를 송신
    SOCKET param = (SOCKET)arg;

    while (1)
    {
        RecvWorld(param);
        SendInputChange(param, players[MyID].inputs);
    }

	return 0;
}