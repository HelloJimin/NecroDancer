#include "stdafx.h"
#include "skeleton.h"


skeleton::skeleton()
{
}


skeleton::~skeleton()
{
}

HRESULT skeleton::init(string name, int x, int y, tagTile * map)
{
	monster::init(name, x, y, map);
	_direction = LEFT;
	_aStar = new aStar;
	_rc = _collisionRc;
	return S_OK;
}

void skeleton::update()
{
	if (BEAT->getCnt() % 58 == 0)
	{
		frontCheck();
		//_nextTileIndex = _aStar->aStarTile(_pCurrentMap,_rc,PLAYER->getCollisionRc());
		temp = _aStar->aStarTile(_pCurrentMap, _rc, PLAYER->getCollisionRc());
	}

	move();

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
