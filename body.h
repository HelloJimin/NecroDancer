#pragma once
#include"item.h"
class body : public item
{
private:
	float _power;

public:
	body();
	body(string name, slotType type, float power, string description, int x, int y, int price);
	~body();
	virtual HRESULT init() override;


	void update() override;
};

