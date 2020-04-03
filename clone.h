#pragma once
#include"monster.h"
class clone : public monster
{
public:
	clone();
	~clone();

	virtual HRESULT init(string name, int x, int y, int coin, tagTile * map) override;

	void frontCheck() override;
	void choiceAction() override;

	void animation() override;
	void move() override;
	void aniCheck() override;
};

