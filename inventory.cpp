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
	addItem(ITEMMANAGER->addItem("±âº»»ð"));
	addItem(ITEMMANAGER->addItem("±âº»´Ü°Ë"));
	///_vItem.push_back(ITEMMANAGER->addItem("±âº»»ð"));
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
		//if (_vItem[0]->getType() == BODY)
		//{
		//	_vItem.insert(_vItem.begin()+1, item);
		//}
		//else
		//{
		//	_vItem.insert(_vItem.begin(), item);
		//}
	}

	else _vItem.push_back(item);

	itemPosionSet();
}

void inventory::swapItem(int arrNum, item*& item)
{
	item->init();
	_vItem[arrNum]->setInven(false);
	swap(_vItem[arrNum], item);

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
		if (_vItem[i]->getType() != BOMB) _vItem[i]->setRect(PointMake(30 + i * 66, 20));

		if (_vItem[i]->getType() == BOMB && getWeapon() == NULL)
		{
			_vItem[i]->setRect(PointMake(30, 20 + 66));
		}
		else if (_vItem[i]->getType() == BOMB && getWeapon() != NULL)
		{
			_vItem[i]->setRect(PointMake(30, 20 + 66+66));
		}
		_vItem[i]->rcSet();
	}
}
