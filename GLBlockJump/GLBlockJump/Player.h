#pragma once
#include "PacketStruct.h"
#include "Object.h"




class Player :
    public Object
{
private:
    float moveSpeed[3]{ 0.0f };
    float rotation[3]{ 0.0f };
    float jumpSpeed{ 0.2f };
public:
    bool isGrounded{ true };
    PlayerInputs inputs{};
};

