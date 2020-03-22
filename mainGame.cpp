#include "stdafx.h"
#include "mainGame.h"


mainGame::mainGame(){}

mainGame::~mainGame(){}

HRESULT mainGame::init()
{
	gameNode::init(true);
	imagesInit();

	BEAT->init();
	PLAYER->init();

	ITEMMANAGER->init();
	MONSTERMANAGER->init();

	SetTextAlign(CAMERAMANAGER->getCameraDC(), TA_RIGHT);
	
	SCENEMANAGER->addScene("맵툴신", new mapTool);
	SCENEMANAGER->addScene("인트로신", new introScene);
	SCENEMANAGER->addScene("테스트신", new testScene);
	SCENEMANAGER->addScene("로비신", new lobbyScene);

	SCENEMANAGER->changeScene("인트로신");

	return S_OK;
}

void mainGame::release()
{
	gameNode::release();
	PLAYER->release();
	ITEMMANAGER->release();
	MONSTERMANAGER->release();
}

void mainGame::update()
{
	gameNode::update();
	SCENEMANAGER->update();
	EFFECTMANAGER->update();

	//ANIMATIONMANAGER->update();
}

void mainGame::render(/*HDC hdc*/)
{
	//흰색 비트맵
	//PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	PatBlt(getMemDC(), CAMERAMANAGER->getCameraCenter().x - WINSIZEX / 2, CAMERAMANAGER->getCameraCenter().y - WINSIZEY / 2, WINSIZEX, WINSIZEY, BLACKNESS);
	//PatBlt(CAMERAMANAGER->getCameraDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(255, 0, 255));
	HBRUSH oldBrush = (HBRUSH)SelectObject(CAMERAMANAGER->getCameraDC(), myBrush);
	Rectangle(CAMERAMANAGER->getCameraDC(), 0, 0, WINSIZEX, WINSIZEY);
	SelectObject(CAMERAMANAGER->getCameraDC(), oldBrush);
	DeleteObject(myBrush);
	//============================================================================이 위로 건드리면 뒤짐=======================================================================================
	
	SCENEMANAGER->render();
	EFFECTMANAGER->render();
	TIMEMANAGER->render(CAMERAMANAGER->getCameraDC());

	//ANIMATIONMANAGER->render();

	//============================================================================이 밑으로 건드리면 뒤짐=======================================================================================
	//백버퍼의 내용을 HDC에 그린다.(지우지마!!)
	//this->getBackBuffer()->render(getHDC(), 0, 0);
	CAMERAMANAGER->render(this->getBackBuffer());
	this->getBackBuffer()->render(getHDC(), 0, 0, CAMERAMANAGER->getCameraCenter().x - WINSIZEX / 2, CAMERAMANAGER->getCameraCenter().y - WINSIZEY / 2, WINSIZEX, WINSIZEY);
}











