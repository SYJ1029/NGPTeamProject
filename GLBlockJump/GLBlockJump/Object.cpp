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


glm::vec3 Object::GetPosVec3()
{
	return glm::vec3(pos[0], pos[1], pos[2]);
}


std::vector<Object> staticObjects;
std::vector<MovingObject> MoveObjects;