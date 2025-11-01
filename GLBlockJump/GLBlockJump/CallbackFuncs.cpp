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
    model = glm::translate(model, glm::vec3(char_pos[0], char_pos[1], char_pos[2]));
    model = glm::rotate(model, glm::radians(char_angle[1]), glm::vec3(0.0, -1.0, 0.0));
    model = glm::rotate(model, glm::radians(char_angle[0]), glm::vec3(1.0, 0.0, 0.0));

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


    // char_angle[1] 기준 회전 행렬 계산
    glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(-char_angle[1]), glm::vec3(0.0f, 1.0f, 0.0f));

    // 전방(forward) 및 우측(right) 벡터 계산
    glm::vec3 forward = glm::vec3(0.0f, 0.0f, -1.0f); // 기본 전방 방향
    glm::vec3 right = glm::vec3(1.0f, 0.0f, 0.0f);    // 기본 우측 방향
    forward = glm::normalize(glm::vec3(rotation * glm::vec4(forward, 0.0f))); // 회전된 전방 벡터
    right = glm::normalize(glm::vec3(rotation * glm::vec4(right, 0.0f)));     // 회전된 우측 벡터

    // 이동 거리
    float moveSpeed = 0.1f;

    if (go_v[0]) { // 앞으로 이동
        char_pos[0] -= forward.x * moveSpeed;
        char_pos[2] -= forward.z * moveSpeed;
    }
    if (go_v[1]) {// 뒤로 이동
        char_pos[0] += forward.x * moveSpeed;
        char_pos[2] += forward.z * moveSpeed;
    }
    if (go_v[2]) { // 왼쪽 이동
        char_pos[0] += right.x * moveSpeed;
        char_pos[2] += right.z * moveSpeed;
    }
    if (go_v[3]) { // 오른쪽 이동
        char_pos[0] -= right.x * moveSpeed;
        char_pos[2] -= right.z * moveSpeed;
    }

    y_speed -= GRAVITY;
    jumpable = infjump;

	OBB charOBB;
	charOBB.center = glm::vec3(char_pos[0], char_pos[1], char_pos[2]);
	charOBB.halfSize = glm::vec3(0.5f, 0.5f, 0.5f);
    glm::mat4 rotMat = glm::yawPitchRoll(
        char_angle[1],  // yaw (Y축)
        char_angle[0],  // pitch (X축)
        char_angle[2]   // roll (Z축)
    );
    charOBB.axis[0] = glm::normalize(glm::vec3(rotMat[0])); // X축
    charOBB.axis[1] = glm::normalize(glm::vec3(rotMat[1])); // Y축
    charOBB.axis[2] = glm::normalize(glm::vec3(rotMat[2])); // Z축

    OBB boxOBB;
    boxOBB.halfSize = glm::vec3(0.5f, 0.5f, 0.5f);
	boxOBB.axis[0] = { 1, 0, 0 };
	boxOBB.axis[1] = { 0, 1, 0 };
	boxOBB.axis[2] = { 0, 0, 1 };

    for (int i = 0; i < count_block; i++) {
		boxOBB.center = staticObjects[i].GetPosVec3();
        if (CheckOBBCollision(charOBB, boxOBB)) {
            float blockPos[3]{ staticObjects[i].GetPosVec3().x, staticObjects[i].GetPosVec3().y, staticObjects[i].GetPosVec3().z};
            if ((char_pos[1] + y_speed) < blockPos[1] + 1.0f && char_pos[1] >= blockPos[1]) {
                char_pos[1] = blockPos[1] + 1.0f;
                y_speed = 0;
                jumpable = 1;
            }
            else if ((char_pos[1] + y_speed) > blockPos[1] - 1.0f && char_pos[1] <= blockPos[1]) {
                char_pos[1] = blockPos[1] - 1.0f;
                y_speed = 0;
            }

            if ((!game_end) && ((blockPos[1] >= 50) && (count_block - i <= 25))) {
                std::cout << "Congratulations! You Win! \npress \"q\" to quit the game.\n";
                game_end = true;
            }

            break;
        }
    }
    for (int i = 0; i < count_moving_block; i++) {
        boxOBB.center = MoveObjects[i].GetPosVec3();
        if (CheckOBBCollision(charOBB, boxOBB)) {
            if ((char_pos[1] + y_speed) < MoveObjects[i].GetPosVec3().y + 1.0f && char_pos[1] >= MoveObjects[i].GetPosVec3().y) {
                char_pos[1] = MoveObjects[i].GetPosVec3().y + 1.0f;
                y_speed = 0;
                jumpable = 1;
            }
            else if ((char_pos[1] + y_speed) > MoveObjects[i].GetPosVec3().y - 1.0f && char_pos[1] <= MoveObjects[i].GetPosVec3().y) {
                char_pos[1] = MoveObjects[i].GetPosVec3().y - 1.0f;
                y_speed = 0;
            }

            for (int j = 0; j < 3; j++) {
                char_pos[j] += MoveObjects[i].GetDirVec3()[j] * 0.03f;
            }
            break;
        }
    }

    for (int i = 0; i < count_moving_block; i++) {
   /*     for (int j = 0; j < 3; j++) {
            if (moving_blocks_vec[i][j] != 0) {
                moving_blocks_chng_pos[i][j] += moving_blocks_vec[i][j] * 0.03f;
                moving_blocks_pos[i][j] += moving_blocks_vec[i][j] * 0.03f;

                if (moving_blocks_chng_pos[i][j] >= 5.0f) moving_blocks_vec[i][j] *= -1;
                else if (moving_blocks_chng_pos[i][j] <= -5.0f) moving_blocks_vec[i][j] *= -1;
            }

        }*/
        MoveObjects[i].Update();
    }

    char_pos[1] += y_speed;


    if (char_pos[1] <= -10.0f) {
        char_pos[0] = 0.0f;
        char_pos[1] = 10.0f;
        char_pos[2] = 0.0f;

        y_speed = 0.0f;
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
    char_angle[1] += deltaX * 0.8f; // x 이동량에 비례하여 y축 회전 각도 변경
    char_angle[0] += deltaY * 0.1f; // y 이동량에 비례하여 x축 회전 각도 변경

    // 각도 범위 제한 (360도 이상, -360도 이하로 가지 않도록 처리)
    for (int i = 0; i < 2; i++) {
        if (char_angle[i] > 360.0f) char_angle[i] -= 360.0f;
        if (char_angle[i] < -360.0f) char_angle[i] += 360.0f;
    }

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
        if (jumpable) {
            y_speed = 0.3f;
            char_pos[1] += y_speed;
        }
        break;
    case '\n':
    case '\r':
        char_angle[0] = 0;
        char_angle[1] = 0;
        before_mouse_x = x;
        before_mouse_y = y;
        break;
    case 'q': // 종료
        exit(0);
        break;
    case 'w': // 앞으로 이동
        go_v[0] = 1;
        break;
    case 's': // 뒤로 이동
        go_v[1] = 1;
        break;
    case 'a': // 왼쪽 이동
        go_v[2] = 1;
        break;
    case 'd': // 오른쪽 이동
        go_v[3] = 1;
        break;
    }
}
void KeyboardUp(unsigned char key, int x, int y) {
    switch (key) {
    case 'w': // 앞으로 이동
        go_v[0] = 0;
        break;
    case 's': // 뒤로 이동
        go_v[1] = 0;
        break;
    case 'a': // 왼쪽 이동
        go_v[2] = 0;
        break;
    case 'd': // 오른쪽 이동
        go_v[3] = 0;
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