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
