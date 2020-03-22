#include "stdafx.h"
#include "feet.h"


feet::feet()
{
}

feet::feet(string name, slotType type, string description, int x, int y, int price)
{
	setItem(type, name, description,  x,  y,  price);
	
}


feet::~feet()
{
}

HRESULT feet::init()
{
	_isShop = false;
	if (_name == "ÈûÀÇÀåÈ­" && !check)
	{
		PLAYER->playerStatus().atk += 1;
		check = true;
	}
	return S_OK;
}

void feet::update()
{
	animation();
}
