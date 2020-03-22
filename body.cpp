#include "stdafx.h"
#include "body.h"


body::body()
{
}

body::body(string name, slotType type, int power, string description, int x, int y, int price)
{
	setItem(type, name, description,  x,  y,price);
	_power = power;
}


body::~body()
{
}

HRESULT body::init()
{
	_isShop = false;
	if (_name != "����")
	{
		PLAYER->playerStatus().def = _power;
	}

	if (_name == "���װ���") PLAYER->setFrameY(1);
	else if (_name == "�谩��") PLAYER->setFrameY(2);
	else if (_name == "����") PLAYER->setFrameY(3);
	SOUNDMANAGER->play("armor");
	return S_OK;
}

void body::update()
{
	animation();
}
