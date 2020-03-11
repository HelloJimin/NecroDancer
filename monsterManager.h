#pragma once
#include"singletonBase.h"
#include"skeleton.h"
#include"greenSlime.h"
#include"blueSlime.h"

class monsterManager : public singletonBase<monsterManager>
{
private:
	tagTile* _map;
	vector<monster*> _vMonster;

public:
	monsterManager();
	~monsterManager();

	HRESULT init();
	void release();
	void update();
	void frontRender(HDC hdc);
	void backRender(HDC hdc);
	void render(HDC hdc);
	void summonGreenSlime(string name, int x, int y);
	void summonBlueSlime(string name, int x, int y);
	void summonSkeleton(string name, int x, int y);
	void setMap(tagTile* map) { _map = map; }

	vector<monster*> getMonster() { return _vMonster; }
};
