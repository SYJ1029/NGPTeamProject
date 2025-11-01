#include "GameState.h"
#include "Object.h"
#include "Player.h"

float char_angle[3] = { 0.0f, 0.0f, 0.0f };
float char_pos[3] = { 0.0f, 10.0f, 0.0f };

int go_v[4] = { 0,0,0,0 };
int count_block = 1;

int count_moving_block = 1;
//float blocks_pos[10000][3];
float moving_blocks_pos[10000][3];
float moving_blocks_chng_pos[10000][3];
int moving_blocks_vec[10000][3];

float y_speed = 0.0f;
bool jumpable;
bool infjump = false;
bool game_end = false ;

int before_mouse_x = 300;
int before_mouse_y = 300;

bool checkCollision(float ax, float ay, float az, float bx, float by, float bz) {
    // 정육면체의 상대적 경계값
    float min_x = -0.5f, max_x = 0.5f;
    float min_y = -0.5f, max_y = 0.5f;
    float min_z = -0.5f, max_z = 0.5f;

    // A의 이동 후 경계
    float a_min_x = ax + min_x;
    float a_max_x = ax + max_x;
    float a_min_y = ay + min_y;
    float a_max_y = ay + max_y;
    float a_min_z = az + min_z;
    float a_max_z = az + max_z;

    // B의 이동 후 경계
    float b_min_x = bx + min_x;
    float b_max_x = bx + max_x;
    float b_min_y = by + min_y;
    float b_max_y = by + max_y;
    float b_min_z = bz + min_z;
    float b_max_z = bz + max_z;

    // 충돌 판정 (AABB 충돌 검사)
    bool x_overlap = (a_min_x <= b_max_x) && (a_max_x >= b_min_x);
    bool y_overlap = (a_min_y <= b_max_y) && (a_max_y >= b_min_y);
    bool z_overlap = (a_min_z <= b_max_z) && (a_max_z >= b_min_z);

    return x_overlap && y_overlap && z_overlap;
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


void input_block_pos(Object& obj, int i, float x, float y, float z) {
    float newPos[3]{ x, y, z };

    obj.Init(newPos);
}
void input_moving_block_pos(MovingObject& move_obj, int i, float x, float y, float z, int vx, int vy, int vz) {
    float newPos[3]{ x, y, z };
    int newDir[3]{ vx, vy,vz };

    move_obj.SetPosVec3(newPos);
    move_obj.SetDirVec3(newDir);
}

void place_platform(std::vector<Object>& staticObj, int& curr, const glm::vec3& v, int dx, int dy, int dz) {

    for (int y = 0; y < dy; ++y) {
        for (int x = 0; x < dx; ++x) {
            for (int z = 0; z < dz; ++z) {
                input_block_pos(staticObj[curr], curr++, v.x + (float)x, v.y + (float)y, v.z + (float)z);
                //std::cout << "block #" << curr << " (" << v.x + (float)x << ", " << v.y + (float)y << ", " << v.z + (float)z << ")\n";
            }
        }
    }
}

void setting(std::vector<Object>& staticObj, std::vector<MovingObject>& dynamicObj, std::array<Player, MAX_PLAYER>& players)
{
    int curr_block_count{};
    int curr_moving_count{};

    staticObj.resize(200);
	dynamicObj.resize(50);

    place_platform(staticObj, curr_block_count, glm::vec3{0.0f, 0.0f, 0.0f}, 5, 1, 5);

    for (int i = 0; i < 6; ++i) {
        place_platform(staticObj, curr_block_count, glm::vec3{ 7.0f + float(i * 6), float(i), 1.0f }, 3, 1, 3);
    }

    place_platform(staticObj, curr_block_count, glm::vec3{ 45.0f, 5.0f, 0.0f }, 5, 1, 5);

    for (int i = 0; i < 6; ++i) {
        place_platform(staticObj, curr_block_count, glm::vec3{ 46.0f, 5.0f + (float)i, 10.0f + (float)i * 6 }, 3, 1, 1);
    }

    place_platform(staticObj, curr_block_count, glm::vec3{ 45.0f, 10.0f, 45.0f }, 5, 1, 5);

    input_moving_block_pos(dynamicObj[curr_moving_count], curr_moving_count++, 43.0f, 14.0f, 47.0f, 0, 1, 0);

    input_block_pos(staticObj[curr_block_count], curr_block_count++, 40.0f, 18.0f, 47.0f);
    input_block_pos(staticObj[curr_block_count], curr_block_count++, 34.0f, 18.0f, 50.0f);
    input_block_pos(staticObj[curr_block_count], curr_block_count++, 28.0f, 19.0f, 47.0f);

    input_moving_block_pos(dynamicObj[curr_moving_count], curr_moving_count++, 25.0f, 19.0f, 42.0f, 0, 0, 1);

    place_platform(staticObj, curr_block_count, glm::vec3{ 25.0f, 19.0f, 32.0f }, 1, 1, 3);

    input_block_pos(staticObj[curr_block_count], curr_block_count++, 18.0f, 19.0f, 33.0f);
    input_block_pos(staticObj[curr_block_count], curr_block_count++, 18.0f, 20.0f, 27.0f);
    input_block_pos(staticObj[curr_block_count], curr_block_count++, 18.0f, 20.0f, 27.0f);
    input_block_pos(staticObj[curr_block_count], curr_block_count++, 14.0f, 21.0f, 23.0f);
    input_block_pos(staticObj[curr_block_count], curr_block_count++, 9.5f, 22.5f, 18.5f);
    input_block_pos(staticObj[curr_block_count], curr_block_count++, 5.0f, 24.0f, 18.0f);
    input_block_pos(staticObj[curr_block_count], curr_block_count++, 7.0f, 25.0f, 12.0f);
    input_block_pos(staticObj[curr_block_count], curr_block_count++, 12.0f, 26.5f, 16.0f);
    input_block_pos(staticObj[curr_block_count], curr_block_count++, 16.0f, 28.0f, 22.0f);
    input_block_pos(staticObj[curr_block_count], curr_block_count++, 15.0f, 30.0f, 27.0f);
    input_block_pos(staticObj[curr_block_count], curr_block_count++, 12.0f, 32.0f, 33.0f);
    input_block_pos(staticObj[curr_block_count], curr_block_count++, 10.0f, 34.5f, 36.0f);
    input_block_pos(staticObj[curr_block_count], curr_block_count++, 7.5f, 36.0f, 38.0f);
    input_block_pos(staticObj[curr_block_count], curr_block_count++, 5.0f, 38.0f, 41.0f);
    input_block_pos(staticObj[curr_block_count], curr_block_count++, 4.0f, 40.0f, 45.0f);
    input_block_pos(staticObj[curr_block_count], curr_block_count++, 3.5f, 42.0f, 48.5f);
    input_block_pos(staticObj[curr_block_count], curr_block_count++, 7.0f, 44.0f, 46.0f);
    input_block_pos(staticObj[curr_block_count], curr_block_count++, 8.0f, 46.0f, 41.0f);
    input_block_pos(staticObj[curr_block_count], curr_block_count++, 3.0f, 48.0f, 42.0f);

    place_platform(staticObj, curr_block_count, glm::vec3{ 0.0f, 50.0f, 45.0f }, 5, 1, 5);

    count_block = curr_block_count;
    count_moving_block = curr_moving_count;
}