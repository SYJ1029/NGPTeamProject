#include "Object.h"
#include "Player.h"

#include "stdafx.h"
#include "InitWorld.h"


// 소켓 전송 오류 관리
#include "SocketError.h"

#include "ServerMacro.h"

// 연결 관리
#include "AcceptClients.h"


extern std::vector<Object> staticObjects;
extern std::vector<MovingObject> MoveObjects;
extern std::array<Player, MAX_PLAYER> players;



SOCKET CreateListenSocket()
{
	// 소켓 생성함수
	SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_sock == INVALID_SOCKET) err_quit("socket()");

	// bind()
	int retval;

	struct sockaddr_in serveraddr;
	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(SERVERPORT);
	retval = bind(listen_sock, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR) err_quit("bind()");


	// listen()
	if (listen(listen_sock, SOMAXCONN) == SOCKET_ERROR) err_quit("listen()");

	return listen_sock;
}

int main()
{
	// 월드 기본 정보 생성
	setting(staticObjects, MoveObjects, players);

	// 윈속 초기화
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	SOCKET listen_sock = CreateListenSocket();

	ConnectSocket(listen_sock);
	SendInitPlayers(listen_sock);

	// 소켓 닫기
	closesocket(listen_sock);
	// 윈속 종료
	WSACleanup();
}