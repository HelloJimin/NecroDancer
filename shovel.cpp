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

	if (_inInventory)
	{
		tagTile* temp = PLAYER->getTile();
		if(temp[PLAYER->playerNextTile()].obj != OBJ_NONE && _power>= temp[PLAYER->playerNextTile()].strength)
		{
			temp[PLAYER->playerNextTile()].obj = OBJ_NONE;
		}
	}
}

void shovel::render()
{
	draw(CAMERAMANAGER->getCameraDC());
}
