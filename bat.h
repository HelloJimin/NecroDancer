#pragma once
#include "monster.h"
class bat : public monster
{
private:

public:
	bat();
	~bat();

	virtual HRESULT init(string name, int x, int y, int coin, tagTile * map) override;
	void move() override;
	void frontCheck() override;
	void choiceAction() override;
};

