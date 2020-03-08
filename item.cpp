#include "stdafx.h"
#include "item.h"


item::item()
{
}

item::~item()
{
}

HRESULT item::init()
{
	return S_OK;
}

void item::release()
{
}

void item::update()
{
	animation();
}

void item::render(HDC hdc)
{
	draw(hdc);
}

int item::getInfo()
{
	return 0;
}

void item::setItem(slotType type, string name, string description)
{
	_name = name;
	_itemImg = IMAGEMANAGER->findImage(name);
	_description = description;
	_type = type;

	switch (type)
	{
	case SHOVEL:
		_slotImg = IMAGEMANAGER->findImage("»ð");
		break;
	case ATTACK:
		_slotImg = IMAGEMANAGER->findImage("¹«±â");
		break;
	case BODY:
		_slotImg = IMAGEMANAGER->findImage("º¸µð");
		break;
	case FEET:
		_slotImg = IMAGEMANAGER->findImage("½Å¹ß");
		break;
	case TORCH:
		_slotImg = IMAGEMANAGER->findImage("È¶ºÒ");
		break;
	case ITEM:
		_slotImg = IMAGEMANAGER->findImage("¾ÆÀÌÅÛ");
		break;
	case BOMB:
		_slotImg = IMAGEMANAGER->findImage("ÆøÅº");
		break;
	}

	_waveCnt = 0;
	_inInventory = false;
	_x = 0;
	_y = 0;

}

void item::animation()
{
	if (!_inInventory)
	{
		_waveCnt++;

		if (_upDown)
		{
			_y -= 0.5f;
			if (_waveCnt > 15) _upDown = false;
		}
		else
		{
			_y += 0.5f;
			if (_waveCnt > 30)
			{
				_upDown = true;
				_waveCnt = 1;
			}
		}
	}
}

void item::draw(HDC hdc)
{
	if (_inInventory)
	{
		_slotImg->render(CAMERAMANAGER->getCameraDC(), _rc.left, _rc.top);
		_itemImg->render(CAMERAMANAGER->getCameraDC(), _rc.left+ 8, _rc.top+11);
	}
	else
	{
		//Rectangle(hdc, _rc.left, _rc.top, _rc.right, _rc.bottom);
		_itemImg->render(hdc, _x-20, _y-40);
	}
}

void item::rcSet()
{
	_rc = RectMakeCenter(_x + 10, _y + 10, _itemImg->getWidth(), _itemImg->getHeight());
}
