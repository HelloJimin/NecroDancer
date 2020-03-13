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
	PLAYER->setWeapom(true);
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
			PLAYER->playerStatus().atkRenge[0] = PLAYER->currentTile() - 1;
			PLAYER->playerStatus().atkRenge[1] = PLAYER->currentTile() - 1 + TILEX;
			PLAYER->playerStatus().atkRenge[2] = PLAYER->currentTile() - 1 - TILEX;
			PLAYER->playerStatus().atkRenge[3] = PLAYER->currentTile() - 1 + TILEX * 2;
			PLAYER->playerStatus().atkRenge[4] = PLAYER->currentTile() - 1 - TILEX * 2;
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
			PLAYER->playerStatus().atkRenge[0] = PLAYER->currentTile() + 1;
			PLAYER->playerStatus().atkRenge[1] = PLAYER->currentTile() + 1 + TILEX;
			PLAYER->playerStatus().atkRenge[2] = PLAYER->currentTile() + 1 - TILEX;
			PLAYER->playerStatus().atkRenge[3] = PLAYER->currentTile() + 1 + TILEX*2;
			PLAYER->playerStatus().atkRenge[4] = PLAYER->currentTile() + 1 - TILEX*2;
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
			PLAYER->playerStatus().atkRenge[0] = PLAYER->currentTile() - TILEX;
			PLAYER->playerStatus().atkRenge[1] = PLAYER->currentTile() - TILEX -1;
			PLAYER->playerStatus().atkRenge[2] = PLAYER->currentTile() - TILEX + 1;
			PLAYER->playerStatus().atkRenge[3] = PLAYER->currentTile() - TILEX - 2;
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
			PLAYER->playerStatus().atkRenge[0] = PLAYER->currentTile() + TILEX;
			PLAYER->playerStatus().atkRenge[1] = PLAYER->currentTile() + TILEX - 1;
			PLAYER->playerStatus().atkRenge[2] = PLAYER->currentTile() + TILEX + 1;
			PLAYER->playerStatus().atkRenge[3] = PLAYER->currentTile() + TILEX - 2;
			PLAYER->playerStatus().atkRenge[4] = PLAYER->currentTile() + TILEX + 2;
			break;
		}
		break;
	}
}


void attack::update()
{
	animation();
}

