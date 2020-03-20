#pragma once
#include "monster.h"
class blueSlime : public monster
{
public:
	blueSlime();
	~blueSlime();

	
	virtual HRESULT init(string name, int x, int y, int coin, tagTile * map) override;

	void frontCheck() override;
	void choiceAction() override;

	void silhouetteRender(HDC hdc);
};

