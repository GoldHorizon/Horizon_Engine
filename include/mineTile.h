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

		void UpdateTile();
		void RevealTile();

		/*
		 * Get Methods
		 */
		bool clicked();
		bool bomb();
		int  count();

		/*
		 * Set Methods
		 */
		void SetClicked(bool c);
		void SetBomb(bool b);
		void SetCount(int c);

	private:
		bool _clicked;
		bool _bomb;
		int  _count;
};
