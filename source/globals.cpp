#include "../include/globals.h"

SDL_Renderer* globalRenderer = nullptr;

Font *defaultFont = nullptr;
Font *menuTitleFont = nullptr;
Font *menuOptionFont = nullptr;
Font *consoleFont = nullptr;

Font *fontList[FONT_COUNT];

std::map<std::string, std::function<void(std::string)>> commands;
//std::vector<std::function<void(std::string)>> commands_temp;
