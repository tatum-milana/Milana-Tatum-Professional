#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <iostream>
#include "TextureManager.h"

using namespace std;

class tile
{

public:

	sf::Sprite tileCover;
	sf::Sprite bomb;
	sf::Sprite flag;
	sf::Sprite number;
	sf::Sprite tileBackground;


	bool isFlagged = false;
	bool bombStatus = false;
	bool hasNum = false;
	bool isCovered = true;
	int x = 0;
	int y = 0;

	int bombCount = 0;

	string tileType = "null";

	// pointer collection
	//counting around the central node clockwise order
	tile* tl = nullptr;
	tile* tm = nullptr;
	tile* tr = nullptr;
	tile* ml = nullptr;
	tile* mr = nullptr;
	tile* bl = nullptr;
	tile* bm = nullptr;
	tile* br = nullptr;

	
	tile();
	void setBomb();
	void setTileType(int bottomBound, int rightBound);
	void countSurroundingBombs();
	void setNumberSprite();

	void revealTile();
	
};



