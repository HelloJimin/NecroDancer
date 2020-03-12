#include "stdafx.h"
#include "dagger.h"


dagger::dagger()
{
}

dagger::dagger(string name, slotType type, int power, string description)
{
	setItem(type, name, description);
	_power = power;
}


dagger::~dagger()
{
}

HRESULT dagger::init()
{
	PLAYER->playerStatus().atkRenge.clear();
	PLAYER->playerStatus().atkRenge.push_back(0);
	PLAYER->playerStatus().atk = _power;
	return S_OK;
}

void dagger::update()
{
	animation();
	if (_inInventory)
	{
		switch (PLAYER->getPlayerDir())	
		{
		case LEFT: PLAYER->playerStatus().atkRenge[0] = PLAYER->currentTile() - 1;
			break;
		case RIGHT:PLAYER->playerStatus().atkRenge[0] = PLAYER->currentTile() + 1;
			break;
		case UP:PLAYER->playerStatus().atkRenge[0] = PLAYER->currentTile() - TILEX;
			break;
		case DOWN:PLAYER->playerStatus().atkRenge[0] = PLAYER->currentTile() + TILEX;
			break;
		}
	}
}
