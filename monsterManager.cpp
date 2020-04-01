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
		if (map[i].startPoint != "�÷��̾�")
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
	if (name == "�׸�������")
	{
		summonGreenSlime(name, x, y);
	}
	else if (name == "��罽����")
	{
		summonBlueSlime(name, x, y);
	}
	else if (name == "���̷���")
	{
		summonSkeleton(name, x, y);
	}
	else if (name == "�����ƮL")
	{
		summonGhost(name, x, y);
	}
	else if (name == "���巹�̽�")
	{
		summonRedWraiths(name, x, y);
	}
	else if (name == "����")
	{
		summonBat(name, x, y);
	}
	else if (name == "�̳�Ÿ��ν�")
	{
		summonMinotaurs(name, x, y);
	}
	else if (name == "����巡��")
	{
		summonRedDragon(name, x, y);
	}
	else if (name == "��������")
	{
		summonShopKeeper(name, x, y);
	}
	else if (name == "����")
	{
		summonZombie(name, x, y);
	}
	else if (name == "������Ż1")
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
