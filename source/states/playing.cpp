#include "../../include/states/playing.h"
#include "../../include/ball.h"
#include "../../include/player.h"
#include "../../include/font.h"
#include "../../include/text.h"
#include "file.h"
#include "engineMethods.h"
#include "globals.h"

#define ClassName StatePlaying

ClassName* ClassName::_thisInstance = nullptr;

ClassName::~ClassName()
{
	Cleanup();
}

void ClassName::Initialize()
{
    //Player* mainPlayer = new Player();
    //mainPlayer->SetName("MainPlayer");
	//mainPlayer->SetDepth(-20);
    //_entities.AddEntity(mainPlayer);

    //Ball* testBall = new Ball();
    //testBall->SetPosition(128, 128);
    //testBall->SetDepth(-10);
    //testBall->SetName("TestBall");
    //_entities.AddEntity(testBall);

    //Ball* testBall2 = new Ball();
    //testBall2->SetPosition(256, 512);
    //testBall2->SetDepth(10);
    //testBall2->SetName("TestBall2");
    //_entities.AddEntity(testBall2);

	//// Test loading fonts/texts
	//Text* testTextLabel = new Text("This is just a test label!!!", defaultFont);
	//testTextLabel->SetPosition({ 600, 300 });
	//testTextLabel->SetMaxWidth(128);
	//testTextLabel->SetWrap(true);
	//testTextLabel->SetDepth(-40);
	//_entities.AddEntity(testTextLabel);
	// End test loading fonts/texts


	//// Begin testing file input/output
	File testFile;
	sVector* svp = testFile.GetDataVector();

	//testFile.OpenFile("test_file.txt", false, true);

	//// I/O here
	//std::cout << "Entering serialize method" << std::endl;
	//
	//svp->push_back(mainPlayer->Serialize());
	//svp->push_back(testBall->Serialize());
	//svp->push_back(testBall2->Serialize());
	//svp->push_back(testTextLabel->Serialize());

	//testFile.WriteFileData();

	//testFile.CloseFile();
	//testFile.PrintData();

	//sVector* testV;
	//testV = ParseSerializedString(testTextLabel->Serialize());

	//for (int i = 0; i < testV->size(); i++)
	//{
	//	std::cout << (*testV)[i] << std::endl;
	//}
	//delete testV;

	//svp->clear();

	testFile.OpenFile("test_file.txt");

	testFile.ReadFileAll();
	testFile.PrintData();

	// Base unserialization loop
	for (int i = 0; i < svp->size(); i++)
	{
		Entity* test = nullptr;
		test = CreateSerializedObject((*svp)[i]);
		if (test == nullptr)
			std::cout << "Error: Could not create serialized object from string " << i << " (returned -1 to playing.cpp)" << std::endl;
		else
			_entities.AddEntity(test);
	}

	//mainPlayer		->Unserialize((*svp)[0]);
	//testBall		->Unserialize((*svp)[1]);
	//testBall2		->Unserialize((*svp)[2]);
	//testTextLabel	->Unserialize((*svp)[3]);

	testFile.CloseFile();
	//// End testing file Input/Output
}

void ClassName::Cleanup()
{
	while (_entities.GetCount() > 0)
	{
		_entities.RemoveByIndex(0);
	}
}

int ClassName::HandleEvents(SDL_Event* event)
{
	_entities.HandleAllEvents(event);

//	const Uint8 *state = SDL_GetKeyboardState(NULL);
//
//	if (state[SDL_SCANCODE_ESCAPE])
//	{
//		return OPEN_MENU;
//	}

	if (event->type == SDL_KEYDOWN)
	{
		switch (event->key.keysym.sym)
		{
		case SDLK_ESCAPE:
			if (event->key.repeat == 0)
				return OPEN_MENU;
		}
	}

	return -1;
}

void ClassName::Update()
{
	if (!IsPaused())
		_entities.UpdateAll();
}

void ClassName::Render(float interpolation)
{
    _entities.RenderAll(interpolation);
}

#ifdef ClassName
#undef ClassName
#endif
