#pragma once


#include "stdafx.h"
#include "SocketError.h"

DWORD WINAPI ClientProcess(LPVOID arg);

void RecvWorld(SOCKET sock);
void SendInputChange(SOCKET sock, const PlayerInputs& input);
