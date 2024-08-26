#pragma once

struct Animation
{
    int xIndex;
    int yIndex;
    int frames;
    int speed;

    Animation(){}
    Animation(int x,int y, int f, int s)
    {
        xIndex = x;
        yIndex = y;
        frames = f;
        speed = s;
    }
};
