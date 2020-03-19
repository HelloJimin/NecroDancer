#include "stdafx.h"
#include "shovel.h"

shovel::shovel()
{

}

shovel::shovel(slotType type, int power, string name, string description, int x, int y)
{
	setItem(type, name, description,  x,  y);
	_power = power;
}


shovel::~shovel()
{
}

HRESULT shovel::init()
{
	PLAYER->playerStatus().minePower = _power;
	return S_OK;
}

void shovel::update()
{
	animation();
}
