#include "Map.hpp"
#include"Game.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include "ECS/ECS.hpp"
#include"ECS/Components.hpp"

extern Manager manager;

Map::Map(std::string tID, int ms, int ts) : texID(tID), mapScale(ms), tileSize(ts)
{
    scaledSize = ms * ts;
}

Map::~Map(){}

void Map::LoadMap(std::string path, int sizeX, int sizeY, int griWidth) {
    std::ifstream mapFile(path);
    if (!mapFile) {
        std::cerr << "Failed to open map file: " << path << std::endl;
        return;
    }

    std::string line;
    mapData.resize(sizeY, std::vector<int>(sizeX));
    
    // Đọc dữ liệu từ file vào mapData
    for (int y = 0; y < sizeY; ++y) {
        if (!std::getline(mapFile, line)) {
            std::cerr << "Failed to read line for map data" << std::endl;
            return;
        }
        std::istringstream ss(line);
        std::string value;
        int x = 0;
        while (std::getline(ss, value, ',')) {
            mapData[y][x] = std::stoi(value);
            x++;
        }
    }

    // Tạo các tile từ dữ liệu map
    for (int y = 0; y < sizeY; ++y) {
        for (int x = 0; x < sizeX; ++x) {
            int tileCode = mapData[y][x];
            int srcX = tileCode % griWidth;
            int srcY = tileCode / griWidth;
            AddTile(srcX * tileSize, srcY * tileSize, x * scaledSize, y * scaledSize);
        }
    }

    // Add tile collision
    for (int y = 0; y < sizeY; ++y) {
        for (int x = 0; x < sizeX; ++x) {
            int tileCode = mapData[y][x];

            const std::vector<int>& tileCodes = getCollisionTileCodes();

            if (std::find(tileCodes.begin(), tileCodes.end(), tileCode) != tileCodes.end())
            { 
                auto& tcol = manager.addEntity();
                tcol.addComponent<ColliderComponent>("terrain", x * scaledSize, y * scaledSize, scaledSize);
                tcol.addGroup(Game::groupColliders);
            }
        }
    }
}

void Map::AddTile(int srcX, int srcY, int xpos, int ypos)
{
    auto& tile(manager.addEntity());
    tile.addComponent<TileComponent>(srcX, srcY, xpos, ypos, tileSize, mapScale, texID);
    tile.addGroup(Game::groupMap);
}

void Map::setCollisionTileCodes(const std::vector<int>& codes) 
{
    collisionTileCodes = codes;
}

const std::vector<int>& Map::getCollisionTileCodes() const
{
    return collisionTileCodes;
}

