#pragma once

#include "Object.h"


MovingObject::MovingObject()
{
	for (int i = 0; i < 3; i++)
	{
		moveSpeed[i] = 0.0f;
		chngeSpeed[i] = 0.0f;
		max_chnge[i] = 0.0f;
	}
}

MovingObject::~MovingObject()
{
}

void MovingObject::Init(float newPos[3])
{
	Object::Init(newPos);
}

void MovingObject::update() 
{
}


void MovingObject::Release()
{

}



