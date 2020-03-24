#pragma once

class raycast
{
private:
	tagTile* tile;
	vector<int> open;
	vector<int> temp;
	int pTile;
	bool ok;
public:
	raycast();
	~raycast();


	void init(tagTile _tile[]);
	void torch(int startTile);
	void playerRay(int startTile, int rayPower);

	void reset();

	bool wallCheck(int tileNum);
};

