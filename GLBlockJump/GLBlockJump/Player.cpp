#include "Player.h"


void Player::Init(float newPos[3])
{
	Object::Init(newPos);
}

void Player::Update()
{

}

void Player::Release()
{
}

bool Player::CheckCollision(const Object& other)
{
	return false;
}