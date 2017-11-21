### Linux Makefile ###

###
### Variables
###
executable := launchEngine.sh

objects := 	main.o \
			game.o \
			globals.o \
			entity.o \
			entityCollection.o \
			ball.o \
			player.o \
			gameState.o \
			playing.o \
			uninitialized.o

flags := -lSDL2 \
		 -lSDL2main \
		 -lSDL2_image \
		 -lm \
		 -lstdc++

#CFLAGS = -c -Wall -Iinclude
#options := -c -g -Wall -Iinclude -I/usr/include/SDL2
options := -c -g -Wall -I/usr/include/SDL2

###
### Main make program
###
all : $(objects)
	gcc -g -o $(executable) $(objects) $(flags)

###
### Source files
###
main.o 				: source/main.cpp include/game.h include/constants.h
	gcc $(options) source/main.cpp

game.o 				: source/game.cpp include/game.h include/entityCollection.h include/enumerations.h
	gcc $(options) source/game.cpp

globals.o 			: source/globals.cpp include/globals.h
	gcc $(options) source/globals.cpp

entity.o 			: source/entity.cpp include/entity.h include/globals.h include/constants.h
	gcc $(options) source/entity.cpp

entityCollection.o  : source/entityCollection.cpp include/entityCollection.h
	gcc $(options) source/entityCollection.cpp

ball.o				: source/ball.cpp include/ball.h include/constants.h
	gcc $(options) source/ball.cpp

player.o			: source/player.cpp
	gcc $(options) source/player.cpp

gameState.o 		: source/gameState.cpp include/gameState.h
	gcc $(options) source/gameState.cpp

###
### List of game states to be compiled ###
###
playing.o			: source/states/playing.cpp include/states/playing.h
	gcc $(options) source/states/playing.cpp

uninitialized.o		: source/states/uninitialized.cpp include/states/uninitialized.h
	gcc $(options) source/states/uninitialized.cpp
###
### Cleans object and executable files (Debug stuff)
###
clean :
	rm -f $(executable) $(objects)
