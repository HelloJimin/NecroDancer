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

	_vItem.push_back(new shovel(SHOVEL, 1, "�⺻��", "���� 1�� ���̴�"));

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
	if (name == "�⺻��")return new shovel(SHOVEL, 1, "�⺻��", "���� 1�� ���̴�");
	if (name == "ƼŸ����")return new shovel(SHOVEL, 2, "ƼŸ����", "���� 2�� ���̴�");
	if (name == "������")return new shovel(SHOVEL, 3, "������", "���� 3�� ���̴�");

}

