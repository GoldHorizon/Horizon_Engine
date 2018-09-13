### Makefile ###

###
### Variables
###
compiler := g++
executable := launchEngine

objects 	:= 	main.o \
				game.o \
				globals.o \
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
				playing.o \
				uninitialized.o \
				pauseMenu.o \
				editor.o \
				console.o

win32_flags :=	-lmingw32 \
				-lSDL2main \
				-lSDL2 \
				-lSDL2_image \
				-lSDL2_ttf \
				-lstdc++
				#-lm

### NOT IMPLEMENTED
win64_flags :=	-m64 \
				-lSDL2main \
				-lSDL2 \
				-lSDL2_image \
				-lSDL2_ttf \
				-lstdc++
				#-lmingw \
				#-lm \


#CFLAGS = -c -Wall -Iinclude
#options := -c -g -Wall -Iinclude -I/usr/include/SDL2
#options := -c -g -Wall -I/usr/include/SDL2 -I../../Workspace/Libraries/SDL2/SDL2-2.0.8/include/

win32_inc_path := -IC:\Users\Nick\Documents\Workspace\Libraries\MinGW\sdl32\include\SDL2
win32_lib_path := -LC:\Users\Nick\Documents\Workspace\Libraries\MinGW\sdl32\lib
win64_inc_path := -IC:\Users\Nick\Documents\Workspace\Libraries\MinGW\sdl64\include\SDL2
win64_lib_path := -LC:\Users\Nick\Documents\Workspace\Libraries\MinGW\sdl64\lib

win32_gcc_flags = -c -Wall -w -Wl,-subsystem,windows $(win32_inc_path) -IC:\Users\Nick\Documents\Git\SDL_Engine\include -static-libstdc++ -std=c++14
win64_gcc_flags = -c -Wall -w -Wl,-subsystem,windows $(win64_inc_path) -static-libstdc++

#ifeq ($(target), win32)
#	options := -c -g -Wall $(win32_inc_path)
#else
#	options := -c -g -Wall $(win64_inc_path)
#endif

###
### Main make program
###
all : $(executable)

$(executable): 	$(objects)
				make clean
				$(compiler) $(objects) $(win32_inc_path) $(win32_lib_path) $(win32_flags) -o $(executable)
				#mkdir -p build/
				#mv $(objects) build/

#win64 :	$(objects)
#	make clean
#	$(compiler) $(objects) $(win64_inc_path) $(win64_lib_path) $(win64_flags) -o $(executable)
#	mkdir -p build/
#	mv $(objects) build/
#
#win32 :	$(objects)
#	make clean
#	gcc -g -o $(executable) $(objects) $(win32_flags)
#	mkdir -p build/
#	mv $(objects) build/
#
#lin32 :
###
### Source files
###
all_files			:  
	$(objects)

main.o 				: source/main.cpp include/game.h include/constants.h
	gcc $(win32_gcc_flags) source/main.cpp

game.o 				: source/game.cpp include/game.h include/globals.h include/constants.h include/ball.h include/enumerations.h include/states/playing.h include/states/uninitialized.h include/states/titleScreen.h include/states/options.h include/states/pauseMenu.h include/states/editor.h include/states/console.h
	gcc $(win32_gcc_flags) source/game.cpp

globals.o 			: source/globals.cpp include/globals.h
	gcc $(win32_gcc_flags) source/globals.cpp

entity.o 			: source/entity.cpp include/entity.h include/globals.h include/constants.h include/engineMethods.h
	gcc $(win32_gcc_flags) source/entity.cpp

entityCollection.o  : source/entityCollection.cpp include/entityCollection.h include/globals.h
	gcc $(win32_gcc_flags) source/entityCollection.cpp

ball.o				: source/ball.cpp include/ball.h include/constants.h include/engineMethods.h
	gcc $(win32_gcc_flags) source/ball.cpp

player.o			: source/player.cpp include/player.h include/constants.h include/engineMethods.h
	gcc $(win32_gcc_flags) source/player.cpp

file.o				: source/file.cpp include/file.h include/level.h include/types.h include/engineMethods.h
	gcc $(win32_gcc_flags) source/file.cpp

level.o				: source/level.cpp include/level.h include/file.h include/types.h include/engineMethods.h
	gcc $(win32_gcc_flags) source/level.cpp

gameState.o 		: source/gameState.cpp include/gameState.h
	gcc $(win32_gcc_flags) source/gameState.cpp

text.o				: source/text.cpp include/text.h include/constants.h include/engineMethods.h include/globals.h
	gcc $(win32_gcc_flags) source/text.cpp

font.o				: source/font.cpp include/font.h include/constants.h include/engineMethods.h
	gcc $(win32_gcc_flags) source/font.cpp

engineMethods.o		: source/engineMethods.cpp include/engineMethods.h include/player.h include/text.h include/ball.h include/wall.h
	gcc $(win32_gcc_flags) source/engineMethods.cpp

drawing.o			: source/drawing.cpp include/drawing.h include/globals.h include/text.h
	gcc $(win32_gcc_flags) source/drawing.cpp

wall.o				: source/wall.cpp include/wall.h
	gcc $(win32_gcc_flags) source/wall.cpp

###
### List of game states to be compiled ###
###
playing.o		: source/states/playing.cpp include/states/playing.h include/ball.h include/player.h include/font.h include/text.h include/file.h include/engineMethods.h include/globals.h
	gcc $(win32_gcc_flags) source/states/playing.cpp

uninitialized.o	: source/states/uninitialized.cpp include/states/uninitialized.h
	gcc $(win32_gcc_flags) source/states/uninitialized.cpp

pauseMenu.o		: source/states/pauseMenu.cpp include/states/pauseMenu.h include/globals.h include/enumerations.h include/constants.h include/drawing.h
	gcc $(win32_gcc_flags) source/states/pauseMenu.cpp

editor.o		: source/states/editor.cpp include/states/editor.h include/gameState.h include/drawing.h include/constants.h include/player.h include/ball.h include/wall.h
	gcc $(win32_gcc_flags) source/states/editor.cpp

console.o		: source/states/console.cpp include/states/console.h include/gameState.h include/drawing.h include/globals.h include/engineMethods.h include/enumerations.h
	gcc $(win32_gcc_flags) source/states/console.cpp

###
### Cleans object and executable files (Debug stuff)
###
clean :
	#rm -fr ./build
	rm -f $(executable)

cleanobjects :
	rm -f *.o

###
### Compiles/links program normally, then runs it
###
run :
	make all
	./launchEngine.exe
