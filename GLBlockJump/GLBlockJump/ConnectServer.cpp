#include "ConnectServer.h"
#include <iostream>
#include "ParticleSendRecv.h"

#include "GameState.h"


PacketParam staticObjParam; // 고정 객체를 전송할 패킷들의 총 정보
float staticObjectPosition[3]; // 고정된 객체들의 각 좌표를 넣어서 그 개수만큼 반복

PacketParam dynamicObjParam; // 움직이는 객체를 전송할 패킷들의 총 정보
float dynamicObjectPosition[3]; // 움직이는 객체들의 각 좌표를 넣어서 그 개수만큼

SOCKET InitSocket(const char* SERVERIP)
{
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        err_display("WSAStartup()");
        return INVALID_SOCKET;
    }

    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        err_display("socket()");
        WSACleanup();
        return INVALID_SOCKET;
    }

    struct sockaddr_in serveraddr;
    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(SERVERPORT);

    int retval = inet_pton(AF_INET, SERVERIP, &serveraddr.sin_addr);
    if (retval <= 0) {
        if (retval == 0)
            printf("[오류] 잘못된 IP 주소 형식: %s\n", SERVERIP);
        else
            err_display("inet_pton()");
        closesocket(sock);
        WSACleanup();
        return INVALID_SOCKET;
    }

    if (connect(sock, (struct sockaddr*)&serveraddr, sizeof(serveraddr)) == SOCKET_ERROR) {
        err_display("connect()");
        closesocket(sock);
        WSACleanup();
        return INVALID_SOCKET;
    }

    return sock;
}

void CleanupSocket(SOCKET sock)
{
    closesocket(sock);
    WSACleanup();
}

void RecvInitPlayers(SOCKET sock, UINT &MyID)
{
    PacketParam header{};
    int pkType = 0;
    int retval = recv(sock, (char*)&pkType, sizeof(int), MSG_WAITALL);
    std::cout << "연결 종료\n\n";
    if (retval <= 0) return;

    header.type = (PacketType)pkType;

    retval = recv(sock, (char*)&header.size, sizeof(header.size), MSG_WAITALL);
    if (retval <= 0) return;

    if (header.type != PACK_INIT_PLAYERS) return;

    int bodySize = header.size / sizeof(PacketParam);
    if (bodySize <= 0 || bodySize > 1024) return;


  

    std::vector<uint8_t> buffer(sizeof(PktInitPlayers));
    retval = recv(sock, (char*)buffer.data(), buffer.size() * sizeof(uint8_t), MSG_WAITALL);
    if (retval <= 0) return;

    PktInitPlayers pkt;
    pkt.Deserialize(buffer.data(), buffer.size());
    MyID = pkt.myPlayerId;

    for (int i = 0; i < 3; ++i) {
        const std::array<float, 3> pos = {
            pkt.players[i].spawnPos[0],
            pkt.players[i].spawnPos[1],
            pkt.players[i].spawnPos[2]
        };
        players[i].Init(pos, pkt.players[i].playerId);
    }
}

void RecvInitWorldStatic(SOCKET sock)
{
    PacketParam header{};
    int pkType = 0;
    int retval = recv(sock, (char*)&pkType, sizeof(int), MSG_WAITALL);
    if (retval <= 0) return;

    header.type = (PacketType)pkType;

    if (header.type != PACK_INIT_WORLD_STATIC)
        return;

    size_t hsize = 0;
    retval = recv(sock, (char*)&hsize, sizeof(size_t), MSG_WAITALL);
    if (retval <= 0) return;

    header.size = ntohl(hsize);



    int bodySize = header.size * 3;
    if (bodySize <= 0) return;

    std::vector<float> buffer(header.size * 3);
    retval = recv_all(sock, (char*)buffer.data(), buffer.size() * 4);
    if (retval == SOCKET_ERROR) 
        err_quit("recv()");


    int objectCount = bodySize / 3;
    staticObjects.resize(objectCount);

    for (int i = 0; i < objectCount; ++i)
    {
        std::array<float, 3> pos = {
            buffer[i * 3 + 0],
            buffer[i * 3 + 1],
            buffer[i * 3 + 2]
        };
        staticObjects[i].Init(pos);
    }

    count_block = staticObjects.size();
}
void RecvInitWorldDynamic(SOCKET sock)
{
    PacketParam header{};
    int pkType = 0;
    int retval = recv(sock, (char*)&pkType, sizeof(int), MSG_WAITALL);
    if (retval <= 0) return;

    header.type = (PacketType)pkType;

    if (header.type != PACK_INIT_WORLD_DYNAMIC)
        return;

    size_t hsize = 0;
    retval = recv(sock, (char*)&hsize, sizeof(size_t), MSG_WAITALL);
    if (retval <= 0) return;

    header.size = ntohl(hsize);



    int bodySize = header.size * 3;
    if (bodySize <= 0) return;

    std::vector<float> buffer(header.size * 3);
    retval = recv(sock, (char*)buffer.data(), buffer.size() * 4, MSG_WAITALL);
    if (retval == SOCKET_ERROR)
        err_quit("recv()");


    int objectCount = bodySize / 3;
    MoveObjects.resize(objectCount);

    for (int i = 0; i < objectCount; ++i)
    {
        std::array<float, 3> pos = {
            buffer[i * 3 + 0],
            buffer[i * 3 + 1],
            buffer[i * 3 + 2]
        };
        MoveObjects[i].Init(pos, {0, 0, 0});
    }

    count_moving_block = MoveObjects.size();
}