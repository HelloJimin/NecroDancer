#include "stdafx.h"
#include "bat.h"


bat::bat()
{
}


bat::~bat()
{
}

HRESULT bat::init(string name, int x, int y, int coin, tagTile * map)
{
	monster::init(name, x, y, coin, map);
	addHp();
	addHp();
	_atk = 0.5f;
	return S_OK;
}

void bat::move()
{
	if (!_isMove) return;

	if (_currentX < _pCurrentMap[_nextTileIndex].x)
	{
		_currentX += _moveSpeed;
	}
	if (_currentX > _pCurrentMap[_nextTileIndex].x)
	{
		_currentX -= _moveSpeed;
	}
	if (_currentY < _pCurrentMap[_nextTileIndex].y)
	{
		_currentY += _moveSpeed;
	}
	if (_currentY > _pCurrentMap[_nextTileIndex].y)
	{
		_currentY -= _moveSpeed;
	}

	if (getDistance(_currentX, _currentY, _pCurrentMap[_nextTileIndex].x, _pCurrentMap[_nextTileIndex].y) == 0) _isMove = false;

	_collisionRc = RectMakeCenter(_currentX, _currentY, 50, 50);
}

void bat::frontCheck()
{
	int rnd = RND->getInt(4);
	switch (rnd)
	{
	case 0:
		_nextTileIndex = _currentTileIndex - 1;
		_direction = LEFT;
		break;
	case 1:
		_nextTileIndex = _currentTileIndex + 1;
		_direction = RIGHT;
		break;
	case 2:
		_nextTileIndex = _currentTileIndex - TILEX;
		_direction = UP;
		break;
	case 3:
		_nextTileIndex = _currentTileIndex + TILEX;
		_direction = DOWN;
		break;
	}
}

void bat::choiceAction()
{
	if (BEAT->getCnt() % 58 == 0)
	{
		frontCheck();

		if (playerCheck())
		{
			_isAttack = true;
			return;
		}

		if (walkableCheck())
		{
			_isMove = true;
			_pCurrentMap[_currentTileIndex].walkable = true;
			_pCurrentMap[_nextTileIndex].walkable = false;
			EFFECTMANAGER->play("점프먼지", _currentX, _currentY);
			_currentTileIndex = _nextTileIndex;
		}
		else
		{
			_isMove = false;
			_nextTileIndex = _currentTileIndex;
		}
	}
}
