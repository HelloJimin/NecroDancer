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

	if (name == "���װ���")return new body("���װ���",BODY,1,"���� 1�� �����̴�");
	if (name == "�谩��")return new body("�谩��",BODY,2,"���� 2�� �����̴�");
	if (name == "����")return new body("����",BODY,3,"���ݷ�2���̴�");

	if (name == "������ȭ")return new feet("������ȭ",FEET,"���ݷ�1 ����");
	if (name == "�߷�����")return new feet("�߷�����",FEET,"����� �ʱ�ȭ�ȵ�");
	if (name == "������ȭ")return new feet("������ȭ",FEET,"��������");

	if (name == "�⺻ȶ��")return new torch("�⺻ȶ��",TORCH,1,"�þ�1����");
	if (name == "������ȶ��")return new torch("������ȶ��",TORCH,3,"�þ�3����");

}

