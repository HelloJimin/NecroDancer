#include "stdafx.h"
#include"mainGame.h"

void mainGame::imagesInit()
{
	//¸ÊÅø
	IMAGEMANAGER->addImage("»ùÇÃÃ¢", "images/maptool/»ùÇÃÃ¢.bmp", 300, WINSIZEY-200, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("¸ÊÅøÁöÇü", "images/maptool/¸ÊÅø_ÁöÇü.bmp", 104*2, 104*2, 4, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("¸ÊÅøº®", "images/maptool/¸ÊÅø_º®.bmp", 104*2, 156*2, 4, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("¸ÊÅø¸ó½ºÅÍ", "images/maptool/¸ÊÅø_¸ó½ºÅÍ.bmp", 216*2, 204*2, 4, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("¸ÊÅø±âÅ¸", "images/maptool/¸ÊÅø_ETC.bmp", 104*2, 104*2, 4, 4, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("´Ý±â", "images/maptool/´Ý±â¹öÆ°.bmp", 64, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("µÚ·Î", "images/maptool/µÚ·Î°¡±â¹öÆ°.bmp", 64, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("¾ÕÀ¸·Î", "images/maptool/¾ÕÀ¸·Î°¡±â¹öÆ°.bmp", 64, 64, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("¿ÀºêÁ§Æ®¹öÆ°", "images/maptool/¿ÀºêÁ§Æ®.bmp", 75, 70, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("º®¹öÆ°", "images/maptool/º®.bmp", 75, 70, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ÁöÇü¹öÆ°", "images/maptool/ÁöÇü.bmp", 75, 70, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("¸ó½ºÅÍ¹öÆ°", "images/maptool/¸ó½ºÅÍ.bmp", 75, 70, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("¼¼ÀÌºê¹öÆ°", "images/maptool/ÀúÀå.bmp", 35, 15, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("·Îµå¹öÆ°", "images/maptool/·Îµå.bmp", 35, 15, true, RGB(255, 0, 255));


	//ÇÃ·¹ÀÌ¾î

	IMAGEMANAGER->addFrameImage("±âº»¸öL", "images/player/nomalBodyL.bmp",80*3, 30*3, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("±âº»¸öR", "images/player/nomalBodyR.bmp",80*3, 30*3, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ÄÉÀÌ´ø½ºL", "images/player/cadensL.bmp",80*3, 30*3, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ÄÉÀÌ´ø½ºR", "images/player/cadensR.bmp",80*3, 30*3, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("¸öÅëR", "images/player/BodyR.bmp",80*3, 120*3, 4, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("¸öÅëL", "images/player/BodyL.bmp",80*3, 120*3, 4, 4, true, RGB(255, 0, 255));



	//UI
	IMAGEMANAGER->addImage("ÄÚÀÎ´ÙÀÌ¾Æ", "images/UI/coinDiamond.bmp", 25*2, 47*2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("½ÉÀå", "images/UI/heart.bmp",80*2, 50*2, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("³ëÆ®ÀüºÎ", "images/UI/noteAll.bmp",18*2, 30*2, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("HP¹Ù", "images/UI/hpBar.bmp",72*2, 22*2,3,1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("³ëÆ®", "images/UI/note1.bmp",6*2, 30*2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ºø³ª°¨", "images/UI/missed.bmp",36*2, 13*2, true, RGB(255, 0, 255));



	// ==============¾ÆÀÌÅÛ =============

	//½½·Ô
	IMAGEMANAGER->addImage("»ð", "images/item/shovel.bmp",60, 66, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("¹«±â", "images/item/attack.bmp",60, 66, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("º¸µð", "images/item/body.bmp",60, 66, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ÆøÅº", "images/item/bomb.bmp",60, 66, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("¾ÆÀÌÅÛ", "images/item/item.bmp",60, 66, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("È¶ºÒ", "images/item/torch.bmp",60, 66, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("½Å¹ß", "images/item/feet.bmp",60, 66, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("´øÁö±â", "images/item/THROW.bmp",60, 66, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("´øÁö¼¼¿ä", "images/item/press.bmp",60, 66, true, RGB(255, 0, 255));

	//¹«±â
	IMAGEMANAGER->addImage("±âº»´Ü°Ë", "images/item/nomalShort.bmp", 48, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Æ¼Å¸´½´Ü°Ë", "images/item/titaniumShort.bmp", 48, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("À¯¸®´Ü°Ë", "images/item/glassShort.bmp", 48, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("À¯¸®Á¶°¢", "images/item/glass.bmp", 48, 48, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("±âº»´ë°Ë", "images/item/nomalBig.bmp", 48, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Æ¼Å¸´½´ë°Ë", "images/item/titaniumBig.bmp", 48, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("À¯¸®´ë°Ë", "images/item/glassBig.bmp", 48, 48, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("±âº»Ã¢", "images/item/nomalSpear.bmp", 48, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Æ¼Å¸´½Ã¢", "images/item/titaniumSpear.bmp", 48, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("À¯¸®Ã¢", "images/item/glassSpear.bmp", 48, 48, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("±âº»È°", "images/item/nomalBow.bmp", 48, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Æ¼Å¸´½È°", "images/item/titaniumBow.bmp", 48, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("À¯¸®È°", "images/item/glassBow.bmp", 48, 48, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("±âº»Ã¤Âï", "images/item/nomalWhip.bmp", 48, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Æ¼Å¸´½Ã¤Âï", "images/item/titaniumWhip.bmp", 48, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("À¯¸®Ã¤Âï", "images/item/glassWhip.bmp", 48, 48, true, RGB(255, 0, 255));

	//»ð
	IMAGEMANAGER->addImage("±âº»»ð", "images/item/nomalShovel.bmp",48, 48 ,true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Æ¼Å¸´½»ð", "images/item/titaniumShovel.bmp",48, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("À¯¸®»ð", "images/item/glassShovel.bmp",48, 48, true, RGB(255, 0, 255));

	//°©¿Ê
	IMAGEMANAGER->addImage("°¡Á×°©¿Ê", "images/item/°¡Á×°©¿Ê.bmp",48, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("¼è°©¿Ê", "images/item/¼è°©¿Ê.bmp",48, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("µµº¹", "images/item/µµº¹.bmp",48, 48, true, RGB(255, 0, 255));

	//½Å¹ß
	IMAGEMANAGER->addImage("¹ß·¹½´Áî", "images/item/¹ß·¹½´Áî.bmp",48, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("³¯°³ÀåÈ­", "images/item/³¯°³ÀåÈ­.bmp",48, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ÈûÀÇÀåÈ­", "images/item/ÈûÀÇÀåÈ­.bmp",48, 48, true, RGB(255, 0, 255));

	//È¶ºÒ
	IMAGEMANAGER->addImage("±âº»È¶ºÒ", "images/item/±âº»È¶ºÒ.bmp",48, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ºû³ª´ÂÈ¶ºÒ", "images/item/ºû³ª´Â È¶ºÒ.bmp",48, 48, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("ÆøÅº", "images/item/ÆøÅº.bmp",48, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ÆøÅº3°³", "images/item/ÆøÅº3°³.bmp",48, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ÆøÅº¾Ö´Ï", "images/item/ÆøÅº¾Ö´Ï.bmp",96*2, 48,4,1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("»ç°ú", "images/item/»ç°ú.bmp",48, 48, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("ÀÛÀºÄÚÀÎ", "images/item/smallCoin.bmp",52, 52, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Å«ÄÚÀÎ", "images/item/bigCoin.bmp",52, 52, true, RGB(255, 0, 255));



	//¸ó½ºÅÍ
	IMAGEMANAGER->addFrameImage("±×¸°½½¶óÀÓ", "images/monster/greenSlime.bmp",92*3, 40*3,4,2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ºí·ç½½¶óÀÓ", "images/monster/blueSlime.bmp",92*3, 40*3,4,2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("¹ÚÁã", "images/monster/bat.bmp",104*3, 32*3,4,2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("½ºÄÌ·¹Åæ", "images/monster/ÇØ°ñ.bmp",200*3, 60*3,8,2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("Åõ¸í°í½ºÆ®L", "images/monster/ghostAlphaL.bmp", 18 * 3, 22 * 3, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Åõ¸í°í½ºÆ®R", "images/monster/ghostAlphaR.bmp", 18 * 3, 22 * 3, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("Åõ¸í°í½ºÆ®L", "images/monster/ghostREAL.bmp",18*3, 22*3,1,1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("·¹µå·¹ÀÌ½º", "images/monster/redWraiths.bmp",39*3, 46*3,3,2, true, RGB(255, 0, 255));



	//SOUND
	SOUNDMANAGER->addSound("1-1", "sound/1-1.mp3", true, true);
	SOUNDMANAGER->addSound("lobby", "sound/lobby.mp3", true, true);

	//EFFECT
	EFFECTMANAGER->addEffect("ÇÒÄû±â", "images/effect/ÇÒÄû±â.bmp", 120*2, 23*2, 30*2, 23*2, 1, 0.3f, 100);
	EFFECTMANAGER->addEffect("Á¡ÇÁ¸ÕÁö", "images/effect/jumpDust.bmp", 50*2, 10*2, 10*2, 10*2, 1, 0.5f, 100);
	EFFECTMANAGER->addEffect("´Ü°ËL", "images/effect/´Ü°ËL.bmp", 60 * 3, 20 * 3, 20 * 3, 20 * 3, 1, 0.3f, 100);
	EFFECTMANAGER->addEffect("´Ü°ËR", "images/effect/´Ü°ËR.bmp", 60 * 3, 20 * 3, 20 *3, 20 * 3, 1, 0.3f, 100);
	EFFECTMANAGER->addEffect("´Ü°ËUp", "images/effect/´Ü°ËUp.bmp", 60 * 3, 20 * 3, 20 * 3, 20 * 3, 1, 0.3f, 100);
	EFFECTMANAGER->addEffect("´Ü°ËDown", "images/effect/´Ü°ËDown.bmp", 60 * 3, 20 * 3, 20 * 3, 20 * 3, 1, 0.3f, 100);

	EFFECTMANAGER->addEffect("±âº»»ð", "images/item/nomalShovel.bmp", 48,48,48,48, 1, 0.1f, 100);
	EFFECTMANAGER->addEffect("Æ¼Å¸´½»ð", "images/item/titaniumShovel.bmp", 48,48, 48,48, 1, 0.1f, 100);
	EFFECTMANAGER->addEffect("À¯¸®»ð", "images/item/glassShovel.bmp",48,48,48,48, 1, 0.1f, 100);


}