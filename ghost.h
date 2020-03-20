#pragma once
#include"monster.h"
#include "aStar.h"

class ghost : public monster
{
private:
	int _alpha;
	aStar* _aStar;

	int atkCnt;
public:
	ghost();
	~ghost();
	
	virtual HRESULT init(string name, int x, int y, int coin, tagTile * map) override;
	virtual void render(HDC hdc) override;
	void silhouetteRender(HDC hdc) override;
	void frontCheck() override;
	void choiceAction() override;
	virtual void move() override;
	void alphaCheck();
};

