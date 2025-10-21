#include "stdafx.h"
#include "CameraAndLight.h"

glm::vec3 cameraPos = glm::vec3(5.0f, 5.0f, 5.001f); // 카메라 위치
glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0, 0.0f); // 카메라가 바라보는 지점
glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);           // 카메라의 위쪽 방향
glm::mat4 projection;   // 투영 행렬 저장
glm::vec3 lightPos = glm::vec3(0.0f, 0.0f, 0.0f); // 광원의 초기 위치
