#pragma once
#include"aStar.h"
#include"raycast.h"
class wallTorch
{
private:
	tagTile* _tile;

	int _frameX;
	int _frameY;
	int _tileNum;

	image* _img;
	
	aStar * _aStar;
	raycast * _ray;

	bool _check;
public:
	wallTorch();
	wallTorch(int tileNum, tagTile tile[]);
	~wallTorch();


	void update();
	void render(HDC hdc);

	void findPlayer();

	int getTileNum() { return _tileNum; }
};

