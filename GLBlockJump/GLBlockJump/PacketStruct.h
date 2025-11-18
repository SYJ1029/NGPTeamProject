#pragma once

#include <iostream>
#include <vector>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include "StateEnums.h"

/* -----------------------------------------
플레이어 입출력 관리 구조체

------------------------------------------*/
struct PlayerInputs {
    int playerid;
    int updown, rightleft; // 위치 이동 계산이 없으므로 int
    bool jump;
    float deltax, deltay;
    bool quit;
};


enum PacketType {
    PACK_INIT_WORLD_STATIC = 0, // 서버 -> 클라 : 월드의 정적 오브젝트 생성
	PACK_INIT_WORLD_DYNAMIC = 1,    // 서버 -> 클라 : 월드의 동적 오브젝트 생성
    PACK_INIT_PLAYERS = 2, // 서버 -> 클라 : 플레이어 초기 스폰 위치/ID/색 등 생성
    PACK_PLAYER_INPUT = 3, // 클라 -> 서버: 클라이언트의 입력 값
    PACK_FRAME_STATE = 4, // 서버 -> 클라 : 매 틱마다 동적 상태(플레이어들, 움직이는 발판)
    PACK_INPUT_COMMAND = 5, // 클라 -> 서버 : 조작 변화(좌우 이동, 점프 등)
    PACK_GAME_STATE_CHANGE = 6 // 서버 -> 클라 : 게임 상태가 변경됨
};

struct PacketParam {
    PacketType type; // PacketType
    size_t size; // 전체 바이트 수(헤더 포함)
};


struct PlayerInitInfo {
    int playerId;
    float spawnPos[3];
};

struct PktInitPlayers {
    int myPlayerId;
    PlayerInitInfo players[3]; // 모든 플레이어의 초기 위치

    PktInitPlayers() {}
    ~PktInitPlayers() {}

    std::vector<uint8_t> Serialize();
    void Deserialize(const uint8_t* data, int size);
};

/*-----------------------
  매 프레임마다 보내고 받게될 정보
-------------------------*/

/*-----------------------
  매 프레임마다 보내게될 정보
-------------------------*/

struct PlayerSyncData {
    int playerId; // 플레이어의 id  
    float position[3]; // 서버 기준 월드 좌표  
    float rotation[3]; // 객체의 회전 각도      
};
struct PktFrameState {
    Game_State gameState; // 지금 게임이 RUNNING인지 FINISHED인지도 함께 보냄  
    PlayerSyncData players[3];

    int move_block_size;
    float (*DynObjPos)[3];

    std::vector<uint8_t> Serialize(); // 구조체 정보들을 하나의 배열로 만들기
    void Deserialize(const uint8_t* data, int size); // 배열에서 다시 구조체 정보로 바꾸기
};

extern CRITICAL_SECTION FrameCS;
extern CRITICAL_SECTION InputCS;