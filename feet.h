#pragma once
#include "item.h"
class feet : public item
{
private:
	bool check = false;
public:
	feet();
	feet(string name, slotType type, string description);
	~feet();

	void update() override;
};

