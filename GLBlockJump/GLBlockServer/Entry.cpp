#include "stdafx.h"
#include "InitWorld.h"

#include "Object.h"
#include "Player.h"



// 소켓 전송 오류 관리
#include "SocketError.h"

#include "ServerMacro.h"

// 연결 관리
#include "AcceptClients.h"
#include "ServerProcess.h"


#include "CollisionManager.h"

bool game_end = true;

// 함수 전방 선언
void ServerMainLoop();
bool WriteFrameState(Game_State& state);

extern std::vector<Object> staticObjects;
extern std::vector<MovingObject> MoveObjects;
extern std::array<Player, MAX_PLAYER> players;



SOCKET CreateListenSocket()
{
	// 소켓 생성함수
	SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_sock == INVALID_SOCKET) err_quit("socket()");

	// bind()
	int retval;

	struct sockaddr_in serveraddr;
	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(SERVERPORT);
	retval = bind(listen_sock, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR) err_quit("bind()");


	// listen()
	if (listen(listen_sock, SOMAXCONN) == SOCKET_ERROR) err_quit("listen()");

	return listen_sock;
}

int main()
{
	// 월드 기본 정보 생성
	InitWorld(staticObjects, MoveObjects, players);

	// 윈속 초기화
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	SOCKET listen_sock = CreateListenSocket();
	SOCKET client_sock[MAX_CLIENTS];


	ConnectSocket(listen_sock, client_sock);
	
	Fs.DynObjPos = new float[count_moving_block][3];
	Game_State semistate = GAME_STATE_RUNNING;

	InitializeCriticalSection(&FrameCS);
	InitializeCriticalSection(&InputCS);
	WriteFrameState(semistate);

	ThreadParam client_param[MAX_CLIENTS];



	for (int i = 0; i < MAX_CLIENTS; ++i)
	{
		client_param[i].id = i;
		client_param[i].sock = client_sock[i];
		CreateThread(NULL, 0, ServerProcess, (LPVOID)&client_param[i], 0, NULL);
	}

	ServerMainLoop();


	// 소켓 닫기
	closesocket(listen_sock);

	DeleteCriticalSection(&FrameCS);
	DeleteCriticalSection(&InputCS);
	// 윈속 종료
	WSACleanup();
}


bool WriteFrameState(Game_State& state)
{
	EnterCriticalSection(&FrameCS);

	Fs.gameState = state;
	for (int i = 0; i < MAX_CLIENTS; ++i)
	{
		Fs.players[i].playerId = i;
		Fs.players[i].position[0] = players[i].GetPosX();
		Fs.players[i].position[1] = players[i].GetPosY();
		Fs.players[i].position[2] = players[i].GetPosZ();

		Fs.players[i].rotation[0] = players[i].GetRotationX();
		Fs.players[i].rotation[1] = players[i].GetRotationY();
		Fs.players[i].rotation[2] = players[i].GetRotationX();
	}

	Fs.move_block_size = count_moving_block;

	for (int i = 0; i < Fs.move_block_size; ++i)
	{
		Fs.DynObjPos[i][0] = MoveObjects[i].GetPosVec3().x;
		Fs.DynObjPos[i][1] = MoveObjects[i].GetPosVec3().y; 
		Fs.DynObjPos[i][2] = MoveObjects[i].GetPosVec3().z;
	}
	

	LeaveCriticalSection(&FrameCS);
	return true;
}

void ServerMainLoop()
{
	Game_State state = GAME_STATE_RUNNING;



	while (1)
	{
		Sleep(1);
		
		for (int i = 0; i < MAX_CLIENTS; ++i)
		{
			players[i].Update();
			ChecKCollisionLoop(players[i]);
		}

		for (int i = 0; i < count_moving_block; ++i)
		{
			MoveObjects[i].Update();
		}

		WriteFrameState(state);


	}
}

