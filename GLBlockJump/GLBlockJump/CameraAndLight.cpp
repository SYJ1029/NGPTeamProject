#include "CameraAndLight.h"
#include "Player.h"

glm::vec3 cameraPos = glm::vec3(5.0f, 5.0f, 5.001f); // 카메라 위치
glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0, 0.0f); // 카메라가 바라보는 지점
glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);           // 카메라의 위쪽 방향
glm::mat4 projection;   // 투영 행렬 저장
glm::vec3 lightPos = glm::vec3(0.0f, 0.0f, 0.0f); // 광원의 초기 위치

void UpdateCamera()
{
    extern UINT MyID;
    // A의 이동 및 회전 변환 계산

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, players[MyID].GetPosVec3());
    model = glm::rotate(model, glm::radians(players[MyID].GetRotationY()), glm::vec3(0.0, -1.0, 0.0));
    model = glm::rotate(model, glm::radians(players[MyID].GetRotationX()), glm::vec3(1.0, 0.0, 0.0));

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