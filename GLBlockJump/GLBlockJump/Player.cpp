#include "Player.h"
#include "StateMacro.h"

void Player::Init(float newPos[3])
{
	Object::Init(newPos);
}

void Player::Update()
{
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

    if (inputs.jump && isGrounded) {
        isGrounded = false;
        moveSpeed[1] = jumpSpeed;
	}
}

void Player::Release()
{
}

bool Player::CheckCollision(const Object& other)
{
	return false;
}

std::array<Player, MAX_PLAYER> players;
