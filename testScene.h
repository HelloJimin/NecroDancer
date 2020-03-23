#pragma once
#include "gameNode.h"
#include"tileNode.h"
#include"wallTorch.h"
#include"trap.h"

class testScene : public gameNode
{
private:
	tagTile _tiles[TILEX * TILEY];
	vector<item*> _vItem;

	bool _isDebug;

	vector<wallTorch*> _vTorch;
	vector<trap*> _vTrap;

	int _hitCnt;

public:
	testScene();
	~testScene();

	HRESULT init();
	void release();
	void update();
	void render(/*HDC hdc*/);

	void allRender();
	void debugRender();
	void setUp();
	void load();

	void torchInit();
	void torchUpdate();

	void trapInit();
	void trapUpdate();

	void groundPattern();
};