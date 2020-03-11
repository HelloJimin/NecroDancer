#include "stdafx.h"
#include "skeleton.h"


skeleton::skeleton()
{
}


skeleton::~skeleton()
{
}

HRESULT skeleton::init(string name, int x, int y, int coin, tagTile * map)
{
	monster::init(name, x, y, coin, map);
	_direction = LEFT;
	_aStar = new aStar;
	_atk = 0.5f;
	return S_OK;
}

void skeleton::render(HDC hdc)
{
	switch (_directionAni)
	{
	case LEFT_TOP: _frameY = 1;
		break;
	case LEFT_BOT: _frameY = 0;
		break;
	case RIGHT_TOP: _frameY = 3;
		break;
	case RIGHT_BOT: _frameY = 2;
		break;
	}
	Rectangle(hdc, _collisionRc.left, _collisionRc.top, _collisionRc.right, _collisionRc.bottom);


	_monsterImg->frameRender(hdc, _collisionRc.left - _monsterImg->getFrameWidth()/8, _collisionRc.top-_monsterImg->getFrameHeight()/4, _frameX, _frameY);
}

void skeleton::frontCheck()
{
	if (BEAT->getCnt() % 58 == 0)
	{
		_nextTileIndex = _aStar->aStarTile(_pCurrentMap,_currentTileIndex ,PLAYER->currentTile());
		choiceAction();
		aniCheck();
	}
}



void skeleton::choiceAction()
{

	if (playerCheck())
	{
		_isAttack = true;
		if (_nextTileIndex == _currentTileIndex - 1) _direction = LEFT;
		else if (_nextTileIndex == _currentTileIndex + 1) _direction = RIGHT;
		else if (_nextTileIndex == _currentTileIndex + TILEX)_direction = DOWN;
		else if (_nextTileIndex == _currentTileIndex - TILEX)_direction = UP;
		_nextTileIndex = _currentTileIndex;
		return;
	}
	else
	{
		_isMove = true;
		if (_nextTileIndex == _currentTileIndex - 1) _direction = LEFT;
		else if (_nextTileIndex == _currentTileIndex + 1) _direction = RIGHT;
		else if (_nextTileIndex == _currentTileIndex + TILEX)_direction = DOWN;
		else if (_nextTileIndex == _currentTileIndex - TILEX)_direction = UP;
		_currentTileIndex = _nextTileIndex;
		return;
	}
}

void skeleton::animation()
{
	if (BEAT->getCnt() % 14 == 0)
	{
		_frameX++;
		if (_frameX > _monsterImg->getMaxFrameX())_frameX = 0;
	}
}
