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
	_monsterNameImg = IMAGEMANAGER->findImage("½ºÄÌ·¹ÅæÀÌ¸§");
	return S_OK;
}

void skeleton::frontCheck()
{
	_nextTileIndex = _aStar->aStarTile(_pCurrentMap,_currentTileIndex ,PLAYER->currentTile());
	
	aniCheck();
}

void skeleton::choiceAction()
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
			EFFECTMANAGER->play("Á¡ÇÁ¸ÕÁö", _currentX, _currentY);
			_currentTileIndex = _nextTileIndex;
		}
		else
		{
			_isMove = false;
			_nextTileIndex = _currentTileIndex;
		}
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

bool skeleton::die()
{
	for (int i = 0; i < _vHp.size(); ++i)
	{
		if (_vHp[i].hp > 0.0f) return false;
	}
	SOUNDMANAGER->play("skel_death");
	return true;	

}
