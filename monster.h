#pragma once
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
	RECT _collisionRc;

	int _currentX, _currentY;
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
	bool _isLockOn;

public:
	monster();
	~monster();

	virtual HRESULT init(string name, int x, int y, int coin, tagTile * map);
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	virtual void animation();
	virtual void frontCheck();
	virtual void attack();
	virtual void choiceAction();

	int currentTile() { return _currentTileIndex; }
	void setMap(tagTile tile[]) { _pCurrentMap = tile; }

	virtual void move();
	virtual bool die();
	void addHp();
	void hpSet();
	void hpRender(HDC hdc);
	void hit(float damage);
	void aniCheck();

	bool wallCheck();
	bool playerCheck();
};

