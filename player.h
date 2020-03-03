#pragma once
#include "singletonBase.h"
#include "tileNode.h"
#include "inventory.h"

enum DIRECTION
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	IDLE
};
enum CURRENT_WEAPON
{
	SWORD,
	BIGSWORD,
	SPEAR,
	whip,
	BOW
};
enum FRONT
{
	NONE,
	MONSTER,
	WALL
};
struct miss
{
	int alpha;
	int speed;
	RECT rc;
	image* img;
};
struct note
{
	int alpha;
	float x[2],y;
	RECT rc[2];
	image* img[2];
};
struct turn
{
	int anime;
	int cnt;
	float speed;

	RECT heartBox;
	image* heart;
	vector<note> vNote;
	bool check;
};
struct hp
{
	image* img;
	RECT rc;
	int currentX;
	float hp;
};
class player : public singletonBase<player>
{
private:
	RECT _temp;
	RECT _rc;
	RECT _collisionRc;

	int _currentX, _currentY;
	int _collisionX, _collisionY;

	int _tileX, _tileY;
	int _nextTileIndex;
	int _currentTileIndex;
	int _wallIndex;

	int _rhythm;

	note _note;

	float _moveSpeed;
	image* _bodyImg;
	image* _headImg;
	DIRECTION _direction;
	CURRENT_WEAPON _weapon;


	tagTile* _pCurrentMap;		//콜바이레퍼런스용 변수
	inventory* _inven;
	
	miss _miss;
	vector<miss> _vMiss;

	int _currentFrameX;
	
	hp _hp;
	vector<hp> _vHp;
	turn _turn;

	int _coin;
	int _diamond;

	bool _isJump;
	bool _isMine;
	char _str[128];
public:
	player();
	~player();

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	void frontCheck();

	void move();
	void setCurrentTile(tagTile tile[]) { _pCurrentMap = tile; }	//콜바이밸류를 통해서 현재 돌아가는 씬이 갖고 있는 타일의 주소값을 받아온다

	void turn();
	void UIrender(HDC hdc);

	bool rhythmCheck() { return _turn.check; }

	void removeNote();

	int playerTile() { return _currentTileIndex; }
	int playerNextTile() { return _nextTileIndex; }
	int wallTile() { return _wallIndex; }

	tagTile* getTile() { return _pCurrentMap; }

	RECT getCollisionRc() { return _collisionRc; }

	inventory* getInven() { return _inven; }

	void HPbarSet();
	bool isMine() { return _isMine; }
	bool* isMine1() { return &_isMine; }

	void setIsMine(bool mine) { _isMine = mine; }

};

