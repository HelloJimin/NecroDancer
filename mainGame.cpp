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
	
	SCENEMANAGER->addScene("������", new mapTool);
	SCENEMANAGER->addScene("��Ʈ�ν�", new introScene);
	SCENEMANAGER->addScene("�׽�Ʈ��", new testScene);
	SCENEMANAGER->addScene("�κ��", new lobbyScene);

	SCENEMANAGER->changeScene("��Ʈ�ν�");

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
	//��� ��Ʈ��
	//PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	PatBlt(getMemDC(), CAMERAMANAGER->getCameraCenter().x - WINSIZEX / 2, CAMERAMANAGER->getCameraCenter().y - WINSIZEY / 2, WINSIZEX, WINSIZEY, BLACKNESS);
	//PatBlt(CAMERAMANAGER->getCameraDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(255, 0, 255));
	HBRUSH oldBrush = (HBRUSH)SelectObject(CAMERAMANAGER->getCameraDC(), myBrush);
	Rectangle(CAMERAMANAGER->getCameraDC(), 0, 0, WINSIZEX, WINSIZEY);
	SelectObject(CAMERAMANAGER->getCameraDC(), oldBrush);
	DeleteObject(myBrush);
	//============================================================================�� ���� �ǵ帮�� ����=======================================================================================
	
	SCENEMANAGER->render();
	EFFECTMANAGER->render();
	TIMEMANAGER->render(CAMERAMANAGER->getCameraDC());

	//ANIMATIONMANAGER->render();

	//============================================================================�� ������ �ǵ帮�� ����=======================================================================================
	//������� ������ HDC�� �׸���.(��������!!)
	//this->getBackBuffer()->render(getHDC(), 0, 0);
	CAMERAMANAGER->render(this->getBackBuffer());
	this->getBackBuffer()->render(getHDC(), 0, 0, CAMERAMANAGER->getCameraCenter().x - WINSIZEX / 2, CAMERAMANAGER->getCameraCenter().y - WINSIZEY / 2, WINSIZEX, WINSIZEY);
}











