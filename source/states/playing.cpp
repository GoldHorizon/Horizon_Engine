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

	ChangeLevel("test_file.txt");

	globalCam->origin = (Align::MID_C);
	globalCam->SetPosition(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);

	//AddLevel("another_test.txt");
	
	Panel* testPanel = new Panel();
	testPanel->SetPosition(64, 64);
	testPanel->SetTitle("Test Panel");
	_entities.AddEntity(testPanel);

	Panel* testPanel2 = new Panel();
	testPanel2->SetPosition(400, 64);
	testPanel2->SetTitle("Panel 2");
	_entities.AddEntity(testPanel2);

    //Player* mainPlayer = new Player();
    //mainPlayer->SetName("MainPlayer");
	//mainPlayer->SetDepth(-20);
    //_entities.AddEntity(mainPlayer);

    //Ball* testBall = new Ball();
    //testBall->SetPosition(128, 128);
    //testBall->SetDepth(-10);
    //testBall->SetName("TestBall");
    //_entities.AddEntity(testBall);

	//// Test loading fonts/texts
	//Text* testTextLabel = new Text("This is just a test label!!!", defaultFont);
	//testTextLabel->SetPosition({ 600, 300 });
	//testTextLabel->SetMaxWidth(128);
	//testTextLabel->SetWrap(true);
	//testTextLabel->SetDepth(-40);
	//_entities.AddEntity(testTextLabel);
	// End test loading fonts/texts


	//File testFile;
	//sVector* svp = testFile.GetDataVector();

	//testFile.OpenFile("test_file.txt", false, true);

	//svp->push_back(mainPlayer->Serialize());

	//testFile.WriteFileData();

	//testFile.CloseFile();

	//sVector* testV;
	//testV = ParseSerializedString(testTextLabel->Serialize());

	//for (int i = 0; i < testV->size(); i++)
	//{
	//	std::cout << (*testV)[i] << std::endl;
	//}
	//delete testV;

	//svp->clear();

	//testFile.OpenFile("test_file.txt");

	//testFile.ReadFileAll();
	//testFile.PrintData();

	// Base unserialization loop
	//for (int i = 0; i < svp->size(); i++)
	//{
	//	Entity* test = nullptr;
	//	test = CreateSerializedObject((*svp)[i]);
	//	if (test == nullptr)
	//		std::cout << "Error: Could not create serialized object from string " << i << " (returned -1 to playing.cpp)" << std::endl;
	//	else
	//		_entities.AddEntity(test);
	//}

	//testBall		->Unserialize((*svp)[1]);

	//testFile.CloseFile();
	//// End testing file Input/Output
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

	_level->HandleAllEvents(event);

//	const Uint8 *state = SDL_GetKeyboardState(NULL);
//
//	if (state[SDL_SCANCODE_ESCAPE])
//	{
//		return OPEN_MENU;
//	}

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
	//else if (event.ev.type == SDL_MOUSEBUTTONDOWN)
	//{
	//	std::cout << "DEBUG: Mouse press in playing state" << std::endl;
	//}

	return -1;
}

void ClassName::Update()
{
	if (!IsPaused())
	{
		_entities.UpdateAll();

		_level->UpdateAll();

		if (Input::KeyHeld(SDLK_h)) globalCam->Move(-4, 0);
		if (Input::KeyHeld(SDLK_j)) globalCam->Move(0, 4);
		if (Input::KeyHeld(SDLK_k)) globalCam->Move(0, -4);
		if (Input::KeyHeld(SDLK_l)) globalCam->Move(4, 0);
	}
}

void ClassName::Render(float interpolation)
{
	_level->RenderAll(interpolation, -globalCam->x(), -globalCam->y());

    _entities.RenderAll(interpolation, -globalCam->x(), -globalCam->y());
}

void ClassName::AddLevel(std::string name)
{
	Level* newLevel = new Level(name);

	if (!newLevel->LoadFromFile())
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
		if (_level == nullptr) delete _level;

		Level* newLevel = new Level(name);

		if (!newLevel->LoadFromFile())
		{
			std::cout << "Error: Could not add level! Level was not found" << std::endl;
			_level = new Level("mine_level");
		}
		else
		{
			//AddLevel(newLevel);
			_level = newLevel;
		}
	}
}

Level* ClassName::GetLevel()
{
	return _level;
	//if (_levelList.size() == 1)
	//{
	//	return _levelList[0];
	//}
	//if (_levelList.size() == 0)
	//{
	//	std::cout << "Error: No level in level list" << std::endl;
	//}
	//else if (_levelList.size() > 1)
	//{
	//	std::cout << "Error: More than 1 level in level list" << std::endl;
	//}

	//return nullptr;
}

void ClassName::Restart()
{
	//for (int i = 0; i < _levelList.size(); i++)
	//{
	//	_levelList[i]->LoadFromFile();
	//}

	_level->LoadFromFile();
}

#ifdef ClassName
#undef ClassName
#endif
