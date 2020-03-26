#pragma once
#include "gameNode.h"
#include"tileNode.h"
#include"wallTorch.h"
#include"trap.h"
#include"bombExplosion.h"
#include"deathmetal.h"

class bossStage : public gameNode
{
private:
	deathmetal _metal;

	tagTile _tiles[TILEX * TILEY];

	vector<wallTorch*> _vTorch;
	vector<trap*> _vTrap;
	vector<bombExplosion*> _vBomb;

	int _hitCnt;


	bool _close;
public:
	bossStage();
	~bossStage();

	HRESULT init();
	void release();
	void update();
	void render(/*HDC hdc*/);

	void allRender();

	void debugRender();
	void hitRender();

	void close();

	void torchInit();
	void torchUpdate();

	void trapInit();
	void trapUpdate();

	void groundPattern();

	void addBomb();
	void bombUpdate();

	bool isWall(int arrNum);

};

