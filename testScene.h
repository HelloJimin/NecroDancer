#pragma once
#include "gameNode.h"
#include"tileNode.h"
class testScene : public gameNode
{
private:
	tagTile _tiles[TILEX * TILEY];
	vector<item*> _vItem;

	bool _isDebug;
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
};