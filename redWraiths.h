#pragma once
#include"monster.h"
#include"aStar.h"
class redWraiths : public monster
{
private:
	aStar* _aStar;


	int _teleportCnt;
public:
	redWraiths();
	~redWraiths();

	virtual HRESULT init(string name, int x, int y, int coin, tagTile * map) override;
	void frontCheck() override;
	void choiceAction() override;
	void move() override;
	void update() override;
	void teleport();
};

