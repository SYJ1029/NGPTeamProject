#include "stdafx.h"
#include "CameraAndLight.h"

glm::vec3 cameraPos = glm::vec3(5.0f, 5.0f, 5.001f); // ī�޶� ��ġ
glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0, 0.0f); // ī�޶� �ٶ󺸴� ����
glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);           // ī�޶��� ���� ����
glm::mat4 projection;   // ���� ��� ����
glm::vec3 lightPos = glm::vec3(0.0f, 0.0f, 0.0f); // ������ �ʱ� ��ġ
