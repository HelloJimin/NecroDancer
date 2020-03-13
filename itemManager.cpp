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

	//_vItem.push_back(new shovel(SHOVEL, 1, "�⺻��", "���� 1�� ���̴�"));

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

	if (name == "�⺻�ܰ�")return new attack("�⺻�ܰ�",ATTACK, FORM_SHORT,1,"���ݷ� 1�� �⺻�ܰ��̴�");
	if (name == "ƼŸ���ܰ�")return new attack("ƼŸ���ܰ�",ATTACK, FORM_SHORT,2,"���ݷ� 2�� �⺻�ܰ��̴�");
	if (name == "�����ܰ�")return new attack("�����ܰ�",ATTACK, FORM_SHORT,3,"���ݷ� 3�� �⺻�ܰ��̴�");

	if (name == "�⺻���")return new attack("�⺻���", ATTACK, FORM_BIG, 1, "���ݷ� 1�� �⺻�ܰ��̴�");
	if (name == "ƼŸ�����")return new attack("ƼŸ�����", ATTACK, FORM_BIG, 2, "���ݷ� 2�� �⺻�ܰ��̴�");
	if (name == "�������")return new attack("�������", ATTACK, FORM_BIG, 3, "���ݷ� 3�� �⺻�ܰ��̴�");

	if (name == "�⺻Ȱ")return new attack("�⺻Ȱ", ATTACK, FORM_BOW, 1, "���ݷ� 1�� �⺻�ܰ��̴�");
	if (name == "ƼŸ��Ȱ")return new attack("ƼŸ��Ȱ", ATTACK, FORM_BOW, 2, "���ݷ� 2�� �⺻�ܰ��̴�");
	if (name == "����Ȱ")return new attack("����Ȱ", ATTACK, FORM_BOW, 3, "���ݷ� 3�� �⺻�ܰ��̴�");

	if (name == "�⺻â")return new attack("�⺻â", ATTACK, FORM_SPEAR , 1, "���ݷ� 1�� �⺻�ܰ��̴�");
	if (name == "ƼŸ��â")return new attack("ƼŸ��â", ATTACK, FORM_SPEAR, 2, "���ݷ� 2�� �⺻�ܰ��̴�");
	if (name == "����â")return new attack("����â", ATTACK, FORM_SPEAR, 3, "���ݷ� 3�� �⺻�ܰ��̴�");

	if (name == "�⺻ä��")return new attack("�⺻ä��", ATTACK, FORM_WHIP, 1, "���ݷ� 1�� �⺻�ܰ��̴�");
	if (name == "ƼŸ��ä��")return new attack("ƼŸ��ä��", ATTACK, FORM_WHIP, 2, "���ݷ� 2�� �⺻�ܰ��̴�");
	if (name == "����ä��")return new attack("����ä��", ATTACK, FORM_WHIP, 3, "���ݷ� 3�� �⺻�ܰ��̴�");


	if (name == "���װ���")return new body("���װ���",BODY,1,"���� 1�� �����̴�");
	if (name == "�谩��")return new body("�谩��",BODY,2,"���� 2�� �����̴�");
	if (name == "����")return new body("����",BODY,3,"���ݷ�2���̴�");

	if (name == "������ȭ")return new feet("������ȭ",FEET,"���ݷ�1 ����");
	if (name == "�߷�����")return new feet("�߷�����",FEET,"����� �ʱ�ȭ�ȵ�");
	if (name == "������ȭ")return new feet("������ȭ",FEET,"��������");

	if (name == "�⺻ȶ��")return new torch("�⺻ȶ��",TORCH,1,"�þ�1����");
	if (name == "������ȶ��")return new torch("������ȶ��",TORCH,3,"�þ�3����");

}

item * itemManager::addCoin(int coinValue, int x, int y)
{
	return new coin(coinValue, x, y);
}

