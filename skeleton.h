#pragma once
#include"monster.h"
#include "aStar.h"
class skeleton : public monster
{
private:
	aStar* _aStar;

	tagTile* temp;
public:
	skeleton();
	~skeleton();

	virtual HRESULT init(string name, int x, int y, int coin, tagTile * map) override;
	virtual void render(HDC hdc) override;
 
	virtual void move() override;
	void frontCheck() override;
};

