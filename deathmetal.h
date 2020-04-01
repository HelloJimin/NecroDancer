#pragma once
#include"monster.h"
#include"aStar.h"

enum bossPhase
{
	PHASE_ONE,
	PHASE_TWO,
	PHASE_THREE
};
class deathmetal : public monster
{
private:
	aStar* _aStar;
	bossPhase _phase;

	int _hitCnt;
	vector<int> _field;
	vector<int> _phaseThreeField;

	bool _isSkill;
	bool _isBreath;
	bool _delay;

	int _breathRenge;

	int _turnSpeed = 3;
public:
	deathmetal();
	~deathmetal();

	HRESULT init(string name, int x, int y, int coin, tagTile * map) override;

	void update() override;

	void frontCheck() override;
	void choiceAction() override;

	void animation() override;

	bool die() override;
	void render(HDC hdc) override;
	void silhouetteRender(HDC hdc) override;
	void attack() override;
	bool rengeCheck(int tile);
	void move() override;
	void aniCheck() override;
	void hit(float damage) override;
	void teleport();
	void summon(string name);

	int endTileFind();

	bool endLineCheck();

	virtual void setIsBeat(int turn) { if (turn % _turnSpeed == 0) _isBeat = true; }

	int currentHpCheck();
};

