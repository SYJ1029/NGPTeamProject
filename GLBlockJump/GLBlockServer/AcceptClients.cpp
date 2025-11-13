#include "AcceptClients.h"
#include "ParticleSendRecv.h"

PlayerInitInfo SendInitOnePlayer(SOCKET& sock, int Id);

DWORD WINAPI ProcessServer(LPVOID arg)
{
	return 0;
}


int ConnectSocket(SOCKET& listen_sock)
{
	int retval = -1;
	// 데이터 통신에 사용할 변수
	SOCKET client_param[MAX_CLIENTS];
	struct sockaddr_in clientaddr;
	int addrlen;
	HANDLE hThread[MAX_CLIENTS];

    PlayerInitInfo info[MAX_CLIENTS];

	while (1) {
		// accept()
		addrlen = sizeof(clientaddr);

		// 접속한 클라이언트의 주소를 담을 문자열
		char addr[INET_ADDRSTRLEN];

		for (int i = 0; i < MAX_CLIENTS; i++)
		{
			client_param[i] = accept(listen_sock, (struct sockaddr*)&clientaddr, &addrlen);
			if (client_param[i] == INVALID_SOCKET) {
				err_quit("accept()"); // err_display()에서 err_quit()로 변경, 오류 시 종료
                
			}

			// 접속한 클라이언트 정보 출력
			inet_ntop(AF_INET, &clientaddr.sin_addr, addr, sizeof(addr));
			printf("\n[TCP 서버] 클라이언트 접속: IP 주소=%s, 포트 번호=%d\n\n",
				addr, ntohs(clientaddr.sin_port));


            info[i] = SendInitOnePlayer(client_param[i], i);
		}

        SendInitPlayers(info, client_param);
        SendInitWorldStatic(client_param);
        SendInitWorldDynamic(client_param);
        //return 0;
	
	}
}

PlayerInitInfo SendInitOnePlayer(SOCKET& sock, int Id)
{
    PacketParam header{};
    int retval;

    header.type = PACK_INIT_PLAYERS;
    header.size = players.size() * sizeof(PktInitPlayers);

    int pkType = (int)header.type;
    retval = send(sock, (char*)&pkType, sizeof(int), 0);
    if (retval == SOCKET_ERROR) err_quit("send()");
    retval = send(sock, (char*)&header.size, sizeof(header.size), 0);
    if (retval == SOCKET_ERROR) err_quit("send()");

    PlayerInitInfo info;
    info.playerId = Id;
    for (int i = 0; i < MAX_CLIENTS; ++i)
    {
        glm::vec3 glmPos = players[Id].GetPosVec3();
        info.spawnPos[0] = glmPos.x;
        info.spawnPos[1] = glmPos.y;
        info.spawnPos[2] = glmPos.z;
    }

    return info;
}


void SendInitPlayers(PlayerInitInfo info[MAX_CLIENTS], SOCKET* sock)
{
   
   
    int retval;

    PktInitPlayers pkt;
    pkt.myPlayerId = 0;

    for (int i = 0; i < MAX_CLIENTS; ++i)
    {
        pkt.myPlayerId = i;
        pkt.players[i] = info[i];
    }

    std::vector<uint8_t> buffer;
    buffer = pkt.Serialize();

    for (int i = 0; i < MAX_CLIENTS; ++i) {

        //ID와 주소를 한꺼번에 전송
        retval = send(sock[i], (char*)buffer.data(), buffer.size() * sizeof(uint8_t), 0);

    }
  
}

void SendInitWorldStatic(SOCKET* sock)
{
    PacketParam header{};
    header.type = PACK_INIT_WORLD_STATIC;
    header.size = staticObjects.size();

    

    for (int i = 0; i < MAX_CLIENTS; ++i) {
        int pktype = header.type;
        int retval = send(sock[i], (char*)&pktype, sizeof(int), 0);
        if (retval == SOCKET_ERROR) err_quit("send()");

        size_t hsize = htonl(header.size);
        retval = send(sock[i], (char*)&hsize, sizeof(header.size), 0);
        if (retval == SOCKET_ERROR) err_quit("send()");


        std::vector<float> buffer(header.size * 3);
        for (int j = 0; j < header.size; j++)
        {
            buffer[j * 3] = staticObjects[j].GetPosVec3().x;
            buffer[j * 3 + 1] = staticObjects[j].GetPosVec3().y;
            buffer[j * 3 + 2] = staticObjects[j].GetPosVec3().z;
        }


        
        retval = send_all(sock[i], (char*)buffer.data(), buffer.size() * 4);
        if (retval == SOCKET_ERROR) err_quit("send()");

    
    }
}


void SendInitWorldDynamic(SOCKET* sock)
{
    PacketParam header{};
    header.type = PACK_INIT_WORLD_DYNAMIC;
    header.size = MoveObjects.size();



    for (int i = 0; i < MAX_CLIENTS; ++i) {
        int pktype = header.type;
        int retval = send(sock[i], (char*)&pktype, sizeof(int), 0);
        if (retval == SOCKET_ERROR) err_quit("send()");

        size_t hsize = htonl(header.size);
        retval = send(sock[i], (char*)&hsize, sizeof(header.size), 0);
        if (retval == SOCKET_ERROR) err_quit("send()");


        std::vector<float> buffer(header.size * 3);
        for (int j = 0; j < buffer.size(); j += 3)
        {
            buffer[j] = MoveObjects[j / 3].GetPosVec3().x;
            buffer[j + 1] = MoveObjects[j / 3].GetPosVec3().y;
            buffer[j + 2] = MoveObjects[j / 3].GetPosVec3().z;
        }



        retval = send(sock[i], (char*)buffer.data(), buffer.size() * 4, 0);
        if (retval == SOCKET_ERROR) err_quit("send()");
    }
}


