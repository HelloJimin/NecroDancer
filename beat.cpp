#include "stdafx.h"
#include "beat.h"


beat::beat()
{
}


beat::~beat()
{
}

HRESULT beat::init()
{
	//턴초기화
	_cnt = 0;
	_speed = 6;
	_anime = 0;
	_turn = 0;
	_heart = IMAGEMANAGER->findImage("심장");
	_heartBox = RectMakeCenter(WINSIZEX / 2, WINSIZEY - 100, _heart->getFrameWidth(), _heart->getFrameHeight());
	_collisionHeart = RectMakeCenter(WINSIZEX / 2, WINSIZEY - 100, 120, 50 * 2);
	for (int i = 0; i < 2; i++)
	{
		_note.img[i] = IMAGEMANAGER->findImage("노트");
		_note.x[0] = 0;
		_note.x[1] = WINSIZEX;
		_note.y = WINSIZEY - 100;
		_note.rc[i] = RectMakeCenter(_note.x[i], _note.y, _note.img[i]->getWidth(), _note.img[i]->getHeight());
		_note.alpha = 0;
	}

	_miss.alpha = 0;
	_miss.img = IMAGEMANAGER->findImage("빗나감");
	_miss.rc = RectMake(_heartBox.left, _heartBox.top, _miss.img->getWidth(), _miss.img->getHeight());
	_miss.speed = 1;
	_vNote.push_back(_note);
	return S_OK;
}

void beat::release()
{
}

void beat::update()
{
	checkBeat();
	miss();
}

void beat::render(HDC hdc)
{
	//박자부분 렌더
	for (int i = 0; i < _vMiss.size(); i++)
	{
		_vMiss[i].img->render(CAMERAMANAGER->getCameraDC(), _vMiss[i].rc.left, _vMiss[i].rc.top);
	}
	for (int i = 0; i < _vNote.size(); i++)
	{
		if (_vNote[i].rc[0].right <= _heartBox.right - 40) _vNote[i].img[0]->alphaRender(CAMERAMANAGER->getCameraDC(), _vNote[i].rc[0].left, _vNote[i].rc[0].top, _vNote[i].alpha);
		if (_vNote[i].rc[1].left >= _heartBox.left + 40) _vNote[i].img[1]->alphaRender(CAMERAMANAGER->getCameraDC(), _vNote[i].rc[1].left, _vNote[i].rc[1].top, _vNote[i].alpha);
	}
	_heart->frameRender(CAMERAMANAGER->getCameraDC(), _heartBox.left, _heartBox.top, _anime, 0);

	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		Rectangle(CAMERAMANAGER->getCameraDC(), _collisionHeart.left, _collisionHeart.top, _collisionHeart.right, _collisionHeart.bottom);
	}
	UINT a = SOUNDMANAGER->getLength("1-1");
	UINT b = SOUNDMANAGER->getPosition("1-1");
	char str[128];
	wsprintf(str, "%d", a);
	TextOut(CAMERAMANAGER->getCameraDC(), WINSIZEX / 2, WINSIZEY / 2,str, strlen(str));
	wsprintf(str, "%d", b);
	TextOut(CAMERAMANAGER->getCameraDC(), WINSIZEX / 2, WINSIZEY / 2+100, str,strlen(str));
}

void beat::checkBeat()
{
	//_speed = 290 * TIMEMANAGER->getElapsedTime();
	_speed = _collisionHeart.left / 43;
	_cnt++;

	UINT a = SOUNDMANAGER->getLength("1-1");
	int b = SOUNDMANAGER->getPosition("1-1");
	if (_cnt+1 == 30)
	a = SOUNDMANAGER->getPosition("1-1");

	//if (_cnt % 29 == 0)
	if (b/100 % 5 == 0)
	{
		_turn++;
		//_vNote.push_back(_note);
	}


	for (int i = 0; i < _vNote.size(); i++)
	{
		_vNote[i].alpha += 7;
		_vNote[i].x[0] += _speed;
		_vNote[i].x[1] -= _speed;

		_vNote[i].rc[0] = RectMakeCenter(_vNote[i].x[0], _vNote[i].y, _vNote[i].img[0]->getWidth(), _vNote[i].img[0]->getHeight());
		_vNote[i].rc[1] = RectMakeCenter(_vNote[i].x[1], _vNote[i].y, _vNote[i].img[1]->getWidth(), _vNote[i].img[1]->getHeight());

		if (IntersectRect(&_temp, &_vNote[i].rc[0], &_collisionHeart))
		{
			_check = true;
		}

		if (_vNote[i].rc[0].right >= _collisionHeart.right)
		{
			//if (!KEYMANAGER->isOnceKeyDown(VK_DOWN) && !KEYMANAGER->isOnceKeyDown(VK_UP) &&
			//	!KEYMANAGER->isOnceKeyDown(VK_LEFT) && !KEYMANAGER->isOnceKeyDown(VK_RIGHT))
			_check = false;
			_vNote.erase(_vNote.begin() + i);
			break;
		}

		if (_check)_anime = 1;
		if (!_check)_anime = 0;
	}
}

void beat::removeNote()
{
	for (int i = 0; i < _vNote.size(); i++)
	{
		if (IntersectRect(&_temp, &_vNote[i].rc[0], &_collisionHeart))
		{
			_check = false;
			_vNote.erase(_vNote.begin() + i);
			break;
		}
	}
}

void beat::miss()
{
	for (int i = 0; i < _vMiss.size(); i++)
	{
		_vMiss[i].rc.top -= _vMiss[i].speed;
		_vMiss[i].rc.bottom -= _vMiss[i].speed;

		if (_vMiss[i].rc.top <= WINSIZEY / 2 + 150)
		{
			_vMiss.erase(_vMiss.begin() + i);
			break;
		}
	}
}

void beat::addMiss()
{
	_vMiss.push_back(_miss);
}
