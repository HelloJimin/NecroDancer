#include "stdafx.h"
#include "introScene.h"


introScene::introScene()
{
}


introScene::~introScene()
{
}

HRESULT introScene::init()
{
	SOUNDMANAGER->play("intro");
	_intro = IMAGEMANAGER->findImage("인트로");

	_button[0].img = IMAGEMANAGER->findImage("스타트");
	_button[1].img = IMAGEMANAGER->findImage("맵툴");
	_button[2].img = IMAGEMANAGER->findImage("나가기");
	_button[0].frameY = 0;
	_button[1].frameY = 0;
	_button[2].frameY = 0;

	for (int i = 0; i < 3; i++)
	{
		_button[i].rc = RectMakeCenter(WINSIZEX/2 + WINSIZEX / 4+20, WINSIZEY/2+(i*_button[i].img->getFrameHeight()), _button[i].img->getFrameWidth(), _button[i].img->getFrameHeight());
	}
	_buttonNum = 0;
	_check = _button[_buttonNum].rc;
	return S_OK;
}

void introScene::release()
{
}

void introScene::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		if (_buttonNum > 0) _buttonNum--;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		if (_buttonNum <2) _buttonNum++;
	}

	_check = _button[_buttonNum].rc;

	RECT temp;
	for (int i = 0; i < 3; i++)
	{
		if (IntersectRect(&temp, &_check, &_button[i].rc))
		{
			_button[i].frameY = 1;

			if(KEYMANAGER->isOnceKeyDown(VK_RETURN))
			switch (i)
			{
			case 0:
				SOUNDMANAGER->stop("intro");
				SCENEMANAGER->changeScene("로비신");
				break;
			case 1:
				SOUNDMANAGER->stop("intro");
				SCENEMANAGER->changeScene("맵툴신");
				break;
			case 2:
				PostQuitMessage(0);
				break;
			}
		}
		else
		{
			_button[i].frameY = 0;
		}
	}
}

void introScene::render()
{
	_intro->render(getMemDC(), 0, 0);

	for (int i = 0; i < 3; i++)
	{
		_button[i].img->frameRender(getMemDC(), _button[i].rc.left, _button[i].rc.top,0, _button[i].frameY);
	}
}
