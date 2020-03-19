#include "stdafx.h"
#include "minotaurs.h"


minotaurs::minotaurs()
{
}


minotaurs::~minotaurs()
{
}

HRESULT minotaurs::init(string name, int x, int y, int coin, tagTile * map)
{
	monster::init(name, x, y, coin, map);
	_direction = LEFT;
	_aStar = new aStar;
	_atk = 2.0f;
	_minePower = 3;
	addHp();
	addHp();
	_isDown = false;
	_isRage = false;
	_downCnt = 0;
	return S_OK;
}

void minotaurs::frontCheck()
{
	if (!_isRage)
	{
		_nextTileIndex = _aStar->aStarBoss(_pCurrentMap, _currentTileIndex, PLAYER->currentTile());
	}
	else
	{
		switch (_direction)
		{
		case LEFT: _nextTileIndex--;
			break;
		case RIGHT:_nextTileIndex++;
			break;
		case UP:_nextTileIndex -= TILEX;
			break;
		case DOWN:_nextTileIndex += TILEX;
			break;
		}
	}
	aniCheck();

	rageCheck();
}

void minotaurs::choiceAction()
{
	if (BEAT->getCnt() % 29 == 0)
	{
		if (_isDown)
		{
			_downCnt++;
			if (_downCnt > 2)
			{
				_isDown = false;
				_downCnt = 0;
			}
			return;
		}

		frontCheck();

		if (playerCheck())
		{
			_isAttack = true;
			_isRage = false;
			_isDown = true;
			_nextTileIndex = _currentTileIndex;
			return;
		}

		if (walkableCheck())
		{
			_isMove = true;
			if (_currentTileIndex == _nextTileIndex)_isMove = false;

			_pCurrentMap[_currentTileIndex].walkable = true;
			_pCurrentMap[_nextTileIndex].walkable = false;
			EFFECTMANAGER->play("점프먼지", _currentX, _currentY);
			_currentTileIndex = _nextTileIndex;
		}
		else
		{
			mine();
			_isMove = false;
			_nextTileIndex = _currentTileIndex;
			if (_isRage)
			{
				_isRage = false;
				_isDown = true;
			}
		}
	}
}

void minotaurs::animation()
{
	if (BEAT->getCnt() % 12 == 0)
	{
		_frameX++;
		if (_isRage && !_isDown) _frameX = 4;
		else if (!_isRage && !_isDown)
		{
			if (_frameX > 3)_frameX = 0;
		}

		if (_isDown)
		{
			_frameX += 5;
			if (_frameX > _monsterImg->getMaxFrameX())_frameX = 5;
		}
	}
}

void minotaurs::render(HDC hdc)
{
	if (KEYMANAGER->isToggleKey(VK_TAB)) Rectangle(hdc, _collisionRc.left, _collisionRc.top, _collisionRc.right, _collisionRc.bottom);
	_monsterImg->frameRender(hdc, _collisionRc.left - _monsterImg->getFrameWidth() / 4, _collisionRc.top - _monsterImg->getFrameHeight() + TILEX, _frameX, _frameY);
	hpRender(hdc);
}

void minotaurs::mine()
{
	if (_minePower >= _pCurrentMap[_nextTileIndex].strength)
	{
		_pCurrentMap[_nextTileIndex].obj = OBJ_NONE;
		_pCurrentMap[_nextTileIndex].strength = 0;
		_pCurrentMap[_nextTileIndex].walkable = true;
	}
}

void minotaurs::move()
{
	if (!_isMove) return;
	switch (_direction)
	{
	case LEFT:
		if (!_isDrop&& getDistance(_currentX, _currentY, _pCurrentMap[_nextTileIndex].x + 26, _pCurrentMap[_nextTileIndex].y - 26) != 0)
		{
			_currentX -= _moveSpeed;
			_currentY -= _moveSpeed;
		}
		else _isDrop = true;

		if (_isDrop&& getDistance(_currentX, _currentY, _pCurrentMap[_nextTileIndex].x, _pCurrentMap[_nextTileIndex].y) != 0)
		{
			_currentX -= _moveSpeed;
			_currentY += _moveSpeed;
		}
		else if (_isDrop&& getDistance(_currentX, _currentY, _pCurrentMap[_nextTileIndex].x, _pCurrentMap[_nextTileIndex].y) == 0)
		{
			_isDrop = false;
			_isMove = false;
		}
		break;
	case RIGHT:
		if (!_isDrop&& getDistance(_currentX, _currentY, _pCurrentMap[_nextTileIndex].x - 26, _pCurrentMap[_nextTileIndex].y - 26) != 0)
		{
			_currentX += _moveSpeed;
			_currentY -= _moveSpeed;
		}
		else _isDrop = true;

		if (_isDrop&& getDistance(_currentX, _currentY, _pCurrentMap[_nextTileIndex].x, _pCurrentMap[_nextTileIndex].y) != 0)
		{
			_currentX += _moveSpeed;
			_currentY += _moveSpeed;
		}
		else if (_isDrop&& getDistance(_currentX, _currentY, _pCurrentMap[_nextTileIndex].x, _pCurrentMap[_nextTileIndex].y) == 0)
		{
			_isDrop = false;
			_isMove = false;
		}
		break;
	case UP:
		if (!_isDrop&& getDistance(_currentX, _currentY, _pCurrentMap[_nextTileIndex].x, _pCurrentMap[_nextTileIndex].y - 26) != 0)
		{
			_currentY -= _moveSpeed;
		}
		else _isDrop = true;

		if (_isDrop&& getDistance(_currentX, _currentY, _pCurrentMap[_nextTileIndex].x, _pCurrentMap[_nextTileIndex].y) != 0)
		{
			_currentY += _moveSpeed;
		}
		else if (_isDrop&& getDistance(_currentX, _currentY, _pCurrentMap[_nextTileIndex].x, _pCurrentMap[_nextTileIndex].y) == 0)
		{
			_isDrop = false;
			_isMove = false;
		}
		break;
	case DOWN:
		if (!_isDrop&& getDistance(_currentX, _currentY, _pCurrentMap[_nextTileIndex].x, _pCurrentMap[_nextTileIndex].y - 78) != 0)
		{
			_currentY -= _moveSpeed;
		}
		else _isDrop = true;

		if (_isDrop&& getDistance(_currentX, _currentY, _pCurrentMap[_nextTileIndex].x, _pCurrentMap[_nextTileIndex].y) != 0)
		{
			_currentY += _moveSpeed;
		}
		else if (_isDrop&& getDistance(_currentX, _currentY, _pCurrentMap[_nextTileIndex].x, _pCurrentMap[_nextTileIndex].y) == 0)
		{
			_isDrop = false;
			_isMove = false;
		}
		break;
	}
	_collisionRc = RectMakeCenter(_currentX, _currentY, 50, 50);
}

void minotaurs::rageCheck()
{
	if (_isRage) return;

	int playerTile = PLAYER->currentTile();
	int checkTile = 5;
	switch (_direction)
	{
	case LEFT:
		for (int i = 0; i < checkTile; i++)
		{
			if (playerTile == _nextTileIndex - i)
			{
				_isRage = true;
			}
		}
		break;
	case RIGHT:
		for (int i = 0; i < checkTile; i++)
		{
			if (playerTile == _nextTileIndex + i)
			{
				_isRage = true;
			}
		}
		break;
	case UP:
		for (int i = 0; i < checkTile; i++)
		{
			if (playerTile == _nextTileIndex - (i*TILEX))
			{
				_isRage = true;
			}
		}
		break;
	case DOWN:
		for (int i = 0; i < checkTile; i++)
		{
			if (playerTile == _nextTileIndex + (i*TILEX))
			{
				_isRage = true;
			}
		}
		break;
	}
}
