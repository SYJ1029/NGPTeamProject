#pragma once

#include "stdafx.h"
#include "SocketError.h"

#include "ServerMacro.h"

#include "Object.h"
#include "player.h"

// 스레드에 소켓 뿐만이 아니라 id를 같이 넘겨준다
struct ThreadParam
{
	SOCKET sock;
	unsigned int id; // id는 곧 자기가 접근할 spArray의 인덱스
};

int ConnectSocket(SOCKET& listen_sock);

void SendInitPlayers(PlayerInitInfo info[MAX_CLIENTS], SOCKET* sock);
void SendInitWorldStatic(SOCKET sock);
void SendInitWorldDynamic(SOCKET sock);

DWORD WINAPI ProcessServer(LPVOID arg);

