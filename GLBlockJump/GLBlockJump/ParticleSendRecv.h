#pragma once

#include "stdafx.h"


int send_all(SOCKET sock, const void* buf, size_t len) {
    const char* p = reinterpret_cast<const char*>(buf);
    size_t sent = 0;
    size_t n;
    while (sent < len) {
        n = send(sock, p + sent, len - sent, 0);
        if (n == SOCKET_ERROR)
            return n;
        if (n > 0) {
            sent += (size_t)n;
            continue;
        }
    }
    return n;
}

// recv_all: 정확히 len 바이트를 채울 때까지 반복
// 성공 시 0, EOF(조기 종료) 시 -2, 에러 시 -1
int recv_all(SOCKET sock, void* buf, size_t len) {
    char* p = reinterpret_cast<char*>(buf);
    size_t recvd = 0;
    size_t n;
    while (recvd < len) {
        n = recv(sock, p + recvd, len - recvd, 0);
        if (n == SOCKET_ERROR)
            return n;
        if (n > 0) {
            recvd += (size_t)n;
            continue;
        }

    }
    return n;
}