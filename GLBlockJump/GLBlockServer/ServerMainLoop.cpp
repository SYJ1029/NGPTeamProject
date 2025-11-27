#include "ServerProcess.h"

#include <chrono>
#include "Object.h"
#include "Player.h"
#include "InitWorld.h"
#include "ServerMainLoop.h"

#include "CollisionManager.h"


bool WriteFrameState(Game_State& state)
{
	EnterCriticalSection(&FrameCS);

	Fs.gameState = state;
	for (int i = 0; i < MAX_CLIENTS; ++i)
	{
		Fs.players[i].playerId = i;
		Fs.players[i].position[0] = players[i].GetPosX();
		Fs.players[i].position[1] = players[i].GetPosY();
		Fs.players[i].position[2] = players[i].GetPosZ();

		Fs.players[i].rotation[0] = players[i].GetRotationX();
		Fs.players[i].rotation[1] = players[i].GetRotationY();
		Fs.players[i].rotation[2] = players[i].GetRotationX();
	}

	Fs.move_block_size = count_moving_block;

	for (int i = 0; i < Fs.move_block_size; ++i)
	{
		Fs.DynObjPos[i][0] = MoveObjects[i].GetPosVec3().x;
		Fs.DynObjPos[i][1] = MoveObjects[i].GetPosVec3().y;
		Fs.DynObjPos[i][2] = MoveObjects[i].GetPosVec3().z;
	}


	LeaveCriticalSection(&FrameCS);
	return true;
}

bool CheckGameEnd()
{
	static bool game_end = false;
	if (game_end) return true;
	for (int i = 0; i < MAX_CLIENTS; ++i)
	{
		if (players[i].GetPosY() >= 50.0f)
		{
			std::cout << "Player " << i << " wins! \nPress \"q\" to quit the game.\n";
			game_end = true;
			return true;
		}
	}
	return false;
}

void ServerMainLoop()
{
	Game_State state = GAME_STATE_RUNNING;

	float frameTime = 0;
	float deltaTime = 2.4f;
	while (1)
	{

		auto timerStart = std::chrono::high_resolution_clock::now();
		if (deltaTime > frameTime);
		else
		{
			for (int i = 0; i < MAX_CLIENTS; ++i)
			{
				players[i].Update();
				ChecKCollisionLoop(players[i]);
			}

			for (int i = 0; i < count_moving_block; ++i)
			{
				MoveObjects[i].Update();
			}

			CheckGameEnd();

			frameTime = 0;
			WriteFrameState(state);
		}


		auto timerEnd = std::chrono::high_resolution_clock::now();
		frameTime += std::chrono::duration<float, std::milli>(timerEnd - timerStart).count();





		WriteFrameState(state);
	}
}