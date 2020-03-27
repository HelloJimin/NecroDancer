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
	int _teleportCnt;

	bool _isSkill;
public:
	deathmetal();
	~deathmetal();

	HRESULT init(string name, int x, int y, int coin, tagTile * map) override;

	void update() override;

	void frontCheck() override;
	void choiceAction() override;

	void animation() override;

	void render(HDC hdc) override;
	void silhouetteRender(HDC hdc) override;
	void move() override;
	void aniCheck() override;
	void hit(float damage) override;
	void teleport();
	void summon();
};

