#include "stdafx.h"
#include "zombie.h"


zombie::zombie()
{
}


zombie::~zombie()
{
}

HRESULT zombie::init(string name, int x, int y, int coin, tagTile * map)
{
	monster::init(name, x, y, coin, map);

	switch (RND->getInt(2))
	{
	case 0:	_direction = LEFT ;
		break;
	case 1:	_direction = UP;
		break;
	}
	aniCheck();
	_atk = 0.5f;
	return S_OK;
}

void zombie::frontCheck()
{
	switch (_direction)
	{
	case LEFT:
		_nextTileIndex = _currentTileIndex - 1;
		break;
	case RIGHT:
		_nextTileIndex = _currentTileIndex + 1;
		break;
	case UP:
		_nextTileIndex = _currentTileIndex - TILEX;
		break;
	case DOWN:
		_nextTileIndex = _currentTileIndex +TILEX;
		break;
	}

	if (!_pCurrentMap[_nextTileIndex].walkable)
	{
		switch (_direction)
		{
		case LEFT:
			_direction = RIGHT;
			break;
		case RIGHT:
			_direction = LEFT;
			break;
		case UP:
			_direction = DOWN;
			break;
		case DOWN:
			_direction = UP;
			break;

		}
	}

	aniCheck();

}

void zombie::choiceAction()
{
	if ( _isBeat)
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

void zombie::animation()
{
	if (BEAT->getCnt() % 12 == 0)
	{
		_frameX++;
		if (_frameX > _monsterImg->getMaxFrameX())_frameX = 0;
	}
}

void zombie::aniCheck()
{
	switch (_direction)
	{
	case LEFT:_frameY = 0;
		break;
	case RIGHT:_frameY = 1;
		break;
	case UP:_frameY = 2;
		break;
	case DOWN:_frameY = 3;
		break;
	}
}

void zombie::silhouetteRender(HDC hdc)
{
	if (KEYMANAGER->isToggleKey(VK_TAB)) Rectangle(hdc, _collisionRc.left, _collisionRc.top, _collisionRc.right, _collisionRc.bottom);
	_monsterImg->frameRender(hdc, _collisionRc.left - _monsterImg->getFrameWidth() / 8, _collisionRc.top - _monsterImg->getFrameHeight() / 4, _frameX, _frameY + 4);
	hpRender(hdc);
}
