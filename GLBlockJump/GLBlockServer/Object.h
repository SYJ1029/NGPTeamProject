#pragma once

#include "stdafx.h"

class Object
{
protected:
	// 객체의 위치는 자식 클래스까지 공동으로 사용할 예정이므로 protected로 선언
	float pos[3]{ 0.0f };
public:
	Object();
	~Object();
	virtual void Init(const std::array<float, 3>& newPos);

	glm::vec3 GetPosVec3() const;
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

	void Init(const std::array<float, 3>& newPos, const std::array<int, 3>& newDir);

	void Update();

	void Release();

	bool CheckCollision(const Object& other);

	glm::ivec3 GetDirVec3();
};

extern std::vector<Object> staticObjects;
extern std::vector<MovingObject> MoveObjects;