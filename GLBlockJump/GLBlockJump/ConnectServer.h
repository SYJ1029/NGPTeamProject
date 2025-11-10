#pragma once

#include "stdafx.h"
#include "SocketError.h"

#define SERVERPORT 9000

SOCKET InitSocket(const char* ip);
void CleanupSocket(SOCKET sock);