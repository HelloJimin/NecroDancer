#include "stdafx.h"
#include "trap.h"


trap::trap()
{
}

trap::trap(OBJECT obj, int tileNum , tagTile tile[])
{
	_tile = tile;
	_tileNum = tileNum;
	_img = IMAGEMANAGER->findImage("함정");
	_trigger = false;
	_trapName  = IMAGEMANAGER->findImage("함정이름");
	_frameX = 0;

	_obj = obj;

	switch (_obj)
	{
	case OBJ_TRAP:
		_frameY = 0;
		break;
	case OBJ_BOMBTRAP:
		_frameY = 5;
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
	animation();
	damageCheck();
}
void trap::render(HDC hdc)
{
	if (!_tile[_tileNum].look) return;
	if (_tile[_tileNum].ray > 0)_img->frameRender(hdc, _rc.left+_img->getFrameWidth()/8, _rc.top+_img->getFrameHeight()/8, _frameX, _frameY);
	else _img->frameRender(hdc, _rc.left, _rc.top, _frameX, _frameY+6);

}

void trap::animation()
{
	if (!_trigger) return;

	if (BEAT->getCnt() % 6 == 0)
	{
		_frameX++;

		if (_obj == OBJ_TRAP)
		{
			if (_frameX > _img->getMaxFrameX())
			{
				//_trigger = false;
				_frameX = _img->getMaxFrameX();
			}
		}
		if (_obj == OBJ_BOMBTRAP)
		{
			if (_frameX > _img->getMaxFrameX())
			{
				_frameX = _img->getMaxFrameX();
			}
		}
		else
		{
			if (_frameX > _img->getMaxFrameX())
			{
				_frameX = 0;
				_trigger = false;
			}
		}
	}
}

void trap::damageCheck()
{
	if (_trigger) return;

	RECT temp;
	if (IntersectRect(&temp, &_rc, &PLAYER->getCollisionRc()) && !PLAYER->getMove())
	{
		if (PLAYER->getFly()) return;
		_frameX++;

		_trigger = true;
		switch (_obj)
		{
		case OBJ_TRAP:
			PLAYER->hit(2.0f, _trapName);
			break;
		case OBJ_LEFT:
			PLAYER->setDirection(LEFT);
			PLAYER->nextTile() = PLAYER->currentTile() - 1;
			PLAYER->moveCheck();
			break;
		case OBJ_RIGHT:
			PLAYER->setDirection(RIGHT);
			PLAYER->nextTile() = PLAYER->currentTile() + 1;
			PLAYER->moveCheck();
			break;
		case OBJ_UP:
			PLAYER->setDirection(UP);
			PLAYER->nextTile() = PLAYER->currentTile() - TILEX;
			PLAYER->moveCheck();
			break;
		case OBJ_DOWN:
			PLAYER->setDirection(DOWN);
			PLAYER->nextTile() = PLAYER->currentTile() + TILEX;
			PLAYER->moveCheck();
			break;
		case OBJ_BOMBTRAP:
			PLAYER->getBomb() = true;
			break;
		}
	}

	if (_obj != OBJ_TRAP) return;

	for (int i = 0; i < MONSTERMANAGER->getMonster().size(); ++i)
	{
		if (IntersectRect(&temp, &_rc, &MONSTERMANAGER->getMonster()[i]->getRc()) && !MONSTERMANAGER->getMonster()[i]->getMove())
		{
			_frameX++;
			_trigger = true;
			MONSTERMANAGER->getMonster()[i]->hit(2);
			MONSTERMANAGER->getMonster()[i]->getHit() = false;
		}
	}
}
