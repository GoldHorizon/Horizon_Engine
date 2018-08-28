#pragma once

enum class GameStateType
{
	UNINITIALIZED,
	TITLE_SCREEN,
	MAIN_MENU,
	OPTIONS,
	PLAYING_GAME,
	PAUSE_MENU,
	LEVEL_EDITOR
};

enum class EditorEntityType {
	PLAYER = 0,
	BALL,
	Count
};

enum KeyEvents {
	GAME_QUIT,
	OPEN_MENU,
	CLOSE_MENU,
	OPTIONS_MENU,
	RESTART,
	LEVEL_EDITOR,
	PLAY_MODE
};

enum TextAlignment {
	ALIGN_LEFT,
	ALIGN_CENTER,
	ALIGN_RIGHT
};
