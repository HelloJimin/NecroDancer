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
	for (int i = 0; i < _vItem.size(); i++)
	{
		_vItem[i]->update();
	}
}

void itemManager::render()
{
	for (int i = 0; i < _vItem.size(); i++)
	{
		_vItem[i]->render(CAMERAMANAGER->getCameraDC());
	}
}

item * itemManager::addItem(string name)
{
	for (int i = 0; i < _vItem.size(); i++)
	{
		if (_vItem[i]->getName() == name)
		{
			return _vItem[i];
		}
	}
}

