#include "stdafx.h"
#include "SocketError.h"
#include "ConnectServer.h"

#include "MeshData.h"
#include "CameraAndLight.h"
#include "GameState.h"

#include "Object.h"
#include "Player.h"

#include "ClientProcess.h"
#include "InitGL.h"

#define BUFSIZE    4096


UINT MyID;

int main(int argc, char** argv)
{
    const char* SERVERIP;
    if (argc < 2)
        SERVERIP = "127.0.0.1";
    else
        SERVERIP = argv[1];

    int retval;

    SOCKET sock = InitSocket(SERVERIP);
	
    RecvInitPlayers(sock, MyID);
    RecvInitWorldStatic(sock);
    RecvInitWorldDynamic(sock);


    InitializeCriticalSection(&FrameCS);
    InitializeCriticalSection(&InputCS);
    CreateThread(NULL, 0, ClientProcess, (LPVOID)&sock, 0, NULL);

    InitGL(argc, argv);

    glutMainLoop();

	DeleteCriticalSection(&FrameCS);
    DeleteCriticalSection(&InputCS);
    CleanupSocket(sock);
}
