#include "stdafx.h"
#include"mainGame.h"

void mainGame::imagesInit()
{
	//����
	IMAGEMANAGER->addImage("����â", "images/maptool/����â.bmp", 300, WINSIZEY-200, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("��������", "images/maptool/����_����.bmp", 104*2, 104*2*4, 4, 4*4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("������", "images/maptool/����_��.bmp", 104*2, 156*2*2, 4, 8, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��������", "images/maptool/����_����.bmp", 216*2, 204*2, 4, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("������Ÿ", "images/maptool/����_ETC.bmp", 104*2, 104*2, 4, 4, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("�ݱ�", "images/maptool/�ݱ��ư.bmp", 64, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�ڷ�", "images/maptool/�ڷΰ����ư.bmp", 64, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("������", "images/maptool/�����ΰ����ư.bmp", 64, 64, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("������Ʈ��ư", "images/maptool/������Ʈ.bmp", 75, 70, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����ư", "images/maptool/��.bmp", 75, 70, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("������ư", "images/maptool/����.bmp", 75, 70, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���͹�ư", "images/maptool/����.bmp", 75, 70, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���̺��ư", "images/maptool/����.bmp", 35, 15, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�ε��ư", "images/maptool/�ε�.bmp", 35, 15, true, RGB(255, 0, 255));


	IMAGEMANAGER->addImage("��Ӱ�", "images/��Ӱ�.bmp", 52, 52, true, RGB(255, 0, 255));


	//�÷��̾�

	IMAGEMANAGER->addFrameImage("�⺻��L", "images/player/nomalBodyL.bmp",80*3, 30*3, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�⺻��R", "images/player/nomalBodyR.bmp",80*3, 30*3, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���̴���L", "images/player/cadensL.bmp",80*3, 30*3, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���̴���R", "images/player/cadensR.bmp",80*3, 30*3, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����R", "images/player/BodyR.bmp",80*3, 120*3, 4, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����L", "images/player/BodyL.bmp",80*3, 120*3, 4, 4, true, RGB(255, 0, 255));



	//UI
	IMAGEMANAGER->addImage("���δ��̾�", "images/UI/coinDiamond.bmp", 25*2, 47*2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����", "images/UI/heart.bmp",80*2, 50*2, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��Ʈ����", "images/UI/noteAll.bmp",18*2, 30*2, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("HP��", "images/UI/hpBar.bmp",72*2, 22*2,3,1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("��Ʈ", "images/UI/note1.bmp",6*2, 30*2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("������", "images/UI/missed.bmp",36*2, 13*2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("��Ʈ��", "images/UI/intro.bmp",WINSIZEX,WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("x��ư", "images/UI/x��ư.bmp",10,10, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("z��ư", "images/UI/z��ư.bmp",10,10, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("���ι��", "images/UI/���ι��.bmp",150,30, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���ι�������", "images/UI/���ι�������.bmp",180,30, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�ⱸ��ܿ���", "images/UI/�ⱸ��ܿ���.bmp",180,30, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("hit", "images/UI/hit.bmp",1024,768, false, RGB(255, 0, 255));


	IMAGEMANAGER->addFrameImage("��ŸƮ", "images/UI/��ŸƮ.bmp",330, 162,1,2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����", "images/UI/����.bmp",330, 162,1,2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("������", "images/UI/������.bmp",330, 162,1,2, true, RGB(255, 0, 255));


	IMAGEMANAGER->addFrameImage("����", "images/UI/number.bmp",120, 18,10,1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��ȶ��", "images/UI/��ȶ��.bmp",48*2, 21*4, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����", "images/UI/trap.bmp",63*2, 204*2, 3, 12, true, RGB(255, 0, 255));



	// ==============������ =============

	//����
	IMAGEMANAGER->addImage("��", "images/item/shovel.bmp",60, 66, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����", "images/item/attack.bmp",60, 66, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����", "images/item/body.bmp",60, 66, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("��ź����", "images/item/bomb.bmp",60, 66, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("������", "images/item/item.bmp",60, 66, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ȶ��", "images/item/torch.bmp",60, 66, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�Ź�", "images/item/feet.bmp",60, 66, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("������", "images/item/THROW.bmp",60, 66, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("��������", "images/item/press.bmp",60, 66, true, RGB(255, 0, 255));

	//����
	IMAGEMANAGER->addImage("�⺻�ܰ�", "images/item/nomalShort.bmp", 48, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ƼŸ���ܰ�", "images/item/titaniumShort.bmp", 48, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�����ܰ�", "images/item/glassShort.bmp", 48, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("��������", "images/item/glass.bmp", 48, 48, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("�⺻���", "images/item/nomalBig.bmp", 48, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ƼŸ�����", "images/item/titaniumBig.bmp", 48, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�������", "images/item/glassBig.bmp", 48, 48, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("�⺻â", "images/item/nomalSpear.bmp", 48, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ƼŸ��â", "images/item/titaniumSpear.bmp", 48, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����â", "images/item/glassSpear.bmp", 48, 48, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("�⺻Ȱ", "images/item/nomalBow.bmp", 48, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ƼŸ��Ȱ", "images/item/titaniumBow.bmp", 48, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����Ȱ", "images/item/glassBow.bmp", 48, 48, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("�⺻ä��", "images/item/nomalWhip.bmp", 48, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ƼŸ��ä��", "images/item/titaniumWhip.bmp", 48, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����ä��", "images/item/glassWhip.bmp", 48, 48, true, RGB(255, 0, 255));

	//��
	IMAGEMANAGER->addImage("�⺻��", "images/item/nomalShovel.bmp",48, 48 ,true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ƼŸ����", "images/item/titaniumShovel.bmp",48, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("������", "images/item/glassShovel.bmp",48, 48, true, RGB(255, 0, 255));

	//����
	IMAGEMANAGER->addImage("���װ���", "images/item/���װ���.bmp",48, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�谩��", "images/item/�谩��.bmp",48, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����", "images/item/����.bmp",48, 48, true, RGB(255, 0, 255));

	//�Ź�
	IMAGEMANAGER->addImage("�߷�����", "images/item/�߷�����.bmp",48, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("������ȭ", "images/item/������ȭ.bmp",48, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("������ȭ", "images/item/������ȭ.bmp",48, 48, true, RGB(255, 0, 255));

	//ȶ��
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
	IMAGEMANAGER->addFrameImage("����", "images/monster/bat.bmp",104*3, 32*3*2,4,4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���̷���", "images/monster/�ذ�.bmp",200*3, 60*3*2,8,4, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("�����ƮL", "images/monster/ghostAlphaL.bmp", 18 * 3, 22 * 3, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�����ƮR", "images/monster/ghostAlphaR.bmp", 18 * 3, 22 * 3, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("�����ƮL", "images/monster/ghostREAL.bmp",18*3, 22*3,1,1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("���巹�̽�", "images/monster/redWraiths.bmp",39*3, 46*3*2,3,4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�̳�Ÿ��ν�", "images/monster/Minotaurs.bmp",450*3, 100*3*2,9,4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����巡��", "images/monster/�巡��.bmp",549*3, 106*3*2,9,4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��������", "images/monster/��������.bmp",376*3, 152*3,8,4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����", "images/monster/����.bmp",153*3, 200*3,8,8, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("������Ż1", "images/boss/phase1.bmp",168*3, 424*3,2,8, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("������Ż2", "images/boss/phase2.bmp",168*3, 212*3,2,4, true, RGB(255, 0, 255));



	//SOUND
	SOUNDMANAGER->addSound("1-1", "sound/1-1.ogg", true, true);
	SOUNDMANAGER->addSound("1-2", "sound/1-2.ogg", true, true);
	SOUNDMANAGER->addSound("1-1shop", "sound/1-1shop.mp3", true, true);
	SOUNDMANAGER->addSound("intro", "sound/intro.mp3", true, true);
	SOUNDMANAGER->addSound("lobby", "sound/lobby.mp3", true, true);
	SOUNDMANAGER->addSound("boss", "sound/boss.ogg", true, true);

	//ȿ����
	SOUNDMANAGER->addSound("hit", "sound/hit.mp3", false, false);
	SOUNDMANAGER->addSound("mineOK", "sound/mineOK.mp3", false, false);
	SOUNDMANAGER->addSound("mineFAIL", "sound/mineFAIL.mp3", false, false);
	SOUNDMANAGER->addSound("openDoor", "sound/openDoor.mp3", false, false);
	SOUNDMANAGER->addSound("bomb", "sound/bomb.mp3", false, false);
	SOUNDMANAGER->addSound("eat", "sound/eat.mp3", false, false);
	SOUNDMANAGER->addSound("dig", "sound/dig.mp3", false, false);
	SOUNDMANAGER->addSound("atk", "sound/atk.mp3", false, false);
	SOUNDMANAGER->addSound("armor", "sound/armor.mp3", false, false);

	//EFFECT
	EFFECTMANAGER->addEffect("������", "images/effect/������.bmp", 120*2, 23*2, 30*2, 23*2, 1, 0.3f,1);
	EFFECTMANAGER->addEffect("��������", "images/effect/jumpDust.bmp", 50*2, 10*2, 10*2, 10*2, 1, 0.5f,5);
	EFFECTMANAGER->addEffect("�ܰ�L", "images/effect/�ܰ�L.bmp", 60 * 3, 20 * 3, 20 * 3, 20 * 3, 1, 0.3f,1);
	EFFECTMANAGER->addEffect("�ܰ�R", "images/effect/�ܰ�R.bmp", 60 * 3, 20 * 3, 20 *3, 20 * 3, 1, 0.3f,1);
	EFFECTMANAGER->addEffect("�ܰ�Up", "images/effect/�ܰ�Up.bmp", 60 * 3, 20 * 3, 20 * 3, 20 * 3, 1, 0.3f,1);
	EFFECTMANAGER->addEffect("�ܰ�Down", "images/effect/�ܰ�Down.bmp", 60 * 3, 20 * 3, 20 * 3, 20 * 3, 1, 0.3f,1);

	EFFECTMANAGER->addEffect("���L", "images/effect/���L.bmp",  69 * 3, 69 * 3, 23 * 3, 69 * 3, 1, 0.3f,1);
	EFFECTMANAGER->addEffect("���R", "images/effect/���R.bmp",  69 * 3, 69 * 3, 23 * 3, 69 * 3, 1, 0.3f,1);
	EFFECTMANAGER->addEffect("���Up", "images/effect/���Up.bmp", 69 * 3, 69 * 3, 69 * 3, 23 * 3, 1, 0.3f,1);
	EFFECTMANAGER->addEffect("���Down", "images/effect/���Down.bmp", 69 * 3, 69 * 3, 69 * 3, 23 * 3, 1, 0.3f,1);

	EFFECTMANAGER->addEffect("ȭ�쳡L", "images/effect/ȭ�쳡L.bmp", 104 * 3, 12 * 3, 52 * 3, 12 * 3, 1, 0.3f,1);
	EFFECTMANAGER->addEffect("ȭ�쳡R", "images/effect/ȭ�쳡R.bmp", 104 * 3, 12 * 3, 52 * 3, 12 * 3, 1, 0.3f,1);
	EFFECTMANAGER->addEffect("ȭ�쳡Up", "images/effect/ȭ�쳡Up.bmp", 12 * 3, 104 * 3, 12 * 3, 52 * 3, 1, 0.3f,1);
	EFFECTMANAGER->addEffect("ȭ�쳡Down", "images/effect/ȭ�쳡Down.bmp", 12 * 3, 104 * 3, 12 * 3, 52 * 3, 1, 0.3f,1);
	EFFECTMANAGER->addEffect("ȭ����ΰ���", "images/effect/ȭ����ΰ���.bmp", 104 * 3, 12 * 3, 52 * 3, 12 * 3, 1, 0.3f,1);
	EFFECTMANAGER->addEffect("ȭ����μ���", "images/effect/ȭ����μ���.bmp", 12 * 3, 104 * 3, 12 * 3, 52 * 3, 1, 0.3f,1);

	EFFECTMANAGER->addEffect("ä��R0", "images/effect/ä��R0.bmp", 96 * 3, 112 * 3, 24 * 3, 112 * 3, 1, 0.3f,1);
	EFFECTMANAGER->addEffect("ä��R1", "images/effect/ä��R1.bmp", 96 * 3, 112 * 3, 24 * 3, 112 * 3, 1, 0.3f,1);
	EFFECTMANAGER->addEffect("ä��R2", "images/effect/ä��R2.bmp", 96 * 3, 112 * 3, 24 * 3, 112 * 3, 1, 0.3f,1);
	EFFECTMANAGER->addEffect("ä��R3", "images/effect/ä��R3.bmp", 96 * 3, 112 * 3, 24 * 3, 112 * 3, 1, 0.3f,1);
	EFFECTMANAGER->addEffect("ä��R4", "images/effect/ä��R4.bmp", 96 * 3, 112 * 3, 24 * 3, 112 * 3, 1, 0.3f,1);
																							   
	EFFECTMANAGER->addEffect("ä��L0", "images/effect/ä��L0.bmp", 96 * 3, 112 * 3, 24 * 3, 112 * 3, 1, 0.3f,1);
	EFFECTMANAGER->addEffect("ä��L1", "images/effect/ä��L1.bmp", 96 * 3, 112 * 3, 24 * 3, 112 * 3, 1, 0.3f,1);
	EFFECTMANAGER->addEffect("ä��L2", "images/effect/ä��L2.bmp", 96 * 3, 112 * 3, 24 * 3, 112 * 3, 1, 0.3f,1);
	EFFECTMANAGER->addEffect("ä��L3", "images/effect/ä��L3.bmp", 96 * 3, 112 * 3, 24 * 3, 112 * 3, 1, 0.3f,1);
	EFFECTMANAGER->addEffect("ä��L4", "images/effect/ä��L4.bmp", 96 * 3, 112 * 3, 24 * 3, 112 * 3, 1, 0.3f,1);
																							   
	EFFECTMANAGER->addEffect("ä��U0", "images/effect/ä��U0.bmp", 112 * 3, 96 * 3, 112 * 3, 24 * 3, 1, 0.3f,1);
	EFFECTMANAGER->addEffect("ä��U1", "images/effect/ä��U1.bmp", 112 * 3, 96 * 3, 112 * 3, 24 * 3, 1, 0.3f,1);
	EFFECTMANAGER->addEffect("ä��U2", "images/effect/ä��U2.bmp", 112 * 3, 96 * 3, 112 * 3, 24 * 3, 1, 0.3f,1);
	EFFECTMANAGER->addEffect("ä��U3", "images/effect/ä��U3.bmp", 112 * 3, 96 * 3, 112 * 3, 24 * 3, 1, 0.3f,1);
	EFFECTMANAGER->addEffect("ä��U4", "images/effect/ä��U4.bmp", 112 * 3, 96 * 3, 112 * 3, 24 * 3, 1, 0.3f,1);
																							   
	EFFECTMANAGER->addEffect("ä��D0", "images/effect/ä��D0.bmp", 112 * 3, 96 * 3, 112 * 3, 24 * 3, 1, 0.3f,1);
	EFFECTMANAGER->addEffect("ä��D1", "images/effect/ä��D1.bmp", 112 * 3, 96 * 3, 112 * 3, 24 * 3, 1, 0.3f,1);
	EFFECTMANAGER->addEffect("ä��D2", "images/effect/ä��D2.bmp", 112 * 3, 96 * 3, 112 * 3, 24 * 3, 1, 0.3f,1);
	EFFECTMANAGER->addEffect("ä��D3", "images/effect/ä��D3.bmp", 112 * 3, 96 * 3, 112 * 3, 24 * 3, 1, 0.3f,1);
	EFFECTMANAGER->addEffect("ä��D4", "images/effect/ä��D4.bmp", 112 * 3, 96 * 3, 112 * 3, 24 * 3, 1, 0.3f,1);

	EFFECTMANAGER->addEffect("�⺻��", "images/item/nomalShovel.bmp", 48,48,48,48, 1, 0.1f,1);
	EFFECTMANAGER->addEffect("ƼŸ����", "images/item/titaniumShovel.bmp", 48,48, 48,48, 1, 0.1f,1);
	EFFECTMANAGER->addEffect("������", "images/item/glassShovel.bmp",48,48,48,48, 1, 0.1f,1);

	EFFECTMANAGER->addEffect("�巡��극��1L", "images/effect/�巡��극��1L.bmp",168*2,24*2,24*2,24*2, 1, 0.1f, 10);
	EFFECTMANAGER->addEffect("�巡��극��1R", "images/effect/�巡��극��1R.bmp",168*2,24*2,24*2,24*2, 1, 0.1f, 10);
	EFFECTMANAGER->addEffect("�巡��극��2", "images/effect/�巡��극��2.bmp",168*2,24*2,24*2,24*2, 1, 0.1f, 10);
	EFFECTMANAGER->addEffect("�巡��극��3", "images/effect/�巡��극��3.bmp",168*2,24*2,24*2,24*2, 1, 0.1f, 10);
	EFFECTMANAGER->addEffect("�巡��극��4", "images/effect/�巡��극��4.bmp",168*2,24*2,24*2,24*2, 1, 0.1f, 10);
	EFFECTMANAGER->addEffect("�巡��극��5", "images/effect/�巡��극��5.bmp",168*2,24*2,24*2,24*2, 1, 0.1f, 10);

	EFFECTMANAGER->addEffect("��ź�ִ�", "images/effect/��ź�ִ�.bmp",89*2,24*2,24*2,24*2, 10, 0.1f,1);
	EFFECTMANAGER->addEffect("��ź����", "images/effect/��ź����.bmp",576*2,74*2,72*2,74*2, 10, 0.1f,1);

}