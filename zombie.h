#pragma once
#include"monster.h"
class zombie : public monster
{
private:


public:
	zombie();
	~zombie();

	HRESULT init(string name, int x, int y, int coin, tagTile * map) override;

	void frontCheck() override;
	void choiceAction() override;

	void animation() override;

	void aniCheck() override;
	void silhouetteRender(HDC hdc) override;
};

