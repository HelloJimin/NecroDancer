#pragma once
#include"monster.h"
#include"aStar.h"
class redWraiths : public monster
{
private:
	aStar* _aStar;


	int _teleportCnt;
	bool _isTeleport;
public:
	redWraiths();
	~redWraiths();

	virtual HRESULT init(string name, int x, int y, int coin, tagTile * map) override;
	void frontCheck() override;
	void choiceAction() override;
	void move() override;
	void animation() override;
	void teleport();

	virtual void setIsBeat(int turn) { if (turn % 1 == 0) _isBeat = true; }

	bool die() override;
};

