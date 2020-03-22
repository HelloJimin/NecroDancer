#include "stdafx.h"
#include "coin.h"


coin::coin()
{
}

coin::coin(int value, int x, int y)
{
	_name = "����";
	_value = value;
	if (_value < 50) _itemImg = IMAGEMANAGER->findImage("��������");
	else _itemImg = IMAGEMANAGER->findImage("ū����");
	_x = x;
	_y = y;

	rcSet();
}


coin::~coin()
{
}

void coin::update()
{
	_rc = RectMakeCenter(_x, _y, 52, 52);
	float _tileX = _rc.left / TILESIZE;
	float _tileY = _rc.top / TILESIZE;
	_currentTileIndex = _tileX + _tileY * TILEX;
}

void coin::render(HDC hdc)
{
	_itemImg->render(hdc, _x-20 , _y-20);
}

int coin::getValue()
{
	return _value;
}
