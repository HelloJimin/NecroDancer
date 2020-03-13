#include "stdafx.h"
#include "redWraiths.h"


redWraiths::redWraiths()
{
}


redWraiths::~redWraiths()
{
}

HRESULT redWraiths::init(string name, int x, int y, int coin, tagTile * map)
{
	monster::init(name, x, y, coin, map);
	_direction = LEFT;
	_aStar = new aStar;
	_atk = 0.5f;
	return S_OK;
}

void redWraiths::frontCheck()
{
	if (BEAT->getCnt() % 29 == 0)
	{
		_teleportCnt++;
		_nextTileIndex = _aStar->aStarTile(_pCurrentMap, _currentTileIndex, PLAYER->currentTile());
		aniCheck();
		choiceAction();
	}
}

void redWraiths::choiceAction()
{
	if (playerCheck())
	{
		_isAttack = true;
		_nextTileIndex = _currentTileIndex;
	}
	else
	{
		_isMove = true;
		_frameX = _monsterImg->getMaxFrameX() - 2;
		_pCurrentMap[_currentTileIndex].walkable = true;
		_pCurrentMap[_nextTileIndex].walkable = false;
		EFFECTMANAGER->play("점프먼지", _currentX, _currentY);
		_currentTileIndex = _nextTileIndex;
	}

}

void redWraiths::move()
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
		_currentY + _moveSpeed;
	}
	if (_currentY > _pCurrentMap[_nextTileIndex].y)
	{
		_currentY -= _moveSpeed;
	}

	if (getDistance(_currentX, _currentY, _pCurrentMap[_nextTileIndex].x, _pCurrentMap[_nextTileIndex].y) == 0) _isMove = false;

	_collisionRc = RectMakeCenter(_currentX, _currentY, 50, 50);
}

void redWraiths::update()
{
	_pCurrentMap[_currentTileIndex].walkable = false;

	teleport();
	animation();
	frontCheck();
	hpSet();
	attack();
	move();
}

void redWraiths::teleport()
{
	if (_teleportCnt == 5)
	{
		//_currentTileIndex때매 순간이동하면 이상한곳에서도 공격할수있는것같음.;
		_isLockOn = true;
		int playerTile = PLAYER->currentTile();

		if (_pCurrentMap[playerTile - 5].walkable)
		{
			_currentX = _pCurrentMap[playerTile - 5].x;
			_currentY = _pCurrentMap[playerTile - 5].y;
			_currentTileIndex = playerTile - 5;
		}
		else if (_pCurrentMap[playerTile + 5].walkable)
		{
			_currentX = _pCurrentMap[playerTile + 5].x;
			_currentY = _pCurrentMap[playerTile + 5].y;
			_currentTileIndex = playerTile + 5;
		}
		else if (_pCurrentMap[playerTile + TILEX*5].walkable)
		{
			_currentX = _pCurrentMap[playerTile + TILEX * 5].x;
			_currentY = _pCurrentMap[playerTile + TILEX * 5].y;
			_currentTileIndex = playerTile + TILEX * 5;
		}
		else if (_pCurrentMap[playerTile - TILEX * 5].walkable)
		{
			_currentX = _pCurrentMap[playerTile - TILEX * 5].x;
			_currentY = _pCurrentMap[playerTile - TILEX * 5].y;
			_currentTileIndex = playerTile - TILEX * 5;
		}
		_collisionRc = RectMakeCenter(_currentX, _currentY, 50, 50);
	}
}
