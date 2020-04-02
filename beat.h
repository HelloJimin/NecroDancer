#pragma once
#include "singletonBase.h"

struct note
{
	RECT rc;
	image* img;
	int alpha;
	float x, y;
	float speed;
	bool colHeart;
	bool render;
};
struct miss
{
	RECT rc;
	image* img;
	int alpha;
	int speed;
	int max;
};

class beat : public singletonBase<beat>
{
private:
	int _anime;
	int _cnt;

	bool _check;
	bool _isBeat;
	RECT _collisionHeart;
	RECT _heartBox;
	image* _heart;

	vector<int> _vRenge;
	vector<note> _vNoteL;
	vector<note> _vNoteR;
	vector<miss> _vMiss;

	RECT _temp;
	
	string _oldMap;
	string _currentMap;

	unsigned int _songLength;
	unsigned int _songPos;

	float _noteTiming;
	float _noteStartTiming;

	float _deltaTime;
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
	void addHint(string keyname);
	void removeNote();
	void load(string map);
	bool getCheck() { return _check;}

	int getCnt() { return _cnt; }
	bool getIsBeat() { return _isBeat; }

	float lerp(float start, float end, float timeAmount) { return (float)((end - start) * timeAmount); }

	void setMap(string currentMap);

	void addNote(float lapse);

	void okTimeReset() { _okTime = 0; }
	float getOkTime() { return _okTime; }

	void beatStart();
	void noteMove();

};

