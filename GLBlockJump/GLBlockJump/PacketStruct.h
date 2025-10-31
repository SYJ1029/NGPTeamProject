#pragma once

/* -----------------------------------------
플레이어 입출력 관리 구조체

------------------------------------------*/
struct PlayerInputs {
    int playerid;
    int updown, rightleft; // 위치 이동 계산이 없으므로 int
    bool jump;
    float deltax, deltay;
};


enum PacketType {
    PACK_INIT_WORLD_STATIC = 0, // 서버 -> 클라 : 월드의 정적 오브젝트 생성
	PACK_INIT_WORLD_DYNAMIC = 1,    // 서버 -> 클라 : 월드의 동적 오브젝트 생성
    PACK_INIT_PLAYERS = 2, // 서버 -> 클라 : 플레이어 초기 스폰 위치/ID/색 등 생성
    PACK_PLAYER_INPUT = 3, // 클라 -> 서버: 클라이언트의 입력 값
    PACK_FRAME_STATE = 3, // 서버 -> 클라 : 매 틱마다 동적 상태(플레이어들, 움직이는 발판)
    PACK_INPUT_COMMAND = 4, // 클라 -> 서버 : 조작 변화(좌우 이동, 점프 등)
    PACK_GAME_STATE_CHANGE = 5 // 서버 -> 클라 : 게임 상태가 변경됨
};

struct PacketParam {
    PacketType type; // PacketType
    size_t size; // 전체 바이트 수(헤더 포함)
};


struct PlayerInitInfo {
    unsigned long long playerId;
    float spawnPos[3];
};

struct PktInitPlayers {
    unsigned long long myPlayerId;
    PlayerInitInfo players[3]; // 모든 플레이어의 초기 위치
};