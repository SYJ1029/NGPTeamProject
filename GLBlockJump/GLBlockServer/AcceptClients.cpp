#include "AcceptClients.h"


DWORD WINAPI ProcessServer(LPVOID arg)
{
	return 0;
}


int ConnectSocket(SOCKET& listen_sock)
{
	int retval = 0;
	// 데이터 통신에 사용할 변수
	ThreadParam client_param[MAX_CLIENTS];
	struct sockaddr_in clientaddr;
	int addrlen;
	HANDLE hThread[MAX_CLIENTS];

	while (1) {
		// accept()
		addrlen = sizeof(clientaddr);

		// 접속한 클라이언트의 주소를 담을 문자열
		char addr[INET_ADDRSTRLEN];

		for (int i = 0; i < MAX_CLIENTS; i++)
		{
			client_param[i].sock = accept(listen_sock, (struct sockaddr*)&clientaddr, &addrlen);
			if (client_param[i].sock == INVALID_SOCKET) {
				err_quit("accept()"); // err_display()에서 err_quit()로 변경, 오류 시 종료
			}

			// 접속한 클라이언트 정보 출력
			inet_ntop(AF_INET, &clientaddr.sin_addr, addr, sizeof(addr));
			printf("\n[TCP 서버] 클라이언트 접속: IP 주소=%s, 포트 번호=%d\n\n",
				addr, ntohs(clientaddr.sin_port));

			// id 설정
			client_param[i].id = i;
		}

		for (int i = 0; i < MAX_CLIENTS; i++) {
			// 쓰레드 생성 없이 전송(게임 시작 이전에 쓰레드를 만들면서 할 필요가 없음)

			WORD len = htons(sizeof(UINT));
			retval = send(client_param[i].sock, (char*)(&len), sizeof(WORD), 0);
			if (retval == SOCKET_ERROR) { err_quit("send()"); }

			std::cout << "길이 보냈음 " << std::endl;

			UINT nid = htonl(client_param[i].id);
			retval = send(client_param[i].sock, (char*)&nid, sizeof(UINT), 0);
			if (retval == SOCKET_ERROR) { err_quit("send()"); }

			std::cout << "ID 보냈음 " << std::endl;

			
		}
	}
}


void SendInitPlayers(SOCKET sock, UINT& MyID)
{
    PacketParam header{};
    int retval;

    header.type = PACK_INIT_PLAYERS;
    header.size = players.size() * sizeof(Player);
    for (int i = 0; i < 3; ++i) {
        retval = send(sock, (char*)&header, sizeof(header), MSG_WAITALL);
        if (retval <= 0) return;
    }


    PlayerInitInfo info[3];
    for (int i = 0; i < MAX_CLIENTS; ++i)
    {
        info[i].playerId = i;
        glm::vec3 glmPos = players[i].GetPosVec3();
        info[i].spawnPos[0] = glmPos.x;
        info[i].spawnPos[1] = glmPos.y;
        info[i].spawnPos[2] = glmPos.z;
    }
    PktInitPlayers* pkt = {};
    pkt->myPlayerId = 0;

    for (int i = 0; i < MAX_CLIENTS; ++i)
    {
        pkt->myPlayerId = i;
        pkt->players[i] = info[i];

        retval = send(sock, (char*)pkt->myPlayerId, sizeof(int), MSG_WAITALL);
        retval = send(sock, (char*)pkt->players->spawnPos, 3 * sizeof(float), MSG_WAITALL);


    }


    std::vector<char> buffer(header.size);

    
    retval = send(sock, buffer.data(), header.size, MSG_WAITALL);
    if (retval <= 0) return;



  
}

void SendInitWorldStatic(SOCKET sock)
{
    PacketParam header{};
    int retval = recv(sock, (char*)&header, sizeof(header), MSG_WAITALL);
    if (retval <= 0) return;

    if (header.type != PACK_INIT_WORLD_STATIC)
        return;

    int bodySize = header.size - sizeof(PacketParam);
    if (bodySize <= 0) return;

    std::vector<float> buffer(bodySize / sizeof(float));
    retval = recv(sock, (char*)buffer.data(), bodySize, MSG_WAITALL);
    if (retval <= 0) return;

    int objectCount = bodySize / (sizeof(float) * 3);
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

}
void SendInitWorldDynamic(SOCKET sock)
{
    PacketParam header{};
    int retval = recv(sock, (char*)&header, sizeof(header), MSG_WAITALL);
    if (retval <= 0) return;

    if (header.type != PACK_INIT_WORLD_DYNAMIC)
        return;

    int bodySize = header.size - sizeof(PacketParam);
    if (bodySize <= 0) return;

    std::vector<float> buffer(bodySize / sizeof(float));
    retval = recv(sock, (char*)buffer.data(), bodySize, MSG_WAITALL);
    if (retval <= 0) return;

    int objectCount = bodySize / (sizeof(float) * 3);
    MoveObjects.resize(objectCount);

    for (int i = 0; i < objectCount; ++i)
    {
        std::array<float, 3> pos = {
            buffer[i * 3 + 0],
            buffer[i * 3 + 1],
            buffer[i * 3 + 2]
        };
        std::array<int, 3> dir = { 0,0,0 }; // 기본 방향값 (클라에서는 사용 X)
        MoveObjects[i].Init(pos, dir);
    }
}


