#pragma once
#include "monster.h"
#include"aStar.h"
class redDragon : public monster
{
private:
	aStar* _aStar;

	int _breathRenge;
	int _minePower;
	int _breathCnt;
	bool _isBreath;

public:
	redDragon();
	~redDragon();

	HRESULT init(string name, int x, int y, int coin, tagTile * map) override;

	void frontCheck() override;
	void choiceAction() override;

	void animation() override;

	void render(HDC hdc) override;
	void move() override;
	void attack() override;
	void mine();

	void breathCheck();

	bool rengeCheck(int tile);
};

