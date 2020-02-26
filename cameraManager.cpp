#include "stdafx.h"
#include "cameraManager.h"

cameraManager::cameraManager(){}

cameraManager::~cameraManager(){}

HRESULT cameraManager::init()
{
	_camera = IMAGEMANAGER->addImage("Ä«¸Þ¶ó", WINSIZEX, WINSIZEY);
	_center = PointMake(WINSIZEX / 2, WINSIZEY / 2);

	_cameraXY = PointMake(_center.x - WINSIZEX / 2, _center.y - WINSIZEY / 2);

	return S_OK;
}

void cameraManager::release()
{
}

void cameraManager::update()
{
	_cameraXY = PointMake(_center.x - WINSIZEX / 2, _center.y - WINSIZEY / 2);
}

void cameraManager::render(HDC hdc)
{
	
}

void cameraManager::render(image * img)
{
	GdiTransparentBlt(img->getMemDC(), _center.x - WINSIZEX / 2, _center.y - WINSIZEY / 2, WINSIZEX, WINSIZEY, _camera->getMemDC(), 0, 0, WINSIZEX, WINSIZEY, RGB(255, 255, 255));
}

void cameraManager::setCameraCenter(POINT point)
{
	_center.x = point.x;
	_center.y = point.y;

	if (_center.x < WINSIZEX / 2)_center.x = WINSIZEX / 2;
	if (_center.x > WINSIZEX*2-100) _center.x = WINSIZEX*2-100;
	if (_center.y < WINSIZEY / 2)_center.y = WINSIZEY / 2;
	if (_center.y > WINSIZEY*2) _center.y = WINSIZEY*2;
}