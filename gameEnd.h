#pragma once

struct tagButton
{
	image* img;
	RECT rc;
	int frameY;

};
class gameEnd
{
private:
	image* _intro;
	tagButton _button[2];

	RECT _check;
	int _buttonNum;

	bool _aClick;
public:
	gameEnd();
	~gameEnd();

	HRESULT init();
	void release();
	void update();
	void render(/*HDC hdc*/);

};

