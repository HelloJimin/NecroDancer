#include "stdafx.h"
#include "apple.h"


apple::apple()
{
}

apple::apple(string name, slotType type, int num, float power, string description, int x, int y, int price)
{
	setItem(type, name, description, x, y, price);
	_num = num;
	_button = IMAGEMANAGER->findImage("c¹öÆ°");
	_heal = power;
}


apple::~apple()
{
}

HRESULT apple::init()
{
	_isShop = false;
	return S_OK;
}

void apple::update()
{
	item::animation();

	if (!_inInventory)return;
	if (KEYMANAGER->isOnceKeyDown('C') && _num > 0)
	{
		PLAYER->heal(_heal);
		_num--;
	}
}

void apple::render(HDC hdc)
{
	if (_inInventory && _num > 0)
	{
		_itemImg = IMAGEMANAGER->findImage(_name);
		_slotImg->render(CAMERAMANAGER->getCameraDC(), _rc.left, _rc.top);
		_itemImg->render(CAMERAMANAGER->getCameraDC(), _rc.left + 8, _rc.top + 11);
		_button->render(CAMERAMANAGER->getCameraDC(), _rc.left + 25, _rc.top + 60);
	}
	else if (!_inInventory)
	{
		_itemImg->render(hdc, _x - 20, _y - 40);
	}
}

void apple::setValue(int num)
{
	_num += num;
}

int apple::getValue()
{
	return _num;
}
