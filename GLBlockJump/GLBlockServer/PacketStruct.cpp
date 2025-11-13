#include "PacketStruct.h"


std::vector<uint8_t> PktInitPlayers::Serialize()
{
    std::vector<uint8_t> buffer;

    auto writeInt = [&](int v) {
        uint32_t net = htonl(v);
        uint8_t* p = reinterpret_cast<uint8_t*>(&net);
        buffer.insert(buffer.end(), p, p + 4);
        };

    auto writeFloat = [&](float f) {
        uint32_t temp;
        memcpy(&temp, &f, 4);
        uint32_t net = htonl(temp);
        uint8_t* p = reinterpret_cast<uint8_t*>(&net);
        buffer.insert(buffer.end(), p, p + 4);
        };
    
    // myPlayerId
    writeInt(myPlayerId);

    // players
    for (int i = 0; i < 3; i++) {
        writeInt(players[i].playerId);
        for (int j = 0; j < 3; j++) {
            writeFloat(players[i].spawnPos[j]);
        }
    }

    return buffer;
}

void PktInitPlayers::Deserialize(const uint8_t* data, int size)
{
    size_t offset = 0;

    auto readInt = [&](int& out) {
        uint32_t net;
        memcpy(&net, data + offset, 4);
        offset += 4;
        out = ntohl(net);
        };

    auto readFloat = [&](float& out) {
        uint32_t net;
        memcpy(&net, data + offset, 4);
        offset += 4;
        uint32_t host = ntohl(net);
        memcpy(&out, &host, 4);
        };

    readInt(myPlayerId);

    for (int i = 0; i < 3; i++) {
        readInt(players[i].playerId);
        for (int j = 0; j < 3; j++) {
            readFloat(players[i].spawnPos[j]);
        }
    }
}
