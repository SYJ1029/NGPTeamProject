#pragma once

#include "Object.h"


MovingObject::MovingObject()
{
}

MovingObject::~MovingObject()
{
}

void MovingObject::SetPosVec3(float newPos[3])
{
	for (int i = 0; i < 3; i++)
		pos[i] = newPos[i];
}
void MovingObject::SetDirVec3(int newDir[3])
{
	for (int i = 0; i < 3; i++)
		dir[i] = newDir[i];
}

void MovingObject::Update() 
{
	float distance = 0.0f;

	for (int i = 0; i < 3; i++) {
		if (dir[i] != 0) {
			distance = dir[i] * 0.03f;

			pos[i] += distance;
			changedLength[i] += distance;

			if (changedLength[i] >= limit || changedLength[i] <= -limit) {
				dir[i] *= -1;
			}
		}
	}
}


void MovingObject::Release()
{

}

bool MovingObject::CheckCollision(const Object& other)
{
	return false;
}

glm::ivec3 MovingObject::GetDirVec3()
{
	return glm::ivec3(dir[0], dir[1], dir[2]);
}

std::vector<MovingObject> MoveObjects;