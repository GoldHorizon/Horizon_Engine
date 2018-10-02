#pragma once

#include "mineTile.h"
#include "entity.h"

class MineBoard : public Entity
{
	public:
		/*
		 * Constructors/Destructors
		 */
		MineBoard();
		~MineBoard();

		/*
		 * Class Methods
		 */
		void HandleEvents(SDL_Event* e);
		void Update();
		void Render(float interpolation, int xOffset = 0, int yOffset = 0);

		void InitTestBoard(int startx, int starty, int sizex, int sizey);
		void PrintTestBoard();
		void ClickTile(int x, int y);
		void ClearBoard();
		MineTile& GetTile(int x, int y);

		/*
		 * Get Methods
		 */
		int width();
		int height();

		/*
		 * Set Methods
		 */

	private:
		MineTile *_board;
		
		int _boardWidth;
		int _boardHeight;
};
