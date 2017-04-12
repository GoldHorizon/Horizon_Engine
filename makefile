executable := launchGame

objects := 	main.o \
			game.o \
			globals.o \
			entity.o \
			entityCollection.o \
			TEMPball.o 

#sources := 
flags := -lSDL2 \
		 -lSDL2main \
		 -lSDL2_image \
		 -lm \
		 -lstdc++

all : $(objects)
	gcc -o $(executable) $(objects) $(flags)

# Old flags: -lSDL2 -lSDL2main -lSDL2_image -lm -lstdc++

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

TEMPball.o			: source/TEMPball.cpp TEMPball.h constants.h
	gcc -c source/TEMPball.cpp

#gameState.o 		: gameState.h
#	gcc -c source/gameState.cpp

clean :
	rm $(executable) $(objects)
