#pragma once
#include"item.h"
class coin : public item
{
private:
	int _value;
public:
	coin();
	coin(int value, int x, int y);
	~coin();

	void update() override;
	void render(HDC hdc) override;
	int getValue() override;
};

