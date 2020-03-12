#include "stdafx.h"
#include"mainGame.h"

void mainGame::imagesInit()
{
	//����
	IMAGEMANAGER->addImage("����â", "images/maptool/����â.bmp", 300, WINSIZEY-200, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("��������", "images/maptool/����_����.bmp", 104*2, 104*2, 4, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("������", "images/maptool/����_��.bmp", 104*2, 156*2, 4, 4, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("�ݱ�", "images/maptool/�ݱ��ư.bmp", 64, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�ڷ�", "images/maptool/�ڷΰ����ư.bmp", 64, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("������", "images/maptool/�����ΰ����ư.bmp", 64, 64, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("������Ʈ��ư", "images/maptool/������Ʈ.bmp", 75, 70, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����ư", "images/maptool/��.bmp", 75, 70, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("������ư", "images/maptool/����.bmp", 75, 70, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���͹�ư", "images/maptool/����.bmp", 75, 70, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���̺��ư", "images/maptool/����.bmp", 35, 15, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�ε��ư", "images/maptool/�ε�.bmp", 35, 15, true, RGB(255, 0, 255));


	//�÷��̾�

	IMAGEMANAGER->addFrameImage("�⺻��L", "images/player/nomalBodyL.bmp",80*3, 30*3, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�⺻��R", "images/player/nomalBodyR.bmp",80*3, 30*3, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���̴���L", "images/player/cadensL.bmp",80*3, 30*3, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���̴���R", "images/player/cadensR.bmp",80*3, 30*3, 4, 1, true, RGB(255, 0, 255));



	//UI
	IMAGEMANAGER->addImage("���δ��̾�", "images/UI/coinDiamond.bmp", 25*2, 47*2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����", "images/UI/heart.bmp",80*2, 50*2, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��Ʈ����", "images/UI/noteAll.bmp",18*2, 30*2, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("HP��", "images/UI/hpBar.bmp",72*2, 22*2,3,1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("��Ʈ", "images/UI/note1.bmp",6*2, 30*2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("������", "images/UI/missed.bmp",36*2, 13*2, true, RGB(255, 0, 255));



	//������
	IMAGEMANAGER->addImage("��", "images/item/shovel.bmp",60, 66, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����", "images/item/attack.bmp",60, 66, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����", "images/item/body.bmp",60, 66, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("��ź", "images/item/bomb.bmp",60, 66, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("������", "images/item/item.bmp",60, 66, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ȶ��", "images/item/torch.bmp",60, 66, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�Ź�", "images/item/feet.bmp",60, 66, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("������", "images/item/THROW.bmp",60, 66, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("��������", "images/item/press.bmp",60, 66, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("�⺻��", "images/item/nomalShovel.bmp",48, 48 ,true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ƼŸ����", "images/item/titaniumShovel.bmp",48, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("������", "images/item/glassShovel.bmp",48, 48, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("�⺻�ܰ�", "images/item/nomalShort.bmp",48, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ƼŸ���ܰ�", "images/item/titaniumShort.bmp",48, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�����ܰ�", "images/item/glassShort.bmp",48, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("��������", "images/item/glass.bmp",48, 48, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("���װ���", "images/item/���װ���.bmp",48, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�谩��", "images/item/�谩��.bmp",48, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����", "images/item/����.bmp",48, 48, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("�߷�����", "images/item/�߷�����.bmp",48, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("������ȭ", "images/item/������ȭ.bmp",48, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("������ȭ", "images/item/������ȭ.bmp",48, 48, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("�⺻ȶ��", "images/item/�⺻ȶ��.bmp",48, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("������ȶ��", "images/item/������ ȶ��.bmp",48, 48, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("��ź", "images/item/��ź.bmp",48, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("��ź3��", "images/item/��ź3��.bmp",48, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��ź�ִ�", "images/item/��ź�ִ�.bmp",96*2, 48,4,1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("���", "images/item/���.bmp",48, 48, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("��������", "images/item/smallCoin.bmp",52, 52, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ū����", "images/item/bigCoin.bmp",52, 52, true, RGB(255, 0, 255));



	//����
	IMAGEMANAGER->addFrameImage("�׸�������", "images/monster/greenSlime.bmp",92*3, 40*3,4,2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��罽����", "images/monster/blueSlime.bmp",92*3, 40*3,4,2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���̷���", "images/monster/�ذ�.bmp",200*3, 60*3,8,2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("�����ƮL", "images/monster/ghostAlphaL.bmp", 18 * 3, 22 * 3, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�����ƮR", "images/monster/ghostAlphaR.bmp", 18 * 3, 22 * 3, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���̴°�Ʈ", "images/monster/ghostREAL.bmp",36*3, 44*3,2,2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("���巹�̽�", "images/monster/redWraiths.bmp",39*3, 23*3,3,1, true, RGB(255, 0, 255));



	//SOUND
	SOUNDMANAGER->addSound("1-1", "sound/1-1.mp3", true, true);

	//EFFECT
	EFFECTMANAGER->addEffect("������", "images/effect/������.bmp", 120*2, 23*2, 30*2, 23*2, 1, 0.5f, 100);
	EFFECTMANAGER->addEffect("��������", "images/effect/jumpDust.bmp", 50*2, 10*2, 10*2, 10*2, 1, 0.5f, 100);
}