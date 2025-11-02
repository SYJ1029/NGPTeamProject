#include "stdafx.h"
#include "SocketError.h"

#include "MeshData.h"
#include "ShaderUtils.h"
#include "BufferInit.h"
#include "TextureUtils.h"
#include "CameraAndLight.h"
#include "GameState.h"
#include "CallbackFuncs.h"
#include "Render.h"

#include "Object.h"
#include "Player.h"


int window_w = 600;
int window_h = 600;
GLint width, height;


// 서버 포트 및 버퍼 크기 정의
#define SERVERPORT 9000
#define BUFSIZE    512

//const int MAX_PLAYER{ 3 };

//extern std::vector<Object> staticObjects;
//extern std::vector<MovingObject> MoveObjects;

extern std::array<Player, MAX_PLAYER> players;

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

    retval = connect(sock, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
    if (retval == SOCKET_ERROR) {
        err_display("connect()");
        closesocket(sock);
        WSACleanup();
    }

    projection = glm::perspective(glm::radians(45.0f), (float)window_w / window_h, 0.1f, 1000.0f);
    srand(time(NULL));
    setting(staticObjects, MoveObjects, players);
   /* for (int i = 0; i < 10000; i++) {
        for (int j = 0; j < 3; j++) {
            moving_blocks_chng_pos[i][j] = 0;
        }
    }*/
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(window_w, window_h);
    glutCreateWindow("TermProj");
    glewExperimental = GL_TRUE;
    glewInit();
    make_shaderProgram();
    InitTexture();
    InitBuffer();
    init();

    glutMotionFunc(Motion);
    glutPassiveMotionFunc(Motion); // 클릭 없이 이동
    glutKeyboardFunc(Keyboard);
    glutKeyboardUpFunc(KeyboardUp);   // 키 떼짐 처리
    //glutMouseFunc(Mouse);
    //glutSpecialFunc(SpecialInput);

    glutTimerFunc(10, TimerFunction, 1);
    glutReshapeFunc(Reshape);
    glutDisplayFunc(drawScene);

    glutMainLoop();
    closesocket(sock);
    WSACleanup();
}
