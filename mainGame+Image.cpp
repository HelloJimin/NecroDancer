#include "stdafx.h"
#include"mainGame.h"

void mainGame::imagesInit()
{
	//����
	IMAGEMANAGER->addImage("����â", "images/maptool/����â.bmp", 300, WINSIZEY-200, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("��������", "images/maptool/����_����.bmp", 104*2, 78*2, 4, 3, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("������", "images/maptool/����_��.bmp", 104*2, 117*2, 4, 3, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("�ݱ�", "images/maptool/�ݱ��ư.bmp", 64, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�ڷ�", "images/maptool/�ڷΰ����ư.bmp", 64, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("������", "images/maptool/�����ΰ����ư.bmp", 64, 64, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("������Ʈ��ư", "images/maptool/������Ʈ.bmp", 75, 70, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����ư", "images/maptool/��.bmp", 75, 70, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("������ư", "images/maptool/����.bmp", 75, 70, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���͹�ư", "images/maptool/����.bmp", 75, 70, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���̺��ư", "images/maptool/����.bmp", 35, 15, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�ε��ư", "images/maptool/�ε�.bmp", 35, 15, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("Ŀ��", "images/maptool/cursor.bmp", 52, 52, true, RGB(255, 0, 255));


	//�÷��̾�

	IMAGEMANAGER->addFrameImage("�⺻��L", "images/player/nomalBodyL.bmp",80*3, 30*3, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�⺻��R", "images/player/nomalBodyR.bmp",80*3, 30*3, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���̴���L", "images/player/cadensL.bmp",80*3, 30*3, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���̴���R", "images/player/cadensR.bmp",80*3, 30*3, 4, 1, true, RGB(255, 0, 255));



	//UI
	IMAGEMANAGER->addImage("���δ��̾�", "images/UI/coinDiamond.bmp", 25*2, 47*2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����", "images/UI/heart.bmp",80*3, 50*2, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��Ʈ����", "images/UI/noteAll.bmp",18*2, 30*2, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("��Ʈ", "images/UI/note1.bmp",6*2, 30*2, true, RGB(255, 0, 255));





	//SOUND
	SOUNDMANAGER->addSound("1-1", "sound/1-1.mp3", true, true);
}