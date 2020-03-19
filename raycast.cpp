#include "stdafx.h"
#include "raycast.h"


raycast::raycast()
{
}


raycast::~raycast()
{
}

void raycast::update()
{
	reset();

	vector<int> open;
	vector<int> temp;
	tagTile* tile = PLAYER->getMap();
	int pTile = PLAYER->currentTile();
	
	open.push_back(pTile);
	int power = 3;

	int dx[] = { -1, 1, TILEX, -TILEY };
	bool ok = true;

	int ray = 1;
	while (ok)
	{

		for (int i = 0; i < open.size(); ++i)
		{

			for (int k = 0; k < 4;++k)
			{
				if (tile[open[i] + dx[k]].ray == 0 && tile[open[i] + dx[k]].walkable)
				{

					tile[open[i] + dx[k]].ray = ray;
				temp.push_back(open[i] + dx[k]);
				}
			}
		}

		swap(open, temp);
		temp.clear();

		if (ray == power)ok = false;

		ray++;

	}



}

void raycast::render(HDC hdc)
{
	tagTile* tile = PLAYER->getMap();
	char str[128];

	for (int i = 0; i < TILEX*TILEX; i++)
	{
		wsprintf(str, "%d", tile[i].ray);
		TextOut(hdc, tile[i].x, tile[i].y, str, strlen(str));
	}
}

void raycast::reset()
{
	tagTile* tile = PLAYER->getMap();
	for (int i = 0; i < TILEX*TILEX; i++)
	{
		if (tile[i].ray == 0) continue;
			
		tile[i].ray = 0;
	}
}
