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
    // A의 이동 및 회전 변환 계산
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, players[0].GetPosVec3());
    model = glm::rotate(model, glm::radians(players[0].GetRotationY()), glm::vec3(0.0, -1.0, 0.0));
    model = glm::rotate(model, glm::radians(players[0].GetRotationX()), glm::vec3(1.0, 0.0, 0.0));

    // 초기 점 (A에서 z+1 위치)
    glm::vec4 initialPoint = glm::vec4(0.0f, 3.0f, -5.0f, 1.0f);

    // 변환된 좌표 계산
    glm::vec4 transformedPoint = model * initialPoint;

    // cameraPos 업데이트
    cameraPos.x = transformedPoint.x;
    cameraPos.y = transformedPoint.y;
    cameraPos.z = transformedPoint.z;

    // A 기준 반대편 점 계산 (기준점에서 반대 방향으로 이동)
    glm::vec4 targetPoint = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

    // 변환된 좌표 계산
    glm::vec4 rotatedTarget = model * targetPoint;

    // cameraTarget 업데이트
    cameraTarget.x = rotatedTarget.x;
    cameraTarget.y = rotatedTarget.y;
    cameraTarget.z = rotatedTarget.z;

    for (int P = 0; P < MAX_PLAYER; P++) {

        glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(-players[P].GetRotationY()), glm::vec3(0.0f, 1.0f, 0.0f));
        players[P].Update();


        bool isGrounded = false;
        for (int i = 0; i < count_block; i++) {
            if (players[P].CheckCollision(staticObjects[i])) {
                float blockPos[3]{ staticObjects[i].GetPosVec3().x, staticObjects[i].GetPosVec3().y, staticObjects[i].GetPosVec3().z };
                if ((players[P].GetPosY() + players[P].GetMoveSpeedY()) < blockPos[1] + 1.0f && players[P].GetPosY() >= blockPos[1]) {
                    players[P].SetPosY(blockPos[1] + 1.0f);
                    players[P].SetMoveSpeedY(0);
                    isGrounded = true;
                }
                else if ((players[P].GetPosY() + players[P].GetMoveSpeedY()) > blockPos[1] - 1.0f && players[P].GetPosY() <= blockPos[1]) {
                    players[P].SetPosY(blockPos[1] - 1.0f);
                    players[P].SetMoveSpeedY(0);
                }

                if ((!game_end) && ((blockPos[1] >= 50) && (count_block - i <= 25))) {
                    std::cout << "Congratulations! You Win! \npress \"q\" to quit the game.\n";
                    game_end = true;
                }

                break;
            }
        }
        for (int i = 0; i < count_moving_block; i++) {
            if (players[P].CheckCollision(MoveObjects[i])) {
                if ((players[P].GetPosY() + players[P].GetMoveSpeedY()) < MoveObjects[i].GetPosVec3().y + 1.0f && players[P].GetPosY() >= MoveObjects[i].GetPosVec3().y) {
                    players[P].SetPosY(MoveObjects[i].GetPosVec3().y + 1.0f);
                    players[P].SetMoveSpeedY(0);
                    isGrounded = true;
                }
                else if ((char_pos[1] + players[P].GetMoveSpeedY()) > MoveObjects[i].GetPosVec3().y - 1.0f && players[P].GetPosY() <= MoveObjects[i].GetPosVec3().y) {
                    char_pos[1] = MoveObjects[i].GetPosVec3().y - 1.0f;
                    players[P].SetMoveSpeedY(0);
                }
                players[P].SetPosX(players[P].GetPosX() + MoveObjects[i].GetDirVec3().x * 0.03f);
                players[P].SetPosY(players[P].GetPosY() + MoveObjects[i].GetDirVec3().y * 0.03f);
                players[P].SetPosZ(players[P].GetPosZ() + MoveObjects[i].GetDirVec3().z * 0.03f);
                break;
            }
        }
        players[P].isGrounded = isGrounded;

        for (int i = 0; i < count_moving_block; i++) {
            MoveObjects[i].Update();
        }
    }

    glutPostRedisplay();
    glutTimerFunc(10, TimerFunction, 1);
}
void Motion(int x, int y)
{
    // x와 y의 변화량 계산
    float deltaX = static_cast<float>(x - before_mouse_x);
    float deltaY = static_cast<float>(y - before_mouse_y);

    // 변화량을 char_angle에 반영
	players[0].SetRotationY(players[0].GetRotationY() + deltaX * 0.8f);
	players[0].SetRotationX(players[0].GetRotationX() + deltaY * 0.1f);

    // 각도 범위 제한 (360도 이상, -360도 이하로 가지 않도록 처리)
	if (players[0].GetRotationX() > 360.0f) players[0].SetRotationX(players[0].GetRotationX() - 360.0f);
	if (players[0].GetRotationX() < -360.0f) players[0].SetRotationX(players[0].GetRotationX() + 360.0f);
	if (players[0].GetRotationY() > 360.0f) players[0].SetRotationY(360.0f);
	if (players[0].GetRotationY() < -360.0f) players[0].SetRotationY(-360.0f);

    // 현재 마우스 위치를 저장하여 다음 호출에서 비교
    before_mouse_x = x;
    before_mouse_y = y;
}


void Keyboard(unsigned char key, int x, int y)
{
    // 키 입력 처리
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
		players[0].inputs.jump = true;
        break;
    case 'q': // 종료
        exit(0);
        break;
    case 'w': // 앞으로 이동
        if (players[0].inputs.updown <= 0)
		players[0].inputs.updown += 1;
        break;
    case 's': // 뒤로 이동
        if (players[0].inputs.updown >= 0)
        players[0].inputs.updown -= 1;
        break;
    case 'a': // 왼쪽 이동
        if (players[0].inputs.rightleft >= 0)
		players[0].inputs.rightleft -= 1;
        break;
    case 'd': // 오른쪽 이동
        if (players[0].inputs.rightleft <= 0)
        players[0].inputs.rightleft += 1;
        break;
    }
}
void KeyboardUp(unsigned char key, int x, int y) {
    switch (key) {
    case 'w': // 앞으로 이동
		if (players[0].inputs.updown >= 0)
        players[0].inputs.updown -= 1;
        break;
    case 's': // 뒤로 이동
        if (players[0].inputs.updown <= 0)
        players[0].inputs.updown += 1;
        break;
    case 'a': // 왼쪽 이동
        if (players[0].inputs.rightleft <= 0)
        players[0].inputs.rightleft += 1;
        break;
    case 'd': // 오른쪽 이동
        if (players[0].inputs.rightleft >= 0)
        players[0].inputs.rightleft -= 1;
        break;
    case ' ':
		players[0].inputs.jump = false;
		break;
    }
}

/*
void SpecialInput(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_LEFT:  // ← 키

        break;
    case GLUT_KEY_RIGHT: // → 키

        break;
    case GLUT_KEY_UP:    // ↑ 키

        break;
    case GLUT_KEY_DOWN:  // ↓ 키

        break;
    }
    glutPostRedisplay();  // 입력 후 다시 그리기
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