#include "stdafx.h"
#include "shopKeeper.h"


shopKeeper::shopKeeper()
{
}


shopKeeper::~shopKeeper()
{
}

HRESULT shopKeeper::init(string name, int x, int y, int coin, tagTile * map)
{
	monster::init(name, x, y, coin, map);
	_direction = LEFT;
	_aStar = new aStar;
	_atk = 2.0f;

	addHp();
	addHp();
	addHp();
	addHp();
	addHp();
	addHp();
	addHp();
	_monsterNameImg = IMAGEMANAGER->findImage("상점주인이름");
	return S_OK;
}

void shopKeeper::update()
{
	BGMcheck();
	if (BEAT->getIsBeat() && !_isBeat)
	{
		_turnCnt++;
		_isBeat = true;
	}
	if (!BEAT->getIsBeat()) _isBeat = false;


	_pCurrentMap[_currentTileIndex].walkable = false;
	animation();

	if (!_isHit)return;

	choiceAction();

	attack();
	move();

	hpSet();

}

void shopKeeper::frontCheck()
{
	_nextTileIndex = _aStar->aStarTile(_pCurrentMap, _currentTileIndex, PLAYER->currentTile());

	aniCheck();
}

void shopKeeper::choiceAction()
{
	if ( _isBeat)
	{
		frontCheck();
		_isBeat = false;
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

			_frameX = _monsterImg->getMaxFrameX() - 2;
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

void shopKeeper::render(HDC hdc)
{
	if (KEYMANAGER->isToggleKey(VK_TAB)) Rectangle(hdc, _collisionRc.left, _collisionRc.top, _collisionRc.right, _collisionRc.bottom);
	_monsterImg->frameRender(hdc, _collisionRc.left - TILEX, _collisionRc.top - _monsterImg->getFrameHeight() + TILEX, _frameX, _frameY);

	hpRender(hdc);
}

void shopKeeper::silhouetteRender(HDC hdc)
{
	if (KEYMANAGER->isToggleKey(VK_TAB)) Rectangle(hdc, _collisionRc.left, _collisionRc.top, _collisionRc.right, _collisionRc.bottom);
	_monsterImg->frameRender(hdc, _collisionRc.left - TILEX, _collisionRc.top - _monsterImg->getFrameHeight() + TILEX, _frameX, _frameY + 2);

	hpRender(hdc);
}

bool shopKeeper::die()
{
	for (int i = 0; i < _vHp.size(); ++i)
	{
		if (_vHp[i].hp > 0.0f) return false;
	}
	SOUNDMANAGER->stop("1-1shop");
	ITEMMANAGER->shopKeeperDie();
	return true;
}

void shopKeeper::hit(float damage)
{
	monster::hit(damage);
	SOUNDMANAGER->stop("1-1shop");
}

void shopKeeper::BGMcheck()
{
	if (_isHit) return;


	float distance = getDistance(_currentX, _currentY, PLAYER->getX(), PLAYER->getY());
	if (distance <= 1000)
	{
		float volume = 1000 / distance ;
		 SOUNDMANAGER->volumeSet("1-1shop", volume * 0.15f);
	}
	else SOUNDMANAGER->volumeSet("1-1shop", 0.0f);


	//if (distance  < 1000) SOUNDMANAGER->volumeSet("1-1shop",1.0f);
	//else SOUNDMANAGER->volumeSet("1-1shop", 0.0f);
}
