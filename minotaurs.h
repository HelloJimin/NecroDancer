#pragma once
#include "monster.h"
#include"aStar.h"
class minotaurs : public monster
{
private:

	aStar* _aStar;

	int _minePower;
	bool _isDown;

	bool _isRage;
	int _downCnt;
public:
	minotaurs();
	~minotaurs();

	HRESULT init(string name, int x, int y, int coin, tagTile * map) override;

	void frontCheck() override;
	void choiceAction() override;

	void animation() override;

	void render(HDC hdc) override;
	void silhouetteRender(HDC hdc) override;
	void move() override;

	void mine();

	void rageCheck();

};

