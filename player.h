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
enum FRONT
{
	NONE,
	MONSTER,
	WALL
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
};
class player : public singletonBase<player>
{
private:
	int _currentX, _currentY;
	RECT _rc;
	int _collisionX, _collisionY;
	RECT _collisionRc;

	int _currentFrameX;

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
	char _str[128];
	RECT _temp;
	float n;
public:
	player();
	~player();

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);
	void UIrender(HDC hdc);

	void setCurrentTile(tagTile tile[]) { _pCurrentMap = tile; }	// 현재 돌아가는 씬이 갖고 있는 타일의 주소값을 받아온다

	void frontCheck();
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

	float lerp(float p1, float p2, float d1) {
		return (1 - d1)*p1 + d1 * p2;
	}
};

