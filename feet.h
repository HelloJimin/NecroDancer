#pragma once
#include "item.h"
class feet : public item
{
private:
	bool check = false;
public:
	feet();
	feet(string name, slotType type, string description, int x, int y, int price);
	~feet();
	virtual HRESULT init() override;

	void update() override;
};

