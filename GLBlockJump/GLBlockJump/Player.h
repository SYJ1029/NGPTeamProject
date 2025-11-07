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

    virtual void Init(const std::array<float, 3>& newPos, uint8_t id);

    void Update();

    void Release();

    bool CheckCollision(const Object& other);

	float GetRotationX() const { return rotation[0]; };
	float GetRotationY() const { return rotation[1]; };
};

extern std::array<Player, MAX_PLAYER> players;

