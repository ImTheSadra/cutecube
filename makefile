CC = g++

flags = -lSDL2main -lSDL2  -lmingw32

includes = -I./sdl/include/SDL2 -I./sdl/include -I./source 

libs = -L./sdl/lib/ -L./sdl/bin

source = main.cpp

output = build/app.exe

all:
	$(CC) $(source) -o $(output) $(libs) $(includes) $(flags)

run:
	@$(output)