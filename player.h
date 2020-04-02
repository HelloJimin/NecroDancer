#pragma once
#include "singletonBase.h"
#include "tileNode.h"
#include "inventory.h"
#include"raycast.h"
#include"gameEnd.h"
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
	float _currentX, _currentY;
	RECT _rc;
	float _collisionX, _collisionY;
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
	gameEnd* _gameEnd;
	int _rhythm;

	//스탯
	status _status;
	hp _hp;
	int _coin;
	int _diamond;
	int _coinMultiplier;
	inventory* _inven;
	raycast* _ray;
	int _rayPower;

	bool _isDrop;
	bool _isMove;
	bool _isAttack;
	bool _isFever;
	bool _isHit;
	bool _isBomb;
	bool _isTaekwondo;
	bool _isOk;
	bool _isBeat;
	bool _isFly;
	bool _isBallet;

	char _str[128];
	RECT _temp;

	attackForm _equipWeaponType;

	coinUI _coinUI;
	coinUI _diamondUI;

	image* _coinFeverImg;
	image* _coinFeverNumImg;

	vector<int> _vTarget;
	bool _isDie;
	string _currentMap;

	image* _monsterName;
public:
	player();
	~player();

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);
	void UIrender(HDC hdc);

	void setMap(tagTile tile[], string map);	// 현재 돌아가는 씬이 갖고 있는 타일의 주소값을 받아온다
	tagTile* getMap() { return _pCurrentMap; }
	void frontCheck();
	void attack();
	void move();
	int currentTile() { return _currentTileIndex; }
	int& nextTile() { return _nextTileIndex; }

	RECT getCollisionRc() { return _collisionRc; }

	inventory* getInven() { return _inven; }

	auto& playerStatus() { return _status; }

	void HPbarSet();
	void mine();
	void getItem(int itemTile);
	void hit(float damege , image* name);

	void keyControl();
	void animation();
	bool walkableCheck();
	bool wallCheck(int tile);
	bool dieCheck();

	int getX() { return _collisionRc.left ; }
	int getY() { return _collisionRc.top ; }

	DIRECTION getPlayerDir() { return _direction; }
	void setDirection(DIRECTION dir) { _direction = dir; }
	void setFrameY(int frameNum) { _frameY = frameNum; }
	void setWeapom(attackForm form) { _equipWeaponType = form; }

	void effectControl(attackForm form, int rengeArrNum, int monArrNum);
	bool rengeCheck(int monArrNum, int tile);
	bool throwRengeCheck(int nextTile);
	bool getFever() { return _isFever; }
	bool& getHit() { return _isHit; }
	bool& getBomb() { return _isBomb; }
	bool getMove() { return _isMove; }
	bool& getTaekwondo() { return _isTaekwondo; }
	bool& getOk() { return _isOk; }

	bool& getBallet() { return _isBallet; }
	bool& getFly() { return _isFly; }

	int& getRayPower() { return _rayPower; }
	void arrowEffect(attackForm form, int monArrNum);
	void throwEffect(int endTile, int throwRenge);
	attackForm getAtkForm() { return _equipWeaponType; }
	void moveCheck();
	void buyItem(int itemTile);

	void feverTime();
	void coinUIupdate();
	void coinUIrender();

	void setIsBeat(bool beat) { _isBeat = beat; }
	bool getIsBeat() { return _isBeat; }
	void attackCheck();
	void isThrow();

	void heal(float healPower);

	float lerp(float start, float end, float timeAmount) { return (float)((end - start) * timeAmount); }

	void gameReset(string map);

	coinUI getCoinUI() { return _coinUI; }

	image* nameImage() { return _monsterName; }
	string currentMapName() { return _currentMap; }

	void feverTimeReset(string hintName = "코인배수사라짐");

	bool getIsBallet() { return _isBallet; }
};

