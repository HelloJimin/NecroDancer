#pragma once
#include "singletonBase.h"

struct note
{
	int alpha;
	float x, y;
	RECT rc;
	image* img;
	float speed;
	bool render;
	bool colHeart;
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

	bool _check;
	bool _isBeat;
	RECT _collisionHeart;
	RECT _heartBox;
	image* _heart;


	vector<note> _vNoteL;
	vector<note> _vNoteR;

	miss _miss;
	vector<miss> _vMiss;

	RECT _temp;

	float test;
	float _deltaTime;
	
	string _oldMap;
	string _currentMap;

	bool _beatOn;
	vector<int> _vRenge;
	unsigned int _songLength;
	unsigned int _songPos;
	float noteTimeInterval;
	float noteTimeIntervalCount;
	int _currentNoteCnt;

	float _okTime;
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
	void load(string map);
	bool getCheck() { return _check;}

	int getCnt() { return _cnt; }
	bool getIsBeat() { return _isBeat; }
	void setBeatOn(bool beaton) { _beatOn = beaton; }

	float lerp(float start, float end, float timeAmount) { return (float)((end - start) * timeAmount); }

	void setMap(string currentMap);

	void addNote(float x);

	void okTimeReset() { _okTime = 0; }
	float getOkTime() { return _okTime; }
};

