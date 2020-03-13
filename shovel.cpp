#include "stdafx.h"
#include "shovel.h"

shovel::shovel()
{

}

shovel::shovel(slotType type, int power, string name, string description)
{
	setItem(type, name, description);
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
