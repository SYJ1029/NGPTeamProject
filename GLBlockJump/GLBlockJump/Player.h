#pragma once
#include "PacketStruct.h"
#include "Object.h"



class Player :
    public Object
{
private:
    int id = 0;
    float moveSpeed[3]{ 0.0f }; // [0,1,2] 순으로 x,y,z축 이동 속도일 경우 y축 이동 속도는 jumpSpeed와 같음(즉, moveSpeed[1]은 사용되지 않음)
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

extern std::array<Player, MAX_PLAYER> players;

