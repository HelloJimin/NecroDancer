#pragma once
#include"item.h"
class bomb :public item
{
private:
	int _num;
	image* _ani;

public:
	bomb();
	bomb(string name, slotType type, int num, string description);
	~bomb();
	void update() override;
	void render(HDC hdc) override;

};

