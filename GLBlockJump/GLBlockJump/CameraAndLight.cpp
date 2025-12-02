#include "CameraAndLight.h"
#include "Player.h"
#include <chrono>

glm::vec3 cameraPos = glm::vec3(5.0f, 5.0f, 5.001f); // 카메라 위치
glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0, 0.0f); // 카메라가 바라보는 지점
glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);           // 카메라의 위쪽 방향
glm::mat4 projection;   // 투영 행렬 저장
glm::vec3 lightPos = glm::vec3(0.0f, 0.0f, 0.0f); // 광원의 초기 위치

bool isLerping;
bool hasLerped;
static float transitionRatio = 0.0f;
static float transitionDuration = 4.0f;
std::chrono::system_clock::time_point prevTime;

glm::vec3 startCameraPos;
glm::vec3 startCameraTarget;

void UpdateCamera()
{
    extern UINT MyID;
    // A의 이동 및 회전 변환 계산

    UINT ID = MyID;

    if (winnerID != -1)
    {
		ID = winnerID;
        if (!hasLerped && MyID != winnerID)
        {
            isLerping = true;
            hasLerped = true;

            transitionRatio = 0.0f;
            prevTime = std::chrono::system_clock::now();

            startCameraPos = cameraPos;
            startCameraTarget = cameraTarget;
        }
    }


    if (isLerping)
    {
        auto currentTime = std::chrono::system_clock::now();
        std::chrono::duration<float> delta = currentTime - prevTime;
        prevTime = currentTime;

        float deltaTime = delta.count();
        transitionRatio += deltaTime / transitionDuration;

        if (transitionRatio >= 1.0f)
        {
            transitionRatio = 1.0f;
            isLerping = false;
        }

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, players[winnerID].GetPosVec3());
        model = glm::rotate(model, glm::radians(players[winnerID].GetRotationY()), glm::vec3(0.0, -1.0, 0.0));
        model = glm::rotate(model, glm::radians(players[winnerID].GetRotationX()), glm::vec3(1.0, 0.0, 0.0));

        glm::vec4 initialPoint = glm::vec4(0.0f, 3.0f, -5.0f, 1.0f);
        glm::vec4 targetPoint = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

        glm::vec3 currentWinnerCamPos = glm::vec3(model * initialPoint);
        glm::vec3 currentWinnerCamTarget = glm::vec3(model * targetPoint);

        cameraPos = glm::mix(startCameraPos, currentWinnerCamPos, transitionRatio);
        cameraTarget = glm::mix(startCameraTarget, currentWinnerCamTarget, transitionRatio);

        return;
    }

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, players[ID].GetPosVec3());
    model = glm::rotate(model, glm::radians(players[ID].GetRotationY()), glm::vec3(0.0, -1.0, 0.0));
    model = glm::rotate(model, glm::radians(players[ID].GetRotationX()), glm::vec3(1.0, 0.0, 0.0));

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
}