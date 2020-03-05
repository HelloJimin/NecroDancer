#pragma once
#include"item.h"
class shovel : public item
{
private:
	int _power;

public:
	shovel();
	shovel(slotType type, int power, string name, string description);

	~shovel();

	void update() override;

};

