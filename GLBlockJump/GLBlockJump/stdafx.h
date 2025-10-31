#define _CRT_SECURE_NO_WARNINGS

// C, C++ ���� ���̺귯��
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

// C++ STL �ڷᱸ�� ���̺귯��
#include <vector>
#include <array>

// OpenGL ���� ���̺귯��
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/freeglut_ext.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>


// ���ڿ�, �ð�, ����, �ؽ���
#include <time.h>
#include <cmath>
#include <string>
#include "stb_image.h"

// ������ ���� ����
#include <WinSock2.h>
#include <WS2tcpip.h>

// ���� ����ü ����
#include "PacketStruct.h"

// ���� ���� ���� Enums
#include "StateEnums.h"

#define GRAVITY 0.01f

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "freeglut.lib")
#pragma comment(lib, "glew32.lib")