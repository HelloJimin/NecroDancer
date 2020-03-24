#include "stdafx.h"
#include "raycast.h"


raycast::raycast()
{
}


raycast::~raycast()
{
}

void raycast::init(tagTile _tile[])
{
	tile = _tile;
}

void raycast::torch(int startTile)
{
	open.clear();
	temp.clear();

	pTile = startTile;
	open.push_back(pTile);

	int power = 2;
	int ray = 1;

	int dx[] = { -1, 1, TILEX, -TILEY };

	ok = true;

	while (ok)
	{
		for (int i = 0; i < open.size(); ++i)
		{
			int check = 0;

			for (int k = 0; k < 4; ++k)
			{
				int checkTile = open[i] + dx[k];
				if (tile[checkTile].look) check++;
				if (check >= 2) tile[open[i]].look = true;

				//if (tile[checkTile].ray > 0) continue;

				tile[checkTile].look = true;
				tile[checkTile].ray = ray;

				//if (tile[checkTile].walkable) temp.push_back(checkTile);

				if (wallCheck(checkTile))
				{
				}
				else
				{
					temp.push_back(checkTile);
				}
			}
		}

		swap(open, temp);
		temp.clear();

		if (ray == power)ok = false;

		ray++;
	}
}

void raycast::playerRay(int startTile, int rayPower)
{
	reset();

	pTile = startTile;
	open.push_back(pTile);

	int power = 5 + rayPower;
	int ray = 1;

	int dx[] = { -1, 1, TILEX, -TILEY };

	ok = true;

	while (ok)
	{
		for (int i = 0; i < open.size(); ++i)
		{
			int check = 0;

			for (int k = 0; k < 4; ++k)
			{
				int checkTile = open[i] + dx[k];

				if (tile[checkTile].look) check++;
				if (check >= 2) tile[open[i]].look = true;

				if (tile[checkTile].ray > 0) continue;

				tile[checkTile].look = true;
				tile[checkTile].ray = ray;


				if (wallCheck(checkTile))
				{
				}
				else
				{
					temp.push_back(checkTile);
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
	if (tile[tileNum].obj == OBJ_NOMALWALL) return true;
	if (tile[tileNum].obj == OBJ_SKULLWALL) return true;
	if (tile[tileNum].obj == OBJ_WHITEWALL) return true;
	if (tile[tileNum].obj == OBJ_GOLDWALL)  return true;
	if (tile[tileNum].obj == OBJ_IRONWALL)  return true;
	if (tile[tileNum].obj == OBJ_NEVERWALL) return true;
	if (tile[tileNum].obj == OBJ_DOOR) return true;
	return false;
}