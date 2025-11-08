#include "stdafx.h"
#include "SocketError.h"

#include "MeshData.h"
#include "CameraAndLight.h"
#include "GameState.h"

#include "Object.h"
#include "Player.h"

#include "InitGL.h"


// 서버 포트 및 버퍼 크기 정의
#define SERVERPORT 9000
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

    WSADATA wsa;
    retval = WSAStartup(MAKEWORD(2, 2), &wsa);
    if (retval != 0) {
        err_display("WSAStartup()");
    }

    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        err_display("socket()");
        WSACleanup();
    }

    struct sockaddr_in serveraddr;
    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;

    retval = inet_pton(AF_INET, SERVERIP, &serveraddr.sin_addr);
    if (retval <= 0) {
        if (retval == 0)
            printf("[오류] 잘못된 IP 주소 형식입니다: %s\n", SERVERIP);
        else
            err_display("inet_pton()");
        closesocket(sock);
        WSACleanup();
    }

    serveraddr.sin_port = htons(SERVERPORT);

 //   retval = connect(sock, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
 //   if (retval == SOCKET_ERROR) {
 //       err_display("connect()");
 //       closesocket(sock);
 //       WSACleanup();
 //   }
 //   
 //   UINT id = -1;
 //   WORD len = 0;
 //   
 //   retval = recv(sock, (char*)&len, sizeof(WORD), MSG_WAITALL);
 //   if (retval == SOCKET_ERROR || retval == 0) { err_display("recv()"); return -1; }

 //   len = ntohs(len);

 //   retval = recv(sock, (char*)&id, len, MSG_WAITALL);
 //   if (retval == SOCKET_ERROR || retval == 0) { err_display("recv()"); return -1; }
 //   
 //   id = ntohl(id);
 //   
	//MyID = id;
 //   printf("이 클라이언트의 ID는 %d\n\n", id);

    setting(staticObjects, MoveObjects, players);
 
    //srand(time(NULL));
    InitGL(argc, argv);

    glutMainLoop();
    closesocket(sock);
    WSACleanup();
}
