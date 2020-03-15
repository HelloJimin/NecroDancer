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
		if (_vMonster[i]->die()) _vMonster.erase(_vMonster.begin() + i);
		else ++i;
	}
}

void monsterManager::frontRender(HDC hdc)
{
	for (int i = 0; i < _vMonster.size(); ++i)
	{
		if (PLAYER->currentTile() >= _vMonster[i]->currentTile())
		{
			_vMonster[i]->render(hdc);
		}
	}
}

void monsterManager::backRender(HDC hdc)
{
	for (int i = 0; i < _vMonster.size(); ++i)
	{
		if (PLAYER->currentTile() < _vMonster[i]->currentTile())
		{
			_vMonster[i]->render(hdc);
		}
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
	mob->init(name, x, y, 25, _map);
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
}
