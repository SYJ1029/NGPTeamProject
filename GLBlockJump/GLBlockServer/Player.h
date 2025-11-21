#pragma once
#include "PacketStruct.h"
#include "Object.h"
#include "StateMacro.h"

class Player :
	public Object
{
private:
	int ID = 0;
	float moveSpeed[3]{ 0.0f };
	float rotation[3]{ 0.0f };
	float jumpSpeed{ 0.3f };
public:
	bool isGrounded{ true };
	PlayerInputs inputs{};
	CRITICAL_SECTION pInputCS;

	~Player();

	virtual void Init(const std::array<float, 3>& newPos, uint8_t id);

	void Update();

	void Release();

	bool CheckCollision(Object& other);

	float GetRotationX() const { return rotation[0]; };
	float SetRotationX(float rotX) { return rotation[0] = rotX; };
	float GetRotationY() const { return rotation[1]; };
	float SetRotationY(float rotY) { return rotation[1] = rotY; };

	float GetPosX() const { return pos[0]; };
	float SetPosX(float posX) { return pos[0] = posX; };
	float GetPosY() const { return pos[1]; };
	float SetPosY(float posY) { return pos[1] = posY; };
	float GetPosZ() const { return pos[2]; };
	float SetPosZ(float posZ) { return pos[2] = posZ; };

	float GetMoveSpeedX() const { return moveSpeed[0]; };
	float SetMoveSpeedX(float speedX) { return moveSpeed[0] = speedX; };
	float GetMoveSpeedY() const { return moveSpeed[1]; };
	float SetMoveSpeedY(float speedY) { return moveSpeed[1] = speedY; };
	float GetMoveSpeedZ() const { return moveSpeed[2]; };
	float SetMoveSpeedZ(float speedZ) { return moveSpeed[2] = speedZ; };
};

extern std::array<Player, MAX_PLAYER> players;

