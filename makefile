all:
	g++ -Iinclude -Iinclude/sdl -Iinclude/headers -Llib -o main src/*.cpp src/cmd/*.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image