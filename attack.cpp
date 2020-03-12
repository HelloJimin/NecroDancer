#include "stdafx.h"
#include "attack.h"


attack::attack()
{
}

attack::attack(string name, slotType type, attackForm form, int power, string description)
{
	setItem(type, name, description);
	_power = power;
	_form = form;
}


attack::~attack()
{
}

HRESULT attack::init()
{
	PLAYER->playerStatus().atk = _power;
	PLAYER->playerStatus().atkRenge.clear();
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

void attack::setRenge()
{

}

void attack::update()
{
	animation();
	if (!_inInventory) return;
	
	switch (PLAYER->getPlayerDir())
	{
	case LEFT:
		switch (_form)
		{
		case FORM_SHORT:
			PLAYER->playerStatus().atkRenge[0] = PLAYER->currentTile() - 1;
			break;
		case FORM_BIG:
			break;
		case FORM_SPEAR:
			break;
		case FORM_BOW:
			break;
		case FORM_WHIP:
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
			break;
		case FORM_SPEAR:
			break;
		case FORM_BOW:
			break;
		case FORM_WHIP:
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
			break;
		case FORM_SPEAR:
			break;
		case FORM_BOW:
			break;
		case FORM_WHIP:
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
			break;
		case FORM_SPEAR:
			break;
		case FORM_BOW:
			break;
		case FORM_WHIP:
			break;
		}
		break;
	}

}

