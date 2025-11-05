#include "InitWorld.h"

int count_block = 0;
int count_moving_block = 0;
const std::array<float, 3> player1_start_pos = { 0.0f, 10.0f, 0.0f };
const std::array<float, 3> player2_start_pos = { 1.0f, 10.0f, 0.0f };
const std::array<float, 3> player3_start_pos = { 2.0f, 10.0f, 0.0f };

void place_platform(std::vector<Object>& staticObj, int& curr, const glm::vec3& v, int dx, int dy, int dz) {

    for (int y = 0; y < dy; ++y) {
        for (int x = 0; x < dx; ++x) {
            for (int z = 0; z < dz; ++z) {
                staticObj[curr++].Init({ v.x + (float)x, v.y + (float)y, v.z + (float)z });
            }
        }
    }
}

void setting(std::vector<Object>& staticObj, std::vector<MovingObject>& dynamicObj, std::array<Player, MAX_PLAYER>& players)
{
    int player_count{};
    int curr_block_count{};
    int curr_moving_count{};

    staticObj.resize(200);
    dynamicObj.resize(50);

    // 플레이어 초기 위치
    players[player_count++].Init(player1_start_pos, player_count);
    players[player_count++].Init(player2_start_pos, player_count);
    players[player_count++].Init(player3_start_pos, player_count);

    // 블럭들 초기 위치
    place_platform(staticObj, curr_block_count, glm::vec3{ 0.0f, 0.0f, 0.0f }, 5, 1, 5);

    for (int i = 0; i < 6; ++i) {
        place_platform(staticObj, curr_block_count, glm::vec3{ 7.0f + float(i * 6), float(i), 1.0f }, 3, 1, 3);
    }

    place_platform(staticObj, curr_block_count, glm::vec3{ 45.0f, 5.0f, 0.0f }, 5, 1, 5);

    for (int i = 0; i < 6; ++i) {
        place_platform(staticObj, curr_block_count, glm::vec3{ 46.0f, 5.0f + (float)i, 10.0f + (float)i * 6 }, 3, 1, 1);
    }

    place_platform(staticObj, curr_block_count, glm::vec3{ 45.0f, 10.0f, 45.0f }, 5, 1, 5);

    dynamicObj[curr_moving_count++].Init({ 43.0f, 14.0f, 47.0f }, { 0,1,0 });

    staticObj[curr_block_count++].Init({ 40.0f, 18.0f, 47.0f });
    staticObj[curr_block_count++].Init({ 34.0f, 18.0f, 50.0f });
    staticObj[curr_block_count++].Init({ 28.0f, 19.0f, 47.0f });

    dynamicObj[curr_moving_count++].Init({ 25.0f, 19.0f, 42.0f }, { 0,0,1 });

    place_platform(staticObj, curr_block_count, glm::vec3{ 25.0f, 19.0f, 32.0f }, 1, 1, 3);

    staticObj[curr_block_count++].Init({ 18.0f, 19.0f, 33.0f });
    staticObj[curr_block_count++].Init({ 18.0f, 20.0f, 27.0f });
    //staticObj[curr_block_count++].Init({ 18.0f, 20.0f, 27.0f });
    staticObj[curr_block_count++].Init({ 14.0f, 21.0f, 23.0f });
    staticObj[curr_block_count++].Init({ 9.5f, 22.5f, 18.5f });
    staticObj[curr_block_count++].Init({ 5.0f, 24.0f, 18.0f });
    staticObj[curr_block_count++].Init({ 7.0f, 25.0f, 12.0f });
    staticObj[curr_block_count++].Init({ 12.0f, 26.5f, 16.0f });
    staticObj[curr_block_count++].Init({ 16.0f, 28.0f, 22.0f });
    staticObj[curr_block_count++].Init({ 15.0f, 30.0f, 27.0f });
    staticObj[curr_block_count++].Init({ 12.0f, 32.0f, 33.0f });
    staticObj[curr_block_count++].Init({ 10.0f, 34.5f, 36.0f });
    staticObj[curr_block_count++].Init({ 7.5f, 36.0f, 38.0f });
    staticObj[curr_block_count++].Init({ 5.0f, 38.0f, 41.0f });
    staticObj[curr_block_count++].Init({ 4.0f, 40.0f, 45.0f });
    staticObj[curr_block_count++].Init({ 3.5f, 42.0f, 48.5f });
    staticObj[curr_block_count++].Init({ 7.0f, 44.0f, 46.0f });
    staticObj[curr_block_count++].Init({ 8.0f, 46.0f, 41.0f });
    staticObj[curr_block_count++].Init({ 3.0f, 48.0f, 42.0f });

    place_platform(staticObj, curr_block_count, glm::vec3{ 0.0f, 50.0f, 45.0f }, 5, 1, 5);

    count_block = curr_block_count;
    count_moving_block = curr_moving_count;
}