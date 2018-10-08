#include <SDL.h>

class Event
{
	public:
		Event();
		~Event();

		void Reset();

		SDL_Event* event();
		bool blocked();

		void SetEvent(SDL_Event* event);
		void SetBlocked(bool blocked = true);

	private:
		SDL_Event* _event;
		bool _blocked;
};
