#pragma once

#include "stdafx.h"
#include "SocketError.h"

#include "ServerMacro.h"
#include "Object.h"
#include "Player.h"





// 클라이언트와의 연결을 확인하고, 게임 월드의 초기 정보를 전송하는 함수
int ConnectSocket(SOCKET& listen_sock, SOCKET* connect_sock);

// 플레이어의 초기 위치와 id를 전송하는 함수
void SendInitPlayers(SOCKET* sock);

// 정적 블록들의 초기 위치를 전송하는 함수
void SendInitWorldStatic(SOCKET* sock);

// 움직이는 블록들의 초기 위치를 전송하는 함수
void SendInitWorldDynamic(SOCKET* sock);


