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
	addItem(ITEMMANAGER->addItem("기본삽"));
	addItem(ITEMMANAGER->addItem("기본단검"));
	///_vItem.push_back(ITEMMANAGER->addItem("기본삽"));
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

	for (int i = 0; i < _vItem.size(); ++i)
	{
		_vItem[i]->setInven(true);
		_vItem[i]->setRect(PointMake(30+i * 66, 20));
		_vItem[i]->rcSet();
	}
}

void inventory::swapItem(int arrNum, item*& item)
{
	item->init();
	_vItem[arrNum]->setInven(false);
	swap(_vItem[arrNum], item);

	//이부분함수화할수있으면 함수화 해보자. 폭탄 위치 조정해야됨
	for (int i = 0; i < _vItem.size(); ++i)
	{
		_vItem[i]->setInven(true);
		_vItem[i]->setRect(PointMake(30 + i * 66, 20));
		_vItem[i]->rcSet();
	}
}

item * inventory::getWeapon()
{
	for (int i = 0; i < _vItem.size(); ++i)
	{
		if (_vItem[i]->getType() == ATTACK) return _vItem[i];
	}
}

item * inventory::getShovel()
{
	for (int i = 0; i < _vItem.size(); ++i)
	{
		if (_vItem[i]->getType() == SHOVEL) return _vItem[i];
	}
}
