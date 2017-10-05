###
### Variables
###
executable := launchGame

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

###
### Main make program
###
all : $(objects)
	gcc -g -o $(executable) $(objects) $(flags)

###
### Source files
###
main.o 				: source/main.cpp game.h constants.h
	gcc -c source/main.cpp

game.o 				: source/game.cpp game.h entityCollection.h enumerations.h
	gcc -c source/game.cpp

globals.o 			: source/globals.cpp globals.h
	gcc -c source/globals.cpp

entity.o 			: source/entity.cpp entity.h globals.h constants.h
	gcc -c source/entity.cpp

entityCollection.o  : source/entityCollection.cpp entityCollection.h
	gcc -c source/entityCollection.cpp

ball.o				: source/ball.cpp ball.h constants.h
	gcc -c source/ball.cpp

player.o			: source/player.cpp
	gcc -c source/player.cpp

gameState.o 		: source/gameState.cpp gameState.h
	gcc -c source/gameState.cpp

###
### List of game states to be compiled ###
###
playing.o			: source/states/playing.cpp states/playing.h
	gcc -c source/states/playing.cpp

uninitialized.o		: source/states/uninitialized.cpp states/uninitialized.h
	gcc -c source/states/uninitialized.cpp
###
### Cleans object and executable files (Debug stuff)
###
clean :
	rm -f $(executable) $(objects)
