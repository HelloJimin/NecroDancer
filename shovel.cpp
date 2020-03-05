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

void shovel::update()
{
	animation();
	if (_inInventory) PLAYER->playerStatus().minePower = _power;
}
