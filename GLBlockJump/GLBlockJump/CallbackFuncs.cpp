#include "stdafx.h"
#include "CallbackFuncs.h"
#include "CameraAndLight.h"
#include "GameState.h"
#include "Object.h"
#include "Player.h"


//extern std::vector<Object> staticObjects;
//extern std::vector<MovingObject> MoveObjects;

extern std::array<Player, MAX_PLAYER> players;

void TimerFunction(int value)
{
    extern UINT MyID;
    if (isMotion) {
        players[MyID].inputs.deltax = 0.0f;
        players[MyID].inputs.deltay = 0.0f;
        isMotion = false;
    }

    glutPostRedisplay();
    glutTimerFunc(10, TimerFunction, 1);
}
void Motion(int x, int y)
{
    extern UINT MyID;
    // x�� y�� ��ȭ�� ���
    float deltaX = static_cast<float>(x - before_mouse_x);
    float deltaY = static_cast<float>(y - before_mouse_y);

    EnterCriticalSection(&InputCS);
	players[MyID].inputs.deltax = deltaX;
	players[MyID].inputs.deltay = deltaY;
    LeaveCriticalSection(&InputCS);
    // ���� ���콺 ��ġ�� �����Ͽ� ���� ȣ�⿡�� ��
    before_mouse_x = x;
    before_mouse_y = y;

	if (!isMotion) {
		isMotion = true;
	}
}


void Keyboard(unsigned char key, int x, int y)
{
    extern UINT MyID;
    EnterCriticalSection(&InputCS);

    switch (key) {
    case 'j':
        if (infjump == 1) {
            infjump = 0;
            std::cout << "inf jump disabled.\n";
        }
        else if (infjump == 0) {
            infjump = 1;
            std::cout << "inf jump enabled.\n";
        }
        break;
    case ' ':
		players[MyID].inputs.jump = true;
        break;
    case 'q': // ����
        players[MyID].inputs.quit = true;
        exit(0);
        break;
    case 'w': // ������ �̵�
        if (players[MyID].inputs.updown <= 0)
		players[MyID].inputs.updown += 1;
        break;
    case 's': // �ڷ� �̵�
        if (players[MyID].inputs.updown >= 0)
        players[MyID].inputs.updown -= 1;
        break;
    case 'a': // ���� �̵�
        if (players[MyID].inputs.rightleft >= 0)
		players[MyID].inputs.rightleft -= 1;
        break;
    case 'd': // ������ �̵�
        if (players[MyID].inputs.rightleft <= 0)
        players[MyID].inputs.rightleft += 1;
        break;
    }

    LeaveCriticalSection(&InputCS);
}
void KeyboardUp(unsigned char key, int x, int y)
{
    extern UINT MyID;
    EnterCriticalSection(&InputCS);

    switch (key) {
    case 'w': // ������ �̵�
		if (players[MyID].inputs.updown >= 0)
        players[MyID].inputs.updown -= 1;
        break;
    case 's': // �ڷ� �̵�
        if (players[MyID].inputs.updown <= 0)
        players[MyID].inputs.updown += 1;
        break;
    case 'a': // ���� �̵�
        if (players[MyID].inputs.rightleft <= 0)
        players[MyID].inputs.rightleft += 1;
        break;
    case 'd': // ������ �̵�
        if (players[MyID].inputs.rightleft >= 0)
        players[MyID].inputs.rightleft -= 1;
        break;
    case ' ':
		players[MyID].inputs.jump = false;
		break;
    }
    LeaveCriticalSection(&InputCS);
}

/*
void SpecialInput(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_LEFT:  // �� Ű

        break;
    case GLUT_KEY_RIGHT: // �� Ű

        break;
    case GLUT_KEY_UP:    // �� Ű

        break;
    case GLUT_KEY_DOWN:  // �� Ű

        break;
    }
    glutPostRedisplay();  // �Է� �� �ٽ� �׸���
}

void Mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
    }
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
    }
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
    }
}
*/