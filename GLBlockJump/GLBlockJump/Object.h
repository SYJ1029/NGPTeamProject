#pragma once
class Object
{
protected:
	// ��ü�� ��ġ�� �ڽ� Ŭ�������� �������� ����� �����̹Ƿ� protected�� ����
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

