cmake_minimum_required(VERSION 3.7)
project(SDL_Test_Game)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        images/MainMenu.png
        images/Paddle.png
        images/PlayButton.png
        images/QuitButton.png
        images/SplashScreen.png
        source/states/playing.cpp
        source/states/uninitialized.cpp
        source/states/titleScreen.cpp
        source/states/options.cpp
        source/states/pauseMenu.cpp
        source/entity.cpp
        source/entityCollection.cpp
        source/game.cpp
        source/gameState.cpp
        source/globals.cpp
        source/main.cpp
        source/ball.cpp
        source/player.cpp
        states/playing.h
        states/uninitialized.h
        states/titleScreen.h
        states/options.h
        states/pauseMenu.h
        constants.h
        entity.h
        entityCollection.h
        enumerations.h
        game.h
        gameState.h
        globals.h
        header.h
        prototypes.h
        ball.h
        player.h)

add_executable(SDL_Test_Game ${SOURCE_FILES})

INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES})