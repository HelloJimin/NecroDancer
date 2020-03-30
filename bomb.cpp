#include "stdafx.h"
#include "bomb.h"


bomb::bomb()
{
}

bomb::bomb(string name, slotType type, int num, string description, int x, int y, int price)
{
	setItem(type, name, description,  x,  y,price);
	_num = num;
	_button = IMAGEMANAGER->findImage("x��ư");
}


bomb::~bomb()
{
}

HRESULT bomb::init()
{
	_isShop = false;
	return S_OK;
}

void bomb::update()
{
	item::animation();

	if (!_inInventory)return;
	if (KEYMANAGER->isOnceKeyDown('X') && _num > 0 )
	{
		_num--;
		PLAYER->getBomb() = true;
	}
}

void bomb::render(HDC hdc)
{
	if (_inInventory && _num > 0)
	{
		_itemImg = IMAGEMANAGER->findImage("��ź");
		_slotImg->render(CAMERAMANAGER->getCameraDC(), _rc.left, _rc.top);
		_itemImg->render(CAMERAMANAGER->getCameraDC(), _rc.left + 8, _rc.top + 11);
		_button->render(CAMERAMANAGER->getCameraDC(), _rc.left + 25, _rc.top + 60);
		IMAGEMANAGER->frameRender("����", CAMERAMANAGER->getCameraDC(), _rc.left + 45, _rc.top + 40, _num, 0);
		IMAGEMANAGER->render("����x��ư", CAMERAMANAGER->getCameraDC(), _rc.left + 35, _rc.top + 50);
	}
	else if(!_inInventory)
	{
		_itemImg->render(hdc, _x - 20, _y - 40);
	}
}

void bomb::setValue(int num)
{
	_num += num;
}

int bomb::getValue()
{
	return _num;
}
