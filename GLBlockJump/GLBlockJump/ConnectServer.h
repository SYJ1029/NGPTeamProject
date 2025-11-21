#pragma once

#include "stdafx.h"
#include "SocketError.h"


#include "Object.h"
#include "Player.h"


#define SERVERPORT 9000

SOCKET InitSocket(const char* ip);
void CleanupSocket(SOCKET sock);

void RecvInitPlayers(SOCKET sock, UINT &MyID);
void RecvInitWorldStatic(SOCKET sock);
void RecvInitWorldDynamic(SOCKET sock);


