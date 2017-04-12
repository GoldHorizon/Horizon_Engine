
// Inspired by Game Dev Geek
// http://gamedevgeek.com/tutorials/managing-game-states-in-c/ 
// and
// https://sourcemaking.com/design_patterns/singleton/cpp/1 

class GameState
{
	/*
	 * Constructors/Destructors
	 */
    protected: GameState() {}
public:
	/*
	 * Class Methods
	 */
    virtual void Initialize() = 0;
    virtual void Cleanup() = 0;

    virtual void Pause() = 0;
    virtual void Resume() = 0;

    virtual void HandleEvents() = 0;
    virtual void Update() = 0;
    virtual void Draw() = 0;

    void ChangeState (GameState* nextState)
    {
        // Send signal to GameStateManager to change state.
    }

    // Note: This may need to go in derived GameState classes...not sure yet
    static GameState* Instance()
    {
        if (thisInstance == nullptr)
        {
            thisInstance = new GameState;
        }
        return thisInstance;
    }

private:
    static GameState* thisInstance;
}

// Initiate global instance to nullptr
GameState* GameState::thisInstance = nullptr;
