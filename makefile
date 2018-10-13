### Makefile ###

###
### Variables
###
compiler := g++
executable := launchEngine

objects 	:= 	main.o \
				game.o \
				globals.o \
				image.o \
				entity.o \
				entityCollection.o \
				ball.o \
				player.o \
				file.o \
				level.o \
				gameState.o \
				text.o \
				font.o \
				engineMethods.o \
				drawing.o \
				wall.o \
				camera.o \
				inputManager.o \
				panel.o \
				event.o \
				mineBoard.o \
				mineTile.o \
				playing.o \
				uninitialized.o \
				pauseMenu.o \
				editor.o \
				console.o \
				minesweeper.o

win32_flags :=	-lmingw32 \
				-lSDL2main \
				-lSDL2 \
				-lSDL2_image \
				-lSDL2_ttf \
				-lstdc++

win32_inc_path := -IC:\Users\Nick\Documents\Workspace\Libraries\MinGW\sdl32\include\SDL2
win32_lib_path := -LC:\Users\Nick\Documents\Workspace\Libraries\MinGW\sdl32\lib

win32_gcc_flags = -c -Wall -w -Wl,-subsystem,windows $(win32_inc_path) -IC:\Users\Nick\Documents\Git\SDL_Engine\include -static-libstdc++ -std=c++14
gcc_flags = -c -Wall -w $(win32_inc_path) -IC:\Users\Nick\Documents\Git\SDL_Engine\include -std=c++14 -g

###
### Main make program
###
all : $(executable)

$(executable): 	
				-mkdir -p build
				-cd build && mv *.o ../
				make $(objects)
				$(compiler) $(objects) $(win32_inc_path) $(win32_lib_path) $(win32_flags) -o $(executable)
				-mv *.o build/

###
### Source files
###
all_files			:  
	$(objects)

main.o 				: source/main.cpp include/game.h include/constants.h
	g++ $(gcc_flags) source/main.cpp

game.o 				: source/game.cpp include/game.h include/globals.h include/constants.h include/ball.h include/enumerations.h include/states/playing.h include/states/uninitialized.h include/states/titleScreen.h include/states/options.h include/states/pauseMenu.h include/states/editor.h include/states/console.h
	g++ $(gcc_flags) source/game.cpp

globals.o 			: source/globals.cpp include/globals.h
	g++ $(gcc_flags) source/globals.cpp

image.o				: source/image.cpp include/image.h
	g++ $(gcc_flags) source/image.cpp

entity.o 			: source/entity.cpp include/entity.h include/globals.h include/constants.h include/engineMethods.h
	g++ $(gcc_flags) source/entity.cpp

entityCollection.o  : source/entityCollection.cpp include/entityCollection.h include/globals.h
	g++ $(gcc_flags) source/entityCollection.cpp

ball.o				: source/ball.cpp include/ball.h include/constants.h include/engineMethods.h
	g++ $(gcc_flags) source/ball.cpp

player.o			: source/player.cpp include/player.h include/constants.h include/engineMethods.h
	g++ $(gcc_flags) source/player.cpp

file.o				: source/file.cpp include/file.h include/level.h include/types.h include/engineMethods.h
	g++ $(gcc_flags) source/file.cpp

level.o				: source/level.cpp include/level.h include/file.h include/types.h include/engineMethods.h
	g++ $(gcc_flags) source/level.cpp

gameState.o 		: source/gameState.cpp include/gameState.h
	g++ $(gcc_flags) source/gameState.cpp

text.o				: source/text.cpp include/text.h include/constants.h include/engineMethods.h include/globals.h
	g++ $(gcc_flags) source/text.cpp

font.o				: source/font.cpp include/font.h include/constants.h include/engineMethods.h
	g++ $(gcc_flags) source/font.cpp

engineMethods.o		: source/engineMethods.cpp include/engineMethods.h include/player.h include/text.h include/ball.h include/wall.h
	g++ $(gcc_flags) source/engineMethods.cpp

drawing.o			: source/drawing.cpp include/drawing.h include/globals.h include/text.h
	g++ $(gcc_flags) source/drawing.cpp

wall.o				: source/wall.cpp include/wall.h
	g++ $(gcc_flags) source/wall.cpp

camera.o			: source/camera.cpp include/camera.h include/globals.h include/types.h include/enumerations.h
	g++ $(gcc_flags) source/camera.cpp
	
inputManager.o		: source/inputManager.cpp include/inputManager.h
	g++ $(gcc_flags) source/inputManager.cpp

panel.o				: source/panel.cpp include/panel.h include/entity.h
	g++ $(gcc_flags) source/panel.cpp

event.o				: source/event.cpp include/event.h
	g++ $(gcc_flags) source/event.cpp

mineBoard.o			: source/mineBoard.cpp include/mineBoard.h include/entity.h
	g++ $(gcc_flags) source/mineBoard.cpp

mineTile.o			: source/mineTile.cpp include/mineTile.h include/entity.h
	g++ $(gcc_flags) source/mineTile.cpp

###
### List of game states to be compiled ###
###
playing.o		: source/states/playing.cpp include/states/playing.h include/ball.h include/player.h include/font.h include/text.h include/file.h include/engineMethods.h include/globals.h
	g++ $(gcc_flags) source/states/playing.cpp

uninitialized.o	: source/states/uninitialized.cpp include/states/uninitialized.h
	g++ $(gcc_flags) source/states/uninitialized.cpp

pauseMenu.o		: source/states/pauseMenu.cpp include/states/pauseMenu.h include/globals.h include/enumerations.h include/constants.h include/drawing.h
	g++ $(gcc_flags) source/states/pauseMenu.cpp

editor.o		: source/states/editor.cpp include/states/editor.h include/gameState.h include/drawing.h include/constants.h include/player.h include/ball.h include/wall.h
	g++ $(gcc_flags) source/states/editor.cpp

console.o		: source/states/console.cpp include/states/console.h include/gameState.h include/drawing.h include/globals.h include/engineMethods.h include/enumerations.h
	g++ $(gcc_flags) source/states/console.cpp

minesweeper.o	: source/states/minesweeper.cpp include/states/minesweeper.h include/mineBoard.h	
	g++ $(gcc_flags) source/states/minesweeper.cpp

###
### Cleans object and executable files (Debug stuff)
###

clean :
	make cleandir
	make cleanobj
	make cleanexec

cleandir :
	rm -fr ./build

cleanobj :
	rm -f *.o

cleanexec :
	rm -f $(executable)

###
### Compiles/links program normally, then runs it
###
run :
	make all
	./launchEngine.exe
