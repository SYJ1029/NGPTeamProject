#include "InitWorld.h"

const std::array<std::array<float, 3>, 3> player_start_pos = {
   0.0f, 10.0f, 0.0f, 
   1.0f, 10.0f, 0.0f, 
   2.0f, 10.0f, 0.0f
};

void InitPlayer(std::array<Player, MAX_PLAYER>& players)
{

    for (int i = 0; i < MAX_PLAYER; ++i)
    {
        players[i].Init(player_start_pos[i], i);
    }

    for (int i = 0; i < MAX_PLAYER; ++i)
    {
        glm::vec3 temp = players[i].GetPosVec3();

        std::cout << "Player" << i << ": " 
            << "(" << temp.x << ", " << temp.y << ", " << temp.z << ")" 
            << std::endl << std::endl;
    }
}


