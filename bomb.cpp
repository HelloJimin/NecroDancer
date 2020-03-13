#include "stdafx.h"
#include "bomb.h"


bomb::bomb()
{
}

bomb::bomb(string name, slotType type, int num, string description)
{
	setItem(type, name, description);
	_num = num;
	_ani = IMAGEMANAGER->findImage("��ź�ִ�");
}


bomb::~bomb()
{
}

HRESULT bomb::init()
{
	return S_OK;
}

void bomb::update()
{
}

void bomb::render(HDC hdc)
{
	if (_inInventory)
	{
		_itemImg = IMAGEMANAGER->findImage("��ź");
		_slotImg->render(CAMERAMANAGER->getCameraDC(), _rc.left, _rc.top);
		_itemImg->render(CAMERAMANAGER->getCameraDC(), _rc.left + 8, _rc.top + 11);
	}
	else
	{
		//Rectangle(hdc, _rc.left, _rc.top, _rc.right, _rc.bottom);
		_itemImg->render(hdc, _x - 20, _y - 40);
	}
}
