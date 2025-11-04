#pragma once

#include <glm/gtc/matrix_transform.hpp>

struct OBB {
    glm::vec3 center;      // 중심 좌표
    glm::vec3 halfSize;    // 각 축 방향 절반 크기 (width/2, height/2, depth/2)
    glm::vec3 axis[3];     // 로컬 축 (X, Y, Z) ? 회전 포함
};
bool CheckOBBCollision(const OBB& A, const OBB& B);