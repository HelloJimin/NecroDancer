#pragma once
#include"item.h"
class dagger : public attack
{
private:
	float _power;
public:
	dagger();
	dagger(string name, slotType type, int power, string description);
	~dagger();
	virtual HRESULT init() override;
	void update() override;
};

