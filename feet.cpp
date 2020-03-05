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

void feet::update()
{
	animation();
	if (_name == "ÈûÀÇÀåÈ­" && !check)
	{
		PLAYER->playerStatus().atk += 1;
		check = true;
	}
}
