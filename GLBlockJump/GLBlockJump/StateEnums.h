#pragma once


enum Game_State : long long
{
	GAME_STATE_WAITING = 0, // 모든 클라이언트 접속 대기 & 초기화 정보 송신 단계
	GAME_STATE_RUNNING = 1, // 실제 경기 중
	GAME_STATE_FINISHED = 2, // 우승자가 정해짐
	GAME_STATE_RESETTING = 3 // 월드/플레이어 리셋 중
};


