#include <SDL.h>

class Event
{
	public:
		/*
		 * Constructors/Destructors
		 */
		Event();
		~Event();

		/*
		 * Class Methods
		 */
		void Reset();
		void Block();

		/*
		 * Get Methods
		 */
		bool blocked();

		/*
		 * Set Methods
		 */

		/*
		 * Public Attributes
		 */
		SDL_Event ev;

	private:
		bool _blocked;
};
