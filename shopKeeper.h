#pragma once
#include"monster.h"
#include"aStar.h"

class shopKeeper : public monster
{
private:
	aStar * _aStar;
public:
	shopKeeper();
	~shopKeeper();

	HRESULT init(string name, int x, int y, int coin, tagTile * map) override;

	void update() override;
	void frontCheck() override;
	void choiceAction() override;

	void render(HDC hdc) override;
	void silhouetteRender(HDC hdc) override;

	bool die() override;
	void hit(float damage) override;
	void BGMcheck();

};

