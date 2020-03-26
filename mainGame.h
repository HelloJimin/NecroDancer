#pragma once
#include"gameNode.h"
#include"mapTool.h"
#include"testScene.h"
#include"lobbyScene.h"
#include"introScene.h"
#include"bossStage.h"

#define DC gameNode::getMemDC()

class mainGame : public gameNode
{
private:

public:
	mainGame();
	~mainGame();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(/*HDC hdc*/);

	void imagesInit();
};

