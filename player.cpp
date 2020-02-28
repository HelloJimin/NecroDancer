#include "stdafx.h"
#include "player.h"


player::player()
{
}


player::~player()
{
}

HRESULT player::init(HDC hdc)
{

	x = WINSIZEX / 2;
	y = WINSIZEY / 2;
	rc = RectMakeCenter(x, y, 50, 50);

	_bodyImg = IMAGEMANAGER->findImage("기본몸R");
	_headImg = IMAGEMANAGER->findImage("케이던스R");


	cnt = 0;
	return S_OK;
}

void player::release()
{
}

void player::update()
{
	cnt++;
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		y -= 3;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		y += 3;
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_bodyImg = IMAGEMANAGER->findImage("기본몸L");
		_headImg = IMAGEMANAGER->findImage("케이던스L");
		x -= 3;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_bodyImg = IMAGEMANAGER->findImage("기본몸R");
		_headImg = IMAGEMANAGER->findImage("케이던스R");
		x += 3;
	}
	CAMERAMANAGER->setCameraCenter(PointMake(x, y));
	rc = RectMakeCenter(x, y, 50, 50);

	if (cnt %15 == 0)
	{
		_currentX++;
		if (_currentX > _bodyImg->getMaxFrameX())_currentX = 0;

	}
}

void player::render(HDC hdc)
{
	Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);

	_bodyImg->frameRender(hdc, rc.left, rc.top-28, _currentX, 0);
	_headImg->frameRender(hdc, rc.left, rc.top-28, _currentX, 0);

}
