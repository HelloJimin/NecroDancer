#include "stdafx.h"
#include "shovel.h"

shovel::shovel()
{

}

shovel::shovel(itemType type, int power, string name, string description)
{
	setItem(type, name, description);
	_power = power;
	_itemImg = IMAGEMANAGER->findImage(name);
}


shovel::~shovel()
{
}


void shovel::release()
{
}

void shovel::update()
{
	animation();

	bool ok = PLAYER->isMine1();
	if (_inInventory && ok)
	{
		tagTile* temp = PLAYER->getTile();
		if(temp[PLAYER->wallTile()].strength<=_power) temp[PLAYER->wallTile()].obj = OBJ_NONE;
		//PLAYER->setIsMine(false);
		ok = false;
		
	}
}

void shovel::render()
{
	draw(CAMERAMANAGER->getCameraDC());
}
