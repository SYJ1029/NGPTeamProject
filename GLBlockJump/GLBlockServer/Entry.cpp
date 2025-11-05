#include "stdafx.h"

// 家南 傈价 坷幅 包府
#include "SocketError.h"

#include "ServerMacro.h"



SOCKET CreateListenSocket()
{
	// 家南 积己窃荐
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
	// 扩加 檬扁拳
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	SOCKET listen_sock = CreateListenSocket();


	// 家南 摧扁
	closesocket(listen_sock);
	// 扩加 辆丰
	WSACleanup();
}