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


	for (int i = 0; i < 737; ++i)
	{
		if (_pCurrentMap[i].terrain != TERRAIN_GROUND) continue;
		_field.push_back(i);
	}
	return S_OK;
}

void deathmetal::update()
{
	if (BEAT->getIsBeat() && !_isBeat)
	{
		_turnCnt++;
		_teleportCnt++;
		_isBeat = true;
		_isSkill = false;
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
		_nextTileIndex = _aStar->aStarReverse(_pCurrentMap, _currentTileIndex, PLAYER->currentTile());

		break;
	case PHASE_THREE:

		break;
	}
	aniCheck();
}

void deathmetal::choiceAction()
{
	if (_isMove)
		return;

	if (TURN2 && _isBeat)
	{
		frontCheck();

		switch (_phase)
		{
		case PHASE_ONE:
			if (playerCheck())
			{
				_isAttack = true;
				_nextTileIndex = _currentTileIndex;
				return;
			}
			break;
		case PHASE_TWO:
			if (_turnCnt % 10 == 0 && MONSTERMANAGER->getMonster().size()<5)
			{
				_isSkill = true;
				summon();
				return;
			}
			break;
		case PHASE_THREE:
			break;		
		}

		if (_phase != PHASE_ONE)
		{
			if (_teleportCnt == 10)
			{
				teleport();
				return;
			}
		}

		if (walkableCheck())
		{
			_isMove = true;
			if (_currentTileIndex == _nextTileIndex)_isMove = false;

			_pCurrentMap[_currentTileIndex].walkable = true;
			_pCurrentMap[_nextTileIndex].walkable = false;
			EFFECTMANAGER->play("Á¡ÇÁ¸ÕÁö", _currentX, _currentY);
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
	if (_isSkill)
	{
		_monsterImg->frameRender(hdc, _collisionRc.left - TILEX * 2 - TILEX / 2, _collisionRc.top - _monsterImg->getFrameHeight() + TILEX, _frameX, _frameY + 2);
	}
	else
	{
		_monsterImg->frameRender(hdc, _collisionRc.left - TILEX * 2 - TILEX / 2, _collisionRc.top - _monsterImg->getFrameHeight() + TILEX, _frameX, _frameY);
	}
	hpRender(hdc);
}

void deathmetal::silhouetteRender(HDC hdc)
{
	if (KEYMANAGER->isToggleKey(VK_TAB)) Rectangle(hdc, _collisionRc.left, _collisionRc.top, _collisionRc.right, _collisionRc.bottom);
	if (_isSkill)
	{
		_monsterImg->frameRender(hdc, _collisionRc.left - TILEX * 2 - TILEX / 2, _collisionRc.top - _monsterImg->getFrameHeight() + TILEX, _frameX, _frameY + 6);
	}
	else
	{
		_monsterImg->frameRender(hdc, _collisionRc.left - TILEX * 2 - TILEX / 2, _collisionRc.top - _monsterImg->getFrameHeight() + TILEX, _frameX, _frameY+4);
	}
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

	if (_phase == PHASE_ONE)
	{
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
	else
	{
		switch (_direction)
		{
		case LEFT:_frameY = 0;
			break;
		case RIGHT:_frameY = 1;
			break;
		}

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
	_hitCnt++;

	if (_hitCnt == 3)
	{
		_teleportCnt = 0;
		_phase = PHASE_TWO;
		_monsterImg = IMAGEMANAGER->findImage("µ¥½º¸ÞÅ»2");
	}
	if (_hitCnt == 6) _phase = PHASE_THREE;

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

	if (_phase != PHASE_ONE)
	{
		teleport();
	}
}

void deathmetal::teleport()
{
	_teleportCnt = 0;

	int summonPosition;
	bool ok = true;

	while (ok)
	{
		int random = RND->getInt(_field.size());
		summonPosition = _field[random];

		if (_pCurrentMap[_field[random]].walkable) ok = false;
	}

	//int summonPosition = PLAYER->currentTile();

	//if (_pCurrentMap[summonPosition - 7].walkable) summonPosition = summonPosition - 7;
	//else if (_pCurrentMap[summonPosition + 7].walkable) summonPosition = summonPosition + 7;
	//else if (_pCurrentMap[summonPosition + TILEX * 7].walkable) summonPosition = summonPosition + TILEX * 7;
	//else if (_pCurrentMap[summonPosition - TILEX * 7].walkable) summonPosition = summonPosition - TILEX * 7;
	//else summonPosition = 555;

	_pCurrentMap[_currentTileIndex].walkable = true;

	_currentTileIndex = summonPosition;
	_currentX = _pCurrentMap[_currentTileIndex].x;
	_currentY = _pCurrentMap[_currentTileIndex].y;
	_nextTileIndex = summonPosition + TILEX;
	_direction = DOWN;
	_collisionRc = RectMakeCenter(_currentX, _currentY, 50, 50);

	//_isMove = true;
}

void deathmetal::summon()
{
	int summonPosition = PLAYER->currentTile();

	if (_pCurrentMap[summonPosition - 5].walkable) summonPosition = summonPosition - 5;
	else if (_pCurrentMap[summonPosition + 5].walkable) summonPosition = summonPosition + 5;
	else if (_pCurrentMap[summonPosition + TILEX * 5].walkable) summonPosition = summonPosition + TILEX * 5;
	else if (_pCurrentMap[summonPosition - TILEX * 5].walkable) summonPosition = summonPosition - TILEX * 5;

	MONSTERMANAGER->summonSkeleton("½ºÄÌ·¹Åæ", _pCurrentMap[summonPosition].x, _pCurrentMap[summonPosition].y);
}
