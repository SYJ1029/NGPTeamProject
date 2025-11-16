#pragma once


#define SERVERPORT 9000
#define BUFSIZE    50

// 서버가 받게될 클라이언트의 수를 미리 정의한다
#define MAX_CLIENTS 3

// 스레드에 소켓 뿐만이 아니라 id를 같이 넘겨준다
struct ThreadParam
{
	SOCKET sock;
	unsigned int id; // 송수신 쓰레드에서 미리 플레이어의 id를 넘긴다. 서버는 이를 통해 3개의 송신 쓰레드에서 각 클라이언트들을 구분한다
};