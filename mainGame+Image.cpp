#include "stdafx.h"
#include"mainGame.h"

void mainGame::imagesInit()
{
	//����

	IMAGEMANAGER->addFrameImage("��������", "images/����_����.bmp", 104*2, 78*2, 4, 3, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("������", "images/����_��.bmp", 104*2, 117*2, 4, 3, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���ú�", "images/���ú�.bmp", 826, 528, true, RGB(255, 0, 255));


	IMAGEMANAGER->addImage("�����ú�", "images/å��.bmp", 46, 136, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�ݱ�", "images/�ݱ��ư.bmp", 64, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�ڷ�", "images/�ڷΰ����ư.bmp", 64, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("������", "images/�����ΰ����ư.bmp", 64, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����", "images/dungeon.bmp", 215, 42, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����", "images/village.bmp", 215, 42, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���̺�", "images/save.bmp", 215, 42, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�ε�", "images/load.bmp", 215, 42, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����", "images/terrain.bmp", 215, 42, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("������Ʈ", "images/object.bmp", 215, 42, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("��Ʈ�ι��", "images/��Ʈ�ι��.bmp", 16384, WINSIZEY, 16, 1, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�ΰ�", "images/�ΰ�.bmp", 172 * 2, 140 * 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("��Ʈ�ν���", "images/��Ʈ�ν���.bmp", 544 / 2, 133 / 2 , true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("��Ʈ�θ���", "images/��Ʈ�θ���.bmp", 544 / 2, 133 / 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("��Ʈ�οɼ�", "images/��Ʈ�οɼ�.bmp", 544 / 2, 133 / 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("��Ʈ�γ�����", "images/��Ʈ�γ�����.bmp", 544 / 2, 133 / 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���������ư", "images/�����ε��ư1.bmp", 100, 100, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���������ư", "images/�����ε��ư2.bmp", 100, 100, true, RGB(255, 0, 255));


	IMAGEMANAGER->addImage("����â", "images/����â.bmp", 300, WINSIZEY-200, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("������Ʈ��ư", "images/������Ʈ.bmp", 75, 70, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����ư", "images/��.bmp", 75, 70, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("������ư", "images/����.bmp", 75, 70, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���͹�ư", "images/����.bmp", 75, 70, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("���̺��ư", "images/����.bmp", 35, 15, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�ε��ư", "images/�ε�.bmp", 35, 15, true, RGB(255, 0, 255));


	//�÷��̾�

	IMAGEMANAGER->addFrameImage("�⺻��L", "images/player/nomalBodyL.bmp",80*3, 30*3, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�⺻��R", "images/player/nomalBodyR.bmp",80*3, 30*3, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���̴���L", "images/player/cadensL.bmp",80*3, 30*3, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���̴���R", "images/player/cadensR.bmp",80*3, 30*3, 4, 1, true, RGB(255, 0, 255));


}