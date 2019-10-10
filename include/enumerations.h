#pragma once

enum class GameStateType
{
	NONE,
	UNINITIALIZED,
	TITLE_SCREEN,
	MAIN_MENU,
	OPTIONS,
	PLAYING_GAME,
	PAUSE_MENU,
	LEVEL_EDITOR,
	CONSOLE,
	MINESWEEPER
};

enum class EditorEntityType {
	PLAYER = 0,
	BALL,
	WALL,
	Count
};

enum class BlendMode {
	NONE,
	BLEND,
	ADD,
	MOD
};

enum class Align {
	TOP_L,
	TOP_C,
	TOP_R,
	MID_L,
	MID_C,
	MID_R,
	BOT_L,
	BOT_C,
	BOT_R
};

enum class TextQuality {
	SOLID,
	BLENDED,
	SHADED
};

enum class PanelType {
	FOCUS,
	STATIC
};

enum class KeyEvent {
	none,
	game_quit,
	open_menu,
	close_menu,
	options_menu,
	restart,
	level_editor,
	play_mode,
	close_console
};

enum class TextAlignment {
	ALIGN_LEFT,
	ALIGN_CENTER,
	ALIGN_RIGHT
};
