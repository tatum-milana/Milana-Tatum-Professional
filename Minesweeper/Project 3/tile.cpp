#include "tile.h"


tile::tile()
{
	tl = nullptr;
	tm = nullptr;
	tr = nullptr;
	ml = nullptr;
	mr = nullptr;
	bl = nullptr;
	bm = nullptr;
	br = nullptr;

	tileCover.setTexture(TextureManager::GetTexture("tile_hidden"));
	bomb.setTexture(TextureManager::GetTexture("mine"));
	flag.setTexture(TextureManager::GetTexture("flag"));
	number.setTexture(TextureManager::GetTexture("number_1"));
	tileBackground.setTexture(TextureManager::GetTexture("tile_revealed"));
	
}

void tile::setBomb()
{
	bombStatus = true;
}

void tile::setTileType(int bottomBound, int rightBound)
{
	if (x == 0)
	{
		if (y == 0) { tileType = "tlc"; }
		else if (y == bottomBound - 1) { tileType = "blc"; }
		else { tileType = "ls"; }
	}
	else if (x == rightBound-1)
	{
		if (y == 0) { tileType = "trc"; }
		else if (y == bottomBound-1) { tileType = "brc"; }
		else { tileType = "rs"; }
	}
	else if (y == 0)
	{
		tileType = "ts";
	}
	else if (y == bottomBound-1)
	{
		tileType = "bs";
	}
	else
	{
		tileType = "middle";
	}

	
}

void tile::countSurroundingBombs()
{
	bombCount = 0;
	if (tl != nullptr)
	{
		if (tl->bombStatus == true)
		{
			bombCount++;
		}
	}
	
	if (tm != nullptr)
	{
		if (tm->bombStatus == true)
		{
			bombCount++;
		}
	}

	if (tr != nullptr)
	{
		if (tr->bombStatus == true)
		{
			bombCount++;
		}
	}

	if (ml != nullptr)
	{
		if (ml->bombStatus == true)
		{
			bombCount++;
		}
	}

	if (mr != nullptr)
	{
		if (mr->bombStatus == true)
		{
			bombCount++;
		}
	}

	if (bl != nullptr)
	{
		if (bl->bombStatus == true)
		{
			bombCount++;
		}
	}

	if (bm != nullptr)
	{
		if (bm->bombStatus == true)
		{
			bombCount++;
		}
	}

	if (br != nullptr)
	{
		if (br->bombStatus == true)
		{
			bombCount++;
		}
	}

	setNumberSprite();

}


void tile::setNumberSprite()
{
	switch (bombCount)
	{
	case 1:
		number.setTexture(TextureManager::GetTexture("number_1"));
		break;
	case 2:
		number.setTexture(TextureManager::GetTexture("number_2"));
		break;
	case 3:
		number.setTexture(TextureManager::GetTexture("number_3"));
		break;
	case 4:
		number.setTexture(TextureManager::GetTexture("number_4"));
		break;
	case 5:
		number.setTexture(TextureManager::GetTexture("number_5"));
		break;
	case 6:
		number.setTexture(TextureManager::GetTexture("number_6"));
		break;
	case 7:
		number.setTexture(TextureManager::GetTexture("number_7"));
		break;
	case 8:
		number.setTexture(TextureManager::GetTexture("number_8"));
		break;
	
	}
}

void tile::revealTile()
{
	if (isCovered == false || isFlagged == true)
	{
		return;
	}
	isCovered = false;
	if (bombStatus == false && bombCount == 0)
	{
		if (tl != nullptr)
		{
			tl->revealTile();
		}

		if (tm != nullptr)
		{
			tm->revealTile();
		}

		if (tr != nullptr)
		{
			tr->revealTile();
		}

		if (ml != nullptr)
		{
			ml->revealTile();
		}

		if (mr != nullptr)
		{
			mr->revealTile();
		}

		if (bl != nullptr)
		{
			bl->revealTile();
		}

		if (bm != nullptr)
		{
			bm->revealTile();
		}

		if (br != nullptr)
		{
			br->revealTile();
		}
	}

}
