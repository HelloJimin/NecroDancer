#pragma once
#include"singletonBase.h"
#include"skeleton.h"
#include"greenSlime.h"
#include"blueSlime.h"
#include"redWraiths.h"
#include"ghost.h"
#include"bat.h"
#include"minotaurs.h"
#include"redDragon.h"
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
	void setMap(tagTile* map);

	void summonGreenSlime(string name, int x, int y);
	void summonBlueSlime(string name, int x, int y);
	void summonSkeleton(string name, int x, int y);
	void summonGhost(string name, int x, int y);
	void summonRedWraiths(string name, int x, int y);
	void summonBat(string name, int x, int y);
	void summonMinotaurs(string name, int x, int y);
	void summonRedDragon(string name, int x, int y);


	void summonControl(string name, int x, int y);
	vector<monster*> getMonster() { return _vMonster; }
};

