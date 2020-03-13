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

	//_vItem.push_back(new shovel(SHOVEL, 1, "기본삽", "강도 1의 삽이다"));

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
	if (name == "기본삽")return new shovel(SHOVEL, 1, "기본삽", "강도 1의 삽이다");
	if (name == "티타늄삽")return new shovel(SHOVEL, 2, "티타늄삽", "강도 2의 삽이다");
	if (name == "유리삽")return new shovel(SHOVEL, 3, "유리삽", "강도 3의 삽이다");

	if (name == "기본단검")return new attack("기본단검",ATTACK, FORM_SHORT,1,"공격력 1의 기본단검이다");
	if (name == "티타늄단검")return new attack("티타늄단검",ATTACK, FORM_SHORT,2,"공격력 2의 기본단검이다");
	if (name == "유리단검")return new attack("유리단검",ATTACK, FORM_SHORT,3,"공격력 3의 기본단검이다");

	if (name == "기본대검")return new attack("기본대검", ATTACK, FORM_BIG, 1, "공격력 1의 기본단검이다");
	if (name == "티타늄대검")return new attack("티타늄대검", ATTACK, FORM_BIG, 2, "공격력 2의 기본단검이다");
	if (name == "유리대검")return new attack("유리대검", ATTACK, FORM_BIG, 3, "공격력 3의 기본단검이다");

	if (name == "기본활")return new attack("기본활", ATTACK, FORM_BOW, 1, "공격력 1의 기본단검이다");
	if (name == "티타늄활")return new attack("티타늄활", ATTACK, FORM_BOW, 2, "공격력 2의 기본단검이다");
	if (name == "유리활")return new attack("유리활", ATTACK, FORM_BOW, 3, "공격력 3의 기본단검이다");

	if (name == "기본창")return new attack("기본창", ATTACK, FORM_SPEAR , 1, "공격력 1의 기본단검이다");
	if (name == "티타늄창")return new attack("티타늄창", ATTACK, FORM_SPEAR, 2, "공격력 2의 기본단검이다");
	if (name == "유리창")return new attack("유리창", ATTACK, FORM_SPEAR, 3, "공격력 3의 기본단검이다");

	if (name == "기본채찍")return new attack("기본채찍", ATTACK, FORM_WHIP, 1, "공격력 1의 기본단검이다");
	if (name == "티타늄채찍")return new attack("티타늄채찍", ATTACK, FORM_WHIP, 2, "공격력 2의 기본단검이다");
	if (name == "유리채찍")return new attack("유리채찍", ATTACK, FORM_WHIP, 3, "공격력 3의 기본단검이다");


	if (name == "가죽갑옷")return new body("가죽갑옷",BODY,1,"방어력 1의 갑옷이다");
	if (name == "쇠갑옷")return new body("쇠갑옷",BODY,2,"방어력 2의 갑옷이다");
	if (name == "도복")return new body("도복",BODY,3,"공격력2배이다");

	if (name == "힘의장화")return new feet("힘의장화",FEET,"공격력1 증가");
	if (name == "발레슈즈")return new feet("발레슈즈",FEET,"배수가 초기화안됨");
	if (name == "날개장화")return new feet("날개장화",FEET,"함정무시");

	if (name == "기본횃불")return new torch("기본횃불",TORCH,1,"시야1증가");
	if (name == "빛나는횃불")return new torch("빛나는횃불",TORCH,3,"시야3증가");

}

item * itemManager::addCoin(int coinValue, int x, int y)
{
	return new coin(coinValue, x, y);
}

