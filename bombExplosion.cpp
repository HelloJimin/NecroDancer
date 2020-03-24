#include "stdafx.h"
#include "bombExplosion.h"


bombExplosion::bombExplosion()
{
}

bombExplosion::bombExplosion(int tileNum, tagTile tile[])
{
	_tile = tile;
	_tileNum = tileNum;
	_img = IMAGEMANAGER->findImage("气藕局聪");

	_frameX = 0;
}


bombExplosion::~bombExplosion()
{
}

void bombExplosion::update()
{
	if (BEAT->getCnt() % 29 == 0)
	{
		_frameX++;

		if (_frameX > _img->getMaxFrameX())
		{
			_trigger = true;
		}
	}

	if (_trigger)
	{
		SOUNDMANAGER->play("bomb");
		EFFECTMANAGER->play("气藕气惯", _tile[_tileNum].x, _tile[_tileNum].y);

		int dx[] = { 0, -1, 1, TILEX, TILEX - 1, TILEX + 1, -TILEY, -(TILEY - 1), -(TILEY + 1) };

		for (int i = 0; i < 9; i++)
		{
			int check = _tileNum + dx[i];

			for (int k = 0; k < MONSTERMANAGER->getMonster().size(); k++)
			{
				if (check == MONSTERMANAGER->getMonster()[k]->currentTile())
				{
					MONSTERMANAGER->getMonster()[k]->hit(3);
				}
			}
			if (_tile[check].obj != OBJ_IRONWALL &&
				_tile[check].obj != OBJ_NEXT &&
				_tile[check].obj != OBJ_BLOCK )
			{	
				_tile[check].obj = OBJ_NONE;
				_tile[check].strength = 0;
				_tile[check].ray = 0;
				_tile[check].itemPoint = "";
				_tile[check].walkable = true;
			}
			if (check == PLAYER->currentTile())
			{
				PLAYER->hit(3);
			}
		}
	}
}

void bombExplosion::render(HDC hdc)
{
	//if (!_tile[_tileNum].look) return;

	_img->frameRender(hdc, _tile[_tileNum].rc.left+10, _tile[_tileNum].rc.top, _frameX, 0);
}
