#pragma once
#include "item.h"
class torch :public item
{
private:
	int _power;
public:
	torch();
	torch(string name, slotType type, int power, string description);
	~torch();

	void update() override;
};
