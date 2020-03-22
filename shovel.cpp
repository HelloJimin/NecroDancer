#include "stdafx.h"
#include "shovel.h"

shovel::shovel()
{

}

shovel::shovel(slotType type, int power, string name, string description, int x, int y, int price)
{
	setItem(type, name, description,  x,  y,  price);
	_power = power;
}


shovel::~shovel()
{
}

HRESULT shovel::init()
{
	_isShop = false;
	PLAYER->playerStatus().minePower = _power;
	return S_OK;
}

void shovel::update()
{
	animation();
}
