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

	virtual void Init(float newPos[3]) override;

	void Update();

    void Release();

	bool CheckCollision(const Object& other);
};

