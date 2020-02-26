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

enum SELECT
{
	TRRAINDRAW,
	OBJDRAW,
	ERASER
};



class mapTool : public gameNode
{
private:
	tagTile _tiles[TILEX * TILEY];
	tagTile _temp[TILEX * TILEY];
	tagSampleTile _sampleTile[SAMPLETILEX * SAMPLETILEY];
	tagCurrentTile _currnetTile;

	tagSampleBook _sampleBook;

	
	tagBottun bottun[4];

	RECT rc[8];
	RECT saveLoad[8];
	image* saveLoadImg_Dungeon[4];
	image* saveLoadImg_Village[4];

	int page;
	//페이지 1~7 던전
	//페이지 8~14 마을
	//페이지 15~16 세이브로드
	image* sampleImage[8]; // 페이지에 맞춰서 뿔려줄 이미지
	bool first;
	bool mouse;

	SELECT _select;

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
	void setSampleTile();
	void sampleSetRc();
	void setPageSample();
	void setMap();
	void setSampleMap();

	void drage();


	void tileRender();
	TERRAIN dungeonTerrainSelect(int frameX, int frameY);
	OBJECT	dungeonObjSelect(int frameX, int frameY);
	TERRAIN villageTerrainSelect(int frameX, int frameY);
	OBJECT	villageObjSelect(int frameX, int frameY);
};

