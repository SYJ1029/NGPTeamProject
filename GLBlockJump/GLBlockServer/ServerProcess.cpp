#include "ServerProcess.h"


PktFrameState Fs;
PlayerInputs pi[MAX_CLIENTS];

void SendWorld(ThreadParam* param)
{

    // 월드의 정보를 패킷에 담아 전송한다.

    PacketParam pkHeader;

    pkHeader.type = PACK_FRAME_STATE;
	// 전송할 패킷의 크기를 계산한다
    
    std::vector<uint8_t> tempData = Fs.Serialize();
	pkHeader.size = sizeof(PacketParam) + tempData.size();

	// 패킷 헤더 전송
    send(param->sock, (char*)&pkHeader, sizeof(PacketParam), 0);
    // 패킷 본문 전송
    std::vector<uint8_t> serializedData = Fs.Serialize();
	send(param->sock, (char*)serializedData.data(), serializedData.size(), 0);
}


DWORD WINAPI ServerProcess(LPVOID arg)
{
    // ThreadParam으로 변환
    ThreadParam* param = (ThreadParam*)arg;
    
    uint32_t clientId = param->id;
    SOCKET clientSock = param->sock;


    while (1)
    {
		// 매 틱마다 월드 정보를 전송
        SendWorld(param);
		// 클라이언트로부터 입력 정보 수신
    }

    return 0;
}
