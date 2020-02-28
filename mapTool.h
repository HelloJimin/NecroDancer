#pragma once
#include"gameNode.h"
#include"tileNode.h"

struct tagBottun
{
	RECT rc;
	image* img;
	int x, y;
};


struct tagSampleBook
{
	tagBottun bottun[3];
	RECT rc;
	RECT sampleRc[10];
	image* img;
	bool Summons;
	int x, y;
};

enum PAGE
{
	PAGE_TERRAIN,
	PAGE_WALL,
	PAGE_OBJ,
	PAGE_MONSTER,
	ERASER
};
struct saveLoad
{
	RECT rc;
	image* image;
};

class mapTool : public gameNode
{
private:
	tagTile _tiles[TILEX * TILEY];
	tagTile _temp[TILEX * TILEY];
	tagCurrentTile _currnetTile;

	tagSampleBook _sampleBook;

	
	tagBottun bottun[4];

	RECT rc[12];

	saveLoad _save[4];
	saveLoad _load[4];
	

	PAGE _page;
	//페이지 1~7 던전
	//페이지 8~14 마을
	//페이지 15~16 세이브로드
	image* sampleImage[12]; // 페이지에 맞춰서 뿔려줄 이미지
	bool first;
	bool mouse;

	POINT _start;
	POINT _end;
	POINT mousePoint;


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
	void setSampleBook();
	void controlSampleBook();
	void sampleBookKey();
	void setSampleBookBottun();
	void sampleBookBottunControl();
	void sampleSetRc();
	void setPageSample();
	void setMap();
	void setSampleMap();

	void drage();


	void tileRender();

	void tileAttribute();
	TERRAIN terrainSelect(int frameX, int frameY);
	OBJECT	objSelect(int frameX, int frameY);
};

