#pragma once

#include "winsock.h"

struct ThreadParam
{
    SOCKET sock;
    unsigned int id; // 송수신 쓰레드에서 미리 플레이어의 id를 넘긴다. 서버는 이를 통해 3개의 송신 쓰레드에서 각 클라이언트들을 구분한다
};
