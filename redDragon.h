#pragma once
#include "monster.h"
#include"aStar.h"
class redDragon : public monster
{
private:
	aStar* _aStar;

	int _breathRenge;
	int _minePower;
	bool _isBreath;
	bool _delay;
public:
	redDragon();
	~redDragon();

	HRESULT init(string name, int x, int y, int coin, tagTile * map) override;

	void frontCheck() override;
	void choiceAction() override;

	void animation() override;

	void render(HDC hdc) override;
	void silhouetteRender(HDC hdc) override;
	void move() override;
	void attack() override;
	void mine();

	void breathCheck();
	bool rengeCheck(int tile);


	bool die() override;

	virtual void setIsBeat(int turn) { if (turn % 2 == 0) _isBeat = true; }
};

