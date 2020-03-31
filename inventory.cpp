#include "stdafx.h"
#include "inventory.h"


inventory::inventory()
{
}


inventory::~inventory()
{
}

HRESULT inventory::init()
{
	addItem(ITEMMANAGER->addItem("기본삽",1,1));
	addItem(ITEMMANAGER->addItem("기본단검",1,1));

	return S_OK;
}

void inventory::release()
{
}

void inventory::update()
{
	for (int i = 0; i < _vItem.size(); ++i)
	{
		_vItem[i]->update();
		if (_vItem[i]->getType() == ATTACK) _vItem[i]->active();
		if (_vItem[i]->getType() == BOMB && _vItem[i]->getValue() == 0)
		{
			_vItem.erase(_vItem.begin() + i);
			--i;
			itemPosionSet();
		}
	}
}

void inventory::render(HDC hdc)
{
	for (int i = 0; i < _vItem.size(); ++i)
	{
		_vItem[i]->render(CAMERAMANAGER->getCameraDC());
	}
}

void inventory::addItem(item * item)
{
	item->init();
	if (item->getType() == BODY)
	{
		_vItem.insert(_vItem.begin(), item);
	}
	else if (item->getType() == ATTACK)
	{
		_vItem.insert(_vItem.begin(), item);

		for (int i = 0; i < _vItem.size(); ++i)
		{
			if (_vItem[i]->getType() == BODY)
			{
				swap(_vItem.front(), _vItem[i]);
			}
		}
	}

	else
	{
		_vItem.push_back(item);
		for (int i = 0; i < _vItem.size(); ++i)
		{
			if (_vItem[i]->getType() == BOMB || _vItem[i]->getType() == ITEM)
			{
				swap(_vItem.back(), _vItem[i]);
				break;
			}
		}
	}

	itemPosionSet();
}

void inventory::swapItem(int arrNum, item*& _item, int itemNum)
{
	if (_item->getType() == BOMB)
	{
		_vItem[arrNum]->setValue(_item->getValue());
		ITEMMANAGER->removeItem(itemNum);
		return;
	}
	_item->init();
	_vItem[arrNum]->setInven(false);
	_vItem[arrNum]->setRect(PointMake(_item->getX(), _item->getY()));

	swap(_vItem[arrNum], _item);
	
	itemPosionSet();
}

item * inventory::getWeapon()
{
	for (int i = 0; i < _vItem.size(); ++i)
	{
		if (_vItem[i]->getType() == ATTACK) return _vItem[i];
	}
	return NULL;
}

item * inventory::getShovel()
{
	for (int i = 0; i < _vItem.size(); ++i)
	{
		if (_vItem[i]->getType() == SHOVEL) return _vItem[i];
	}
	return NULL;
}

item * inventory::getBomb()
{
	for (int i = 0; i < _vItem.size(); ++i)
	{
		if (_vItem[i]->getType() == BOMB) return _vItem[i];
	}
	return NULL;
}

item * inventory::getApple()
{
	for (int i = 0; i < _vItem.size(); ++i)
	{
		if (_vItem[i]->getType() == ITEM) return _vItem[i];
	}
	return NULL;
}

void inventory::throwItem()
{
	for (int i = 0; i < _vItem.size(); ++i)
	{
		if (_vItem[i]->getType() == ATTACK)
		{
			_vItem.erase(_vItem.begin() + i);
			break;
		}
	}
}

void inventory::itemPosionSet()
{
	for (int i = 0; i < _vItem.size(); ++i)
	{
		_vItem[i]->setInven(true);

		if (_vItem[i]->getType() != BOMB && _vItem[i]->getType() != ITEM)
			_vItem[i]->setRect(PointMake(30 + i * 66, 20));

		if (_vItem[i]->getType() == BOMB)
		{
			if (PLAYER->getAtkForm() != FORM_SHORT)
			{
				_vItem[i]->setRect(PointMake(30, 50 + 46));

			}
			else if (PLAYER->getAtkForm() == FORM_SHORT)
			{
				_vItem[i]->setRect(PointMake(30, 50 + 66 + 66));
			}

			if(getWeapon() == NULL)
			{
				_vItem[i]->setRect(PointMake(30, 50 + 66));
			}
		}
		if (_vItem[i]->getType() == ITEM)
		{
			if (PLAYER->getAtkForm() != FORM_SHORT && getBomb() == NULL)
			{
				_vItem[i]->setRect(PointMake(30, 50 + 46));
			}
			else if (PLAYER->getAtkForm() == FORM_SHORT && getBomb() == NULL)
			{
				_vItem[i]->setRect(PointMake(30, 50 + 66 + 66));
			}
			else if (PLAYER->getAtkForm() != FORM_SHORT && getBomb() != NULL)
			{
				_vItem[i]->setRect(PointMake(30, 50 + 66 + 66));
			}
			else if (PLAYER->getAtkForm() == FORM_SHORT && getBomb() != NULL)
			{
				_vItem[i]->setRect(PointMake(30, 50 + 66 + 66 + 89));
			}

		}
		_vItem[i]->rcSet();
	}
}
