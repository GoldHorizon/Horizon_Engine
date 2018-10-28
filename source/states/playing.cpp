#include "states/playing.h"
#include "ball.h"
#include "player.h"
#include "font.h"
#include "text.h"
#include "file.h"
#include "engineMethods.h"
#include "globals.h"
#include "inputManager.h"
#include "panel.h"

#define ClassName StatePlaying

ClassName* ClassName::_thisInstance = nullptr;

ClassName::~ClassName()
{
	Cleanup();
}

void ClassName::Initialize()
{
	_level = nullptr;

	// @todo Set this to be based on a startup variables file eventually
	//ChangeLevel("test_file");

	// Set global camera to be at 0, 0 in top left corner
	globalCam->origin = (Align::MID_C);
	globalCam->SetPosition(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
}

void ClassName::Cleanup()
{
	while (_entities.GetCount() > 0)
	{
		_entities.RemoveByIndex(0);
	}

	delete _level;
}

int ClassName::HandleEvents(Event& event)
{
	_entities.HandleAllEvents(event);

	if (_level != nullptr)
		_level->HandleAllEvents(event);

	if (event.ev.type == SDL_KEYDOWN)
	{
		switch (event.ev.key.keysym.sym)
		{
		case SDLK_ESCAPE:
			if (event.ev.key.repeat == 0)
				return OPEN_MENU;
			break;
		}
	}

	return -1;
}

void ClassName::Update()
{
	if (!IsPaused())
	{
		_entities.UpdateAll();

		if (_level != nullptr)
			_level->UpdateAll();

		if (Input::KeyHeld(SDLK_h)) globalCam->Move(-4, 0);
		if (Input::KeyHeld(SDLK_j)) globalCam->Move(0, 4);
		if (Input::KeyHeld(SDLK_k)) globalCam->Move(0, -4);
		if (Input::KeyHeld(SDLK_l)) globalCam->Move(4, 0);
	}
}

void ClassName::Render(float interpolation)
{
	if (_level != nullptr)
		_level->RenderAll(interpolation, -globalCam->x(), -globalCam->y());

    _entities.RenderAll(interpolation, -globalCam->x(), -globalCam->y());
}

void ClassName::AddLevel(std::string name)
{
	Level* newLevel = new Level(name);

	if (!newLevel->LoadLevel())
	{
		std::cout << "Error: Could not add level! Level was not found" << std::endl;
	}
	else
	{
		AddLevel(newLevel);
	}
}

void ClassName::AddLevel(Level* level)
{
	//_levelList.push_back(level);
}

void ClassName::ChangeLevel(std::string name)
{
	if (_level == nullptr || name != _level->GetFileName()) {
		Level* newLevel = new Level(name);

		if (!newLevel->LoadLevel())
		{
			std::cout << "Error: Could not add level! Level was not found" << std::endl;
			//_level = new Level("mine_level");
		}
		else
		{
			if (_level != nullptr) 
				delete _level;

			//AddLevel(newLevel);
			_level = newLevel;
		}
	}
}

Level* ClassName::GetLevel()
{
	return _level;
}

void ClassName::Restart()
{
	if (_level != nullptr)
		_level->LoadLevel();
}

#ifdef ClassName
#undef ClassName
#endif
