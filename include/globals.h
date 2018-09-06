#pragma once

#include "SDL.h"

#include "font.h"
#include "text.h"
#include "constants.h"
#include "types.h"

#include <map>
#include <functional>
#include <vector>

extern SDL_Renderer* globalRenderer;

extern Font *defaultFont;
extern Font *menuTitleFont;
extern Font *menuOptionFont;
extern Font *consoleFont;

extern Font *fontList[FONT_COUNT];

// Commands
extern std::map<std::string, std::function<void(sVector)>> commands;
