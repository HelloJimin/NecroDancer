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
}

void monsterManager::frontRender(HDC hdc)
{
	for (int i = 0; i < _vMonster.size(); ++i)
	{
		if (PLAYER->playerTile() >= _vMonster[i]->currentTile())
		{
			_vMonster[i]->render(hdc);

		}
	}

}

void monsterManager::backRender(HDC hdc)
{
	for (int i = 0; i < _vMonster.size(); ++i)
	{
		if (PLAYER->playerTile() < _vMonster[i]->currentTile())
		{
			_vMonster[i]->render(hdc);

		}
	}
}

//void monsterManager::render(HDC hdc)
//{
//	for (int i = 0; i < _vMonster.size(); ++i)
//	{
//		_vMonster[i]->render(hdc);
//	}
//}

void monsterManager::summonGreenSlime(string name, int x, int y)
{
	monster* mob = new greenSlime;
	mob->init(name, x, y, _map);
	_vMonster.push_back(mob);
}
