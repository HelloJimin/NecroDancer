#pragma once
#include"item.h"

class hpSlot : public item
{
public:
	hpSlot();
	hpSlot(int x, int y);;
	~hpSlot();

	void update() override;
	void render(HDC hdc) override;

};

