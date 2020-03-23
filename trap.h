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
public:
	trap();
	trap(OBJECT obj , int tileNum , tagTile tile[]);
	~trap();

	void update();
	void render(HDC hdc);

	int getTileNum() { return _tileNum; }
};

