#include "Board.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include "tile.h"
#include "Random.h"
#include "TextureManager.h"
using namespace std;


//constructors


Board::Board()
{
	smile.setTexture(TextureManager::GetTexture("face_happy"));
	winFace.setTexture(TextureManager::GetTexture("face_win"));
	lossFace.setTexture(TextureManager::GetTexture("face_lose"));
	debugButton.setTexture(TextureManager::GetTexture("debug"));
	test1Butt.setTexture(TextureManager::GetTexture("test_1"));
	test2Butt.setTexture(TextureManager::GetTexture("test_2"));
	test3Butt.setTexture(TextureManager::GetTexture("test_3"));
}

//getters
int Board::GetWidth()
{
	return width;
}

int Board::GetTileWidth()
{
	return tileWidth;
}

int Board::GetHeight()
{
	return height;
}

int Board::GetTileHeight()
{
	return tileHeight;
}

int Board::GetMines()
{
	return mineCount;
}

int Board::GetTiles()
{
	return tileCount;
}

void Board::SetStats(int w, int h, int mc)
{
	tileWidth = w;
	tileHeight = h;
	width = w * 32;
	height = (h * 32) + 100;
	tileCount = (w * h);
	mineCount = mc;
	configMineCount = mc;

	for (int i = 0; i < tileCount; i++)
	{
		tile newTile;
		tiles.push_back(newTile);
	}

	int tileCnt = 0;
	for (int i = 0; i < tileHeight; i++)
	{
		for (int j = 0; j < tileWidth; j++)
		{
			tiles[tileCnt].x = j;
			tiles[tileCnt].y = i;
			//cout << tiles[tileCount].x << ", " << tiles[tileCount].y << endl;
			tileCnt++;
		}
	}

	

	GenerateBombPlacement(mineCount);

	
	
	
	cout << "width " << width << endl;
	cout << "height " << height << endl;
	cout << "minecount " << mineCount << endl;
	cout << "tileCount" << tileCount << endl;
	//cout << tiles.size() << endl;
}

void Board::GenerateBombPlacement(int mc)
{
	vector<int> bombplacement;
	int count = 0;
	while (bombplacement.size() != mc)
	{
		int tileVal = Random::Number(0, tileCount-1);

		if (count > 0)
		{
			for (unsigned int j = 0; j < bombplacement.size(); j++)
			{
				if (tileVal == bombplacement[j])
				{
					continue;
				}
			}
		}
		count++;
		bombplacement.push_back(tileVal);
		cout << "bomb placed at tile " << tileVal << endl;
	}
	cout << bombplacement.size() << endl;

	
	for (int i = 0; i < bombplacement.size(); i++)
	{
		int where = bombplacement[i];
		tiles[where].setBomb();
	}

	NumbersReset();
	ValuesForTileCounter();
	mineCount = bombplacement.size();
}

void Board::loadBoard(int board)
{
	if (board == 4)
	{
		CoverBoard();
		ClearBoard();
		GenerateBombPlacement(configMineCount);
		ValuesForTileCounter();
		loss = false;
		win = false;
		return;
	}

	if (board == 0)
	{
	if (debugMode == true && loss != true && win != true)
	{
		debugMode = false;
		cout << "Debug mode off!" << endl;
	}
	else if (debugMode == false && loss != true && win != true)
	{
		debugMode = true;
		cout << "Debug mode on!" << endl;
	}

	return;
	}

	board = board;

	ClearBoard();
	string fileName = "boards/testboard" + to_string(board) + ".brd";
	

	vector<char> bombPlacement;
	mineCount = 0;
	ifstream inFile(fileName);
	if (inFile.is_open())
	{
		cout << "test file opened!" << endl;
		string line = "null";
		istringstream stream(line);
		string data = "null";
		while (inFile >> data)
		{
			cout << data << endl;
			for (int i = 0; i < data.length(); i++)
			{
				char  c = data.at(i);
				bombPlacement.push_back(c);
			}
		}


		for (int i = 0; i < bombPlacement.size(); i++)
		{
			if (bombPlacement[i] == '1')
			{
				tiles[i].setBomb();
				mineCount++;
			}

		}

		NumbersReset();
		ValuesForTileCounter();
	}
	
	else
	{
		cout << "test file could not open!" << endl;
	}
	loss = false;
	win = false;



}

void Board::CoverBoard()
{
	for (int i = 0; i < tiles.size(); i++)
	{
		tiles[i].isCovered = true;
	}
}

void Board::ClearBoard()
{
	for (int i = 0; i < tiles.size(); i++)
	{
		tiles[i].bombStatus = false;
		
			tiles[i].isFlagged = false;
		
	}
	flagCount = 0;

}

bool Board::CheckWin()
{
	win = true;
	for (int i = 0; i < tiles.size(); i++)
	{
		if (tiles[i].isCovered == true && tiles[i].bombStatus == false)
		{
			win = false;
		}

	}
	if (win == true)
	{
		for (int i = 0; i < tiles.size(); i++)
		{
			if (tiles[i].bombStatus == true)
			{
				tiles[i].isFlagged = true;
				flagCount++;
			}
		}

	}
	

	return win;
}

void Board::SetPointers()
{
	for (int i = 0; i < tileCount; i++)
	{
		
		if (tiles[i].tileType == "middle")
		{
			for (int j = 0; j < tileCount; j++)
			{
				//top left
				if (((tiles[i].x) - 1 == tiles[j].x) && (tiles[i].y) - 1 == tiles[j].y)
				{
					tiles[i].tl = & tiles[j];
				}
				//top middle
				else if (((tiles[i].x) == tiles[j].x) && (tiles[i].y) - 1 == tiles[j].y)
				{
					tiles[i].tm = & tiles[j];
				}
				//top right
				else if (((tiles[i].x) + 1 == tiles[j].x) && (tiles[i].y) - 1 == tiles[j].y)
				{
					tiles[i].tr = & tiles[j];
				}
				//middle left
				else if (((tiles[i].x) - 1 == tiles[j].x) && (tiles[i].y) == tiles[j].y)
				{
					tiles[i].ml = &tiles[j];
				}
				//middle right
				else if (((tiles[i].x) + 1 == tiles[j].x) && (tiles[i].y) == tiles[j].y)
				{
					tiles[i].mr = &tiles[j];
				}
				//bottom left
				else if (((tiles[i].x) - 1 == tiles[j].x) && (tiles[i].y) + 1 == tiles[j].y)
				{
					tiles[i].bl = &tiles[j];
				}
				//bottom middle
				else if (((tiles[i].x) == tiles[j].x) && (tiles[i].y) + 1 == tiles[j].y)
				{
					tiles[i].bm = &tiles[j];
				}

				//bottom right
				else if (((tiles[i].x) +  1 == tiles[j].x) && (tiles[i].y) + 1 == tiles[j].y)
				{
					tiles[i].br = &tiles[j];
				}
				
			}
		}


		else if (tiles[i].tileType == "tlc")
		{
			for (int j = 0; j < tileCount; j++)
			{
				
				
				//middle right
				if (((tiles[i].x) + 1 == tiles[j].x) && (tiles[i].y) == tiles[j].y)
				{
					tiles[i].mr = &tiles[j];
				}
				//bottom middle
				else if (((tiles[i].x) == tiles[j].x) && (tiles[i].y) + 1 == tiles[j].y)
				{
					tiles[i].bm = &tiles[j];
				}

				//bottom right
				else if (((tiles[i].x) + 1 == tiles[j].x) && (tiles[i].y) + 1 == tiles[j].y)
				{
					tiles[i].br = &tiles[j];
				}
			}
		}

		else if (tiles[i].tileType == "trc")
		{
			for (int j = 0; j < tileCount; j++)
			{
				
				//middle left
				if (((tiles[i].x) - 1 == tiles[j].x) && (tiles[i].y) == tiles[j].y)
				{
					tiles[i].ml = &tiles[j];
				}
				
				//bottom left
				else if (((tiles[i].x) - 1 == tiles[j].x) && (tiles[i].y) + 1 == tiles[j].y)
				{
					tiles[i].bl = &tiles[j];
				}
				//bottom middle
				else if (((tiles[i].x) == tiles[j].x) && (tiles[i].y) + 1 == tiles[j].y)
				{
					tiles[i].bm = &tiles[j];
				}

				
				
			}
		}
		else if (tiles[i].tileType == "blc")
		{
			for (int j = 0; j < tileCount; j++)
			{
				
				
				//top middle
				 if (((tiles[i].x) == tiles[j].x) && (tiles[i].y) - 1 == tiles[j].y)
				{
					tiles[i].tm = &tiles[j];
				}
				//top right
				else if (((tiles[i].x) + 1 == tiles[j].x) && (tiles[i].y) - 1 == tiles[j].y)
				{
					tiles[i].tr = &tiles[j];
				}
				
				//middle right
				else if (((tiles[i].x) + 1 == tiles[j].x) && (tiles[i].y) == tiles[j].y)
				{
					tiles[i].mr = &tiles[j];
				}
								
			}
		}

		else if (tiles[i].tileType == "brc")
		{
			for (int j = 0; j < tileCount; j++)
			{
				//top left
				if (((tiles[i].x) - 1 == tiles[j].x) && (tiles[i].y) - 1 == tiles[j].y)
				{
					tiles[i].tl = &tiles[j];
				}
				//top middle
				else if (((tiles[i].x) == tiles[j].x) && (tiles[i].y) - 1 == tiles[j].y)
				{
					tiles[i].tm = &tiles[j];
				}
				
				//middle left
				else if (((tiles[i].x) - 1 == tiles[j].x) && (tiles[i].y) == tiles[j].y)
				{
					tiles[i].ml = &tiles[j];
				}			
				
			}
		}

		else if (tiles[i].tileType == "ls")
		{
			for (int j = 0; j < tileCount; j++)
			{
				
				
				//top middle
				 if (((tiles[i].x) == tiles[j].x) && (tiles[i].y) - 1 == tiles[j].y)
				{
					tiles[i].tm = &tiles[j];
				}
				//top right
				else if (((tiles[i].x) + 1 == tiles[j].x) && (tiles[i].y) - 1 == tiles[j].y)
				{
					tiles[i].tr = &tiles[j];
				}
				
				//middle right
				else if (((tiles[i].x) + 1 == tiles[j].x) && (tiles[i].y) == tiles[j].y)
				{
					tiles[i].mr = &tiles[j];
				}
				
				//bottom middle
				else if (((tiles[i].x) == tiles[j].x) && (tiles[i].y) + 1 == tiles[j].y)
				{
					tiles[i].bm = &tiles[j];
				}

				//bottom right
				else if (((tiles[i].x) + 1 == tiles[j].x) && (tiles[i].y) + 1 == tiles[j].y)
				{
					tiles[i].br = &tiles[j];
				}
			}
		}

		else if (tiles[i].tileType == "rs")
		{
			for (int j = 0; j < tileCount; j++)
			{
				//top left
				if (((tiles[i].x) - 1 == tiles[j].x) && (tiles[i].y) - 1 == tiles[j].y)
				{
					tiles[i].tl = &tiles[j];
				}
				//top middle
				else if (((tiles[i].x) == tiles[j].x) && (tiles[i].y) - 1 == tiles[j].y)
				{
					tiles[i].tm = &tiles[j];
				}
				
				//middle left
				else if (((tiles[i].x) - 1 == tiles[j].x) && (tiles[i].y) == tiles[j].y)
				{
					tiles[i].ml = &tiles[j];
				}
				
				//bottom left
				else if (((tiles[i].x) - 1 == tiles[j].x) && (tiles[i].y) + 1 == tiles[j].y)
				{
					tiles[i].bl = &tiles[j];
				}
				//bottom middle
				else if (((tiles[i].x) == tiles[j].x) && (tiles[i].y) + 1 == tiles[j].y)
				{
					tiles[i].bm = &tiles[j];
				}
				
			}
		}

		else if (tiles[i].tileType == "ts")
		{
			for (int j = 0; j < tileCount; j++)
			{	
				
				//middle left
				if (((tiles[i].x) - 1 == tiles[j].x) && (tiles[i].y) == tiles[j].y)
				{
					tiles[i].ml = &tiles[j];
				}
				//middle right
				else if (((tiles[i].x) + 1 == tiles[j].x) && (tiles[i].y) == tiles[j].y)
				{
					tiles[i].mr = &tiles[j];
				}
				//bottom left
				else if (((tiles[i].x) - 1 == tiles[j].x) && (tiles[i].y) + 1 == tiles[j].y)
				{
					tiles[i].bl = &tiles[j];
				}
				//bottom middle
				else if (((tiles[i].x) == tiles[j].x) && (tiles[i].y) + 1 == tiles[j].y)
				{
					tiles[i].bm = &tiles[j];
				}

				//bottom right
				else if (((tiles[i].x) + 1 == tiles[j].x) && (tiles[i].y) + 1 == tiles[j].y)
				{
					tiles[i].br = &tiles[j];
				}
			}
		}

		else if (tiles[i].tileType == "bs")
		{
			for (int j = 0; j < tileCount; j++)
			{
				//top left
				if (((tiles[i].x) - 1 == tiles[j].x) && (tiles[i].y) - 1 == tiles[j].y)
				{
					tiles[i].tl = &tiles[j];
				}
				//top middle
				else if (((tiles[i].x) == tiles[j].x) && (tiles[i].y) - 1 == tiles[j].y)
				{
					tiles[i].tm = &tiles[j];
				}
				//top right
				else if (((tiles[i].x) + 1 == tiles[j].x) && (tiles[i].y) - 1 == tiles[j].y)
				{
					tiles[i].tr = &tiles[j];
				}
				//middle left
				else if (((tiles[i].x) - 1 == tiles[j].x) && (tiles[i].y) == tiles[j].y)
				{
					tiles[i].ml = &tiles[j];
				}
				//middle right
				else if (((tiles[i].x) + 1 == tiles[j].x) && (tiles[i].y) == tiles[j].y)
				{
					tiles[i].mr = &tiles[j];
				}
				
			}
		}
	}
}

void Board::NumbersReset()
{
	for (int i = 0; i < tileCount; i++)
	{
		tiles[i].setTileType(tileHeight, tileWidth );
	}

	SetPointers();

	for (int i = 0; i < tileCount; i++)
	{
		tiles[i].countSurroundingBombs();
		tiles[i].isCovered = true;
	}
}

void Board::LossActions()
{
	loss = true;
	
}

void Board::ValuesForTileCounter()
{
	int value = mineCount - flagCount;

	if (mineCount < flagCount)
	{
		pos = false;
		value = flagCount - mineCount;
		value = abs(value);
	}
	else if (mineCount > flagCount || mineCount == flagCount  )
	{
		pos = true;
	}

	hundredsPlace = value / 100;
	tensPlace = (value - (hundredsPlace * 100)) / 10;
	onesPlace = (value - (hundredsPlace * 100) - (tensPlace * 10)) / 1;

}