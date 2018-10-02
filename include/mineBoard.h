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
		//char *_testBoard;
		MineTile *_board;
		
		int _boardWidth;
		int _boardHeight;
};
