#include "stdafx.h"
#include "ghost.h"


ghost::ghost()
{
}


ghost::~ghost()
{
}

HRESULT ghost::init(string name, int x, int y, int coin, tagTile * map)
{
	monster::init(name, x, y, coin, map);
	_atk = 0.5f;
	_alpha = 255;
	_aStar = new aStar;
	_monsterNameImg = IMAGEMANAGER->findImage("유령이름");
	return S_OK;
}

void ghost::render(HDC hdc)
{
	if (KEYMANAGER->isToggleKey(VK_TAB)) Rectangle(hdc, _collisionRc.left, _collisionRc.top, _collisionRc.right, _collisionRc.bottom);
	_monsterImg->alphaRender(hdc, _collisionRc.left - _monsterImg->getFrameWidth() / 8, _collisionRc.top - _monsterImg->getFrameHeight() / 4, _alpha);
	hpRender(hdc);
}

void ghost::silhouetteRender(HDC hdc)
{
	if (KEYMANAGER->isToggleKey(VK_TAB)) Rectangle(hdc, _collisionRc.left, _collisionRc.top, _collisionRc.right, _collisionRc.bottom);
	_monsterImg->alphaRender(hdc, _collisionRc.left - _monsterImg->getFrameWidth() / 8, _collisionRc.top - _monsterImg->getFrameHeight() / 4, _alpha);
	hpRender(hdc);
}

void ghost::frontCheck()
{
	alphaCheck();

	_nextTileIndex = _aStar->aStarTile(_pCurrentMap, _currentTileIndex, PLAYER->currentTile());
	if (atkCnt==1)
	{
		if (PLAYER->currentTile() == _nextTileIndex) _isAttack = true;
	}
	aniCheck();
}

void ghost::choiceAction()
{
	if ( _isBeat)
	{
		_isBeat = false;
		atkCnt++;
		atkCnt %= 2;
		frontCheck();

		if (playerCheck())
		{
			_nextTileIndex = _currentTileIndex;
			return;
		}

		if (walkableCheck())
		{
			_isMove = true;
			_pCurrentMap[_currentTileIndex].walkable = true;
			_pCurrentMap[_nextTileIndex].walkable = false;
			_currentTileIndex = _nextTileIndex;
		}
		else
		{
			_isMove = false;
			_nextTileIndex = _currentTileIndex;
		}
	}
}

void ghost::move()
{
	if (!_isMove) return;
	
	if (_currentX < _pCurrentMap[_nextTileIndex].x)
	{
		_currentX += _moveSpeed;
	}
	if (_currentX > _pCurrentMap[_nextTileIndex].x)
	{
		_currentX -= _moveSpeed;
	}
	if (_currentY < _pCurrentMap[_nextTileIndex].y)
	{
		_currentY += _moveSpeed;
	}
	if (_currentY > _pCurrentMap[_nextTileIndex].y)
	{
		_currentY -= _moveSpeed;
	}

	if (getDistance(_currentX, _currentY, _pCurrentMap[_nextTileIndex].x, _pCurrentMap[_nextTileIndex].y) == 0) _isMove = false;

	_collisionRc = RectMakeCenter(_currentX, _currentY, 50, 50);

}

void ghost::alphaCheck()
{
	DIRECTION pDirection = PLAYER->getPlayerDir();
	if (_direction == 0 && pDirection == 1 || _direction == 1 && pDirection == 0 ||
		_direction == 2 && pDirection == 3 || _direction == 3 && pDirection == 2) _alpha = 255;
	else _alpha = 100;

	if (_direction == LEFT) _monsterImg = IMAGEMANAGER->findImage("투명고스트L");
	if (_direction == RIGHT) _monsterImg = IMAGEMANAGER->findImage("투명고스트R");
}

bool ghost::die()
{
	for (int i = 0; i < _vHp.size(); ++i)
	{
		if (_vHp[i].hp > 0.0f) return false;
	}
	SOUNDMANAGER->play("ghost_attack");
	return true;
}
