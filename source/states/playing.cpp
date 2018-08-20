#include "../../include/states/playing.h"
#include "../../include/ball.h"
#include "../../include/player.h"
#include "../../include/font.h"
#include "../../include/text.h"
#include "file.h"

#define ClassName StatePlaying

ClassName* ClassName::_thisInstance = nullptr;

ClassName::~ClassName()
{
	Cleanup();
}

void ClassName::Initialize()
{
    Player* mainPlayer = new Player();
    mainPlayer->SetName("MainPlayer");
	mainPlayer->SetDepth(-20);
    _entities.AddEntity(mainPlayer);

    Ball* testBall = new Ball();
    testBall->SetPosition(128, 128);
    testBall->SetDepth(-10);
    testBall->SetName("TestBall");
    _entities.AddEntity(testBall);

    Ball* testBall2 = new Ball();
    testBall2->SetPosition(256, 512);
    testBall2->SetDepth(10);
    testBall2->SetName("TestBall2");
    _entities.AddEntity(testBall2);

	// Test loading fonts/texts
	Font* testFont = new Font("Test Font");
	testFont->LoadFont("assets/Inconsolata-Regular.ttf", 12);

	Text* testTextLabel = new Text("This is just a test label!!!", testFont);
	testTextLabel->SetPosition({ 128, 300 });
	testTextLabel->SetMaxWidth(128);
	testTextLabel->SetWrap(true);
	testTextLabel->SetDepth(-40);
	// End test loading fonts/texts

	_entities.AddEntity(testTextLabel);

	// Begin testing file input/output
	//File testFile;

	//testFile.OpenFile("test_file.txt", false, true);

	//// I/O here
	//sVector* svp = testFile.GetDataVector();
	//std::cout << "Entering serialize method" << std::endl;
	//
	//svp->push_back(mainPlayer->Serialize());
	//svp->push_back(testBall->Serialize());
	//svp->push_back(testBall2->Serialize());
	////svp->push_back(testTextLabel->Serialize());

	//testFile.WriteFileData();

	//testFile.CloseFile();
	//testFile.PrintData();
	//svp->clear();

	//testFile.OpenFile("test_file.txt");

	//testFile.ReadFileAll();
	//testFile.PrintData();

	//mainPlayer->Unserialize(svp->back());

	//testFile.CloseFile();
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
