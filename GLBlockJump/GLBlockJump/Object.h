#pragma once
class Object
{
protected:
	// 객체의 위치는 자식 클래스까지 공동으로 사용할 예정이므로 protected로 선언
	float pos[3]{ 0.0f };
public:
	Object();
	~Object();
	virtual void Init(float newPos[3]);
};

class MovingObject : public Object
{
private:
	float moveSpeed[3];
	float chngeSpeed[3];
	float max_chnge[3];
public:
	MovingObject();
	~MovingObject();
	virtual void Init(float newPos[3]);

	void update();

	void Release();
};

