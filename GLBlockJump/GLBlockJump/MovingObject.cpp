#pragma once

#include "Object.h"


MovingObject::MovingObject()
{
}

MovingObject::~MovingObject()
{
}

void MovingObject::Init(const std::array<float, 3>& newPos, const std::array<int, 3>& newDir)
{
	Object::Init(newPos);
	for (int i = 0; i < 3; i++) {
		dir[i] = newDir[i];
	}
}

void MovingObject::Update()
{
	float distance = 0.0f;

	for (int i = 0; i < 3; i++) {
		if (dir[i] != 0) {
			distance = dir[i] * speed;

			pos[i] += distance;
			changedLength[i] += distance;

			if (changedLength[i] >= limit || changedLength[i] <= -limit) {
				dir[i] *= -1;
			}
		}
	}
}

glm::ivec3 MovingObject::GetDirVec3()
{
	return glm::ivec3(dir[0], dir[1], dir[2]);
}

std::vector<MovingObject> MoveObjects;