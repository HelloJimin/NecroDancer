#include "stdafx.h"
#include "monster.h"


monster::monster()
{
}


monster::~monster()
{
}

HRESULT monster::init(string name, int x, int y, tagTile * map)
{
	_pCurrentMap = map;
	_monsterImg = IMAGEMANAGER->findImage(name);
	_currentX = x;
	_currentY = y;
	_silhouette = false;
	_frameX = 0;
	_frameY = 0;
	_rhythm = 0;
	_attack = false;
	_direction = DOWN;
	_rc = RectMakeCenter(_currentX, _currentY, _monsterImg->getFrameWidth(), _monsterImg->getFrameHeight());
	_collisionRc = _rc;

	_tileX = _rc.left / TILESIZE;
	_tileY = _rc.top / TILESIZE;
	_currentTileIndex = _tileX + _tileY * TILEX + TILEX;
	return S_OK;
}

void monster::release()
{
}

void monster::update()
{
	animation();
	rhythmUpdate();
	frontCheck();
}

void monster::render(HDC hdc)
{
	_monsterImg->frameRender(hdc, _rc.left, _rc.top, _frameX, _frameY);
}

void monster::animation()
{

	if (PLAYER->getTurnCnt() % 12 == 0)
	{
		_frameX++;
		if (_frameX > _monsterImg->getMaxFrameX())_frameX = 0;
	}
	if (_silhouette) _frameY = 1;
	else _frameY = 0;
}

void monster::frontCheck()
{
	_tileX = _rc.left / TILESIZE;
	_tileY = _rc.top / TILESIZE;


	switch (_direction)
	{
	case LEFT:
		_currentTileIndex = _tileX + _tileY * TILEX;
		_nextTileIndex = _tileX - 1 + _tileY * TILEX;
		break;
	case RIGHT:
		_currentTileIndex = (_tileX + _tileY * TILEX);
		_nextTileIndex = (_tileX + _tileY * TILEX) + 1;
		break;
	case UP:
		_currentTileIndex = _tileX + _tileY * TILEX;
		_nextTileIndex = _tileX + (_tileY - 1) * TILEX;
		break;
	case DOWN:
		_currentTileIndex = _tileX + (_tileY - 1) * TILEX + TILEX;
		_nextTileIndex = _tileX + _tileY * TILEX + TILEX;
		break;
	}
}

void monster::attack()
{
}

void monster::rhythmUpdate()
{
	if (PLAYER->getTurnCnt() % 29 == 0)
	{
		_rhythm++;
	}
}
