#include "stdafx.h"
#include "wallTorch.h"


wallTorch::wallTorch()
{
}

wallTorch::wallTorch(int tileNum, tagTile tile[])
{
	_img = IMAGEMANAGER->findImage("º®È¶ºÒ");
	_tile = tile;
	_tileNum = tileNum;
	_frameX = 0;
	_frameY = 0;

	_aStar = new aStar;
	_ray = new raycast;
	_ray->init(_tile);
}


wallTorch::~wallTorch()
{
}


void wallTorch::update()
{
	findPlayer();

	if (BEAT->getCnt() % 12 == 0)
	{
		_frameX++;
		if (_frameX > _img->getMaxFrameX())_frameX = 0;
	}
}

void wallTorch::render(HDC hdc)
{
	if (!_tile[_tileNum].look) return;
	if(_tile[_tileNum].ray>0)_img->frameRender(hdc, _tile[_tileNum].x-10, _tile[_tileNum].y-52, _frameX, _frameY);
	else _img->frameRender(hdc, _tile[_tileNum].x - 10, _tile[_tileNum].y - 52, _frameX, _frameY+1);
}

void wallTorch::findPlayer()
{
	//if (!_check)
	//{
	//	if (CAMERAX - TILEX >= _tile[_tileNum].x || _tile[_tileNum].x >= CAMERAX + WINSIZEX + TILEX ||
	//		CAMERAY - TILEX >= _tile[_tileNum].y || _tile[_tileNum].y >= CAMERAY + WINSIZEY + TILEX) return;
	//	if (_aStar->findPlayer(_tile, _tileNum, PLAYER->currentTile()))
	//	{
	//		_check = true;
	//	}
	//}
	//else
	//{
	//	_tile[_tileNum].look = true;
	//	_tile[_tileNum].ray = 1;
	//	_ray->torch(_aStar->getNextTile());

	//	if (CAMERAX - TILEX >= _tile[_tileNum].x || _tile[_tileNum].x >= CAMERAX + WINSIZEX + TILEX ||
	//		CAMERAY - TILEX >= _tile[_tileNum].y || _tile[_tileNum].y >= CAMERAY + WINSIZEY + TILEX)
	//		_check = false;
	//}


	if (CAMERAX - TILEX >= _tile[_tileNum].x || _tile[_tileNum].x >= CAMERAX + WINSIZEX + TILEX ||
		CAMERAY - TILEX >= _tile[_tileNum].y || _tile[_tileNum].y >= CAMERAY + WINSIZEY + TILEX) return;

	int p = PLAYER->currentTile();
	if (getDistance(_tile[_tileNum].x, _tile[_tileNum].y, _tile[p].x, _tile[p].y) > 400) return;

	if (_aStar->findPlayer(_tile, _tileNum, PLAYER->currentTile()))
	{
		_check = true;
		_tile[_tileNum].look = true;
		_tile[_tileNum].ray = 1;
		_ray->torch(_aStar->getNextTile());
	}
}
