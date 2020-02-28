#pragma once
#include "mapTool.h"
class testScene : public mapTool
{
public:
	testScene();
	~testScene();

	HRESULT init();
	void release();
	void update();
	void render(/*HDC hdc*/);

};

