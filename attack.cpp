#include "stdafx.h"
#include "attack.h"


attack::attack()
{
}

attack::attack(string name, slotType type, attackForm form, int power, string description, int x, int y, int price)
{
	setItem(type, name, description, x, y, price);
	_power = power;
	_form = form;
	_button = IMAGEMANAGER->findImage("z버튼");
	if (form == FORM_SHORT)
	{
		_throw.slot = IMAGEMANAGER->findImage("던지기");
		_throw.item = IMAGEMANAGER->findImage(name);
		_throw.fire = false;
		_throw.rc = RectMakeCenter(40,30+66,_throw.slot->getWidth(),_throw.slot->getHeight());
	}
}


attack::~attack()
{
}

HRESULT attack::init()
{
	_inInventory = true;
	_isShop = false;
	PLAYER->setWeapom(_form);
	PLAYER->playerStatus().atk = _power;
	PLAYER->playerStatus().atkRenge.clear();
	//SOUNDMANAGER->play("pickup_weapon");
	switch (_form)
	{
	case FORM_SHORT:
		PLAYER->playerStatus().atkRenge.push_back(0);
		break;				  
	case FORM_BIG:			  
		PLAYER->playerStatus().atkRenge.push_back(0);
		PLAYER->playerStatus().atkRenge.push_back(0);
		PLAYER->playerStatus().atkRenge.push_back(0);
		break;				  
	case FORM_SPEAR:		  
		PLAYER->playerStatus().atkRenge.push_back(0);
		PLAYER->playerStatus().atkRenge.push_back(0);
		break;				  
	case FORM_BOW:			  
		PLAYER->playerStatus().atkRenge.push_back(0);
		PLAYER->playerStatus().atkRenge.push_back(0);
		PLAYER->playerStatus().atkRenge.push_back(0);
		PLAYER->playerStatus().atkRenge.push_back(0);
		PLAYER->playerStatus().atkRenge.push_back(0);
		break;				  
	case FORM_WHIP:			  
		PLAYER->playerStatus().atkRenge.push_back(0);
		PLAYER->playerStatus().atkRenge.push_back(0);
		PLAYER->playerStatus().atkRenge.push_back(0);
		PLAYER->playerStatus().atkRenge.push_back(0);
		PLAYER->playerStatus().atkRenge.push_back(0);
		break;
	}
	return S_OK;
}

void attack::active()
{
	switch (PLAYER->getPlayerDir())
	{
	case LEFT:
		switch (_form)
		{
		case FORM_SHORT:
			PLAYER->playerStatus().atkRenge[0] = PLAYER->currentTile() - 1;
			break;
		case FORM_BIG:
			PLAYER->playerStatus().atkRenge[0] = PLAYER->currentTile() - 1;
			PLAYER->playerStatus().atkRenge[1] = PLAYER->currentTile() - 1 + TILEX;
			PLAYER->playerStatus().atkRenge[2] = PLAYER->currentTile() - 1 - TILEX;
			break;
		case FORM_SPEAR:
			PLAYER->playerStatus().atkRenge[0] = PLAYER->currentTile() - 1;
			PLAYER->playerStatus().atkRenge[1] = PLAYER->currentTile() - 2;
			break;
		case FORM_BOW:
			PLAYER->playerStatus().atkRenge[0] = PLAYER->currentTile() - 1;
			PLAYER->playerStatus().atkRenge[1] = PLAYER->currentTile() - 2;
			PLAYER->playerStatus().atkRenge[2] = PLAYER->currentTile() - 3;
			PLAYER->playerStatus().atkRenge[3] = PLAYER->currentTile() - 4;
			PLAYER->playerStatus().atkRenge[4] = PLAYER->currentTile() - 5;
			break;
		case FORM_WHIP:
			PLAYER->playerStatus().atkRenge[3] = PLAYER->currentTile() - 1 - TILEX * 2;
			PLAYER->playerStatus().atkRenge[1] = PLAYER->currentTile() - 1 - TILEX;
			PLAYER->playerStatus().atkRenge[0] = PLAYER->currentTile() - 1;
			PLAYER->playerStatus().atkRenge[2] = PLAYER->currentTile() - 1 + TILEX;
			PLAYER->playerStatus().atkRenge[4] = PLAYER->currentTile() - 1 + TILEX * 2;
			break;
		}
		break;
	case RIGHT:
		switch (_form)
		{
		case FORM_SHORT:
			PLAYER->playerStatus().atkRenge[0] = PLAYER->currentTile() + 1;
			break;
		case FORM_BIG:
			PLAYER->playerStatus().atkRenge[0] = PLAYER->currentTile() + 1;
			PLAYER->playerStatus().atkRenge[1] = PLAYER->currentTile() + 1 + TILEX;
			PLAYER->playerStatus().atkRenge[2] = PLAYER->currentTile() + 1 - TILEX;
			break;
		case FORM_SPEAR:
			PLAYER->playerStatus().atkRenge[0] = PLAYER->currentTile() + 1;
			PLAYER->playerStatus().atkRenge[1] = PLAYER->currentTile() + 2;
			break;
		case FORM_BOW:
			PLAYER->playerStatus().atkRenge[0] = PLAYER->currentTile() + 1;
			PLAYER->playerStatus().atkRenge[1] = PLAYER->currentTile() + 2;
			PLAYER->playerStatus().atkRenge[2] = PLAYER->currentTile() + 3;
			PLAYER->playerStatus().atkRenge[3] = PLAYER->currentTile() + 4;
			PLAYER->playerStatus().atkRenge[4] = PLAYER->currentTile() + 5;
			break;
		case FORM_WHIP:
			PLAYER->playerStatus().atkRenge[3] = PLAYER->currentTile() + 1 - TILEX*2;
			PLAYER->playerStatus().atkRenge[1] = PLAYER->currentTile() + 1 - TILEX;
			PLAYER->playerStatus().atkRenge[0] = PLAYER->currentTile() + 1;
			PLAYER->playerStatus().atkRenge[2] = PLAYER->currentTile() + 1 + TILEX;
			PLAYER->playerStatus().atkRenge[4] = PLAYER->currentTile() + 1 + TILEX*2;
			break;
		}
		break;
	case UP:
		switch (_form)
		{
		case FORM_SHORT:
			PLAYER->playerStatus().atkRenge[0] = PLAYER->currentTile() - TILEX;
			break;
		case FORM_BIG:
			PLAYER->playerStatus().atkRenge[0] = PLAYER->currentTile() - TILEX;
			PLAYER->playerStatus().atkRenge[1] = PLAYER->currentTile() - TILEX - 1;
			PLAYER->playerStatus().atkRenge[2] = PLAYER->currentTile() - TILEX + 1;
			break;
		case FORM_SPEAR:
			PLAYER->playerStatus().atkRenge[0] = PLAYER->currentTile() - TILEX;
			PLAYER->playerStatus().atkRenge[1] = PLAYER->currentTile() - TILEX*2;
			break;
		case FORM_BOW:
			PLAYER->playerStatus().atkRenge[0] = PLAYER->currentTile() - TILEX;
			PLAYER->playerStatus().atkRenge[1] = PLAYER->currentTile() - TILEX*2;
			PLAYER->playerStatus().atkRenge[2] = PLAYER->currentTile() - TILEX*3;
			PLAYER->playerStatus().atkRenge[3] = PLAYER->currentTile() - TILEX*4;
			PLAYER->playerStatus().atkRenge[4] = PLAYER->currentTile() - TILEX*5;
			break;
		case FORM_WHIP:
			PLAYER->playerStatus().atkRenge[3] = PLAYER->currentTile() - TILEX - 2;
			PLAYER->playerStatus().atkRenge[1] = PLAYER->currentTile() - TILEX -1;
			PLAYER->playerStatus().atkRenge[0] = PLAYER->currentTile() - TILEX;
			PLAYER->playerStatus().atkRenge[2] = PLAYER->currentTile() - TILEX + 1;
			PLAYER->playerStatus().atkRenge[4] = PLAYER->currentTile() - TILEX + 2;
			break;
		}
		break;
	case DOWN:
		switch (_form)
		{
		case FORM_SHORT:
			PLAYER->playerStatus().atkRenge[0] = PLAYER->currentTile() + TILEX;
			break;
		case FORM_BIG:
			PLAYER->playerStatus().atkRenge[0] = PLAYER->currentTile() + TILEX;
			PLAYER->playerStatus().atkRenge[1] = PLAYER->currentTile() + TILEX - 1;
			PLAYER->playerStatus().atkRenge[2] = PLAYER->currentTile() + TILEX + 1;
			break;
		case FORM_SPEAR:
			PLAYER->playerStatus().atkRenge[0] = PLAYER->currentTile() + TILEX;
			PLAYER->playerStatus().atkRenge[1] = PLAYER->currentTile() + TILEX*2;
			break;
		case FORM_BOW:
			PLAYER->playerStatus().atkRenge[0] = PLAYER->currentTile() + TILEX;
			PLAYER->playerStatus().atkRenge[1] = PLAYER->currentTile() + TILEX * 2;
			PLAYER->playerStatus().atkRenge[2] = PLAYER->currentTile() + TILEX * 3;
			PLAYER->playerStatus().atkRenge[3] = PLAYER->currentTile() + TILEX * 4;
			PLAYER->playerStatus().atkRenge[4] = PLAYER->currentTile() + TILEX * 5;
			break;
		case FORM_WHIP:
			PLAYER->playerStatus().atkRenge[3] = PLAYER->currentTile() + TILEX - 2;
			PLAYER->playerStatus().atkRenge[1] = PLAYER->currentTile() + TILEX - 1;
			PLAYER->playerStatus().atkRenge[0] = PLAYER->currentTile() + TILEX;
			PLAYER->playerStatus().atkRenge[2] = PLAYER->currentTile() + TILEX + 1;
			PLAYER->playerStatus().atkRenge[4] = PLAYER->currentTile() + TILEX + 2;
			break;
		}
		break;
	}
}


void attack::update()
{
	animation();
	if (_form == FORM_SHORT)
	{
		if (KEYMANAGER->isOnceKeyDown('Z'))
		{
			_throw.fire = true;
			_throw.slot = IMAGEMANAGER->findImage("던지세요");
		}
	}
}

void attack::render(HDC hdc)
{
	item::render(hdc);

	if (_inInventory && _form == FORM_SHORT)
	{
		_throw.slot->render(CAMERAMANAGER->getCameraDC(), _throw.rc.left+7, _throw.rc.top+21);
		_throw.item->render(CAMERAMANAGER->getCameraDC(), _throw.rc.left + 14, _throw.rc.top + 32);
		if(!_throw.fire) _button->render(CAMERAMANAGER->getCameraDC(), _throw.rc.left + 32, _throw.rc.top + 75);
	}
}


