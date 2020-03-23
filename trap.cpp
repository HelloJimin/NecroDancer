#include "stdafx.h"
#include "trap.h"


trap::trap()
{
}

trap::trap(OBJECT obj, int tileNum , tagTile tile[])
{
	_tile = tile;
	_tileNum = tileNum;
	_img = IMAGEMANAGER->findImage("วิมค");
	_trigger = false;

	_frameX = 0;

	_obj = obj;


	switch (_obj)
	{
	case OBJ_TRAP:
		_frameY = 0;
		break;
	case OBJ_LEFT:
		_frameY = 1;
		break;
	case OBJ_RIGHT:
		_frameY = 2;
		break;
	case OBJ_UP:
		_frameY = 3;
		break;
	case OBJ_DOWN:
		_frameY =4;
		break;
	}

	_rc = RectMakeCenter(_tile[_tileNum].x, _tile[_tileNum].y, 50, 50);

}


trap::~trap()
{
}

void trap::update()
{
	if (_trigger) return;


	RECT temp;

	//if (_obj == OBJ_TRAP)
	//{
	//	for (int i = 0; i < MONSTERMANAGER->getMonster().size();)
	//	{
	//		if (IntersectRect(&temp, &_rc, &MONSTERMANAGER->getMonster()[i]->getRc()))
	//		{
	//			_trigger = true;
	//			MONSTERMANAGER->getMonster()[i]->hit(2.0f);
	//			break;
	//		}
	//	}
	//}

	//if (_tile[PLAYER->currentTile()].x == _tile[_tileNum].x &&
	//	_tile[PLAYER->currentTile()].y == _tile[_tileNum].y && !PLAYER->getMove())
	//{
	//	_trigger = true;
	//	switch (_obj)
	//	{
	//	case OBJ_TRAP:
	//		PLAYER->hit(2.0f);
	//		break;
	//	case OBJ_LEFT:

	//		PLAYER->setDirection(LEFT);
	//		PLAYER->nextTile() = PLAYER->currentTile() - 1;
	//		PLAYER->moveCheck();

	//		break;
	//	}
	//}
	if (IntersectRect(&temp, &_rc, &PLAYER->getCollisionRc()) && !PLAYER->getMove())
	{
		_trigger = true;
		switch (_obj)
		{
		case OBJ_TRAP:
			PLAYER->hit(2.0f);
			break;
		case OBJ_LEFT:
			PLAYER->setDirection(LEFT);
			PLAYER->nextTile() = PLAYER->currentTile() - 1;
			PLAYER->moveCheck();
			break;
		case OBJ_RIGHT:

			break;
		case OBJ_UP:

			break;
		case OBJ_DOWN:
	
			break;
		}
	}
	
}
void trap::render(HDC hdc)
{
	if (!_tile[_tileNum].look) return;
	if (_tile[_tileNum].ray > 0)_img->frameRender(hdc, _tile[_tileNum].x - 10, _tile[_tileNum].y - 52, _frameX, _frameY);
	else _img->frameRender(hdc, _tile[_tileNum].x - 10, _tile[_tileNum].y - 52, _frameX, _frameY + 5);


}
