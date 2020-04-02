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
		_button[i].rc = RectMakeCenter(WINSIZEX / 2 , WINSIZEY / 2 + _button[i].img->getFrameHeight()*3+ (i*_button[i].img->getFrameHeight()), _button[i].img->getFrameWidth(), _button[i].img->getFrameHeight());
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
				_buttonNum = 0;
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

void gameEnd::render(int coin)
{
	if(!_aClick) IMAGEMANAGER->render("죽었습니다", CAMERAMANAGER->getCameraDC(), WINSIZEX / 2 - 233 * 3 / 2, WINSIZEY / 2 + 200);
	else
	{
		IMAGEMANAGER->alphaRender("어둡게", EFFECTMANAGER->getDC(), CAMERAX, CAMERAY, 150);
		IMAGEMANAGER->render("게임요약", CAMERAMANAGER->getCameraDC(), WINSIZEX / 2 - 51*3, 100);
		IMAGEMANAGER->render("다음적에게죽음", CAMERAMANAGER->getCameraDC(), WINSIZEX / 2 - 86*5, 300);
		PLAYER->nameImage()->render(CAMERAMANAGER->getCameraDC(), WINSIZEX / 2 - 86 * 5 + 20 + IMAGEMANAGER->findImage("다음적에게죽음")->getWidth() , 300);
		IMAGEMANAGER->render("코인점수", CAMERAMANAGER->getCameraDC(), WINSIZEX / 2 - 86*4 + 20, 400);

		int temp = 0;
		for (int i = 0; i < 3; i++)
		{
			if (coin < 100 && i == 0)continue;
			if (coin < 10 && i == 1)continue;
			PLAYER->getCoinUI().coinImg[i].img->frameRender(CAMERAMANAGER->getCameraDC(), WINSIZEX / 2 - 86 * 4 +40 + IMAGEMANAGER->findImage("코인점수")->getWidth() + (temp*PLAYER->getCoinUI().coinImg[i].img->getFrameWidth()), 405, PLAYER->getCoinUI().coinImg[i].frameX, 0);
			temp++;
		}

		for (int i = 0; i < 2; i++)
		{
			_button[i].img->frameRender(CAMERAMANAGER->getCameraDC(), _button[i].rc.left, _button[i].rc.top, 0, _button[i].frameY);
		}
	}
}
