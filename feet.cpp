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
	PLAYER->getFly() = false;
	PLAYER->getBallet() = false;

	if (_name == "�߷�����")PLAYER->getBallet() = true;
	else if (_name == "������ȭ")PLAYER->getFly() = true;

	_isShop = false;

	return S_OK;
}

void feet::update()
{
	animation();
}
