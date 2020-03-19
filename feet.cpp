#include "stdafx.h"
#include "feet.h"


feet::feet()
{
}

feet::feet(string name, slotType type, string description)
{
	setItem(type, name, description);
	
}


feet::~feet()
{
}

HRESULT feet::init()
{
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
