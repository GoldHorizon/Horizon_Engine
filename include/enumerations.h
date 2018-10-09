#pragma once

enum class GameStateType
{
	UNINITIALIZED,
	TITLE_SCREEN,
	MAIN_MENU,
	OPTIONS,
	PLAYING_GAME,
	PAUSE_MENU,
	LEVEL_EDITOR,
	CONSOLE
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

enum KeyEvents {
	GAME_QUIT,
	OPEN_MENU,
	CLOSE_MENU,
	OPTIONS_MENU,
	RESTART,
	LEVEL_EDITOR,
	PLAY_MODE,
	CLOSE_CONSOLE
};

enum TextAlignment {
	ALIGN_LEFT,
	ALIGN_CENTER,
	ALIGN_RIGHT
};
