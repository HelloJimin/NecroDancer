#pragma once
#define TURN1 _turnCnt % 1 == 0
#define TURN2 _turnCnt % 2 == 0

enum DIRECTION_ANI
{
	LEFT_TOP,
	LEFT_BOT,
	RIGHT_TOP,
	RIGHT_BOT
};
class monster
{
protected:
	tagTile* _pCurrentMap;

	image* _monsterImg;
	image* _monsterNameImg;
	RECT _collisionRc;

	float _currentX, _currentY;
	int _frameX, _frameY;

	int _tileX, _tileY;
	int _currentTileIndex;
	int _nextTileIndex;

	DIRECTION _direction;
	DIRECTION_ANI _directionAni;

	vector<hp> _vHp;
	float _atk;
	int _coin;
	float _moveSpeed;

	bool _isMove;
	bool _isDrop;
	bool _isAttack;
	bool _isHit;

	bool _isLook;

	bool _isBoss;

	bool _isBeat;
	int _turnCnt;
public:
	monster();
	~monster();

	virtual HRESULT init(string name, int x, int y, int coin, tagTile * map);
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);
	virtual void silhouetteRender(HDC hdc);

	virtual void animation();
	virtual void frontCheck();
	virtual void attack();
	virtual void choiceAction();

	int currentTile() { return _currentTileIndex; }
	void setMap(tagTile tile[]) { _pCurrentMap = tile; }
	int getCoin() { return _coin; }

	virtual void move();
	virtual bool die();
	void addHp();
	virtual void hpSet();
	void hpRender(HDC hdc);
	virtual void hit(float damage);
	virtual void aniCheck();
	void getHp();

	bool walkableCheck();
	bool playerCheck();
	POINT getXY() { return PointMake(_currentX, _currentY); }
	RECT getRc() { return _collisionRc; }

	void setLook(bool look) { _isLook = look; }

	bool getMove() { return _isMove; }
	bool& getHit() { return _isHit; }

	bool getIsBoss() { return _isBoss; }
	
	virtual void setIsBeat(int turn) { if(turn % 3 == 0) _isBeat = true; }
};

