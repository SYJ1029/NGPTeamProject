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
	unsigned int id; // 송수신 쓰레드에서 미리 플레이어의 id를 넘긴다. 서버는 이를 통해 3개의 송신 쓰레드에서 각 클라이언트들을 구분한다
};


// 클라이언트와의 연결을 확인하고, 게임 월드의 초기 정보를 전송하는 함수
int ConnectSocket(SOCKET& listen_sock);

// 플레이어의 초기 위치와 id를 전송하는 함수
void SendInitPlayers(PlayerInitInfo info[MAX_CLIENTS], SOCKET* sock);

// 정적 블록들의 초기 위치를 전송하는 함수
void SendInitWorldStatic(SOCKET* sock);

// 움직이는 블록들의 초기 위치를 전송하는 함수
void SendInitWorldDynamic(SOCKET* sock);


