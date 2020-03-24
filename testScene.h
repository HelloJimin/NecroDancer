#pragma once
#include "gameNode.h"
#include"tileNode.h"
#include"wallTorch.h"
#include"trap.h"
#include"bombExplosion.h"
class testScene : public gameNode
{
private:
	tagTile _tiles[TILEX * TILEY];
	vector<item*> _vItem;

	bool _isDebug;

	vector<wallTorch*> _vTorch;
	vector<trap*> _vTrap;
	vector<bombExplosion*> _vBomb;

	int _hitCnt;

	int _currentMapNumber;


	int _nextDoorNum;
public:
	testScene();
	~testScene();

	HRESULT init();
	void release();
	void update();
	void render(/*HDC hdc*/);

	void allRender();
	void debugRender();
	void hitRender();

	void setUp();
	void load();

	void torchInit();
	void torchUpdate();

	void trapInit();
	void trapUpdate();

	void groundPattern();

	void addBomb();
	void bombUpdate();

	bool isWall(int arrNum);

	void doorUpdate();
};