#include "globals.h"

SDL_Renderer* globalRenderer = nullptr;
Camera* globalCam = nullptr;

Font *defaultFont = nullptr;
Font *menuTitleFont = nullptr;
Font *menuOptionFont = nullptr;
Font *consoleFont = nullptr;

Font *fontList[FONT_COUNT];

std::map<std::string, std::function<void(std::vector<std::string>)>> commands;

// Test command stuff
//std::map<std::string, Command> test_commands;
//
//void AddCommand(std::string name, auto lambda, int min_args, int max_args)
//{
//	Command new_command;
//	new_command.min_args = min_args;
//	new_command.max_args = max_args;
//	auto test = [=] (auto ... more) {
//		
//	};
//
//	test_commands[name] = lambda;
//}

