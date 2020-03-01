#pragma once
#include"gameNode.h"
#include"tileNode.h"

enum PAGE
{
	PAGE_TERRAIN,
	PAGE_WALL,
	PAGE_OBJ,
	PAGE_MONSTER,
	ERASER
};

struct tagBottun
{
	RECT rc;
	image* img;
	int x, y;
};

struct tagSampleWindow
{
	tagBottun button[3];
	RECT rc;
	image* img;
	bool open;
	int x, y;
};

struct tagSaveLoad
{
	RECT rc;
	image* image;
};

struct tagSampleImage
{
	image* image;
	RECT rc;
};

class mapTool : public gameNode
{
private:
	PAGE _page;

	tagTile _tiles[TILEX * TILEY];
	tagCurrentTile _currnetTile;

	tagSampleWindow _sampleWindow;
	tagSampleImage _sampleImage[12]; // 페이지에 맞춰서 뿌려줄 이미지

	tagBottun   _button[4];
	tagSaveLoad _save[4];
	tagSaveLoad _load[4];



	POINT _start;
	POINT _end;
	POINT _mousePoint;

	bool _mouse;

public:
	mapTool();
	~mapTool();

	HRESULT init();
	void relaese();
	void update();
	void render();


	void save();
	void load();

	void cameraMove();
	void setUp();
	void mapInit();
	void setSampleWindow();
	void controlSampleWindow();
	void sampleWindowKey();
	void setSampleWindowBottun();
	void sampleSetRc();
	void setSamplePage();
	void setMap();
	void setSampleMap();

	void drage();
	void pageControl();
	void tileAttribute();


	TERRAIN terrainSelect(int frameX, int frameY);
	OBJECT	objSelect(int frameX, int frameY);
};

