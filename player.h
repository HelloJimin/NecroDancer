#pragma once
#include "singletonBase.h"
#include "tileNode.h"
#include "inventory.h"
#include"raycast.h"
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
struct coinUI
{
	image* x;
	tagPrice coinImg[3];
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
	raycast* _ray;

	bool _isDrop;
	bool _isMove;
	bool _isAttack;

	char _str[128];
	RECT _temp;

	attackForm _equipWeaponType;

	coinUI _coinUI;
	coinUI _diamondUI;
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
	void getItem(int itemTile);
	void hit(float damege);

	void keyControl();
	void animation();
	bool walkableCheck();
	bool wallCheck(int tile);

	int getX() { return _currentX; }
	int getY() { return _currentY; }

	DIRECTION getPlayerDir() { return _direction; }
	void setFrameY(int frameNum) { _frameY = frameNum; }
	void setWeapom(attackForm form) { _equipWeaponType = form; }

	void effectControl(attackForm form, int rengeArrNum, int monArrNum);
	bool rengeCheck(int monArrNum, int tile);
	bool throwRengeCheck(int nextTile);

	void arrowEffect(attackForm form, int monArrNum);
	void throwEffect(int endTile, int throwRenge);

	void moveCheck();
	void buyItem(int itemTile);

	void coinUIupdate();
	void coinUIrender();
};

