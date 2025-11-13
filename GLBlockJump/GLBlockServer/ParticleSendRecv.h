#pragma once

#include "stdafx.h"
#include "SocketError.h"

#include "ServerMacro.h"



int send_all(int sock, const void* buf, size_t len) {
    const char* p = reinterpret_cast<const char*>(buf);
    size_t sent = 0;
    while (sent < len) {
        size_t n = send(sock, p + sent, len - sent, 0);
        if (n == SOCKET_ERROR)
            err_quit("recv()");
        if (n > 0) {
            sent += (size_t)n;
            continue;
        }
    }
    return 0;
}

// recv_all: 정확히 len 바이트를 채울 때까지 반복
// 성공 시 0, EOF(조기 종료) 시 -2, 에러 시 -1
int recv_all(int sock, void* buf, size_t len) {
    char* p = reinterpret_cast<char*>(buf);
    size_t recvd = 0;
    while (recvd < len) {
        size_t n = recv(sock, p + recvd, len - recvd, 0);
        if (n == SOCKET_ERROR)
            err_quit("recv()");
        if (n > 0) {
            recvd += (size_t)n;
            continue;
        }

    }
    return 0;
}