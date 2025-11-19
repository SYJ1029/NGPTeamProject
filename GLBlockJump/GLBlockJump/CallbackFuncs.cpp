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
    for (int P = 0; P < MAX_PLAYER; P++) {

        glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(-players[P].GetRotationY()), glm::vec3(0.0f, 1.0f, 0.0f));
        //players[P].Update();


        //bool isGrounded = false;
        //for (int i = 0; i < count_block; i++) {
        //    if (players[P].CheckCollision(staticObjects[i])) {
        //        float blockPos[3]{ staticObjects[i].GetPosVec3().x, staticObjects[i].GetPosVec3().y, staticObjects[i].GetPosVec3().z };
        //        if ((players[P].GetPosY() + players[P].GetMoveSpeedY()) < blockPos[1] + 1.0f && players[P].GetPosY() >= blockPos[1]) {
        //            players[P].SetPosY(blockPos[1] + 1.0f);
        //            players[P].SetMoveSpeedY(0);
        //            isGrounded = true;
        //        }
        //        else if ((players[P].GetPosY() + players[P].GetMoveSpeedY()) > blockPos[1] - 1.0f && players[P].GetPosY() <= blockPos[1]) {
        //            players[P].SetPosY(blockPos[1] - 1.0f);
        //            players[P].SetMoveSpeedY(0);
        //        }

        //        if ((!game_end) && ((blockPos[1] >= 50) && (count_block - i <= 25))) {
        //            std::cout << "Congratulations! You Win! \npress \"q\" to quit the game.\n";
        //            game_end = true;
        //        }

        //        break;
        //    }
        //}
        //for (int i = 0; i < count_moving_block; i++) {
        //    if (players[P].CheckCollision(MoveObjects[i])) {
        //        if ((players[P].GetPosY() + players[P].GetMoveSpeedY()) < MoveObjects[i].GetPosVec3().y + 1.0f && players[P].GetPosY() >= MoveObjects[i].GetPosVec3().y) {
        //            players[P].SetPosY(MoveObjects[i].GetPosVec3().y + 1.0f);
        //            players[P].SetMoveSpeedY(0);
        //            isGrounded = true;
        //        }
        //        else if ((char_pos[1] + players[P].GetMoveSpeedY()) > MoveObjects[i].GetPosVec3().y - 1.0f && players[P].GetPosY() <= MoveObjects[i].GetPosVec3().y) {
        //            char_pos[1] = MoveObjects[i].GetPosVec3().y - 1.0f;
        //            players[P].SetMoveSpeedY(0);
        //        }
        //        players[P].SetPosX(players[P].GetPosX() + MoveObjects[i].GetDirVec3().x * 0.03f);
        //        players[P].SetPosY(players[P].GetPosY() + MoveObjects[i].GetDirVec3().y * 0.03f);
        //        players[P].SetPosZ(players[P].GetPosZ() + MoveObjects[i].GetDirVec3().z * 0.03f);
        //        break;
        //    }
        //}
        //players[P].isGrounded = isGrounded;

        //for (int i = 0; i < count_moving_block; i++) {
        //    MoveObjects[i].Update();
        //}
    }

    /*
	using namespace std;
    cout << "-----------------------------------------------------------\n";
    cout << "Player " << MyID << " Inputs - UpDown: " << players[MyID].inputs.updown
        << "\n RightLeft: " << players[MyID].inputs.rightleft
        << "\n Jump: " << (players[MyID].inputs.jump ? "True" : "False")
        << "\n deltax: " << players[MyID].inputs.deltax
        << "\n deltay: " << players[MyID].inputs.deltay << '\n';
    */

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