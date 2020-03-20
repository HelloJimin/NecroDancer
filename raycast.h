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


	void init();
	void update();

	void reset();

	bool wallCheck(int tileNum);
};

