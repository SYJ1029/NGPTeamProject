#pragma once
#include <vector>
#include <array>
#include "Object.h"
#include "Player.h"
#include "StateMacro.h"

class Object;
class MovingObject;
class Player;

extern int count_block;
extern int count_moving_block;
extern const std::array<std::array<float, 3>, 3> player_start_pos;
void setting(std::vector<Object>&, std::vector<MovingObject>&, std::array<Player, MAX_PLAYER>&);
void InitPlayer(std::array<Player, MAX_PLAYER>&);