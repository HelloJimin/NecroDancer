#pragma once
class monster
{

protected:
	RECT _rc;
	RECT _collisionRc;

	int _currentX, _currentY;
	int _frameX, _frameY;

	int _tileX, _tileY;
	int _currentTileIndex;
	int _nextTileIndex;
	image* _monsterImg;

	float _atk;
	vector<hp> _vHp;

	bool _silhouette;
	bool _attack;
	tagTile* _pCurrentMap;
	DIRECTION _direction;
	int _coin;

	int _rhythm;
	float _moveSpeed;
	bool _isMove;
public:
	monster();
	~monster();

	virtual HRESULT init(string name, int x, int y, tagTile* map);
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	void animation();
	virtual void frontCheck();
	virtual void attack();

	int currentTile() { return _currentTileIndex; }
	void setMap(tagTile tile[]) { _pCurrentMap = tile; }

	virtual void move();
};

