#pragma once

enum class GameStateType
{
	UNINITIALIZED,
	TITLE_SCREEN,
	MAIN_MENU,
	OPTIONS,
	PLAYING_GAME,
	PAUSE_MENU
};

enum KeyEvents {
	GAME_QUIT,
	OPEN_MENU,
	CLOSE_MENU
};

enum TextAlignment {
	ALIGN_LEFT,
	ALIGN_CENTER,
	ALIGN_RIGHT
};
