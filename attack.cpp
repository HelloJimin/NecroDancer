#include "stdafx.h"
#include "attack.h"


attack::attack()
{
}

attack::attack(string name, slotType type, attackForm form, int power, string description)
{
	setItem(type, name, description);
	_power = power;
	_form = form;
}


attack::~attack()
{
}

void attack::update()
{
	animation();
	if (_inInventory)
	{
		PLAYER->playerStatus().atk = _power;
	}
		
}

