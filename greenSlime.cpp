#include "stdafx.h"
#include "greenSlime.h"


greenSlime::greenSlime()
{
}


greenSlime::~greenSlime()
{
}


HRESULT greenSlime::init(string name, int x, int y, tagTile * map)
{
	monster::init(name, x, y, map);
	_atk = 0.5f;
	return S_OK;

}

void greenSlime::update()
{
	animation();
	if (BEAT->getCnt() % 58 == 0)
	{
		frontCheck();
	}

	attack();
}

void greenSlime::frontCheck()
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
			EFFECTMANAGER->play("ÇÒÄû±â", _pCurrentMap[front[i]].rc.left+30, _pCurrentMap[front[i]].rc.top);
			_attack = true;
		}
		else
		{
			_attack = false;
		}
	}
}

void greenSlime::attack()
{
	if (_attack)
	{
		PLAYER->hit(_atk);
		_attack = false;
	}
}

