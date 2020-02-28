#include "stdafx.h"
#include"mainGame.h"

void mainGame::imagesInit()
{
	//맵툴

	IMAGEMANAGER->addFrameImage("맵툴지형", "images/맵툴_지형.bmp", 104*2, 78*2, 4, 3, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("맵툴벽", "images/맵툴_벽.bmp", 104*2, 117*2, 4, 3, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("셈플북", "images/셈플북.bmp", 826, 528, true, RGB(255, 0, 255));


	IMAGEMANAGER->addImage("옆셈플북", "images/책옆.bmp", 46, 136, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("닫기", "images/닫기버튼.bmp", 64, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("뒤로", "images/뒤로가기버튼.bmp", 64, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("앞으로", "images/앞으로가기버튼.bmp", 64, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("던전", "images/dungeon.bmp", 215, 42, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("마을", "images/village.bmp", 215, 42, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("세이브", "images/save.bmp", 215, 42, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("로드", "images/load.bmp", 215, 42, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("지형", "images/terrain.bmp", 215, 42, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("오브젝트", "images/object.bmp", 215, 42, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("인트로배경", "images/인트로배경.bmp", 16384, WINSIZEY, 16, 1, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("로고", "images/로고.bmp", 172 * 2, 140 * 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("인트로시작", "images/인트로시작.bmp", 544 / 2, 133 / 2 , true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("인트로맵툴", "images/인트로맵툴.bmp", 544 / 2, 133 / 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("인트로옵션", "images/인트로옵션.bmp", 544 / 2, 133 / 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("인트로나가기", "images/인트로나가기.bmp", 544 / 2, 133 / 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("던전저장버튼", "images/맵툴로드버튼1.bmp", 100, 100, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("마을저장버튼", "images/맵툴로드버튼2.bmp", 100, 100, true, RGB(255, 0, 255));


	IMAGEMANAGER->addImage("샘플창", "images/샘플창.bmp", 300, WINSIZEY-200, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("오브젝트버튼", "images/오브젝트.bmp", 75, 70, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("벽버튼", "images/벽.bmp", 75, 70, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("지형버튼", "images/지형.bmp", 75, 70, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("몬스터버튼", "images/몬스터.bmp", 75, 70, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("세이브버튼", "images/저장.bmp", 35, 15, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("로드버튼", "images/로드.bmp", 35, 15, true, RGB(255, 0, 255));


	//플레이어

	IMAGEMANAGER->addFrameImage("기본몸L", "images/player/nomalBodyL.bmp",80*3, 30*3, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("기본몸R", "images/player/nomalBodyR.bmp",80*3, 30*3, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("케이던스L", "images/player/cadensL.bmp",80*3, 30*3, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("케이던스R", "images/player/cadensR.bmp",80*3, 30*3, 4, 1, true, RGB(255, 0, 255));


}