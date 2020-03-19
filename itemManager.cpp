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
	if (name == "�⺻��")return new shovel(SHOVEL, 1, "�⺻��", "���� 1�� ���̴�",x,y);
	if (name == "ƼŸ����")return new shovel(SHOVEL, 2, "ƼŸ����", "���� 2�� ���̴�",x,y);
	if (name == "������")return new shovel(SHOVEL, 3, "������", "���� 3�� ���̴�",x,y);

	if (name == "�⺻�ܰ�")return new attack("�⺻�ܰ�",ATTACK, FORM_SHORT,1,"���ݷ� 1�� �⺻�ܰ��̴�",x,y);
	if (name == "ƼŸ���ܰ�")return new attack("ƼŸ���ܰ�",ATTACK, FORM_SHORT,2,"���ݷ� 2�� �⺻�ܰ��̴�",x,y);
	if (name == "�����ܰ�")return new attack("�����ܰ�",ATTACK, FORM_SHORT,3,"���ݷ� 3�� �⺻�ܰ��̴�",x,y);

	if (name == "�⺻���")return new attack("�⺻���", ATTACK, FORM_BIG, 1, "���ݷ� 1�� �⺻�ܰ��̴�",x,y);
	if (name == "ƼŸ�����")return new attack("ƼŸ�����", ATTACK, FORM_BIG, 2, "���ݷ� 2�� �⺻�ܰ��̴�",x,y);
	if (name == "�������")return new attack("�������", ATTACK, FORM_BIG, 3, "���ݷ� 3�� �⺻�ܰ��̴�",x,y);

	if (name == "�⺻Ȱ")return new attack("�⺻Ȱ", ATTACK, FORM_BOW, 1, "���ݷ� 1�� �⺻�ܰ��̴�",x,y);
	if (name == "ƼŸ��Ȱ")return new attack("ƼŸ��Ȱ", ATTACK, FORM_BOW, 2, "���ݷ� 2�� �⺻�ܰ��̴�",x,y);
	if (name == "����Ȱ")return new attack("����Ȱ", ATTACK, FORM_BOW, 3, "���ݷ� 3�� �⺻�ܰ��̴�",x,y);

	if (name == "�⺻â")return new attack("�⺻â", ATTACK, FORM_SPEAR , 1, "���ݷ� 1�� �⺻�ܰ��̴�",x,y);
	if (name == "ƼŸ��â")return new attack("ƼŸ��â", ATTACK, FORM_SPEAR, 2, "���ݷ� 2�� �⺻�ܰ��̴�",x,y);
	if (name == "����â")return new attack("����â", ATTACK, FORM_SPEAR, 3, "���ݷ� 3�� �⺻�ܰ��̴�",x,y);

	if (name == "�⺻ä��")return new attack("�⺻ä��", ATTACK, FORM_WHIP, 1, "���ݷ� 1�� �⺻�ܰ��̴�",x,y);
	if (name == "ƼŸ��ä��")return new attack("ƼŸ��ä��", ATTACK, FORM_WHIP, 2, "���ݷ� 2�� �⺻�ܰ��̴�",x,y);
	if (name == "����ä��")return new attack("����ä��", ATTACK, FORM_WHIP, 3, "���ݷ� 3�� �⺻�ܰ��̴�",x,y);


	if (name == "���װ���")return new body("���װ���",BODY,1,"���� 1�� �����̴�",x,y);
	if (name == "�谩��")return new body("�谩��",BODY,2,"���� 2�� �����̴�",x,y);
	if (name == "����")return new body("����",BODY,3,"���ݷ�2���̴�",x,y);

	if (name == "������ȭ")return new feet("������ȭ",FEET,"���ݷ�1 ����",x,y);
	if (name == "�߷�����")return new feet("�߷�����",FEET,"����� �ʱ�ȭ�ȵ�",x,y);
	if (name == "������ȭ")return new feet("������ȭ",FEET,"��������",x,y);

	if (name == "��ź")return new bomb("��ź",BOMB,1,"�ı�",x,y);

}

void itemManager::addCoin(int coinValue, int x, int y)
{
	_vItem.push_back(new coin(coinValue, x, y));
}

void itemManager::setMap()
{
	_map = PLAYER->getMap();

	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (_map[i].itemPoint == "") continue;

		_vItem.push_back(addItem(_map[i].itemPoint, _map[i].x, _map[i].y));		
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
