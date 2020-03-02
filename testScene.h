#pragma once
#include "gameNode.h"
#include"tileNode.h"
class testScene : public gameNode
{
private:
	tagTile _tiles[TILEX * TILEY];
	vector<item*> _vItem;

public:
	testScene();
	~testScene();

	HRESULT init();
	void release();
	void update();
	void render(/*HDC hdc*/);

	void setUp();
	void tileRender();
	void load();
};