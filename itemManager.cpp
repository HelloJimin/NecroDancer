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
	_vItem.clear();
	return S_OK;
}

void itemManager::release()
{
}

void itemManager::update()
{
	for (int i = 0; i < _vItem.size(); ++i)
	{
		_vItem[i]->update();
	}
}

void itemManager::render()
{
	//for (int i = 0; i < _vitem.size(); ++i)
	//{
	//	_vitem[i]->render();
	//}
}

item * itemManager::addItem(string name,int x, int y)
{
	if (name == "�⺻��")return new shovel(SHOVEL, 1, "�⺻��", "���� 1�� ���̴�",x,y , 10);
	if (name == "ƼŸ����")return new shovel(SHOVEL, 2, "ƼŸ����", "���� 2�� ���̴�",x,y,200);
	if (name == "������")return new shovel(SHOVEL, 3, "������", "���� 3�� ���̴�",x,y,40);

	if (name == "�⺻�ܰ�")return new attack("�⺻�ܰ�",ATTACK, FORM_SHORT,1,"���ݷ� 1�� �⺻�ܰ��̴�",x,y,10);
	if (name == "ƼŸ���ܰ�")return new attack("ƼŸ���ܰ�",ATTACK, FORM_SHORT,2,"���ݷ� 2�� �⺻�ܰ��̴�",x,y,200);
	if (name == "�����ܰ�")return new attack("�����ܰ�",ATTACK, FORM_SHORT,3,"���ݷ� 3�� �⺻�ܰ��̴�",x,y,40);

	if (name == "�⺻���")return new attack("�⺻���", ATTACK, FORM_BIG, 1, "���ݷ� 1�� �⺻�ܰ��̴�",x,y,50);
	if (name == "ƼŸ�����")return new attack("ƼŸ�����", ATTACK, FORM_BIG, 2, "���ݷ� 2�� �⺻�ܰ��̴�",x,y,300);
	if (name == "�������")return new attack("�������", ATTACK, FORM_BIG, 3, "���ݷ� 3�� �⺻�ܰ��̴�",x,y,50);

	if (name == "�⺻Ȱ")return new attack("�⺻Ȱ", ATTACK, FORM_BOW, 1, "���ݷ� 1�� �⺻�ܰ��̴�",x,y,50);
	if (name == "ƼŸ��Ȱ")return new attack("ƼŸ��Ȱ", ATTACK, FORM_BOW, 2, "���ݷ� 2�� �⺻�ܰ��̴�",x,y,300);
	if (name == "����Ȱ")return new attack("����Ȱ", ATTACK, FORM_BOW, 3, "���ݷ� 3�� �⺻�ܰ��̴�",x,y,50);

	if (name == "�⺻â")return new attack("�⺻â", ATTACK, FORM_SPEAR , 1, "���ݷ� 1�� �⺻�ܰ��̴�",x,y,50);
	if (name == "ƼŸ��â")return new attack("ƼŸ��â", ATTACK, FORM_SPEAR, 2, "���ݷ� 2�� �⺻�ܰ��̴�",x,y,300);
	if (name == "����â")return new attack("����â", ATTACK, FORM_SPEAR, 3, "���ݷ� 3�� �⺻�ܰ��̴�",x,y,50);

	if (name == "�⺻ä��")return new attack("�⺻ä��", ATTACK, FORM_WHIP, 1, "���ݷ� 1�� �⺻�ܰ��̴�",x,y,50);
	if (name == "ƼŸ��ä��")return new attack("ƼŸ��ä��", ATTACK, FORM_WHIP, 2, "���ݷ� 2�� �⺻�ܰ��̴�",x,y,300);
	if (name == "����ä��")return new attack("����ä��", ATTACK, FORM_WHIP, 3, "���ݷ� 3�� �⺻�ܰ��̴�",x,y,50);

	if (name == "�⺻ȶ��")return new torch("�⺻ȶ��", TORCH, 1, "���ݷ� 3�� �⺻�ܰ��̴�",x,y,100);
	if (name == "������ȶ��")return new torch("������ȶ��", TORCH, 3, "���ݷ� 3�� �⺻�ܰ��̴�",x,y,300);

	if (name == "���װ���")return new body("���װ���",BODY,0.5f,"���� 1�� �����̴�",x,y,50);
	if (name == "�谩��")return new body("�谩��",BODY,1.0f,"���� 2�� �����̴�",x,y,200);
	if (name == "����")return new body("����",BODY,0,"���ݷ�2���̴�",x,y,90);

	if (name == "������ȭ")return new feet("������ȭ",FEET,"���ݷ�1 ����",x,y,150);
	if (name == "�߷�����")return new feet("�߷�����",FEET,"����� �ʱ�ȭ�ȵ�",x,y,150);
	if (name == "������ȭ")return new feet("������ȭ",FEET,"��������",x,y,150);

	if (name == "��ź")return new bomb("��ź",BOMB,1,"�ı�",x,y,50);
	if (name == "HP����")return new hpSlot(x,y);
	if (name == "���")return new apple("���",ITEM,1,0.5f,"ȸ��",x,y,10);
	if (name == "ġŲ")return new apple("ġŲ",ITEM,1,3.0f,"ȸ��",x,y,10);

}

void itemManager::addCoin(int coinValue, int x, int y)
{
	_vItem.push_back(new coin(coinValue, x, y));
}

void itemManager::setMap()
{
	_vItem.clear();

	_map = PLAYER->getMap();

	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (_map[i].itemPoint == ""  || _map[i].itemPoint == "��ȶ��") continue;

		_vItem.push_back(addItem(_map[i].itemPoint, _map[i].x, _map[i].y));		
	}

	for (int i = 0; i < _vItem.size(); ++i)
	{
		_vItem[i]->shopCheck();
	}
}

void itemManager::removeItem(int arrNum)
{
	_vItem.erase(_vItem.begin() + arrNum);
}

void itemManager::addItemList(string name, int x, int y)
{
	_vItem.push_back(addItem(name, x, y));
}

void itemManager::shopKeeperDie()
{
	for (int i = 0; i < _vItem.size(); ++i)
	{
		if (!_vItem[i]->getIsShop())continue;
		_vItem[i]->getIsShop() = false;

	}
}
