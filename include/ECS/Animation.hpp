#pragma once

struct Animation
{
    int xIndex;
    int yIndex;
    int frames;
    int speed;

    int frameWidth  = -1; // -1 = dùng mặc định theo transform
    int frameHeight = -1;



    Animation() = default;
    Animation(int x,int y, int f, int s)
    {
        xIndex = x;
        yIndex = y;
        frames = f;
        speed = s;
    }

    Animation(int x,int y, int f, int s, int w, int h)
    {
        xIndex = x;
        yIndex = y;
        frames = f;
        speed = s;
        frameWidth = w;
        frameHeight = h;
    }
};
