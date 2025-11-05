#include "Object.h"


Object::Object()
{
}

Object::~Object()
{
}

void Object::Init(const std::array<float, 3>& newPos)
{
	for (int i = 0; i < 3; i++)
		pos[i] = newPos[i];
}

glm::vec3 Object::GetPosVec3() const
{
	return glm::vec3(pos[0], pos[1], pos[2]);
}


std::vector<Object> staticObjects;