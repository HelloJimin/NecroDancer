#include "stdafx.h"
#include "hpSlot.h"


hpSlot::hpSlot()
{
}

hpSlot::hpSlot(int x, int y)
{
	_name = "HP½½·Ô";
	_x = x;
	_y = y;

	_itemImg = IMAGEMANAGER->findImage(_name);
	rcSet();
}


hpSlot::~hpSlot()
{
}

void hpSlot::update()
{
	_rc = RectMakeCenter(_x, _y, 52, 52);
	float _tileX = _rc.left / TILESIZE;
	float _tileY = _rc.top / TILESIZE;
	_currentTileIndex = _tileX + _tileY * TILEX;
}

void hpSlot::render(HDC hdc)
{
	_itemImg->render(hdc, _x - 20, _y - 20);
}
