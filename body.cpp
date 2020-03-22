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
	if (_name != "µµº¹")
	{
		PLAYER->playerStatus().def = _power;
	}

	if (_name == "°¡Á×°©¿Ê") PLAYER->setFrameY(1);
	else if (_name == "¼è°©¿Ê") PLAYER->setFrameY(2);
	else if (_name == "µµº¹") PLAYER->setFrameY(3);
	SOUNDMANAGER->play("armor");
	return S_OK;
}

void body::update()
{
	animation();
}
