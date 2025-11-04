#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS

// C, C++ 관련 라이브러리
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

// C++ STL 자료구조 라이브러리
#include <vector>
#include <array>

// OpenGL 관련 라이브러리
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/freeglut_ext.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>


// 문자열, 시간, 수학, 텍스쳐
#include <time.h>
#include <cmath>
#include <string>
// 윈도우 소켓 관련
#include <WinSock2.h>
#include <WS2tcpip.h>

// 소켓 구조체 관련
#include "PacketStruct.h"

// 게임 진행 상태 Enums
#include "StateEnums.h"

// 고정된 초기 값들에 대한 매크로 모음
#include "StateMacro.h"

//서버용 충돌 관리
#include "CollisionManager.h"

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "freeglut.lib")
#pragma comment(lib, "glew32.lib")