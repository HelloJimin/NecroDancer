#pragma once
#include"singletonBase.h"

class cameraManager : public singletonBase<cameraManager>
{
private:
	image* _camera;
	POINT _center;

	POINT _cameraXY;

public:
	cameraManager();
	~cameraManager();

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);
	void render(image* img);

	void setCameraCenter(POINT point);

	HDC getCameraDC() { return _camera->getMemDC(); }

	POINT getCameraCenter() { return _center; }
	POINT getCameraXY() { return _cameraXY; }

};

