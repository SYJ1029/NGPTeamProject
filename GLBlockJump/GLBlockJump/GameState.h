#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "stdafx.h"
#include "StateMacro.h"
#include "MeshData.h"
#include "Object.h"
#include "Player.h"

extern float char_angle[3];
extern float char_pos[3];
extern const std::array<float, 3> player1_start_pos;
extern const std::array<float, 3> player2_start_pos;
extern const std::array<float, 3> player3_start_pos;
extern int go_v[4];
extern int count_block;
extern int count_moving_block;
extern float y_speed;
extern bool jumpable;
extern bool infjump;
extern bool game_end;

bool checkCollision(float ax, float ay, float az, float bx, float by, float bz);

#endif