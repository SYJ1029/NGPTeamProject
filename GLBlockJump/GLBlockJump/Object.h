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
	virtual void Init(float newPos[3]);

	glm::vec3 GetPosVec3();
};

class MovingObject : public Object
{
private:
	float moveSpeed[3]{0.0f, 0.0f, 0.0f};
	float chngeSpeed[3]{0.0f, 0.0f, 0.0f};
	float max_chnge[3]{8.0f, 8.0f, 8.0f};
public:
	MovingObject();
	~MovingObject();
	/*virtual void Init(float newPos[3]);*/

	void update();

	void Release();

	bool CheckCollision(const Object& other);

	
};

extern std::vector<Object> staticObjects;
extern std::vector<MovingObject> MoveObjects;