#include "stdafx.h"
#include "blueSlime.h"


blueSlime::blueSlime()
{
}


blueSlime::~blueSlime()
{
}

HRESULT blueSlime::init(string name, int x, int y, int coin, tagTile * map)
{
	monster::init(name, x, y, coin, map);
	_atk = 0.5f;
	return S_OK;
}

void blueSlime::frontCheck()
{
	if (BEAT->getCnt() % 58 == 0)
	{
		switch (_direction)
		{
		case UP: _direction = DOWN;
			break;
		case DOWN: _direction = UP;
			break;
		}
	}
	monster::frontCheck();

}

void blueSlime::choiceAction()
{
	RECT temp;
	if (playerCheck())
	{
		_isAttack = true;
		switch (_direction)
		{
		case UP: _direction = DOWN;
			break;
		case DOWN: _direction = UP;
			break;
		}
		return;
	}
	if (wallCheck())
	{
		_isMove = true;
		_currentTileIndex = _nextTileIndex;
	}
	else
	{
		_isMove = false;
		_nextTileIndex = _currentTileIndex;
	}
}
