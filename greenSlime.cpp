#include "stdafx.h"
#include "greenSlime.h"


greenSlime::greenSlime()
{
}


greenSlime::~greenSlime()
{
}


HRESULT greenSlime::init(string name, int x, int y, int coin, tagTile * map)
{
	monster::init(name, x, y, coin, map);
	_atk = 0.0f;
	_monsterNameImg = IMAGEMANAGER->findImage("그린슬라임이름");
	return S_OK;
}

void greenSlime::update()
{
	_pCurrentMap[_currentTileIndex].walkable = false;

	animation();
}

void greenSlime::render(HDC hdc)
{
	if (KEYMANAGER->isToggleKey(VK_TAB)) Rectangle(hdc, _collisionRc.left, _collisionRc.top, _collisionRc.right, _collisionRc.bottom);
	_monsterImg->frameRender(hdc, _collisionRc.left - _monsterImg->getFrameWidth() / 8, _collisionRc.top - _monsterImg->getFrameHeight() / 4, _frameX, _frameY);
	hpRender(hdc);
}

void greenSlime::silhouetteRender(HDC hdc)
{
	if (KEYMANAGER->isToggleKey(VK_TAB)) Rectangle(hdc, _collisionRc.left, _collisionRc.top, _collisionRc.right, _collisionRc.bottom);
	_monsterImg->frameRender(hdc, _collisionRc.left - _monsterImg->getFrameWidth() / 8, _collisionRc.top - _monsterImg->getFrameHeight() / 4, _frameX, _frameY+1);
	hpRender(hdc);
}



