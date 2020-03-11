#pragma once
#include"monster.h"
#include "aStar.h"
class skeleton : public monster
{
private:
	aStar* _aStar;

public:
	skeleton();
	~skeleton();

	virtual HRESULT init(string name, int x, int y, int coin, tagTile * map) override;
	virtual void render(HDC hdc) override;

	void frontCheck() override;
	void choiceAction() override; 
	void animation() override;
	
};
