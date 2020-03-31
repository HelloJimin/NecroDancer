#include "stdafx.h"
#include "gameEnd.h"


gameEnd::gameEnd()
{
}


gameEnd::~gameEnd()
{
}

HRESULT gameEnd::init()
{
	_button[0].img = IMAGEMANAGER->findImage("로비로돌아가기");
	_button[1].img = IMAGEMANAGER->findImage("빠른재시작");
	_button[0].frameY = 0;
	_button[1].frameY = 0;

	for (int i = 0; i < 2; i++)
	{
		_button[i].rc = RectMakeCenter(WINSIZEX / 2 + WINSIZEX / 4 + 20, WINSIZEY / 2 + (i*_button[i].img->getFrameHeight()), _button[i].img->getFrameWidth(), _button[i].img->getFrameHeight());
	}
	_buttonNum = 0;
	_check = _button[_buttonNum].rc;

	return S_OK;
}

void gameEnd::release()
{
}

void gameEnd::update()
{
	if (KEYMANAGER->isOnceKeyDown('A')) _aClick = true;

	if (!_aClick)return;

	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		if (_buttonNum > 0) _buttonNum--;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		if (_buttonNum < 1) _buttonNum++;
	}

	_check = _button[_buttonNum].rc;

	RECT temp;
	for (int i = 0; i < 2; i++)
	{
		if (IntersectRect(&temp, &_check, &_button[i].rc))
		{
			_button[i].frameY = 1;

			if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
			{
				_aClick = false;
				switch (i)
				{
				case 0:
					PLAYER->gameReset("로비신");
					break;
				case 1:
					PLAYER->gameReset("테스트신");
					break;
				}
			}
		}
		else
		{
			_button[i].frameY = 0;
		}
	}
}

void gameEnd::render()
{
	if(!_aClick) IMAGEMANAGER->render("죽었습니다", CAMERAMANAGER->getCameraDC(), WINSIZEX / 2 - 233 * 3 / 2, WINSIZEY / 2 + 200);
	else
	{
		for (int i = 0; i < 2; i++)
		{
			_button[i].img->frameRender(CAMERAMANAGER->getCameraDC(), _button[i].rc.left, _button[i].rc.top, 0, _button[i].frameY);
		}
	}
}
