#include "stdafx.h"
#include "progressBar.h"
progressBar::progressBar()
{
}


progressBar::~progressBar()
{
}

HRESULT progressBar::init(char * frontImage, char * backImage, float x, float y, int width, int height)
{
	_x = x;
	_y = y;


	_progressBarFront = new image;
	_progressBarFront->init(frontImage, x, y, width, height, true, RGB(255, 0, 255));

	_progressBarBack = new image;
	_progressBarBack->init(backImage, x, y, width, height, true, RGB(255, 0, 255));

	_rcProgress = RectMake(x, y, width, height);

	_width = _progressBarFront->getWidth();

	return S_OK;
}

void progressBar::release()
{
	SAFE_DELETE(_progressBarFront);
	SAFE_DELETE(_progressBarBack);
}

void progressBar::update() {}

void progressBar::render()
{
	_progressBarBack->render(getMemDC(), _rcProgress.left, _y, 0, 0, _progressBarBack->getWidth(), _progressBarBack->getHeight());

	_progressBarFront->render(getMemDC(), _rcProgress.left, _y, 0, 0, _width, _progressBarBack->getHeight());

}
void progressBar::setGauge(float currentGauge, float maxGauge)
{
	_width = (currentGauge / maxGauge)* _progressBarBack->getWidth();
}


PlayerHpbar::PlayerHpbar() {}

PlayerHpbar::~PlayerHpbar() {}

HRESULT PlayerHpbar::init(char * frontImage, char * backImage, float x, float y, float width, float height)
{
	_x = x;
	_y = y;

	_progressBarFront = IMAGEMANAGER->findImage(frontImage);
	_progressBarBack = IMAGEMANAGER->findImage(backImage);

	_rcProgress = RectMake(_x, _y, IMAGEMANAGER->findImage(frontImage)->getWidth(), IMAGEMANAGER->findImage(frontImage)->getHeight());

	_width = _progressBarFront->getWidth();

	return S_OK;
}

void PlayerHpbar::release()
{
	SAFE_DELETE(_progressBarFront);
	SAFE_DELETE(_progressBarBack);
}

void PlayerHpbar::update() {}

void PlayerHpbar::render()
{
	_progressBarBack->render(CAMERAMANAGER->getCameraDC(), _rcProgress.left, _y, 0, 0, _progressBarBack->getWidth(), _progressBarBack->getHeight());
	_progressBarFront->render(CAMERAMANAGER->getCameraDC(), _rcProgress.left + 26, _y, 0, 0, _width - 26, _progressBarBack->getHeight());

	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		Rectangle(CAMERAMANAGER->getCameraDC(), _rcProgress.left, _rcProgress.top, _rcProgress.right, _rcProgress.bottom);
	}
}

void PlayerHpbar::setGauge(float currentGauge, float maxGauge)
{
	_width = (currentGauge / maxGauge)* _progressBarBack->getWidth();
}
