#pragma once
#include "gameNode.h"
#include"tileNode.h"
class lobbyScene : public gameNode
{
private:
	tagTile _tiles[TILEX * TILEY];
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
};

