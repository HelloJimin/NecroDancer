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

	_isShop = false;
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

void item::setItem(slotType type, string name, string description, int x, int y, int price)
{
	setPrice(price);

	_name = name;
	_itemImg = IMAGEMANAGER->findImage(name);
	_description = description;
	_type = type;

	switch (type)
	{
	case SHOVEL:
		_slotImg = IMAGEMANAGER->findImage("삽");
		break;
	case ATTACK:
		_slotImg = IMAGEMANAGER->findImage("무기");
		break;
	case BODY:
		_slotImg = IMAGEMANAGER->findImage("보디");
		break;
	case FEET:
		_slotImg = IMAGEMANAGER->findImage("신발");
		break;
	case TORCH:
		_slotImg = IMAGEMANAGER->findImage("횃불");
		break;
	case ITEM:
		_slotImg = IMAGEMANAGER->findImage("아이템");
		break;
	case BOMB:
		_slotImg = IMAGEMANAGER->findImage("폭탄슬롯");
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
	else if (!_inInventory && _isShop)
	{
		_itemImg->render(hdc, _x - 26, _y - 52);
		tagTile* temp = PLAYER->getMap();
		for (int i = 0; i < _vPriceImg.size(); ++i)
		{
			_vPriceImg[i]->img->frameRender(hdc, temp[_currentTileIndex-TILEX*2].rc.left+
			_vPriceImg[i]->img->getFrameWidth() +(i*_vPriceImg[i]->img->getFrameWidth()), 
			temp[_currentTileIndex - TILEX * 2].rc.bottom + _vPriceImg[i]->img->getFrameHeight()*4+10,
			_vPriceImg[i]->frameX, 0);
		}
	}
	else if(!_inInventory)
	{
		_itemImg->render(hdc, _x - 26, _y - 52);
	}
}

void item::rcSet()
{
	_rc = RectMakeCenter(_x + 10, _y + 10, _itemImg->getWidth(), _itemImg->getHeight());
}

void item::setPrice(int price)
{
	_price = price;

	if (_price >= 100)
	{
		tagPrice* temp = new tagPrice;
		temp->img = new image;
		temp->img =	IMAGEMANAGER->findImage("숫자");
		temp->frameX = _price % 1000 / 100;
		_vPriceImg.push_back(temp);
	}
	if (_price >= 10)
	{
		tagPrice* temp = new tagPrice;
		temp->img = new image;
		temp->img = IMAGEMANAGER->findImage("숫자");
		temp->frameX = _price % 100 / 10;
		_vPriceImg.push_back(temp);
	}
	tagPrice* temp = new tagPrice;
	temp->img = new image;
	temp->img = IMAGEMANAGER->findImage("숫자");
	temp->frameX = _price % 10;
	_vPriceImg.push_back(temp);
}

void item::shopCheck()
{
	tagTile* _tile = PLAYER->getMap();
	if (_tile[_currentTileIndex - TILEX * 2].terrain == TERRAIN_SHOP || _tile[_currentTileIndex - TILEX * 2].startPoint=="상점주인") 
		_isShop = true;
	else _isShop = false;

}
