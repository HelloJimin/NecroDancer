#include "stdafx.h"
#include "body.h"


body::body()
{
}

body::body(string name, slotType type, int power, string description)
{
	setItem(type, name, description);
	_power = power;
}


body::~body()
{
}

void body::update()
{
	animation();
	if (_inInventory && _name != "µµº¹")
	{
		PLAYER->playerStatus().def = _power;
	}
}
