#pragma once

#include "InitWorld.h"
#include "ServerProcess.h"

#include <chrono>
#include "Object.h"
#include "Player.h"

#include "CollisionManager.h"

// 함수 선언
void ServerMainLoop();
bool WriteFrameState(Game_State& state);