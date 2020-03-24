#include "stdafx.h"
#include "torch.h"


torch::torch()
{
}

torch::torch(string name, slotType type, int power, string description, int x, int y, int price)
{
	setItem(type, name, description, x, y, price);
	_power = power;
}

torch::~torch()
{
}

HRESULT torch::init()
{
	_isShop = false;
	PLAYER->getRayPower() = _power;

	return S_OK;
}

void torch::update()
{
	animation();
}
