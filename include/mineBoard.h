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

		void CreateBoard(int sizex, int sizey);
		void GenerateBombs(int startx, int starty);
		void SetTileCounters();

		void ClickTile(int x, int y);
		void ClearBoard();
		MineTile& GetTile(int x, int y);

		void InitTestBoard(int startx, int starty, int sizex, int sizey);
		void PrintTestBoard();

		/*
		 * Get Methods
		 */
		int width();
		int height();
		bool generated();
		bool ended();

		/*
		 * Set Methods
		 */
		void SetGenerated(bool g);
		void SetEnded(bool e);

	private:
		MineTile *_board;
		
		int _boardWidth;
		int _boardHeight;

		int _bombCount;
		int _tilesLeft;

		bool _generated;
		bool _ended;
};
