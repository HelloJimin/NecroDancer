#include "stdafx.h"
#include "redDragon.h"


redDragon::redDragon()
{
}


redDragon::~redDragon()
{
}

HRESULT redDragon::init(string name, int x, int y, int coin, tagTile * map)
{
	monster::init(name, x, y, coin, map);
	_direction = LEFT;
	_aStar = new aStar;
	_atk = 1.5f;
	_breathRenge = 0;
	_minePower = 2;
	addHp();
	addHp();
	addHp();
	addHp();
	_isBoss = true;
	_monsterNameImg = IMAGEMANAGER->findImage("�巡���̸�");
	return S_OK;
}

void redDragon::frontCheck()
{
	_nextTileIndex = _aStar->aStarBoss(_pCurrentMap, _currentTileIndex, PLAYER->currentTile());
	breathCheck();
	aniCheck();
}

void redDragon::choiceAction()
{
	if (_isMove) return;

	if (_isBeat)
	{
		_isBeat = false;
		if (_delay)
		{
			_isBreath = true;
			_isAttack = true;
			return;
		}

		frontCheck();

		if (_delay)return;

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
			EFFECTMANAGER->play("��������", _currentX, _currentY);
			_currentTileIndex = _nextTileIndex;
		}
		else
		{
			mine();
			_isMove = false;
			_nextTileIndex = _currentTileIndex;
		}
	}
}

void redDragon::animation()
{
	if (!_delay)
	{
		if (BEAT->getCnt() % 12 == 0)
		{
			_frameX++;
			if (_frameX > 3)_frameX = 0;
		}
	}
	else
	{
		if (BEAT->getCnt() % 22 == 0)
		{
			_frameX++;
			if (_frameX > _monsterImg->getMaxFrameX())
			{
				_delay = false;
				_isBreath = false;
				_isAttack = false;
				_isBreath = false;
				_frameX =0;
			}
		}
	}
}

void redDragon::render(HDC hdc)
{
	if (KEYMANAGER->isToggleKey(VK_TAB)) Rectangle(hdc, _collisionRc.left, _collisionRc.top, _collisionRc.right, _collisionRc.bottom);
	_monsterImg->frameRender(hdc, _collisionRc.left - TILEX*2 - TILEX / 2, _collisionRc.top - _monsterImg->getFrameHeight() + TILEX + 15, _frameX, _frameY);

	hpRender(hdc);
}

void redDragon::silhouetteRender(HDC hdc)
{
	if (KEYMANAGER->isToggleKey(VK_TAB)) Rectangle(hdc, _collisionRc.left, _collisionRc.top, _collisionRc.right, _collisionRc.bottom);
	_monsterImg->frameRender(hdc, _collisionRc.left - TILEX*2 - TILEX/2, _collisionRc.top - _monsterImg->getFrameHeight() + TILEX + 15, _frameX, _frameY+2);

	hpRender(hdc);
}

void redDragon::move()
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

void redDragon::attack()
{
	if (_isBreath && _isAttack)
	{
		_isBreath = false;
		_isAttack = false;
		_isBreath = false;

		_breathRenge = 0;
		int temp = _nextTileIndex;

		switch (_direction)
		{
		case LEFT:
			EFFECTMANAGER->play("�巡��극��1L", _pCurrentMap[_currentTileIndex-1].x, _pCurrentMap[_currentTileIndex-1].y);
			while (rengeCheck(temp))
			{
				_breathRenge++;
				temp--;
			}
			break;
		case RIGHT:
			EFFECTMANAGER->play("�巡��극��1R", _pCurrentMap[_currentTileIndex+1].x, _pCurrentMap[_currentTileIndex+1].y);
			while (rengeCheck(temp))
			{
				_breathRenge++;
				temp++;
			}
			break;
		}

		char breath[128];
		//2,3,4,5
		for (int i = 0; i < _breathRenge; i++)
		{
			wsprintf(breath, "�巡��극��%d", i%4+2);
			switch (_direction)
			{
			case LEFT:	EFFECTMANAGER->play(breath, _pCurrentMap[_currentTileIndex-1].x - ((i+1)*52), _pCurrentMap[_currentTileIndex-1].y);
				if (_nextTileIndex - i == PLAYER->currentTile()) PLAYER->hit(_atk, _monsterNameImg);
				break;
			case RIGHT:EFFECTMANAGER->play(breath, _pCurrentMap[_currentTileIndex+1].x + ((i+1)*52), _pCurrentMap[_currentTileIndex+1].y);
				if (_nextTileIndex + i == PLAYER->currentTile()) PLAYER->hit(_atk , _monsterNameImg);
				break;
			}
		}
		return;
	}
	monster::attack();
}

void redDragon::mine()
{
	if (_minePower >= _pCurrentMap[_nextTileIndex].strength)
	{
		_pCurrentMap[_nextTileIndex].obj = OBJ_NONE;
		_pCurrentMap[_nextTileIndex].strength = 0;
		_pCurrentMap[_nextTileIndex].walkable = true;
	}
}

void redDragon::breathCheck()
{
	int playerTile = PLAYER->currentTile();
	int checkTile = 5;
	switch (_direction)
	{
	case LEFT:
		for (int i = 0; i < checkTile; i++)
		{
			if (playerTile == _currentTileIndex - i)
			{
				_delay = true;
				_frameX = 4;
				break;
			}
		}
		break;
	case RIGHT:
		for (int i = 0; i < checkTile; i++)
		{
			if (playerTile == _currentTileIndex + i)
			{
				_delay = true;
				_frameX = 4;
				break;
			}
		}
		break;
	case UP:	_delay = false;
		break;
	case DOWN:	_delay = false;
		break;
	}
}

bool redDragon::die()
{
	for (int i = 0; i < _vHp.size(); ++i)
	{
		if (_vHp[i].hp > 0.0f) return false;
	}

	SOUNDMANAGER->play("dragon_death");
	BEAT->addHint("�ⱸ��ܿ���");
	return true;
}

bool redDragon::rengeCheck(int tile)
{
	if(_pCurrentMap[tile].obj == OBJ_NOMALWALL)return false;
	if(_pCurrentMap[tile].obj == OBJ_SKULLWALL)return false;
	if(_pCurrentMap[tile].obj == OBJ_WHITEWALL)return false;
	if(_pCurrentMap[tile].obj == OBJ_GOLDWALL )return false;
	if(_pCurrentMap[tile].obj == OBJ_IRONWALL )return false;
	if(_pCurrentMap[tile].obj == OBJ_NEVERWALL)return false;

	else return true;
}
