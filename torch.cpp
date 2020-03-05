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

void torch::update()
{
	animation();
}
