#pragma once
#include <string>
#include <vector>

class Map
{
public:
     Map(const char* mfp, int ms, int ts);
    ~Map();

    void LoadMap(std::string path, int sizeX, int sizeY, int griWidth);
    void AddTile(int srcX, int srcY, int xpos, int ypos);

private:
    const char* mapFilePath;
    int mapScale;
    int tileSize;
    int scaledSize;
    std::vector<std::vector<int>> mapData;

};


