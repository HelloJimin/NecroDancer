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
	_isFire = false;
	_power = 3;
	_frameX = 0;
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
	item::animation();

	if (!_inInventory)return;

	if (KEYMANAGER->isOnceKeyDown('X') && _num>0)
	{
		tagTile* tempMap = PLAYER->getMap();
		bombTile = PLAYER->currentTile();

		_isFire = true;
		_num--;

		bombX = tempMap[bombTile].x;
		bombY = tempMap[bombTile].y;

		//EFFECTMANAGER->play("��ź�ִ�", x, y);
	}
	if (_isFire && BEAT->getCnt() % 29 == 0)
	{
		_frameX++;
	}

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
	
	if (_isFire)
	{
		_ani->frameRender(hdc, bombX, bombY, _frameX, 0);
	}
}

void bomb::active()
{
	if (!_isFire) return;

	if (_frameX > _ani->getMaxFrameX())
	{
		tagTile* tempMap = PLAYER->getMap();

		_frameX = 0;
		_isFire = false;

		int dx[] = { 0, -1, 1, TILEX, TILEY, TILEX-1, TILEX+1, TILEY-1, TILEY+1 };

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
				tempMap[check].obj == OBJ_NONE;
				tempMap[check].strength = 0;
				tempMap[check].walkable = true;
			}
			if (check == PLAYER->currentTile())
			{
				PLAYER->hit(_power);
			}
		}
	}
}
