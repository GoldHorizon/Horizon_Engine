#pragma once

#include "mineTile.h"

const int BOARD_WIDTH = 10;
const int BOARD_HEIGHT = 10;

class MineBoard
{
	public:
		/*
		 * Constructors/Destructors
		 */
		//MineBoard();
		//~MineBoard();

		/*
		 * Class Methods
		 */
		void InitTestBoard(int startx = -1, int starty = -1);
		void PrintTestBoard();

		/*
		 * Get Methods
		 */

		/*
		 * Set Methods
		 */

	private:
		char _testBoard[BOARD_WIDTH][BOARD_HEIGHT];
};
