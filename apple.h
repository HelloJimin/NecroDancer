#pragma once
#include"item.h"
class apple : public item
{
private:
	int _num;

	image* _button;
	float _heal;
public:
	apple();
	apple(string name, slotType type, int num, float power, string description, int x, int y, int price);
	~apple();

	virtual HRESULT init() override;

	void update() override;
	void render(HDC hdc) override;
	void setValue(int num) override;


	int getValue() override;
};

