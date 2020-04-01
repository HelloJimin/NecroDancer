#pragma once
class trap
{
private:
	tagTile* _tile;

	int _frameX;
	int _frameY;
	int _tileNum;

	bool _trigger;
	RECT _rc;
	image* _img;

	OBJECT _obj;

	image* _trapName;
public:
	trap();
	trap(OBJECT obj , int tileNum , tagTile tile[]);
	~trap();

	void update();
	void render(HDC hdc);
	void animation();
	int getTileNum() { return _tileNum; }
	void damageCheck();
};

