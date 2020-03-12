#include "stdafx.h"
#include "monster.h"


monster::monster()
{
}


monster::~monster()
{
}

HRESULT monster::init(string name, int x, int y, int coin, tagTile * map)
{
	_pCurrentMap = map;

	_monsterImg = IMAGEMANAGER->findImage(name);
	_currentX = x;
	_currentY = y;

	_collisionRc = RectMakeCenter(_currentX, _currentY, 50, 50);
	_tileX = _collisionRc.left / TILESIZE;
	_tileY = _collisionRc.top / TILESIZE;
	_currentTileIndex = _tileX + _tileY * TILEX;
	_pCurrentMap[_currentTileIndex].walkable = false;

	_frameX = 0;
	_frameY = 0;
	_moveSpeed = 13.0f;

	_coin = coin;

	_direction = DOWN;
	_directionAni = LEFT_BOT;

	_isAttack = false;
	_isMove = false;
	_isHit = false;
	_isLockOn = false;

	addHp();
	return S_OK;
}

void monster::release()
{
}

void monster::update()
{
	_pCurrentMap[_currentTileIndex].walkable = false;

	animation();
	frontCheck();
	hpSet();
	attack();
	move();
}

void monster::render(HDC hdc)
{
	if (KEYMANAGER->isToggleKey(VK_TAB)) Rectangle(hdc, _collisionRc.left, _collisionRc.top, _collisionRc.right, _collisionRc.bottom);
	_monsterImg->frameRender(hdc, _collisionRc.left - _monsterImg->getFrameWidth() / 8, _collisionRc.top- _monsterImg->getFrameHeight()/4, _frameX, _frameY);
	hpRender(hdc);
}

void monster::animation()
{
	if (BEAT->getCnt() % 12 == 0)
	{
		_frameX++;
		if (_frameX > _monsterImg->getMaxFrameX())_frameX = 0;
	}
}

void monster::frontCheck()
{
	if (BEAT->getCnt() % 58 == 0)
	{
		_tileX = _collisionRc.left / TILESIZE;
		_tileY = _collisionRc.top / TILESIZE;
		_currentTileIndex = _tileX + _tileY * TILEX;

		switch (_direction)
		{
		case LEFT:
			_nextTileIndex = _tileX + _tileY * TILEX - 1;
			break;
		case RIGHT:
			_nextTileIndex = _tileX + _tileY * TILEX + 1;
			break;
		case UP:
			_nextTileIndex = _tileX + (_tileY - 1) * TILEX;
			break;
		case DOWN:
			_nextTileIndex = _tileX + (_tileY + 1) * TILEX;
			break;
		}
		choiceAction();
	}
}

void monster::attack()
{
	if (!_isAttack) return;

	PLAYER->hit(_atk);
	int x = PLAYER->getCollisionRc().left + (PLAYER->getCollisionRc().right - PLAYER->getCollisionRc().left) / 2;
	int y = PLAYER->getCollisionRc().top + (PLAYER->getCollisionRc().bottom - PLAYER->getCollisionRc().top) / 2;
	EFFECTMANAGER->play("할퀴기", x , y);
	_isAttack = false;
}

void monster::move()
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

bool monster::die()
{
	for (int i = 0; i < _vHp.size(); ++i)
	{
		if (_vHp[i].hp > 0.0f) return false;
	}
	_pCurrentMap[_currentTileIndex].walkable = true;
	_pCurrentMap[_currentTileIndex].item = ITEMMANAGER->addCoin(_coin, _pCurrentMap[_currentTileIndex].x, _pCurrentMap[_currentTileIndex].y);
	return true;
}

void monster::addHp()
{
	hp _hp;
	_hp.currentX = 2;
	_hp.img = IMAGEMANAGER->findImage("HP바");
	_hp.hp = 1.0f;

	_vHp.push_back(_hp);
}

void monster::hpSet()
{
	for (int i = 0; i < _vHp.size(); ++i)
	{
		if (_vHp[i].hp <= 0.0f) _vHp[i].currentX = 2;
		if (_vHp[i].hp == 0.5f) _vHp[i].currentX = 1;
		if (_vHp[i].hp == 1.0f) _vHp[i].currentX = 0;

		_vHp[i].rc = RectMakeCenter(_collisionRc.left+(i*_vHp[i].img->getFrameWidth())/2, _collisionRc.top - _vHp[i].img->getFrameHeight()/2, _vHp[i].img->getFrameWidth(), _vHp[i].img->getFrameHeight());
	}
}

void monster::hpRender(HDC hdc)
{
	if (!_isHit) return;

	for (int i = 0; i < _vHp.size(); ++i)
	{
		_vHp[i].img->frameRender(hdc, _vHp[i].rc.left, _vHp[i].rc.top, _vHp[i].currentX, 0);
	}
}

void monster::hit(float damage)
{
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

void monster::aniCheck()
{
	int monsterX = _pCurrentMap[_currentTileIndex].x;
	int monsterY = _pCurrentMap[_currentTileIndex].y;
	int playerX = _pCurrentMap[PLAYER->currentTile()].x;
	int playerY = _pCurrentMap[PLAYER->currentTile()].y;

	if (monsterX > playerX && monsterY > playerY)
	{
		_directionAni = LEFT_TOP;
	}
	else if (monsterX < playerX && monsterY > playerY)
	{
		_directionAni = RIGHT_TOP;
	}
	else if (monsterX > playerX && monsterY < playerY)
	{
		_directionAni = LEFT_BOT;
	}
	else if (monsterX < playerX && monsterY < playerY)
	{
		_directionAni = RIGHT_BOT;
	}

	switch (_directionAni)
	{
	case LEFT_TOP: _frameY = 0;
		break;
	case LEFT_BOT: _frameY = 0;
		break;
	case RIGHT_TOP: _frameY = 1;
		break;
	case RIGHT_BOT: _frameY = 1;
		break;
	}

	if (_nextTileIndex == _currentTileIndex - 1) _direction = LEFT;
	else if (_nextTileIndex == _currentTileIndex + 1) _direction = RIGHT;
	else if (_nextTileIndex == _currentTileIndex + TILEX)_direction = DOWN;
	else if (_nextTileIndex == _currentTileIndex - TILEX)_direction = UP;
}

bool monster::wallCheck()
{
	if (!_pCurrentMap[_nextTileIndex].walkable) return false;

	return true;
}

bool monster::playerCheck()
{
	if (PLAYER->currentTile() == _nextTileIndex) return true;

	return false;
}

void monster::choiceAction()
{
	RECT temp;
	if (playerCheck())
	{
		_isAttack = true;
		return;
	}
	if (wallCheck())
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
		_nextTileIndex = _currentTileIndex;
	}
}
