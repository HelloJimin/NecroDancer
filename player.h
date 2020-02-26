#pragma once
#include"singletonBase.h"
class player : public singletonBase<player>
{
private:
	RECT rc;
	int x, y;
public:
	player();
	~player();

	HRESULT init(HDC hdc);
	void release();
	void update();
	void render(HDC hdc);

};

