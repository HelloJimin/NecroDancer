#pragma once
#include"item.h"
class body : public item
{
private:
	int _power;

public:
	body();
	body(string name, slotType type, int power, string description, int x, int y, int price);
	~body();
	virtual HRESULT init() override;


	void update() override;
};

