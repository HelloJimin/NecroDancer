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


	return S_OK;
}

void player::release()
{
}

void player::update()
{
	if (KEYMANAGER->isStayKeyDown('W'))
	{
		y -= 3;
	}
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		y += 3;
	}
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		x -= 3;
	}
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		x += 3;
	}
	CAMERAMANAGER->setCameraCenter(PointMake(x, y));
	rc = RectMakeCenter(x, y, 50, 50);

}

void player::render(HDC hdc)
{
	Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
}
