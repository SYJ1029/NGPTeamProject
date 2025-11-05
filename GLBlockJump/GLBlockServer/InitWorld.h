#pragma once
#include "Object.h"
#include "Player.h"
#include "StateMacro.h"

int count_block;
int count_moving_block;
extern const std::array<float, 3> player1_start_pos;
extern const std::array<float, 3> player2_start_pos;
extern const std::array<float, 3> player3_start_pos;

void setting(std::vector<Object>&, std::vector<MovingObject>& j, std::array<Player, MAX_PLAYER>&);