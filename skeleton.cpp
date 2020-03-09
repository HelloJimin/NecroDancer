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

void skeleton::move()
{

	if (_isMove)
	{
		if (_rc.left != temp->rc.left || _rc.top!= temp->rc.top)
		{
			_rc = temp->rc;
		}
		else
		{
			_isMove = false;
		}
	}


}

void skeleton::frontCheck()
{
	monster::frontCheck();
	temp = _aStar->aStarTile(_pCurrentMap, _rc, PLAYER->getCollisionRc());

	//_nextTileIndex = _aStar->aStarTile(_pCurrentMap,_rc,PLAYER->getCollisionRc());
	//temp = _aStar->aStarTile(_pCurrentMap, _rc, PLAYER->getCollisionRc());
}
