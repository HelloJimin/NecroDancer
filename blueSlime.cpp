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
	addHp();
	_atk = 0.5f;
	return S_OK;
}

void blueSlime::frontCheck()
{
	switch (_direction)
	{
	case UP:
		_direction = DOWN;
		_nextTileIndex = _currentTileIndex + TILEX;
		break;
	case DOWN: 
		_direction = UP;
		_nextTileIndex = _currentTileIndex - TILEX;
		break;
	}
}

void blueSlime::choiceAction()
{
	if (BEAT->getCnt() % 58 == 0)
	{
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

		frontCheck();

		if (walkableCheck())
		{
			_isMove = true;
			_pCurrentMap[_currentTileIndex].walkable = true;
			_pCurrentMap[_nextTileIndex].walkable = false;
			EFFECTMANAGER->play("��������", _currentX, _currentY);
			_currentTileIndex = _nextTileIndex;
		}
		else
		{
			_isMove = false;
			switch (_direction)
			{
			case UP: _direction = DOWN;
				break;
			case DOWN: _direction = UP;
				break;
			}
			_nextTileIndex = _currentTileIndex;
		}
	}
}
