#include "stdafx.h"
#include "greenSlime.h"


greenSlime::greenSlime()
{
}


greenSlime::~greenSlime()
{
}


HRESULT greenSlime::init(string name, int x, int y, int coin, tagTile * map)
{
	monster::init(name, x, y, coin, map);
	_atk = 0.5f;
	return S_OK;
}

void greenSlime::update()
{
	animation();
	frontCheck();

	hpSet();
	attack();
}

void greenSlime::frontCheck()
{
	if (BEAT->getCnt() % 58 == 0)
	{
		_tileX = _collisionRc.left / TILESIZE;
		_tileY = _collisionRc.top / TILESIZE;
		_currentTileIndex = _tileX + _tileY * TILEX;

		front[0] = _tileX + _tileY * TILEX - 1;
		front[1] = _tileX + _tileY * TILEX + 1;
		front[2] = _tileX + (_tileY - 1) * TILEX;
		front[3] = _tileX + (_tileY + 1) * TILEX;

		RECT temp;
		for (int i = 0; i < 4; i++)
		{
			if (IntersectRect(&temp, &PLAYER->getCollisionRc(), &_pCurrentMap[front[i]].rc))
			{
				EFFECTMANAGER->play("ÇÒÄû±â", _pCurrentMap[front[i]].rc.left + 30, _pCurrentMap[front[i]].rc.top);
				_isAttack = true;
			}
			else
			{
				_isAttack = false;
			}
		}
	}
}

void greenSlime::attack()
{
	if (_isAttack)
	{
		PLAYER->hit(_atk);
		_isAttack = false;
	}
}

