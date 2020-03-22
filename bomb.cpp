#include "stdafx.h"
#include "bomb.h"


bomb::bomb()
{
}

bomb::bomb(string name, slotType type, int num, string description, int x, int y, int price)
{
	setItem(type, name, description,  x,  y,price);
	_num = num;
	_ani = IMAGEMANAGER->findImage("气藕局聪");
	_isFire = false;
	_power = 3;
	_frameX = 0;
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

	if (KEYMANAGER->isOnceKeyDown('X') && _num>0 && !_isFire)
	{
		tagTile* tempMap = PLAYER->getMap();
		bombTile = PLAYER->currentTile();

		_isFire = true;
		_num--;

		bombX = tempMap[bombTile].x;
		bombY = tempMap[bombTile].y;
	}
	if (_isFire && BEAT->getCnt() % 29 == 0)
	{
		_frameX++;
	}
}

void bomb::render(HDC hdc)
{
	if (_inInventory && _num > 0)
	{
		_itemImg = IMAGEMANAGER->findImage("气藕");
		_slotImg->render(CAMERAMANAGER->getCameraDC(), _rc.left, _rc.top);
		_itemImg->render(CAMERAMANAGER->getCameraDC(), _rc.left + 8, _rc.top + 11);
	}
	else if(!_inInventory)
	{
		_itemImg->render(hdc, _x - 20, _y - 40);
	}
	
	if (_isFire)
	{
		_ani->frameRender(EFFECTMANAGER->getDC() , bombX-25, bombY-25, _frameX, 0);
	}
}

void bomb::active()
{
	if (!_isFire) return;

	
	if (_frameX > _ani->getMaxFrameX())
	{
		SOUNDMANAGER->play("bomb");
		EFFECTMANAGER->play("气藕气惯", bombX, bombY);
		tagTile* tempMap = PLAYER->getMap();

		_frameX = 0;
		_isFire = false;

		int dx[] = { 0, -1, 1, TILEX, TILEX-1, TILEX+1, -TILEY, -(TILEY-1), -(TILEY+1) };

		for (int i = 0; i < 9; i++)
		{
			int check = bombTile + dx[i];

			for (int k = 0; k < MONSTERMANAGER->getMonster().size(); k++)
			{
				if (check == MONSTERMANAGER->getMonster()[k]->currentTile())
				{
					MONSTERMANAGER->getMonster()[k]->hit(_power);
				}
			}
			if (tempMap[check].obj == OBJ_NOMALWALL ||
				tempMap[check].obj == OBJ_SKULLWALL ||
				tempMap[check].obj == OBJ_WHITEWALL ||
				tempMap[check].obj == OBJ_GOLDWALL ||
				tempMap[check].obj == OBJ_IRONWALL)
			{
				tempMap[check].obj = OBJ_NONE;
				tempMap[check].strength = 0;
				tempMap[check].ray = 0;
				tempMap[check].itemPoint = "";
				tempMap[check].walkable = true;
			}
			if (check == PLAYER->currentTile())
			{
				PLAYER->hit(_power);

			}
		}
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
