
#define SDL_MAIN_HANDLED
#include"Game.hpp"


Game* game = nullptr;

int main(int argc, char const *argv[])
{

    const int FPS = 60;
    const int farmeDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    game = new Game();
                                                                                    //true để full màn hình
    game->init("shadow knights v.0.1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 960, 640, false);

    while (game->running())
    {

        frameStart = SDL_GetTicks();

        game -> handleEvents();
        game -> update();
        game ->render();

        //cho chúng ta biết khoảng thời gian đã trôi qua kể từ khi khung hình cuối cùng được kết xuất.
        frameTime = SDL_GetTicks() - frameStart;

        //kiểm tra xem độ trễ khung hình có lớn hơn thời gian khung hình hay không. 
        if (farmeDelay > frameTime)
        {
            //Hàm SDL_Delay() tạm dừng việc thực thi chương trình trong một số mili giây được chỉ định.
            SDL_Delay(farmeDelay - frameTime);
        }
        
    }

    game->clean();

    return 0;
}
