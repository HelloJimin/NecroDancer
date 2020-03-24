#pragma once
#include "singletonBase.h"

struct note
{
	int alpha;
	float x[2], y;
	RECT rc[2];
	image* img[2];
};
struct miss
{
	int alpha;
	int speed;
	RECT rc;
	image* img;
	int max;
};
class beat : public singletonBase<beat>
{
private:
	int _anime;
	int _cnt;
	int _turn;
	float _speed;
	bool _check;

	RECT _collisionHeart;
	RECT _heartBox;
	image* _heart;

	note _note;
	vector<note> _vNote;

	miss _miss;
	vector<miss> _vMiss;

	RECT _temp;

	float test;
	float _deltaTime;

	bool _beatOn;
	vector<int> _vRenge;
	unsigned int _songLength;
	unsigned int _songPos;
	float noteTimeInterval;
	float noteTimeIntervalCount;
public:
	beat();
	~beat();

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	void checkBeat();
	void missUpdate();

	void addMiss();
	void addCoinMiss();
	void removeNote();
	void load();
	bool getCheck() { return _check;}
	int getCnt() { return _cnt; }

	void setBeatOn(bool beaton) { _beatOn = beaton; }

	float lerp(float start, float end, float timeAmount) { return (float)((end - start) * timeAmount); }


};

