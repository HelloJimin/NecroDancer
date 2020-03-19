#include "stdafx.h"
#include "torch.h"


torch::torch()
{
}

torch::torch(string name, slotType type, int power, string description)
{
	setItem(type, name, description);
	_power = power;
}


torch::~torch()
{
}

HRESULT torch::init()
{
	return S_OK;
}

void torch::update()
{
	animation();
}
