SRCS := $(wildcard src/*.cpp)//

all:
	g++ -I SDL2-w64/include -I include -L SDL2-w64/lib -o bin/debug/main $(SRCS) -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer && start bin/debug/main