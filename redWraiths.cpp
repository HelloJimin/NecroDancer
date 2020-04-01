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
	_monsterNameImg = IMAGEMANAGER->findImage("혼령이름");
	return S_OK;
}

void redWraiths::frontCheck()
{
	_nextTileIndex = _aStar->aStarStraight(_pCurrentMap, _currentTileIndex, PLAYER->currentTile());
	aniCheck();

	_teleportCnt++;
	if (_teleportCnt == 15)
	{
		teleport();
		_isTeleport = true;
	}
}

void redWraiths::choiceAction()
{
	if (_isBeat)
	{
		frontCheck();
		_isBeat = false;
		if (playerCheck())
		{
			_isAttack = true;
			_nextTileIndex = _currentTileIndex;
			return;
		}

		if (walkableCheck())
		{
			_isMove = true;
			if (_currentTileIndex == _nextTileIndex)_isMove = false;

			_frameX = _monsterImg->getMaxFrameX() - 2;
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
		_currentY += _moveSpeed;
	}
	if (_currentY > _pCurrentMap[_nextTileIndex].y)
	{
		_currentY -= _moveSpeed;
	}

	if (getDistance(_currentX, _currentY, _pCurrentMap[_nextTileIndex].x, _pCurrentMap[_nextTileIndex].y) == 0) _isMove = false;

	_collisionRc = RectMakeCenter(_currentX, _currentY, 50, 50);
}

void redWraiths::animation()
{
	if (_isTeleport && BEAT->getCnt()%12 == 0)
	{
		_frameX++;
		if (_frameX > _monsterImg->getMaxFrameX())
		{
			_isTeleport = false;
			_frameX = 0;
		}
	}
}

void redWraiths::teleport()
{
	SOUNDMANAGER->play("wraith_cry");
	//if (_isTeleport)
	{
		_teleportCnt++;
		_isMove = false;
		int playerTile = PLAYER->currentTile();

		if (_pCurrentMap[playerTile - 5].walkable)
		{
			_currentX = _pCurrentMap[playerTile - 5].x;
			_currentY = _pCurrentMap[playerTile - 5].y;
			_currentTileIndex = playerTile - 5;
		}
		else if (_pCurrentMap[playerTile - TILEX*5].walkable)
		{
			_currentX = _pCurrentMap[playerTile - TILEX*5].x;
			_currentY = _pCurrentMap[playerTile - TILEX*5].y;
			_currentTileIndex = playerTile - TILEX*5;
		}
		else if (_pCurrentMap[playerTile + 5].walkable)
		{
			_currentX = _pCurrentMap[playerTile + 5].x;
			_currentY = _pCurrentMap[playerTile + 5].y;
			_currentTileIndex = playerTile + 5;
		}
		else if (_pCurrentMap[playerTile + TILEX*5].walkable)
		{
			_currentX = _pCurrentMap[playerTile + TILEX*5].x;
			_currentY = _pCurrentMap[playerTile + TILEX*5].y;
			_currentTileIndex = playerTile + TILEX*5;
		}
		_collisionRc = RectMakeCenter(_currentX, _currentY, 50, 50);
	}
}

bool redWraiths::die()
{
	for (int i = 0; i < _vHp.size(); ++i)
	{
		if (_vHp[i].hp > 0.0f) return false;
	}
	SOUNDMANAGER->play("wraith_death");
	return true;
}
