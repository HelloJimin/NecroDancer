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

void item::active()
{
}

int item::getValue()
{
	return 0;
}

bool item::getBool()
{
	return false;
}

void item::setValue(int num)
{
}

void item::setItem(slotType type, string name, string description,int x, int y)
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
		_slotImg = IMAGEMANAGER->findImage("ÆøÅº½½·Ô");
		break;
	}

	_waveCnt = 0;
	_inInventory = false;
	_x = x;
	_y = y;
	_rc = RectMakeCenter(_x, _y, 52, 52);

	int _tileX = _rc.left / TILESIZE;
	int _tileY = _rc.top / TILESIZE;
	_currentTileIndex = _tileX + _tileY * TILEX;

}

void item::animation()
{
	if (_inInventory) return;
	
	_rc = RectMakeCenter(_x, _y, 52, 52);
	float _tileX = _rc.left / TILESIZE;
	float _tileY = _rc.top / TILESIZE;
	_currentTileIndex = _tileX + _tileY * TILEX;

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

void item::draw(HDC hdc)
{
	if (_inInventory)
	{
		_slotImg->render(CAMERAMANAGER->getCameraDC(), _rc.left, _rc.top);
		_itemImg->render(CAMERAMANAGER->getCameraDC(), _rc.left+ 8, _rc.top+11);
	}
	else
	{
		_itemImg->render(hdc, _x-26, _y-52);
	}
}

void item::rcSet()
{
	_rc = RectMakeCenter(_x + 10, _y + 10, _itemImg->getWidth(), _itemImg->getHeight());
}
