#pragma once

#include "SDL.h"

#include "font.h"
#include "text.h"
#include "constants.h"
#include "types.h"
#include "camera.h"

#include <map>
#include <functional>
#include <vector>

// Rendering
extern SDL_Renderer* globalRenderer;
extern Camera* globalCam;

// Fonts
extern Font *defaultFont;
extern Font *menuTitleFont;
extern Font *menuOptionFont;
extern Font *consoleFont;

extern Font *fontList[FONT_COUNT]; // Used for serialization of text objects

// Commands
extern std::map<std::string, std::function<void(std::vector<std::string>)>> commands;


// Test command stuff
//struct Command {
//	std::string name;
//	std::function<void(sVector)> console_command;
//	int min_args;
//	int max_args;
//};
//
//extern std::map<std::string, Command> test_commands;
//
////extern void AddCommand(std::string name, auto lambda, int min_args, int max_args);
//void AddCommand(std::string name, auto lambda, int min_args, int max_args)
//{
//	Command new_command;
//	new_command.name = name;
//	new_command.console_command = lambda;
//	new_command.min_args = min_args;
//	new_command.max_args = max_args;
//
//	auto test = [=] (auto ... more) {
//		
//	};
//
//	test_commands[name] = lambda;
//}
//
//void CallCommand(std::string name, sVector argList)
//{
//	if (test_commands.find(name) != test_commands.end())
//	{
//		// Execute command with arg list given
//		//commands[name](args);
//		auto test = [=] (auto ... more) {
//			
//		};
//	}
//}
