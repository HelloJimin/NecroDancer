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
	_silhouette = false;
	_frameX = 0;
	_frameY = 0;
	_rhythm = 0;
	_moveSpeed = 13.0f;
	_attack = false;


	_rc = RectMakeCenter(_currentX, _currentY, _monsterImg->getFrameWidth(), _monsterImg->getFrameHeight());
	_collisionRc = RectMakeCenter(_currentX, _currentY, 50, 50);

	_coin = coin;

	_direction = DOWN;
	_tileX = _rc.left / TILESIZE;
	_tileY = _rc.top / TILESIZE;
	_currentTileIndex = _tileX + _tileY * TILEX + TILEX;
	addHp();
	return S_OK;
}

void monster::release()
{
}

void monster::update()
{
	hpSet();
	frontCheck();
	animation();
	attack();
}

void monster::render(HDC hdc)
{
	if (KEYMANAGER->isToggleKey(VK_TAB)) Rectangle(hdc, _collisionRc.left, _collisionRc.top, _collisionRc.right, _collisionRc.bottom);
	_monsterImg->frameRender(hdc, _collisionRc.left, _collisionRc.top, _frameX, _frameY);
	hpRender(hdc);
}

void monster::animation()
{

	if (BEAT->getCnt() % 12 == 0)
	{
		_frameX++;
		if (_frameX > _monsterImg->getMaxFrameX())_frameX = 0;
	}
	if (_silhouette) _frameY = 1;
	else _frameY = 0;
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
		_isMove = true;
	}
}

void monster::attack()
{
}

void monster::move()
{
}

bool monster::die()
{
	for (int i = 0; i < _vHp.size(); ++i)
	{
		if (_vHp[i].hp > 0.0f) return false;
	}
	_pCurrentMap[_currentTileIndex].item = ITEMMANAGER->addCoin(_coin, _pCurrentMap[_currentTileIndex].x, _pCurrentMap[_currentTileIndex].y);
	return true;
}

void monster::addHp()
{
	hp _hp;
	_hp.currentX = 2;
	_hp.img = IMAGEMANAGER->findImage("HP¹Ù");
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

		_vHp[i].rc = RectMakeCenter(_rc.left+(i*_vHp[i].img->getFrameWidth())/2, _rc.top - _vHp[i].img->getFrameHeight()/2, _vHp[i].img->getFrameWidth(), _vHp[i].img->getFrameHeight());
	}
}

void monster::hpRender(HDC hdc)
{
	for (int i = 0; i < _vHp.size(); ++i)
	{
		_vHp[i].img->frameRender(hdc, _vHp[i].rc.left, _vHp[i].rc.top, _vHp[i].currentX, 0);
	}
}

void monster::hit(float damage)
{
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
	hpSet();
}
