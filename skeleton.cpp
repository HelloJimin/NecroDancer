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
	_rc = _collisionRc;
	return S_OK;
}

void skeleton::render(HDC hdc)
{
	Rectangle(hdc, _rc.left, _rc.top, _rc.right, _rc.bottom);
	//Rectangle(hdc, _pCurrentMap[_nextTileIndex].rc.left, _pCurrentMap[_nextTileIndex].rc.top, _pCurrentMap[_nextTileIndex].rc.right, _pCurrentMap[_nextTileIndex].rc.bottom);
	//_aStar->render();
}

void skeleton::frontCheck()
{
	monster::frontCheck();
	//temp = _aStar->aStarTile(_pCurrentMap, _rc, PLAYER->getCollisionRc());

	if (BEAT->getCnt() % 58 == 0)
	{
		_nextTileIndex = _aStar->aStarTile(_pCurrentMap, _rc, PLAYER->getCollisionRc(),_currentTileIndex ,PLAYER->currentTile());
		_currentTileIndex = _nextTileIndex;
	}
	//temp = _aStar->aStarTile(_pCurrentMap, _rc, PLAYER->getCollisionRc());
}

void skeleton::move()
{
	if (!_isMove) return;

	if (_rc.left != _pCurrentMap[_nextTileIndex].rc.left || _rc.top != _pCurrentMap[_nextTileIndex].rc.top)
	{
		_rc = _pCurrentMap[_nextTileIndex].rc;
		_collisionRc = _pCurrentMap[_nextTileIndex].rc;
	}
	else
	{
		_isMove = false;
	}

}

void skeleton::choiceAction()
{
	_isMove = true;
}
