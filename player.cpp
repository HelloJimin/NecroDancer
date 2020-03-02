#include "stdafx.h"
#include "player.h"

player::player(){}
player::~player(){}

HRESULT player::init()
{
	_inven = new inventory;
	_inven->init();

	_bodyImg = IMAGEMANAGER->findImage("기본몸R");
	_headImg = IMAGEMANAGER->findImage("케이던스R");

	//플레이어 시작위치
	_currentX = _collisionX = 494;
	_currentY = _collisionY = 338;
	
	_rc = RectMakeCenter(_currentX, _currentY, 50, 50);
	_collisionRc = _rc;

	_tileX = _rc.left / TILESIZE;
	_tileY = _rc.top / TILESIZE;
	_nextTileIndex = (_tileX + 1 + _tileY * TILEX) + TILEX - 1;

	_direction = DOWN;
	_weapon = SWORD;

	_isJump = false;
	_isMove = false;

	_moveSpeed = 13;
	_coin = _diamond = 0;


	//턴초기화
	_turn.cnt = 0;
	_turn.speed = 6;
	_turn.anime = 0;
	_turn.heart = IMAGEMANAGER->findImage("심장");
	_turn.heartBox = RectMakeCenter(WINSIZEX / 2, WINSIZEY - 100, _turn.heart->getFrameWidth(), _turn.heart->getFrameHeight());

	for (int i = 0; i < 2; i++)
	{
		_note.img[i] = IMAGEMANAGER->findImage("노트");
		_note.x[0] = WINSIZEX / 2 - (4 * 234);
		_note.x[1] = WINSIZEX / 2 + (4 * 234);
		_note.y = WINSIZEY - 100;
		_note.rc[i] = RectMakeCenter(_note.x[i], _note.y, _note.img[i]->getWidth(), _note.img[i]->getHeight());
	}

	return S_OK;
}

void player::release()
{
//	SAFE_DELETE(_inven);
}

void player::update()
{
	_inven->update();
	turn();
	
	_turn.check = true;
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		if (rhythmCheck())
		{
			_direction = LEFT;
			frontCheck();
			removeNote();
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		if (rhythmCheck())
		{
			_direction = RIGHT;
			frontCheck();
			removeNote();
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		if (rhythmCheck())
		{
			_direction = UP;
			frontCheck();
			removeNote();
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		if (rhythmCheck())
		{
			_direction = DOWN;
			frontCheck();
			removeNote();
		}
	}

	move();
}

void player::render(HDC hdc)
{
	//앞타일 확인용 렌더
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		Rectangle(hdc, _collisionRc.left, _collisionRc.top, _collisionRc.right, _collisionRc.bottom);

	}
	switch (_direction)
	{
	case LEFT:
		_bodyImg = IMAGEMANAGER->findImage("기본몸L");
		_headImg = IMAGEMANAGER->findImage("케이던스L");
		break;
	case RIGHT:
		_bodyImg = IMAGEMANAGER->findImage("기본몸R");
		_headImg = IMAGEMANAGER->findImage("케이던스R");
		break;
	}

	int x, y;
	x = _collisionRc.left + (_collisionRc.right - _collisionRc.left) / 2;
	y = _collisionRc.top + (_collisionRc.bottom - _collisionRc.top) / 2;
	CAMERAMANAGER->setCameraCenter(PointMake(x, y));

	_bodyImg->frameRender(hdc, _rc.left, _rc.top - 28, _currentFrameX, 0);
	_headImg->frameRender(hdc, _rc.left, _rc.top - 28, _currentFrameX, 0);

}

void player::frontCheck()
{
	//타일 앞의 몬스터가 공격인지 판별 후



	//앞 타일이 비어있는지 판별
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
		_currentTileIndex = _tileX + (_tileY-1) * TILEX + TILEX;
		_nextTileIndex = _tileX + _tileY * TILEX + TILEX ;
		break;
	}
	//앞타일이 비어있으면 이동
	if (_pCurrentMap[_nextTileIndex].obj == OBJ_NONE)
	{
		_isMove = true;
		_isJump = true;
	}
	else
	{
		_nextTileIndex = _currentTileIndex;
	}
}

void player::move()
{
	if (_isMove&& _pCurrentMap[_nextTileIndex].obj == OBJ_NONE)//좌우이동
	{
		switch (_direction)
		{
		case LEFT:
			if (_pCurrentMap[_nextTileIndex].x != _currentX)
			{
				_currentX -= _moveSpeed;
				_collisionX -= _moveSpeed;
			}
			else _isMove = false;
			break;
		case RIGHT:
			if (_pCurrentMap[_nextTileIndex].x!= _currentX)
			{
				_currentX += _moveSpeed;
				_collisionX += _moveSpeed;
			}
			else _isMove = false;
			break;
		case UP:
			if (_pCurrentMap[_nextTileIndex].y != _collisionY)
			{
				_collisionY -= _moveSpeed;
			}
			else _isMove = false;
			break;
		case DOWN:
			if (_pCurrentMap[_nextTileIndex].y != _collisionY)
			{
				_collisionY += _moveSpeed;
			}
			else _isMove = false;
			break;
		}
	}

	if (_isJump)  //상하이동
	{
		switch (_direction)
		{
		case LEFT:
			if (_pCurrentMap[_nextTileIndex].y - 26 != _currentY) _currentY -= _moveSpeed;
			else _isJump = false;
			break;
		case RIGHT:
			if (_pCurrentMap[_nextTileIndex].y - 26 != _currentY) _currentY -= _moveSpeed;
			else _isJump = false;
			break;
		case UP:
			if (_pCurrentMap[_nextTileIndex].y - 26 != _currentY) _currentY -= _moveSpeed;
			else _isJump = false;
			break;
		case DOWN:
			if (_pCurrentMap[_nextTileIndex].y - 78 != _currentY) _currentY -= _moveSpeed;
			else _isJump = false;
			break;
		}
	}
	else if (!_isJump && _pCurrentMap[_nextTileIndex].obj == OBJ_NONE)
	{
		if (_pCurrentMap[_nextTileIndex].y != _currentY) _currentY += _moveSpeed;
	}

	_rc = RectMakeCenter(_currentX, _currentY, 50, 50);
	_collisionRc = RectMakeCenter(_collisionX, _collisionY, 50, 50);

	//애니메이션 움직임
	if (_turn.cnt % 12 == 0)
	{
		_currentFrameX++;
		if (_currentFrameX > _bodyImg->getMaxFrameX())_currentFrameX = 0;
	}
}

void player::turn()
{
	_turn.speed = 300 * TIMEMANAGER->getElapsedTime();
	_turn.cnt++;
	if (_turn.cnt % 29 == 0)
	{
		_turn.vNote.push_back(_note);
	}

	for (int i = 0; i < _turn.vNote.size(); i++)
	{
		_turn.vNote[i].x[0] += _turn.speed;
		_turn.vNote[i].x[1] -= _turn.speed;

		_turn.vNote[i].rc[0] = RectMakeCenter(_turn.vNote[i].x[0], _turn.vNote[i].y, _turn.vNote[i].img[0]->getWidth(), _turn.vNote[i].img[0]->getHeight());
		_turn.vNote[i].rc[1] = RectMakeCenter(_turn.vNote[i].x[1], _turn.vNote[i].y, _turn.vNote[i].img[1]->getWidth(), _turn.vNote[i].img[1]->getHeight());

		if (IntersectRect(&_temp, &_turn.vNote[i].rc[0], &_turn.heartBox))
		{
			_turn.check = true;
		}
		
		if (_turn.vNote[i].rc[0].right >= _turn.heartBox.right + _turn.vNote[i].img[0]->getWidth())
		{
			_turn.check = false;
			_turn.vNote.erase(_turn.vNote.begin() + i);
			break;
		}

		if(_turn.check) _turn.anime = 1;
		if(!_turn.check) _turn.anime = 0;
	}
}

void player::UIrender(HDC hdc)
{
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		if (_pCurrentMap[_nextTileIndex].obj != OBJ_NONE)
		{
			HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(255, 0, 0));
			HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);
			Rectangle(hdc, _pCurrentMap[_nextTileIndex].rc.left, _pCurrentMap[_nextTileIndex].rc.top, _pCurrentMap[_nextTileIndex].rc.right, _pCurrentMap[_nextTileIndex].rc.bottom);
			SelectObject(hdc, oldBrush);
			DeleteObject(myBrush);
		}
		HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0));
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);
		Rectangle(hdc, _pCurrentMap[_currentTileIndex].rc.left, _pCurrentMap[_currentTileIndex].rc.top, _pCurrentMap[_currentTileIndex].rc.right, _pCurrentMap[_currentTileIndex].rc.bottom);
		SelectObject(hdc, oldBrush);
		DeleteObject(myBrush);

	}
	//인벤토리 렌더....
	_inven->render(hdc);

	//우상단 코인다이아 부분 렌더
	IMAGEMANAGER->render("코인다이아", CAMERAMANAGER->getCameraDC(), WINSIZEX - 50*3 , 20 );
	SetTextColor(CAMERAMANAGER->getCameraDC(), RGB(255, 255, 255));
	HFONT myFont = CreateFont(20, 0, 0, 0, 800, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, TEXT("굴림"));
	HFONT oldFont = (HFONT)SelectObject(CAMERAMANAGER->getCameraDC(), myFont);
	wsprintf(_str, "x%d", _coin);
	TextOut(CAMERAMANAGER->getCameraDC(), WINSIZEX - 60, 40 ,  _str, strlen(_str));
	wsprintf(_str, "x%d", _diamond);
	TextOut(CAMERAMANAGER->getCameraDC(), WINSIZEX - 60, 85, _str, strlen(_str));
	SelectObject(CAMERAMANAGER->getCameraDC(), oldFont);
	DeleteObject(myFont);

	//박자부분 렌더
	for (int i = 0; i < _turn.vNote.size(); i++)
	{
		if (_turn.vNote[i].rc[0].right <= _turn.heartBox.right-40) _turn.vNote[i].img[0]->alphaRender(CAMERAMANAGER->getCameraDC(), _turn.vNote[i].rc[0].left, _turn.vNote[i].rc[0].top, 255);
		if (_turn.vNote[i].rc[1].left >= _turn.heartBox.left+40) _turn.vNote[i].img[1]->alphaRender(CAMERAMANAGER->getCameraDC(), _turn.vNote[i].rc[1].left, _turn.vNote[i].rc[1].top, 255);
	}
	_turn.heart->frameRender(CAMERAMANAGER->getCameraDC(), _turn.heartBox.left, _turn.heartBox.top, _turn.anime ,0);

	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		Rectangle(CAMERAMANAGER->getCameraDC(), _turn.heartBox.left, _turn.heartBox.top, _turn.heartBox.right, _turn.heartBox.bottom);
	}


}

void player::removeNote()
{
	for (int i = 0; i < _turn.vNote.size(); i++)
	{
		if (IntersectRect(&_temp, &_turn.vNote[i].rc[0], &_turn.heartBox))
		{
			_turn.check = false;
			_turn.vNote.erase(_turn.vNote.begin() + i);
			break;
		}
	}
}

