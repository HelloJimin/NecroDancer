#include "stdafx.h"
#include"mainGame.h"

void mainGame::imagesInit()
{
	//맵툴
	IMAGEMANAGER->addImage("샘플창", "images/maptool/샘플창.bmp", 300, WINSIZEY-200, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("맵툴지형", "images/maptool/맵툴_지형.bmp", 104*2, 104*2*4, 4, 4*4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("맵툴벽", "images/maptool/맵툴_벽.bmp", 104*2, 156*2*2, 4, 8, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("맵툴몬스터", "images/maptool/맵툴_몬스터.bmp", 216*2, 204*2, 4, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("맵툴기타", "images/maptool/맵툴_ETC.bmp", 104*2, 104*2, 4, 4, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("닫기", "images/maptool/닫기버튼.bmp", 64, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("뒤로", "images/maptool/뒤로가기버튼.bmp", 64, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("앞으로", "images/maptool/앞으로가기버튼.bmp", 64, 64, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("오브젝트버튼", "images/maptool/오브젝트.bmp", 75, 70, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("벽버튼", "images/maptool/벽.bmp", 75, 70, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("지형버튼", "images/maptool/지형.bmp", 75, 70, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("몬스터버튼", "images/maptool/몬스터.bmp", 75, 70, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("세이브버튼", "images/maptool/저장.bmp", 35, 15, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("로드버튼", "images/maptool/로드.bmp", 35, 15, true, RGB(255, 0, 255));


	IMAGEMANAGER->addImage("어둡게", "images/어둡게.bmp", 52, 52, true, RGB(255, 0, 255));


	//플레이어

	IMAGEMANAGER->addFrameImage("기본몸L", "images/player/nomalBodyL.bmp",80*3, 30*3, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("기본몸R", "images/player/nomalBodyR.bmp",80*3, 30*3, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("케이던스L", "images/player/cadensL.bmp",80*3, 30*3, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("케이던스R", "images/player/cadensR.bmp",80*3, 30*3, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("몸통R", "images/player/BodyR.bmp",80*3, 120*3, 4, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("몸통L", "images/player/BodyL.bmp",80*3, 120*3, 4, 4, true, RGB(255, 0, 255));



	//UI
	IMAGEMANAGER->addImage("코인다이아", "images/UI/coinDiamond.bmp", 25*2, 47*2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("심장", "images/UI/heart.bmp",80*2, 50*2, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("노트전부", "images/UI/noteAll.bmp",18*2, 30*2, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("HP바", "images/UI/hpBar.bmp",72*2, 22*2,3,1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("노트", "images/UI/note1.bmp",6*2, 30*2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("빗나감", "images/UI/missed.bmp",36*2, 13*2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("인트로", "images/UI/intro.bmp",WINSIZEX,WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("x버튼", "images/UI/x버튼.bmp",10,10, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("z버튼", "images/UI/z버튼.bmp",10,10, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("코인배수", "images/UI/코인배수.bmp",150,30, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("코인배수사라짐", "images/UI/코인배수사라짐.bmp",180,30, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("출구계단열림", "images/UI/출구계단열림.bmp",180,30, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("hit", "images/UI/hit.bmp",1024,768, false, RGB(255, 0, 255));


	IMAGEMANAGER->addFrameImage("스타트", "images/UI/스타트.bmp",330, 162,1,2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("맵툴", "images/UI/맵툴.bmp",330, 162,1,2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("나가기", "images/UI/나가기.bmp",330, 162,1,2, true, RGB(255, 0, 255));


	IMAGEMANAGER->addFrameImage("숫자", "images/UI/number.bmp",120, 18,10,1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("벽횃불", "images/UI/벽횃불.bmp",48*2, 21*4, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("함정", "images/UI/trap.bmp",63*2, 204*2, 3, 12, true, RGB(255, 0, 255));



	// ==============아이템 =============

	//슬롯
	IMAGEMANAGER->addImage("삽", "images/item/shovel.bmp",60, 66, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("무기", "images/item/attack.bmp",60, 66, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("보디", "images/item/body.bmp",60, 66, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("폭탄슬롯", "images/item/bomb.bmp",60, 66, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("아이템", "images/item/item.bmp",60, 66, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("횃불", "images/item/torch.bmp",60, 66, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("신발", "images/item/feet.bmp",60, 66, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("던지기", "images/item/THROW.bmp",60, 66, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("던지세요", "images/item/press.bmp",60, 66, true, RGB(255, 0, 255));

	//무기
	IMAGEMANAGER->addImage("기본단검", "images/item/nomalShort.bmp", 48, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("티타늄단검", "images/item/titaniumShort.bmp", 48, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("유리단검", "images/item/glassShort.bmp", 48, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("유리조각", "images/item/glass.bmp", 48, 48, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("기본대검", "images/item/nomalBig.bmp", 48, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("티타늄대검", "images/item/titaniumBig.bmp", 48, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("유리대검", "images/item/glassBig.bmp", 48, 48, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("기본창", "images/item/nomalSpear.bmp", 48, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("티타늄창", "images/item/titaniumSpear.bmp", 48, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("유리창", "images/item/glassSpear.bmp", 48, 48, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("기본활", "images/item/nomalBow.bmp", 48, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("티타늄활", "images/item/titaniumBow.bmp", 48, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("유리활", "images/item/glassBow.bmp", 48, 48, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("기본채찍", "images/item/nomalWhip.bmp", 48, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("티타늄채찍", "images/item/titaniumWhip.bmp", 48, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("유리채찍", "images/item/glassWhip.bmp", 48, 48, true, RGB(255, 0, 255));

	//삽
	IMAGEMANAGER->addImage("기본삽", "images/item/nomalShovel.bmp",48, 48 ,true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("티타늄삽", "images/item/titaniumShovel.bmp",48, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("유리삽", "images/item/glassShovel.bmp",48, 48, true, RGB(255, 0, 255));

	//갑옷
	IMAGEMANAGER->addImage("가죽갑옷", "images/item/가죽갑옷.bmp",48, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("쇠갑옷", "images/item/쇠갑옷.bmp",48, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("도복", "images/item/도복.bmp",48, 48, true, RGB(255, 0, 255));

	//신발
	IMAGEMANAGER->addImage("발레슈즈", "images/item/발레슈즈.bmp",48, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("날개장화", "images/item/날개장화.bmp",48, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("힘의장화", "images/item/힘의장화.bmp",48, 48, true, RGB(255, 0, 255));

	//횃불
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
	IMAGEMANAGER->addFrameImage("박쥐", "images/monster/bat.bmp",104*3, 32*3*2,4,4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("스켈레톤", "images/monster/해골.bmp",200*3, 60*3*2,8,4, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("투명고스트L", "images/monster/ghostAlphaL.bmp", 18 * 3, 22 * 3, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("투명고스트R", "images/monster/ghostAlphaR.bmp", 18 * 3, 22 * 3, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("투명고스트L", "images/monster/ghostREAL.bmp",18*3, 22*3,1,1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("레드레이스", "images/monster/redWraiths.bmp",39*3, 46*3*2,3,4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("미노타우로스", "images/monster/Minotaurs.bmp",450*3, 100*3*2,9,4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("레드드래곤", "images/monster/드래곤.bmp",549*3, 106*3*2,9,4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("상점주인", "images/monster/상점주인.bmp",376*3, 152*3,8,4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("좀비", "images/monster/좀비.bmp",153*3, 200*3,8,8, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("데스메탈1", "images/boss/phase1.bmp",168*3, 424*3,2,8, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("데스메탈2", "images/boss/phase2.bmp",168*3, 212*3,2,4, true, RGB(255, 0, 255));



	//SOUND
	SOUNDMANAGER->addSound("1-1", "sound/1-1.ogg", true, true);
	SOUNDMANAGER->addSound("1-2", "sound/1-2.ogg", true, true);
	SOUNDMANAGER->addSound("1-1shop", "sound/1-1shop.mp3", true, true);
	SOUNDMANAGER->addSound("intro", "sound/intro.mp3", true, true);
	SOUNDMANAGER->addSound("lobby", "sound/lobby.mp3", true, true);
	SOUNDMANAGER->addSound("boss", "sound/boss.ogg", true, true);

	//효과음
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
	EFFECTMANAGER->addEffect("할퀴기", "images/effect/할퀴기.bmp", 120*2, 23*2, 30*2, 23*2, 1, 0.3f,1);
	EFFECTMANAGER->addEffect("점프먼지", "images/effect/jumpDust.bmp", 50*2, 10*2, 10*2, 10*2, 1, 0.5f,5);
	EFFECTMANAGER->addEffect("단검L", "images/effect/단검L.bmp", 60 * 3, 20 * 3, 20 * 3, 20 * 3, 1, 0.3f,1);
	EFFECTMANAGER->addEffect("단검R", "images/effect/단검R.bmp", 60 * 3, 20 * 3, 20 *3, 20 * 3, 1, 0.3f,1);
	EFFECTMANAGER->addEffect("단검Up", "images/effect/단검Up.bmp", 60 * 3, 20 * 3, 20 * 3, 20 * 3, 1, 0.3f,1);
	EFFECTMANAGER->addEffect("단검Down", "images/effect/단검Down.bmp", 60 * 3, 20 * 3, 20 * 3, 20 * 3, 1, 0.3f,1);

	EFFECTMANAGER->addEffect("대검L", "images/effect/대검L.bmp",  69 * 3, 69 * 3, 23 * 3, 69 * 3, 1, 0.3f,1);
	EFFECTMANAGER->addEffect("대검R", "images/effect/대검R.bmp",  69 * 3, 69 * 3, 23 * 3, 69 * 3, 1, 0.3f,1);
	EFFECTMANAGER->addEffect("대검Up", "images/effect/대검Up.bmp", 69 * 3, 69 * 3, 69 * 3, 23 * 3, 1, 0.3f,1);
	EFFECTMANAGER->addEffect("대검Down", "images/effect/대검Down.bmp", 69 * 3, 69 * 3, 69 * 3, 23 * 3, 1, 0.3f,1);

	EFFECTMANAGER->addEffect("화살끝L", "images/effect/화살끝L.bmp", 104 * 3, 12 * 3, 52 * 3, 12 * 3, 1, 0.3f,1);
	EFFECTMANAGER->addEffect("화살끝R", "images/effect/화살끝R.bmp", 104 * 3, 12 * 3, 52 * 3, 12 * 3, 1, 0.3f,1);
	EFFECTMANAGER->addEffect("화살끝Up", "images/effect/화살끝Up.bmp", 12 * 3, 104 * 3, 12 * 3, 52 * 3, 1, 0.3f,1);
	EFFECTMANAGER->addEffect("화살끝Down", "images/effect/화살끝Down.bmp", 12 * 3, 104 * 3, 12 * 3, 52 * 3, 1, 0.3f,1);
	EFFECTMANAGER->addEffect("화살라인가로", "images/effect/화살라인가로.bmp", 104 * 3, 12 * 3, 52 * 3, 12 * 3, 1, 0.3f,1);
	EFFECTMANAGER->addEffect("화살라인세로", "images/effect/화살라인세로.bmp", 12 * 3, 104 * 3, 12 * 3, 52 * 3, 1, 0.3f,1);

	EFFECTMANAGER->addEffect("채찍R0", "images/effect/채찍R0.bmp", 96 * 3, 112 * 3, 24 * 3, 112 * 3, 1, 0.3f,1);
	EFFECTMANAGER->addEffect("채찍R1", "images/effect/채찍R1.bmp", 96 * 3, 112 * 3, 24 * 3, 112 * 3, 1, 0.3f,1);
	EFFECTMANAGER->addEffect("채찍R2", "images/effect/채찍R2.bmp", 96 * 3, 112 * 3, 24 * 3, 112 * 3, 1, 0.3f,1);
	EFFECTMANAGER->addEffect("채찍R3", "images/effect/채찍R3.bmp", 96 * 3, 112 * 3, 24 * 3, 112 * 3, 1, 0.3f,1);
	EFFECTMANAGER->addEffect("채찍R4", "images/effect/채찍R4.bmp", 96 * 3, 112 * 3, 24 * 3, 112 * 3, 1, 0.3f,1);
																							   
	EFFECTMANAGER->addEffect("채찍L0", "images/effect/채찍L0.bmp", 96 * 3, 112 * 3, 24 * 3, 112 * 3, 1, 0.3f,1);
	EFFECTMANAGER->addEffect("채찍L1", "images/effect/채찍L1.bmp", 96 * 3, 112 * 3, 24 * 3, 112 * 3, 1, 0.3f,1);
	EFFECTMANAGER->addEffect("채찍L2", "images/effect/채찍L2.bmp", 96 * 3, 112 * 3, 24 * 3, 112 * 3, 1, 0.3f,1);
	EFFECTMANAGER->addEffect("채찍L3", "images/effect/채찍L3.bmp", 96 * 3, 112 * 3, 24 * 3, 112 * 3, 1, 0.3f,1);
	EFFECTMANAGER->addEffect("채찍L4", "images/effect/채찍L4.bmp", 96 * 3, 112 * 3, 24 * 3, 112 * 3, 1, 0.3f,1);
																							   
	EFFECTMANAGER->addEffect("채찍U0", "images/effect/채찍U0.bmp", 112 * 3, 96 * 3, 112 * 3, 24 * 3, 1, 0.3f,1);
	EFFECTMANAGER->addEffect("채찍U1", "images/effect/채찍U1.bmp", 112 * 3, 96 * 3, 112 * 3, 24 * 3, 1, 0.3f,1);
	EFFECTMANAGER->addEffect("채찍U2", "images/effect/채찍U2.bmp", 112 * 3, 96 * 3, 112 * 3, 24 * 3, 1, 0.3f,1);
	EFFECTMANAGER->addEffect("채찍U3", "images/effect/채찍U3.bmp", 112 * 3, 96 * 3, 112 * 3, 24 * 3, 1, 0.3f,1);
	EFFECTMANAGER->addEffect("채찍U4", "images/effect/채찍U4.bmp", 112 * 3, 96 * 3, 112 * 3, 24 * 3, 1, 0.3f,1);
																							   
	EFFECTMANAGER->addEffect("채찍D0", "images/effect/채찍D0.bmp", 112 * 3, 96 * 3, 112 * 3, 24 * 3, 1, 0.3f,1);
	EFFECTMANAGER->addEffect("채찍D1", "images/effect/채찍D1.bmp", 112 * 3, 96 * 3, 112 * 3, 24 * 3, 1, 0.3f,1);
	EFFECTMANAGER->addEffect("채찍D2", "images/effect/채찍D2.bmp", 112 * 3, 96 * 3, 112 * 3, 24 * 3, 1, 0.3f,1);
	EFFECTMANAGER->addEffect("채찍D3", "images/effect/채찍D3.bmp", 112 * 3, 96 * 3, 112 * 3, 24 * 3, 1, 0.3f,1);
	EFFECTMANAGER->addEffect("채찍D4", "images/effect/채찍D4.bmp", 112 * 3, 96 * 3, 112 * 3, 24 * 3, 1, 0.3f,1);

	EFFECTMANAGER->addEffect("기본삽", "images/item/nomalShovel.bmp", 48,48,48,48, 1, 0.1f,1);
	EFFECTMANAGER->addEffect("티타늄삽", "images/item/titaniumShovel.bmp", 48,48, 48,48, 1, 0.1f,1);
	EFFECTMANAGER->addEffect("유리삽", "images/item/glassShovel.bmp",48,48,48,48, 1, 0.1f,1);

	EFFECTMANAGER->addEffect("드래곤브레스1L", "images/effect/드래곤브레스1L.bmp",168*2,24*2,24*2,24*2, 1, 0.1f, 10);
	EFFECTMANAGER->addEffect("드래곤브레스1R", "images/effect/드래곤브레스1R.bmp",168*2,24*2,24*2,24*2, 1, 0.1f, 10);
	EFFECTMANAGER->addEffect("드래곤브레스2", "images/effect/드래곤브레스2.bmp",168*2,24*2,24*2,24*2, 1, 0.1f, 10);
	EFFECTMANAGER->addEffect("드래곤브레스3", "images/effect/드래곤브레스3.bmp",168*2,24*2,24*2,24*2, 1, 0.1f, 10);
	EFFECTMANAGER->addEffect("드래곤브레스4", "images/effect/드래곤브레스4.bmp",168*2,24*2,24*2,24*2, 1, 0.1f, 10);
	EFFECTMANAGER->addEffect("드래곤브레스5", "images/effect/드래곤브레스5.bmp",168*2,24*2,24*2,24*2, 1, 0.1f, 10);

	EFFECTMANAGER->addEffect("폭탄애니", "images/effect/폭탄애니.bmp",89*2,24*2,24*2,24*2, 10, 0.1f,1);
	EFFECTMANAGER->addEffect("폭탄폭발", "images/effect/폭탄폭발.bmp",576*2,74*2,72*2,74*2, 10, 0.1f,1);

}