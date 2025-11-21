#include "GameState.h"
#include "Object.h"
#include "Player.h"

float char_angle[3] = { 0.0f, 0.0f, 0.0f };
float char_pos[3] = { 0.0f, 10.0f, 0.0f };

const std::array<float, 3> player1_start_pos = { 0.0f, 10.0f, 0.0f };
const std::array<float, 3> player2_start_pos = { 1.0f, 10.0f, 0.0f };
const std::array<float, 3> player3_start_pos = { 2.0f, 10.0f, 0.0f };

int go_v[4] = { 0,0,0,0 };
int count_block = 0;
int count_moving_block = 0;

float y_speed = 0.0f;
bool jumpable;
bool infjump = false;
bool game_end = false ;

int before_mouse_x = 300;
int before_mouse_y = 300;

bool isMotion = false;

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


