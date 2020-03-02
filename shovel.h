#pragma once
#include"item.h"
class shovel : public item
{
private:
	int _power;

public:
	shovel();
	shovel(itemType type, int power, string name, string description);

	~shovel();

	void release() override;
	void update() override;
	void render(/*HDC hdc*/);

	int getInfo() override { return _power; }
};

