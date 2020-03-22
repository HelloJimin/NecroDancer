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
	void update(int startTile);
	void torch(int startTile);

	void reset();

	bool wallCheck(int tileNum);
};

