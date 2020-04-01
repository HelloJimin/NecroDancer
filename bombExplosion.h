#pragma once
class bombExplosion
{
private:
	tagTile* _tile;

	int _frameX;
	int _tileNum;


	RECT _rc;
	image* _img;

	bool _trigger;

	image* _bombName;
public:
	bombExplosion();
	bombExplosion(int tileNum, tagTile tile[]);
	~bombExplosion();

	void update();

	void render(HDC hdc);

	bool getTrigger() { return _trigger; }

	int getTileNum() { return _tileNum; }

};

