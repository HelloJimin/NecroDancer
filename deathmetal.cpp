#include "stdafx.h"
#include "deathmetal.h"


deathmetal::deathmetal()
{
}


deathmetal::~deathmetal()
{
}

HRESULT deathmetal::init(string name, int x, int y, int coin, tagTile * map)
{
	monster::init(name, x, y, coin, map);

	_aStar = new aStar;
	_isBoss = true;
	_atk = 2.0f;
	addHp();
	addHp();
	addHp();
	addHp();
	addHp();
	addHp();


	_direction = LEFT;
	_phase = PHASE_ONE;

	return S_OK;
}

void deathmetal::update()
{
	if (BEAT->getIsBeat() && !_isBeat)
	{
		_turnCnt++;
		_isBeat = true;
	}
	if (!BEAT->getIsBeat()) _isBeat = false;


	_pCurrentMap[_currentTileIndex].walkable = false;

	choiceAction();

	attack();
	move();

	animation();
	hpSet();

}

void deathmetal::frontCheck()
{
	switch (_phase)
	{
	case PHASE_ONE:
		_nextTileIndex = _aStar->aStarTile(_pCurrentMap, _currentTileIndex, PLAYER->currentTile());

		break;
	case PHASE_TWO:
		break;
	case PHASE_THREE:
		break;
	}
	aniCheck();
}

void deathmetal::choiceAction()
{
	if (_isMove) return;
	if (TURN2 && _isBeat)
	{
		frontCheck();

		if (playerCheck())
		{
			_isAttack = true;
			_nextTileIndex = _currentTileIndex;
			return;
		}

		if (walkableCheck())
		{
			_isMove = true;
			if (_currentTileIndex == _nextTileIndex)_isMove = false;

			_pCurrentMap[_currentTileIndex].walkable = true;
			_pCurrentMap[_nextTileIndex].walkable = false;
			EFFECTMANAGER->play("점프먼지", _currentX, _currentY);
			_currentTileIndex = _nextTileIndex;
		}
		else
		{
			_isMove = false;
			_nextTileIndex = _currentTileIndex;
		}
	}
}

void deathmetal::animation()
{
	if (BEAT->getCnt() % 12 == 0)
	{
		_frameX++;
		if (_frameX > _monsterImg->getMaxFrameX())_frameX = 0;
	}
}

void deathmetal::render(HDC hdc)
{
	if (KEYMANAGER->isToggleKey(VK_TAB)) Rectangle(hdc, _collisionRc.left, _collisionRc.top, _collisionRc.right, _collisionRc.bottom);
	//switch (_direction)
	//{
	//case LEFT:
	//	_monsterImg->frameRender(hdc, _collisionRc.left - TILEX * 2 - TILEX / 2, _collisionRc.top - _monsterImg->getFrameHeight() + TILEX, _frameX, _frameY);

	//	break;
	//case RIGHT:
	//	_monsterImg->frameRender(hdc, _collisionRc.left - TILEX * 2 , _collisionRc.top - _monsterImg->getFrameHeight() + TILEX, _frameX, _frameY);

	//	break;
	//case UP:
	//	_monsterImg->frameRender(hdc, _collisionRc.left - TILEX * 2 , _collisionRc.top - _monsterImg->getFrameHeight() + TILEX, _frameX, _frameY);

	//	break;
	//case DOWN:
	//	_monsterImg->frameRender(hdc, _collisionRc.left - TILEX * 2 - TILEX / 2, _collisionRc.top - _monsterImg->getFrameHeight() + TILEX, _frameX, _frameY);

	//	break;
	//}
	_monsterImg->frameRender(hdc, _collisionRc.left - TILEX * 2 - TILEX / 2, _collisionRc.top - _monsterImg->getFrameHeight() + TILEX, _frameX, _frameY);

	hpRender(hdc);
}

void deathmetal::silhouetteRender(HDC hdc)
{
	if (KEYMANAGER->isToggleKey(VK_TAB)) Rectangle(hdc, _collisionRc.left, _collisionRc.top, _collisionRc.right, _collisionRc.bottom);
	_monsterImg->frameRender(hdc, _collisionRc.left - TILEX * 2 - TILEX / 2, _collisionRc.top - _monsterImg->getFrameHeight() + TILEX, _frameX, _frameY + 4);

	hpRender(hdc);
}

void deathmetal::move()
{
	if (!_isMove) return;
	switch (_direction)
	{
	case LEFT:
		if (!_isDrop&& getDistance(_currentX, _currentY, _pCurrentMap[_nextTileIndex].x + 26, _pCurrentMap[_nextTileIndex].y - 26) != 0)
		{
			_currentX -= _moveSpeed;
			_currentY -= _moveSpeed;
		}
		else _isDrop = true;

		if (_isDrop&& getDistance(_currentX, _currentY, _pCurrentMap[_nextTileIndex].x, _pCurrentMap[_nextTileIndex].y) != 0)
		{
			_currentX -= _moveSpeed;
			_currentY += _moveSpeed;
		}
		else if (_isDrop&& getDistance(_currentX, _currentY, _pCurrentMap[_nextTileIndex].x, _pCurrentMap[_nextTileIndex].y) == 0)
		{
			_isDrop = false;
			_isMove = false;
		}
		break;
	case RIGHT:
		if (!_isDrop&& getDistance(_currentX, _currentY, _pCurrentMap[_nextTileIndex].x - 26, _pCurrentMap[_nextTileIndex].y - 26) != 0)
		{
			_currentX += _moveSpeed;
			_currentY -= _moveSpeed;
		}
		else _isDrop = true;

		if (_isDrop&& getDistance(_currentX, _currentY, _pCurrentMap[_nextTileIndex].x, _pCurrentMap[_nextTileIndex].y) != 0)
		{
			_currentX += _moveSpeed;
			_currentY += _moveSpeed;
		}
		else if (_isDrop&& getDistance(_currentX, _currentY, _pCurrentMap[_nextTileIndex].x, _pCurrentMap[_nextTileIndex].y) == 0)
		{
			_isDrop = false;
			_isMove = false;
		}
		break;
	case UP:
		if (!_isDrop&& getDistance(_currentX, _currentY, _pCurrentMap[_nextTileIndex].x, _pCurrentMap[_nextTileIndex].y - 26) != 0)
		{
			_currentY -= _moveSpeed;
		}
		else _isDrop = true;

		if (_isDrop&& getDistance(_currentX, _currentY, _pCurrentMap[_nextTileIndex].x, _pCurrentMap[_nextTileIndex].y) != 0)
		{
			_currentY += _moveSpeed;
		}
		else if (_isDrop&& getDistance(_currentX, _currentY, _pCurrentMap[_nextTileIndex].x, _pCurrentMap[_nextTileIndex].y) == 0)
		{
			_isDrop = false;
			_isMove = false;
		}
		break;
	case DOWN:
		if (!_isDrop&& getDistance(_currentX, _currentY, _pCurrentMap[_nextTileIndex].x, _pCurrentMap[_nextTileIndex].y - 78) != 0)
		{
			_currentY -= _moveSpeed;
		}
		else _isDrop = true;

		if (_isDrop&& getDistance(_currentX, _currentY, _pCurrentMap[_nextTileIndex].x, _pCurrentMap[_nextTileIndex].y) != 0)
		{
			_currentY += _moveSpeed;
		}
		else if (_isDrop&& getDistance(_currentX, _currentY, _pCurrentMap[_nextTileIndex].x, _pCurrentMap[_nextTileIndex].y) == 0)
		{
			_isDrop = false;
			_isMove = false;
		}
		break;
	}
	_collisionRc = RectMakeCenter(_currentX, _currentY, 50, 50);
}

void deathmetal::aniCheck()
{

	if (_nextTileIndex == _currentTileIndex - 1) _direction = LEFT;
	else if (_nextTileIndex == _currentTileIndex + 1) _direction = RIGHT;
	else if (_nextTileIndex == _currentTileIndex + TILEX)_direction = DOWN;
	else if (_nextTileIndex == _currentTileIndex - TILEX)_direction = UP;

	switch (_direction)
	{
	case LEFT:_frameY = 0;
		break;
	case RIGHT:_frameY = 1;
		break;
	case UP:_frameY = 3;
		break;
	case DOWN:_frameY = 2;
		break;
	}
}

void deathmetal::hit(float damage)
{
	if (_phase == PHASE_ONE)
	{
		DIRECTION pDirection = PLAYER->getPlayerDir();
		if (_direction == 0 && pDirection == 1 || _direction == 1 && pDirection == 0 ||
			_direction == 2 && pDirection == 3 || _direction == 3 && pDirection == 2)
		{

			switch (_direction)
			{
			case LEFT:
				_nextTileIndex = _currentTileIndex + 1;
				_direction = RIGHT;
				break;
			case RIGHT:
				_nextTileIndex = _currentTileIndex - 1;
				_direction = LEFT;
				break;
			case UP:
				_nextTileIndex = _currentTileIndex + TILEX;
				_direction = DOWN;
				break;
			case DOWN:
				_nextTileIndex = _currentTileIndex - TILEX;
				_direction = UP;
				break;
			}
			if (walkableCheck())
			{
				_isMove = true;
				_pCurrentMap[_currentTileIndex].walkable = true;
				_pCurrentMap[_nextTileIndex].walkable = false;
				_currentTileIndex = _nextTileIndex;

			}


			return;
		}
	}


	_isHit = true;

	for (int i = 0; i < _vHp.size(); i++)
	{
		if (_vHp[i].hp <= 0) continue;

		if (damage > 0)
		{
			float temp = _vHp[i].hp;
			_vHp[i].hp -= damage;
			damage -= temp;
		}
		else break;
	}
}
