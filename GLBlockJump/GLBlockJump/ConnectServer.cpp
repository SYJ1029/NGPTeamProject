#include "ConnectServer.h"

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