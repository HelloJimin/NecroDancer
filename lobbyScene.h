#pragma once
#include "gameNode.h"
#include"tileNode.h"
#include"wallTorch.h"

class lobbyScene : public gameNode
{
private:
	tagTile _tiles[TILEX * TILEY];
	vector<wallTorch*> _vTorch;
public:
	lobbyScene();
	~lobbyScene();

	HRESULT init();
	void release();
	void update();
	void render(/*HDC hdc*/);

	void allRender();
	void debugRender();
	void setUp();
	void load();

	void groundPattern();
	void next();
	void torchUpdate();
	void torchInit();
};

