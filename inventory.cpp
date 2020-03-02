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
	//_vItem.push_back(ITEMMANAGER->addItem("±âº»»ð"));
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
	item->setInven(true);
	_vItem.push_back(item);
	for (int i = 0; i < _vItem.size(); ++i)
	{
		_vItem[i]->setRect(PointMake(i + 1 * 50, 50));
	}
}
