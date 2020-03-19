#pragma once
#include"item.h"
class shovel : public item
{
private:
	int _power;

public:
	shovel();
	shovel(slotType type, int power, string name, string description, int x, int y);

	~shovel();
	virtual HRESULT init() override;

	void update() override;

};

