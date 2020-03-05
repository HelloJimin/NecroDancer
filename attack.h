#pragma once
#include "item.h"
enum attackForm
{
	FORM_SHORT,
	FORM_BIG,
	FORM_SPEAR,
	FORM_BOW,
	FORM_WHIP
};
class attack : public item
{
private:
	attackForm _form;
	float _power;

public:
	attack();
	attack(string name, slotType type, attackForm form, int power, string description);
	~attack();

	void update() override;
};

