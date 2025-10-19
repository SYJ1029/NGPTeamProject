#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "stdafx.h"

extern float char_angle[3];
extern float char_pos[3];
extern int go_v[4];
extern int count_block;
extern float blocks_pos[10000][3];
extern int count_moving_block;
extern float moving_blocks_pos[10000][3];
extern float moving_blocks_chng_pos[10000][3];
extern int moving_blocks_vec[10000][3];
extern float y_speed;
extern bool jumpable;
extern bool infjump;
extern bool game_end;


extern int before_mouse_x;
extern int before_mouse_y;

bool checkCollision(float ax, float ay, float az, float bx, float by, float bz);
void setting();
void input_block_pos(int i, float x, float y, float z);
void input_moving_block_pos(int i, float x, float y, float z, int vx, int vy, int vz);
void place_platform(int& curr, const glm::vec3& v, int dx, int dy, int dz);

#endif