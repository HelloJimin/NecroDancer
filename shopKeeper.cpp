#include "stdafx.h"
#include "shopKeeper.h"


shopKeeper::shopKeeper()
{
}


shopKeeper::~shopKeeper()
{
}

HRESULT shopKeeper::init(string name, int x, int y, int coin, tagTile * map)
{
	monster::init(name, x, y, coin, map);
	_direction = LEFT;
	_aStar = new aStar;
	_atk = 2.0f;

	addHp();
	addHp();
	addHp();
	addHp();
	addHp();
	addHp();
	addHp();

	return S_OK;
}

void shopKeeper::update()
{
	_pCurrentMap[_currentTileIndex].walkable = false;
	animation();

	if (!_isHit)return;

	choiceAction();

	attack();
	move();

	hpSet();

}

void shopKeeper::frontCheck()
{
	_nextTileIndex = _aStar->aStarTile(_pCurrentMap, _currentTileIndex, PLAYER->currentTile());

	aniCheck();
}

void shopKeeper::choiceAction()
{
	if (BEAT->getCnt() % 29 == 0)
	{
		frontCheck();

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
			EFFECTMANAGER->play("��������", _currentX, _currentY);
			_currentTileIndex = _nextTileIndex;
		}
		else
		{
			_isMove = false;
			_nextTileIndex = _currentTileIndex;
		}
	}
}

void shopKeeper::render(HDC hdc)
{
	if (KEYMANAGER->isToggleKey(VK_TAB)) Rectangle(hdc, _collisionRc.left, _collisionRc.top, _collisionRc.right, _collisionRc.bottom);
	_monsterImg->frameRender(hdc, _collisionRc.left - TILEX, _collisionRc.top - _monsterImg->getFrameHeight() + TILEX, _frameX, _frameY);

	hpRender(hdc);
}

void shopKeeper::silhouetteRender(HDC hdc)
{
	if (KEYMANAGER->isToggleKey(VK_TAB)) Rectangle(hdc, _collisionRc.left, _collisionRc.top, _collisionRc.right, _collisionRc.bottom);
	_monsterImg->frameRender(hdc, _collisionRc.left - TILEX, _collisionRc.top - _monsterImg->getFrameHeight() + TILEX, _frameX, _frameY + 2);

	hpRender(hdc);
}