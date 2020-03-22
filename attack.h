#pragma once
#include "item.h"
enum attackForm
{
	FORM_SHORT,
	FORM_BIG,
	FORM_SPEAR,
	FORM_BOW,
	FORM_WHIP,
	FORM_NONE
};
struct isThrow
{
	image* slot;
	image* item;
	bool fire;
	RECT rc;
};
class attack : public item
{
private:
	attackForm _form;
	float _power;

	isThrow _throw;

public:
	attack();
	attack(string name, slotType type, attackForm form, int power, string description, int x, int y, int price);
	~attack();
	virtual HRESULT init() override;
	virtual void active() override;
	void update() override;

	void render(HDC hdc) override;
	bool getBool() { return _throw.fire; }
};

