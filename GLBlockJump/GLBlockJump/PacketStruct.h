#pragma once

/* -----------------------------------------
�÷��̾� ����� ���� ����ü

------------------------------------------*/
struct PlayerInputs {
    int playerid;
    int updown, rightleft; // ��ġ �̵� ����� �����Ƿ� int
    bool jump;
    float deltax, deltay;
};


enum PacketType {
    PACK_INIT_WORLD_STATIC = 0, // ���� -> Ŭ�� : ������ ���� ������Ʈ ����
	PACK_INIT_WORLD_DYNAMIC = 1,    // ���� -> Ŭ�� : ������ ���� ������Ʈ ����
    PACK_INIT_PLAYERS = 2, // ���� -> Ŭ�� : �÷��̾� �ʱ� ���� ��ġ/ID/�� �� ����
    PACK_PLAYER_INPUT = 3, // Ŭ�� -> ����: Ŭ���̾�Ʈ�� �Է� ��
    PACK_FRAME_STATE = 3, // ���� -> Ŭ�� : �� ƽ���� ���� ����(�÷��̾��, �����̴� ����)
    PACK_INPUT_COMMAND = 4, // Ŭ�� -> ���� : ���� ��ȭ(�¿� �̵�, ���� ��)
    PACK_GAME_STATE_CHANGE = 5 // ���� -> Ŭ�� : ���� ���°� �����
};

struct PacketParam {
    PacketType type; // PacketType
    size_t size; // ��ü ����Ʈ ��(��� ����)
};


struct PlayerInitInfo {
    unsigned long long playerId;
    float spawnPos[3];
};

struct PktInitPlayers {
    unsigned long long myPlayerId;
    PlayerInitInfo players[3]; // ��� �÷��̾��� �ʱ� ��ġ
};