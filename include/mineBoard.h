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
		void ClearBoard();

		/*
		 * Get Methods
		 */

		/*
		 * Set Methods
		 */

	private:
		char *_testBoard;
		MineTile *_board;
		
		int _boardWidth;
		int _boardHeight;
};
