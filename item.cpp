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

void item::setItem(itemType type, string name, string description)
{
	_name = name;
	_description = description;

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
	_rc = RectMakeCenter(_x, _y, _slotImg->getWidth(), _slotImg->getHeight());
}

void item::animation()
{
	if (!_inInventory)
	{
		_waveCnt++;

		if (_upDown)
		{
			_y -= 0.5;
			if (_waveCnt > 15) _upDown = false;
		}
		else
		{
			_y += 0.5;
			if (_waveCnt > 30)
			{
				_upDown = true;
				_waveCnt = 1;
			}
		}
	}
	_rc = RectMakeCenter(_x, _y, _slotImg->getWidth(), _slotImg->getHeight());
}

void item::draw(HDC hdc)
{
	if (_inInventory)
	{
		_slotImg->render(CAMERAMANAGER->getCameraDC(), _rc.left, _rc.top);
		_itemImg->render(CAMERAMANAGER->getCameraDC(), _rc.left+5, _rc.top+10);
	}
	else
	{
		Rectangle(hdc, _rc.left, _rc.top, _rc.right, _rc.bottom);
		_itemImg->render(hdc, _rc.left, _rc.top);
	}
}
