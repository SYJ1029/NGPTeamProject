#include "ServerMainLoop.h"

#ifdef _DEBUG
float DEBUG_SPEED_MULTIPLIER = 0.1f;
#else
float DEBUG_SPEED_MULTIPLIER = 1.0f;
#endif


bool WriteFrameState(Game_State& state)
{
	EnterCriticalSection(&FrameCS);

	Fs.gameState = state;
	if(state == GAME_STATE_FINISHED)
	{
		Fs.winnerId = winnerId;
	}
	else
	{
		Fs.winnerId = -1;
	}

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
	return Fs.gameState == GAME_STATE_RUNNING;
}

int CheckGameEnd()
{
	if (!game_end) return -1;
	for (int i = 0; i < MAX_CLIENTS; ++i)
	{
		if (players[i].GetPosY() >= 50.0f)
		{
			std::cout << "Player " << i << " wins! \nPress \"q\" to quit the game.\n";
			game_end = true;
			return i;
		}
	}
	return -1;
}

void ServerMainLoop()
{
	Game_State state = GAME_STATE_RUNNING;

	float frameTime = 0;
	float deltaTime = 2.4f * DEBUG_SPEED_MULTIPLIER;
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


			//winnerId = CheckGameEnd();
			if (-1 != winnerId) {
				state = GAME_STATE_FINISHED;
			}

			frameTime = 0;
			WriteFrameState(state);

			if (clientRestartFlags[0] && clientRestartFlags[1] && clientRestartFlags[2]
				&& !clientQuitFlags[0] && !clientQuitFlags[1] && !clientQuitFlags[2])
			{
				// 모든 클라이언트가 리스타트를 눌렀다면 월드와 플레이어들을 초기화한다
				std::cout << "All clients requested restart. Resetting world and players.\n";
				InitWorld(staticObjects, MoveObjects, players);
				winnerId = -1;
				game_end = false;
				for (int i = 0; i < MAX_CLIENTS; ++i)
				{
					clientRestartFlags[i] = false;

					// input도 초기화
					players[i].inputs.clear();
				}

				state = GAME_STATE_RUNNING;
				continue;
			}

			if (state == GAME_STATE_FINISHED
				&& clientQuitFlags[0] && clientQuitFlags[1] && clientQuitFlags[2])
			{
				std::cout << "All clients have quit. Server is shutting down.\n";
				break;
			}
		}


		auto timerEnd = std::chrono::high_resolution_clock::now();
		frameTime += std::chrono::duration<float, std::milli>(timerEnd - timerStart).count();





		WriteFrameState(state);
	}

	
}