#include "stdafx.h"
#include "monsterManager.h"


monsterManager::monsterManager()
{
}


monsterManager::~monsterManager()
{
}

HRESULT monsterManager::init()
{
	_vMonster.clear();
	return S_OK;
}

void monsterManager::release()
{
}

void monsterManager::update()
{
	for (int i = 0; i < _vMonster.size(); ++i)
	{
		_vMonster[i]->update();
	}
	for (int i = 0; i < _vMonster.size();)
	{
		if (_vMonster[i]->die())
		{
			tagTile* temp = PLAYER->getMap();
			temp[_vMonster[i]->currentTile()].walkable = true;
			if(_vMonster[i]->getCoin() > 0 )ITEMMANAGER->addCoin(_vMonster[i]->getCoin(), temp[_vMonster[i]->currentTile()].x, temp[_vMonster[i]->currentTile()].y);
			_vMonster.erase(_vMonster.begin() + i);
		}

		else ++i;
	}
}
void monsterManager::render(HDC hdc)
{
	for (int i = 0; i < _vMonster.size(); ++i)
	{
		_vMonster[i]->render(hdc);
	}
}

void monsterManager::setMap(tagTile * map)
{
	_vMonster.clear();

	_map = map;
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (map[i].startPoint == "") continue;
		if (map[i].startPoint != "플레이어")
		{
			summonControl(map[i].startPoint, map[i].x, map[i].y);
		}
	}
}

void monsterManager::summonGreenSlime(string name, int x, int y)
{
	monster* mob = new greenSlime;
	mob->init(name, x, y, 10, _map);
	_vMonster.push_back(mob);
}
void monsterManager::summonBlueSlime(string name, int x, int y)
{
	monster* mob = new blueSlime;
	mob->init(name, x, y, 15, _map);
	_vMonster.push_back(mob);
}
void monsterManager::summonSkeleton(string name, int x, int y)
{
	monster* mob = new skeleton;
	mob->init(name, x, y, 15, _map);
	_vMonster.push_back(mob);
}

void monsterManager::summonGhost(string name, int x, int y)
{
	monster* mob = new ghost;
	mob->init(name, x, y, 15, _map);
	_vMonster.push_back(mob);
}

void monsterManager::summonRedWraiths(string name, int x, int y)
{
	monster* mob = new redWraiths;
	mob->init(name, x, y, 15, _map);
	_vMonster.push_back(mob);
}

void monsterManager::summonBat(string name, int x, int y)
{
	monster* mob = new bat;
	mob->init(name, x, y, 15, _map);
	_vMonster.push_back(mob);
}

void monsterManager::summonMinotaurs(string name, int x, int y)
{
	monster* mob = new minotaurs;
	mob->init(name, x, y, 50, _map);
	_vMonster.push_back(mob);
}

void monsterManager::summonRedDragon(string name, int x, int y)
{
	monster* mob = new redDragon;
	mob->init(name, x, y, 50, _map);
	_vMonster.push_back(mob);
}

void monsterManager::summonShopKeeper(string name, int x, int y)
{
	monster* mob = new shopKeeper;
	mob->init(name, x, y, 100, _map);
	_vMonster.push_back(mob);
}

void monsterManager::summonZombie(string name, int x, int y)
{
	monster* mob = new zombie;
	mob->init(name, x, y, 10, _map);
	_vMonster.push_back(mob);
}

void monsterManager::summonBoss(string name, int x, int y)
{
	monster* mob = new deathmetal;
	mob->init(name, x, y, 0, _map);
	_vMonster.push_back(mob);
}

void monsterManager::summonControl(string name, int x, int y)
{
	if (name == "그린슬라임")
	{
		summonGreenSlime(name, x, y);
	}
	else if (name == "블루슬라임")
	{
		summonBlueSlime(name, x, y);
	}
	else if (name == "스켈레톤")
	{
		summonSkeleton(name, x, y);
	}
	else if (name == "투명고스트L")
	{
		summonGhost(name, x, y);
	}
	else if (name == "레드레이스")
	{
		summonRedWraiths(name, x, y);
	}
	else if (name == "박쥐")
	{
		summonBat(name, x, y);
	}
	else if (name == "미노타우로스")
	{
		summonMinotaurs(name, x, y);
	}
	else if (name == "레드드래곤")
	{
		summonRedDragon(name, x, y);
	}
	else if (name == "상점주인")
	{
		summonShopKeeper(name, x, y);
	}
	else if (name == "좀비")
	{
		summonZombie(name, x, y);
	}
	else if (name == "데스메탈1")
	{
		summonBoss(name, x, y);
	}
}

bool monsterManager::getBossMonster()
{
	for (int i = 0; i < _vMonster.size();++i)
	{
		if (_vMonster[i]->getIsBoss())
		{
			return true;
		}
	}
	return false;
}

void monsterManager::setMove(int turn)
{
	for (int i = 0; i < _vMonster.size(); ++i)
	{
		_vMonster[i]->setIsBeat(turn);
	}
}
