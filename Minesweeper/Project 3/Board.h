#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <iostream>
#include "tile.h"
#include "TextureManager.h"
using namespace std;
class Board
{
	int width = 0;
	int tileWidth = 0;

	int height = 0;
	int tileHeight = 0;

	int tileCount = 0;
	int mineCount = 0;
	int configMineCount = 0;
	
	


public:
	vector<tile> tiles;

	bool win = false;
	bool loss = false;
	bool debugMode = false;
	int flagCount = 0;
	int hundredsPlace = 0;
	int tensPlace = 0;
	int onesPlace = 0;
	bool pos = true; // true = pos, false = neg


	sf::Sprite smile;
	sf::Sprite winFace;
	sf::Sprite lossFace;

	sf::Sprite debugButton;
	sf::Sprite test1Butt;
	sf::Sprite test2Butt;
	sf::Sprite test3Butt;

	sf::Sprite sign;
	sf::Sprite hudredsVis;
	sf::Sprite tensVis;
	sf::Sprite onesVis;

//basic data
	
	Board();

	int GetWidth();
	int GetTileWidth();
	int GetHeight();
	int GetTileHeight();
	int GetMines();
	int GetTiles();
	void SetStats(int w, int h, int mc);
	void loadBoard(int board);
	

	//building the board
	void GenerateBombPlacement(int mc);
	void CoverBoard();
	void ClearBoard();
	bool CheckWin();
	void SetPointers();
	void NumbersReset();
	void LossActions();

	void ValuesForTileCounter();
};

