#include "stdafx.h"
#include "Object.h"


Object::Object()
{
}

Object::~Object()
{
}

void Object::Init(float newPos[3])
{
	for (int i = 0; i < 3; i++)
		pos[i] = newPos[i];
}



