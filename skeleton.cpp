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

void skeleton::frontCheck()
{
	if (BEAT->getCnt() % 58 == 0)
	{
		_nextTileIndex = _aStar->aStarTile(_pCurrentMap,_currentTileIndex ,PLAYER->currentTile());
		aniCheck();
		choiceAction();
	}
}

void skeleton::choiceAction()
{
	if (playerCheck())
	{
		_isAttack = true;
		_nextTileIndex = _currentTileIndex;
	}
	else
	{
		_isMove = true;
		_frameX = _monsterImg->getMaxFrameX()-2;
		_pCurrentMap[_currentTileIndex].walkable = true;
		_pCurrentMap[_nextTileIndex].walkable = false;
		EFFECTMANAGER->play("점프먼지", _currentX, _currentY);
		_currentTileIndex = _nextTileIndex;
	}
}

void skeleton::animation()
{
	if (BEAT->getCnt() % 12 == 0)
	{
		_frameX++;
		if (_frameX > _monsterImg->getMaxFrameX())_frameX = 0;
	}
}
