#include "Player.h"
#include "StateMacro.h"

void Player::Init(float newPos[3], uint8_t id)
{
	Object::Init(newPos);
	ID = id;
}

void Player::Update()
{
    //�����¿� �̵�
    glm::mat4 rotMat = glm::rotate(glm::mat4(1.0f), glm::radians(-rotation[1]), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::vec3 forward = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 right = glm::vec3(1.0f, 0.0f, 0.0f);
    forward = glm::normalize(glm::vec3(rotMat * glm::vec4(forward, 0.0f)));
    right = glm::normalize(glm::vec3(rotMat * glm::vec4(right, 0.0f)));

    if (inputs.updown == 1) {
        pos[0] -= forward.x * moveSpeed[0];
        pos[2] -= forward.z * moveSpeed[2];
    }
    else if (inputs.updown == -1) {
        pos[0] += forward.x * moveSpeed[0];
        pos[2] += forward.z * moveSpeed[2];
    }
    if (inputs.rightleft == -1) {
        pos[0] += right.x * moveSpeed[0];
        pos[2] += right.z * moveSpeed[2];
    }
    else if (inputs.rightleft == 1) {
        pos[0] -= right.x * moveSpeed[0];
        pos[2] -= right.z * moveSpeed[2];
    }

    //����
    if (inputs.jump && isGrounded) {
        isGrounded = false;
        moveSpeed[1] = jumpSpeed;
	}

    //��������
    moveSpeed[1] -= GRAVITY;
	pos[1] += moveSpeed[1];
}

void Player::Release()
{
}

bool Player::CheckCollision(const Object& other)
{
    OBB PlayerOBB;
    PlayerOBB.center = glm::vec3(pos[0], pos[1], pos[2]);
    PlayerOBB.halfSize = glm::vec3(0.5f, 0.5f, 0.5f);
    glm::mat4 rotMat = glm::yawPitchRoll(
        rotation[1],
        rotation[0],
        rotation[2]
    );
    PlayerOBB.axis[0] = glm::normalize(glm::vec3(rotMat[0]));
    PlayerOBB.axis[1] = glm::normalize(glm::vec3(rotMat[1]));
    PlayerOBB.axis[2] = glm::normalize(glm::vec3(rotMat[2]));

    OBB boxOBB;
    boxOBB.halfSize = glm::vec3(0.5f, 0.5f, 0.5f);
    boxOBB.axis[0] = { 1, 0, 0 };
    boxOBB.axis[1] = { 0, 1, 0 };
    boxOBB.axis[2] = { 0, 0, 1 };

    //CheckCollision �Լ� ���� �� ��������� ������ Server�� Update() �Լ� �ۼ� �� �� �Լ����� �߶󳻾� 
    //Server�� Update() �Լ����� �浹 �˻縦 ���� Object�鿡 ���� �ݺ��� ������ �� ������ ����, �ۼ��� �δ� ���� ����.
    //�ϴ� ���� �̸� �ۼ� �ص�.

    boxOBB.center = other.GetPosVec3();
    if (CheckOBBCollision(PlayerOBB, boxOBB)) {
        return true;
    }
	return false;
}

std::array<Player, MAX_PLAYER> players;
