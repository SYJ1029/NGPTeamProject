#include "stdafx.h"
#include "SocketError.h"
#include "ConnectServer.h"

#include "MeshData.h"
#include "CameraAndLight.h"
#include "GameState.h"

#include "Object.h"
#include "Player.h"

#include "InitGL.h"

#define BUFSIZE    512

//const int MAX_PLAYER{ 3 };

//extern std::vector<Object> staticObjects;
//extern std::vector<MovingObject> MoveObjects;
//extern std::array<Player, MAX_PLAYER> players;
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

    UINT id = 0;
    WORD len = 0;
    
    /*
	// [테스트용] 서버로부터 이 클라이언트의 ID만 받음
    retval = recv(sock, (char*)&len, sizeof(WORD), MSG_WAITALL);
    if (retval == SOCKET_ERROR || retval == 0) { err_display("recv()"); return -1; }

    len = ntohs(len);

    retval = recv(sock, (char*)&id, len, MSG_WAITALL);
    if (retval == SOCKET_ERROR || retval == 0) { err_display("recv()"); return -1; }
    
    id = ntohl(id);
    */

	MyID = id;
    printf("이 클라이언트의 ID는 %d\n\n", MyID);

    /*
    int len;
    char buf[BUFSIZE];

    
    while (1) {
        retval = recv(sock, (char*)&len, sizeof(int), MSG_WAITALL);
        if (retval <= 0 || len == 0)
            break;

        retval = recv(sock, buf, len, MSG_WAITALL);
        if (retval <= 0)
            break;
    }
    */
	
    //RecvInitPlayers(sock, MyID);
    //RecvInitWorldStatic(sock);
    //RecvInitWorldDynamic(sock);
    setting(staticObjects, MoveObjects, players);
 
    //srand(time(NULL));
    InitGL(argc, argv);

    glutMainLoop();
    CleanupSocket(sock);
}
