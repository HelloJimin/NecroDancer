#include "stdafx.h"
#include "itemManager.h"


itemManager::itemManager()
{
}


itemManager::~itemManager()
{
}

HRESULT itemManager::init()
{

	_vItem.push_back(new shovel(SHOVEL, 1, "±âº»»ğ", "°­µµ 1ÀÇ »ğÀÌ´Ù"));

	return S_OK;
}

void itemManager::release()
{
}

void itemManager::update()
{

}

void itemManager::render()
{

}

item * itemManager::addItem(string name)
{
	if (name == "±âº»»ğ")return new shovel(SHOVEL, 1, "±âº»»ğ", "°­µµ 1ÀÇ »ğÀÌ´Ù");
	if (name == "Æ¼Å¸´½»ğ")return new shovel(SHOVEL, 2, "Æ¼Å¸´½»ğ", "°­µµ 2ÀÇ »ğÀÌ´Ù");
	if (name == "À¯¸®»ğ")return new shovel(SHOVEL, 3, "À¯¸®»ğ", "°­µµ 3ÀÇ »ğÀÌ´Ù");

}

