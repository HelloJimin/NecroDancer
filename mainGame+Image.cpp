#include "stdafx.h"
#include"mainGame.h"

void mainGame::imagesInit()
{
	//맵툴
	IMAGEMANAGER->addImage("샘플창", "images/maptool/샘플창.bmp", 300, WINSIZEY-200, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("맵툴지형", "images/maptool/맵툴_지형.bmp", 104*2, 78*2, 4, 3, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("맵툴벽", "images/maptool/맵툴_벽.bmp", 104*2, 117*2, 4, 3, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("닫기", "images/maptool/닫기버튼.bmp", 64, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("뒤로", "images/maptool/뒤로가기버튼.bmp", 64, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("앞으로", "images/maptool/앞으로가기버튼.bmp", 64, 64, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("오브젝트버튼", "images/maptool/오브젝트.bmp", 75, 70, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("벽버튼", "images/maptool/벽.bmp", 75, 70, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("지형버튼", "images/maptool/지형.bmp", 75, 70, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("몬스터버튼", "images/maptool/몬스터.bmp", 75, 70, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("세이브버튼", "images/maptool/저장.bmp", 35, 15, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("로드버튼", "images/maptool/로드.bmp", 35, 15, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("커서", "images/maptool/cursor.bmp", 52, 52, true, RGB(255, 0, 255));


	//플레이어

	IMAGEMANAGER->addFrameImage("기본몸L", "images/player/nomalBodyL.bmp",80*3, 30*3, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("기본몸R", "images/player/nomalBodyR.bmp",80*3, 30*3, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("케이던스L", "images/player/cadensL.bmp",80*3, 30*3, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("케이던스R", "images/player/cadensR.bmp",80*3, 30*3, 4, 1, true, RGB(255, 0, 255));



	//UI
	IMAGEMANAGER->addImage("코인다이아", "images/UI/coinDiamond.bmp", 25*2, 47*2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("심장", "images/UI/heart.bmp",80*3, 50*2, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("노트전부", "images/UI/noteAll.bmp",18*2, 30*2, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("노트", "images/UI/note1.bmp",6*2, 30*2, true, RGB(255, 0, 255));





	//SOUND
	SOUNDMANAGER->addSound("1-1", "sound/1-1.mp3", true, true);
}