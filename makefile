game : main.o game.o globals.o entity.o entityCollection.o TEMPball.o
	gcc -o game.sh main.o game.o globals.o entity.o entityCollection.o TEMPball.o -lSDL2 -lSDL2main -lSDL2_image -lm -lstdc++

main.o : game.h constants.h source/main.cpp
	gcc -c source/main.cpp

game.o : entityCollection.h enumerations.h source/game.cpp game.h
	gcc -c source/game.cpp

globals.o : source/globals.cpp globals.h
	gcc -c source/globals.cpp

entity.o : globals.h constants.h source/entity.cpp entity.h
	gcc -c source/entity.cpp

entityCollection.o : source/entityCollection.cpp
	gcc -c source/entityCollection.cpp

TEMPball.o : constants.h source/TEMPball.cpp TEMPball.h
	gcc -c source/TEMPball.cpp

clean :
	rm game.sh main.o game.o globals.o entity.o entityCollection.o TEMPball.o
