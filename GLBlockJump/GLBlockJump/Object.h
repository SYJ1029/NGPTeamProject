#pragma once

#include "stdafx.h"

class Object
{
protected:
	// ��ü�� ��ġ�� �ڽ� Ŭ�������� �������� ����� �����̹Ƿ� protected�� ����
	float pos[3]{ 0.0f };
public:
	Object();
	~Object();
	virtual void Init(float newPos[3]);

	glm::vec3 GetPosVec3() const ;
};

class MovingObject : public Object
{
private:
	int dir[3]{ 0,0,0 };
	float speed{ 0.03f };
	float changedLength[3]{ 0.0f, 0.0f, 0.0f };
	float limit{ 5.0f };
public:
	MovingObject();
	~MovingObject();

	void Init(float newPos[3], int newDir[3]);

	void Update();

	void Release();

	bool CheckCollision(const Object& other);

	glm::ivec3 GetDirVec3();
};

extern std::vector<Object> staticObjects;
extern std::vector<MovingObject> MoveObjects;