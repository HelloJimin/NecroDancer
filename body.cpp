#include "stdafx.h"
#include "body.h"


body::body()
{
}

body::body(string name, slotType type, int power, string description, int x, int y)
{
	setItem(type, name, description,  x,  y);
	_power = power;
}


body::~body()
{
}

HRESULT body::init()
{
	if (_name != "����")
	{
		PLAYER->playerStatus().def = _power;
	}

	if (_name == "���װ���") PLAYER->setFrameY(1);
	else if (_name == "�谩��") PLAYER->setFrameY(2);
	else if (_name == "����") PLAYER->setFrameY(3);
	return S_OK;
}

void body::update()
{
	animation();
}
