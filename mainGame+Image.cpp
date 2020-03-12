#include "stdafx.h"
#include"mainGame.h"

void mainGame::imagesInit()
{
	//맵툴
	IMAGEMANAGER->addImage("샘플창", "images/maptool/샘플창.bmp", 300, WINSIZEY-200, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("맵툴지형", "images/maptool/맵툴_지형.bmp", 104*2, 104*2, 4, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("맵툴벽", "images/maptool/맵툴_벽.bmp", 104*2, 156*2, 4, 4, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("닫기", "images/maptool/닫기버튼.bmp", 64, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("뒤로", "images/maptool/뒤로가기버튼.bmp", 64, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("앞으로", "images/maptool/앞으로가기버튼.bmp", 64, 64, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("오브젝트버튼", "images/maptool/오브젝트.bmp", 75, 70, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("벽버튼", "images/maptool/벽.bmp", 75, 70, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("지형버튼", "images/maptool/지형.bmp", 75, 70, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("몬스터버튼", "images/maptool/몬스터.bmp", 75, 70, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("세이브버튼", "images/maptool/저장.bmp", 35, 15, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("로드버튼", "images/maptool/로드.bmp", 35, 15, true, RGB(255, 0, 255));


	//플레이어

	IMAGEMANAGER->addFrameImage("기본몸L", "images/player/nomalBodyL.bmp",80*3, 30*3, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("기본몸R", "images/player/nomalBodyR.bmp",80*3, 30*3, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("케이던스L", "images/player/cadensL.bmp",80*3, 30*3, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("케이던스R", "images/player/cadensR.bmp",80*3, 30*3, 4, 1, true, RGB(255, 0, 255));



	//UI
	IMAGEMANAGER->addImage("코인다이아", "images/UI/coinDiamond.bmp", 25*2, 47*2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("심장", "images/UI/heart.bmp",80*2, 50*2, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("노트전부", "images/UI/noteAll.bmp",18*2, 30*2, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("HP바", "images/UI/hpBar.bmp",72*2, 22*2,3,1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("노트", "images/UI/note1.bmp",6*2, 30*2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("빗나감", "images/UI/missed.bmp",36*2, 13*2, true, RGB(255, 0, 255));



	//아이템
	IMAGEMANAGER->addImage("삽", "images/item/shovel.bmp",60, 66, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("무기", "images/item/attack.bmp",60, 66, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("보디", "images/item/body.bmp",60, 66, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("폭탄", "images/item/bomb.bmp",60, 66, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("아이템", "images/item/item.bmp",60, 66, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("횃불", "images/item/torch.bmp",60, 66, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("신발", "images/item/feet.bmp",60, 66, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("던지기", "images/item/THROW.bmp",60, 66, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("던지세요", "images/item/press.bmp",60, 66, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("기본삽", "images/item/nomalShovel.bmp",48, 48 ,true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("티타늄삽", "images/item/titaniumShovel.bmp",48, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("유리삽", "images/item/glassShovel.bmp",48, 48, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("기본단검", "images/item/nomalShort.bmp",48, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("티타늄단검", "images/item/titaniumShort.bmp",48, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("유리단검", "images/item/glassShort.bmp",48, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("유리조각", "images/item/glass.bmp",48, 48, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("가죽갑옷", "images/item/가죽갑옷.bmp",48, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("쇠갑옷", "images/item/쇠갑옷.bmp",48, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("도복", "images/item/도복.bmp",48, 48, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("발레슈즈", "images/item/발레슈즈.bmp",48, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("날개장화", "images/item/날개장화.bmp",48, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("힘의장화", "images/item/힘의장화.bmp",48, 48, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("기본횃불", "images/item/기본횃불.bmp",48, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("빛나는횃불", "images/item/빛나는 횃불.bmp",48, 48, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("폭탄", "images/item/폭탄.bmp",48, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("폭탄3개", "images/item/폭탄3개.bmp",48, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("폭탄애니", "images/item/폭탄애니.bmp",96*2, 48,4,1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("사과", "images/item/사과.bmp",48, 48, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("작은코인", "images/item/smallCoin.bmp",52, 52, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("큰코인", "images/item/bigCoin.bmp",52, 52, true, RGB(255, 0, 255));



	//몬스터
	IMAGEMANAGER->addFrameImage("그린슬라임", "images/monster/greenSlime.bmp",92*3, 40*3,4,2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("블루슬라임", "images/monster/blueSlime.bmp",92*3, 40*3,4,2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("스켈레톤", "images/monster/해골.bmp",200*3, 60*3,8,2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("투명고스트L", "images/monster/ghostAlphaL.bmp", 18 * 3, 22 * 3, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("투명고스트R", "images/monster/ghostAlphaR.bmp", 18 * 3, 22 * 3, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("보이는고스트", "images/monster/ghostREAL.bmp",36*3, 44*3,2,2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("레드레이스", "images/monster/redWraiths.bmp",39*3, 23*3,3,1, true, RGB(255, 0, 255));



	//SOUND
	SOUNDMANAGER->addSound("1-1", "sound/1-1.mp3", true, true);

	//EFFECT
	EFFECTMANAGER->addEffect("할퀴기", "images/effect/할퀴기.bmp", 120*2, 23*2, 30*2, 23*2, 1, 0.5f, 100);
	EFFECTMANAGER->addEffect("점프먼지", "images/effect/jumpDust.bmp", 50*2, 10*2, 10*2, 10*2, 1, 0.5f, 100);
}