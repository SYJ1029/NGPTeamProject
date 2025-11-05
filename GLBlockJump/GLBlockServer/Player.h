#pragma once
#include "Object.h"
#include "PacketStruct.h"
//#include "MeshData.h" 

class Object;

class Player : public Object
{
private:
    int ID = 0;
    float moveSpeed[3]{ 0.0f };
    float rotation[3]{ 0.0f };
    float jumpSpeed{ 0.2f };
public:
    Player() {}
    ~Player() {}
    bool isGrounded{ true };
    PlayerInputs inputs{};

    virtual void Init(const std::array<float, 3>& newPos, uint8_t id);

    void Update();

    void Release();

    bool CheckCollision(const Object& other);
};

extern std::array<Player, MAX_PLAYER> players;

