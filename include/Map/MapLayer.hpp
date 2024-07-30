#pragma once
#include<Map/Map.hpp>
#include<Game.hpp>

class MapLayer
{

public:
    MapLayer();
    ~MapLayer() = default;

    void LoadMapLayer()
    {
        Map* m_Layer1 = new Map("res/gfx/TX Tileset Grass.png", 2, 32);
        Map* m_Layer2 = new Map("res/gfx/TX Plant.png",2, 32);

        m_Layer1->LoadMap("res/gfx/mapFile_Layer1.csv", 30, 20, 8);
        m_Layer2->LoadMap("res/gfx/m_layer2.csv", 30,20, 16);
        /* Map - Layer*/
           
    }
};