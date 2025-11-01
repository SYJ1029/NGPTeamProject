#pragma once
#include "PacketStruct.h"
#include "Object.h"
#include "MeshData.h" 

class Player :
    public Object
{
private:
    int ID = 0;
    float moveSpeed[3]{ 0.0f };
    float rotation[3]{ 0.0f };
    float jumpSpeed{ 0.2f };
public:
    bool isGrounded{ true };
    PlayerInputs inputs{};

	virtual void Init(float newPos[3], uint8_t id);

	void Update();

    void Release();

	bool CheckCollision(const Object& other);
};

extern std::array<Player, MAX_PLAYER> players;

