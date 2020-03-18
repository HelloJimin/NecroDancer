#pragma once
#include "singletonBase.h"
#include "tileNode.h"
#include "inventory.h"

enum DIRECTION
{
	LEFT,
	RIGHT,
	UP,
	DOWN
};
struct hp
{
	image* img;
	RECT rc;
	int currentX;
	float hp;
};
struct status
{
	vector<hp> vHp;
	int atk;
	int def;
	int minePower;

	vector<int> atkRenge;
};

class player : public singletonBase<player>
{
private:
	int _currentX, _currentY;
	RECT _rc;
	int _collisionX, _collisionY;
	RECT _collisionRc;

	int _frameX, _frameY;

	int _tileX, _tileY;
	int _currentTileIndex;
	int _nextTileIndex;

	float _moveSpeed;
	image* _bodyImg;
	image* _headImg;

	DIRECTION _direction;

	tagTile* _pCurrentMap;	
	
	int _rhythm;

	//스탯
	status _status;
	hp _hp;
	int _coin;
	int _diamond;
	inventory* _inven;

	bool _isDrop;
	bool _isMove;
	bool _isAttack;

	char _str[128];
	RECT _temp;

	attackForm _equipWeaponType;
public:
	player();
	~player();

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);
	void UIrender(HDC hdc);

	void setMap(tagTile tile[]);	// 현재 돌아가는 씬이 갖고 있는 타일의 주소값을 받아온다
	tagTile* getMap() { return _pCurrentMap; }
	void frontCheck();
	void attack();
	void move();
	int currentTile() { return _currentTileIndex; }
	int nextTile() { return _nextTileIndex; }

	RECT getCollisionRc() { return _collisionRc; }

	inventory* getInven() { return _inven; }

	auto& playerStatus() { return _status; }

	void HPbarSet();
	void mine();
	void getItem();
	void hit(float damege);

	void keyControl();
	void animation();
	bool wallCheck();
	bool monsterCheck();

	int getX() { return _currentX; }
	int getY() { return _currentY; }

	DIRECTION getPlayerDir() { return _direction; }
	void setFrameY(int frameNum) { _frameY = frameNum; }
	void setWeapom(attackForm form) { _equipWeaponType = form; }

	void effectControl(attackForm form, int monArrNum);
	bool rengeCheck(int monArrNum, int tile);
	bool throwRengeCheck(int nextTile);

	void arrowEffect(attackForm form, int monArrNum);
	void throwEffect(int endTile, int throwRenge);
};

