#include "CollisionManager.h"
#include "InitWorld.h"


float char_pos[3] = { 0.0f, 10.0f, 0.0f };

bool ChecKCollisionLoop(Player& player)
{
    bool isGrounded = false;
    for (int i = 0; i < count_block; i++) {
        if (player.CheckCollision(staticObjects[i])) {
            float blockPos[3]{ staticObjects[i].GetPosVec3().x, staticObjects[i].GetPosVec3().y, staticObjects[i].GetPosVec3().z };
            if ((player.GetPosY() + player.GetMoveSpeedY()) < blockPos[1] + 1.0f && player.GetPosY() >= blockPos[1]) {
                player.SetPosY(blockPos[1] + 1.0f);
                player.SetMoveSpeedY(0);
                isGrounded = true;
            }
            else if ((player.GetPosY() + player.GetMoveSpeedY()) > blockPos[1] - 1.0f && player.GetPosY() <= blockPos[1]) {
                player.SetPosY(blockPos[1] - 1.0f);
                player.SetMoveSpeedY(0);
            }

            if ((!game_end) && ((blockPos[1] >= 50) && (count_block - i <= 25))) {
                std::cout << "Congratulations! You Win! \npress \"q\" to quit the game.\n";
                game_end = true;
            }

            break;
        }
    }
    for (int i = 0; i < count_moving_block; i++) {
        if (player.CheckCollision(MoveObjects[i])) {
            if ((player.GetPosY() + player.GetMoveSpeedY()) < MoveObjects[i].GetPosVec3().y + 1.0f && player.GetPosY() >= MoveObjects[i].GetPosVec3().y) {
                player.SetPosY(MoveObjects[i].GetPosVec3().y + 1.0f);
                player.SetMoveSpeedY(0);
                isGrounded = true;
            }
            else if ((char_pos[1] + player.GetMoveSpeedY()) > MoveObjects[i].GetPosVec3().y - 1.0f && player.GetPosY() <= MoveObjects[i].GetPosVec3().y) {
                char_pos[1] = MoveObjects[i].GetPosVec3().y - 1.0f;
                player.SetMoveSpeedY(0);
            }
            player.SetPosX(player.GetPosX() + MoveObjects[i].GetDirVec3().x * 0.03f);
            player.SetPosY(player.GetPosY() + MoveObjects[i].GetDirVec3().y * 0.03f);
            player.SetPosZ(player.GetPosZ() + MoveObjects[i].GetDirVec3().z * 0.03f);
            break;
        }
    }
    player.isGrounded = isGrounded;
    return false;
}

bool CheckOBBCollision(const OBB& A, const OBB& B)
{
    const float EPSILON = 1e-5f;
    glm::mat3 R, AbsR;

    // 회전 행렬 R[i][j] = A의 i축과 B의 j축 내적
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            R[i][j] = glm::dot(A.axis[i], B.axis[j]);

    // 두 중심 간의 벡터
    glm::vec3 t = B.center - A.center;
    // A의 로컬 좌표계로 변환
    t = glm::vec3(glm::dot(t, A.axis[0]), glm::dot(t, A.axis[1]), glm::dot(t, A.axis[2]));

    // 절댓값 행렬 (부동소수점 오차 보정)
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            AbsR[i][j] = std::fabs(R[i][j]) + EPSILON;

    float ra, rb;

    // (1) A의 세 축
    for (int i = 0; i < 3; i++) {
        ra = A.halfSize[i];
        rb = B.halfSize[0] * AbsR[i][0] + B.halfSize[1] * AbsR[i][1] + B.halfSize[2] * AbsR[i][2];
        if (std::fabs(t[i]) > ra + rb) return false;
    }

    // (2) B의 세 축
    for (int j = 0; j < 3; j++) {
        ra = A.halfSize[0] * AbsR[0][j] + A.halfSize[1] * AbsR[1][j] + A.halfSize[2] * AbsR[2][j];
        rb = B.halfSize[j];
        if (std::fabs(t[0] * R[0][j] + t[1] * R[1][j] + t[2] * R[2][j]) > ra + rb) return false;
    }

    // (3) 축의 외적 9개 (A_i × B_j)
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            ra = A.halfSize[(i + 1) % 3] * AbsR[(i + 2) % 3][j] +
                A.halfSize[(i + 2) % 3] * AbsR[(i + 1) % 3][j];
            rb = B.halfSize[(j + 1) % 3] * AbsR[i][(j + 2) % 3] +
                B.halfSize[(j + 2) % 3] * AbsR[i][(j + 1) % 3];
            float val = std::fabs(t[(i + 2) % 3] * R[(i + 1) % 3][j] -
                t[(i + 1) % 3] * R[(i + 2) % 3][j]);
            if (val > ra + rb) return false;
        }
    }

    return true; // 분리축이 없으면 충돌
}


