#include "stdafx.h"
#include "greenSlime.h"


greenSlime::greenSlime()
{
}


greenSlime::~greenSlime()
{
}


HRESULT greenSlime::init(string name, int x, int y, int coin, tagTile * map)
{
	monster::init(name, x, y, coin, map);
	_atk = 0.0f;
	return S_OK;
}

void greenSlime::update()
{
	animation();
}



