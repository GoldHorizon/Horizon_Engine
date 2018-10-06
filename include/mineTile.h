#pragma once

#include "entity.h"

class MineTile : public Entity
{
	public:
		/*
		 * Constructors/Destructors
		 */
		MineTile();
		~MineTile();

		/*
		 * Class Methods
		 */
		void HandleEvents(SDL_Event* e);
		void Update();

		void RevealTile();

		/*
		 * Get Methods
		 */
		bool clicked();
		bool flagged();
		bool bomb();
		int  count();

		/*
		 * Set Methods
		 */
		void SetClicked(bool c);
		void SetFlagged(bool f);
		void SetBomb(bool b);
		void SetCount(int c);

	private:
		bool _clicked;
		bool _flagged;
		bool _bomb;
		int  _count;
};
