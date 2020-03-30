#include "stdafx.h"
#include "blueSlime.h"


blueSlime::blueSlime()
{
}


blueSlime::~blueSlime()
{
}

HRESULT blueSlime::init(string name, int x, int y, int coin, tagTile * map)
{
	monster::init(name, x, y, coin, map);
	addHp();
	_atk = 0.5f;
	return S_OK;
}

void blueSlime::frontCheck()
{
	switch (_direction)
	{
	case UP:
		_direction = DOWN;
		_nextTileIndex = _currentTileIndex + TILEX;
		break;
	case DOWN: 
		_direction = UP;
		_nextTileIndex = _currentTileIndex - TILEX;
		break;
	}
}

void blueSlime::choiceAction()
{
	if (_isBeat)
	{
		_isBeat = false;
		frontCheck();
		if (playerCheck())
		{
			_isAttack = true;
			switch (_direction)
			{
			case UP: _direction = DOWN;
				break;
			case DOWN: _direction = UP;
				break;
			}
			return;
		}


		if (walkableCheck())
		{
			_isMove = true;
			_pCurrentMap[_currentTileIndex].walkable = true;
			_pCurrentMap[_nextTileIndex].walkable = false;
			EFFECTMANAGER->play("점프먼지", _currentX, _currentY);
			_currentTileIndex = _nextTileIndex;

		}
		else
		{
			_isMove = false;
			switch (_direction)
			{
			case UP: _direction = DOWN;
				break;
			case DOWN: _direction = UP;
				break;
			}
			_nextTileIndex = _currentTileIndex;
		}
	}
}

void blueSlime::silhouetteRender(HDC hdc)
{
	if (KEYMANAGER->isToggleKey(VK_TAB)) Rectangle(hdc, _collisionRc.left, _collisionRc.top, _collisionRc.right, _collisionRc.bottom);
	_monsterImg->frameRender(hdc, _collisionRc.left - _monsterImg->getFrameWidth() / 8, _collisionRc.top - _monsterImg->getFrameHeight() / 4, _frameX, _frameY+1);
	hpRender(hdc);
}
