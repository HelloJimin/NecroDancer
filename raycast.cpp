#include "stdafx.h"
#include "raycast.h"


raycast::raycast()
{
}


raycast::~raycast()
{
}

void raycast::init()
{
	tile = PLAYER->getMap();
}

void raycast::update()
{
	reset();

	pTile = PLAYER->currentTile();
	open.push_back(pTile);
	
	int power = 5;
	int ray = 1;

	int dx[] = { -1, 1, TILEX, -TILEY };

	ok = true;

	while (ok)
	{
		for (int i = 0; i < open.size(); ++i)
		{
			for (int k = 0; k < 4;++k)
			{
				if (tile[open[i] + dx[k]].ray > 0) continue;

				if (wallCheck(open[i] + dx[k]))
				{
					tile[open[i] + dx[k]].look = true;
					tile[open[i] + dx[k]].ray = ray;
					
					if(tile[open[i] + dx[k]].walkable) temp.push_back(open[i] + dx[k]);
				}
			}
		}

		swap(open, temp);
		temp.clear();

		if (ray == power)ok = false;

		ray++;
	}
}

void raycast::reset()
{
	open.clear();
	temp.clear();

	for (int i = 0; i < TILEX*TILEX; i++)
	{
		if (tile[i].ray == 0) continue;
			
		tile[i].ray = 0;
	}
}

bool raycast::wallCheck(int tileNum)
{
	if (tile[tileNum].obj == OBJ_NOMALWALL) false;
	if (tile[tileNum].obj == OBJ_SKULLWALL) false;
	if (tile[tileNum].obj == OBJ_WHITEWALL) false;
	if (tile[tileNum].obj == OBJ_GOLDWALL) false;
	if (tile[tileNum].obj == OBJ_IRONWALL) false;
	if (tile[tileNum].obj == OBJ_NEVERWALL) false;
	return true;
}
