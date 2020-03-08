#pragma once

//타일사이즈
#define TILESIZE 52
#define BIGNUM 20000		//초기값(F)
//크기
#define TILEX 52
#define TILEY 52

//타일 총 사이즈
#define TILESIZEX TILESIZE * TILEX
#define TILESIZEY TILESIZE * TILEY

//지형
enum TERRAIN
{
	//아무것도없는		땅
	TERRAIN_NONE, TERRAIN_GROUND
};

//오브젝트
enum OBJECT
{
	OBJ_NONE, OBJ_NOMALWALL, OBJ_SKULLWALL, OBJ_WHITEWALL, OBJ_IRONWALL, OBJ_GOLDWALL, OBJ_DOOR
};

//포지션 정의
enum POS
{

};

//타일구조체
struct tagTile
{
	TERRAIN terrain;			//지형
	OBJECT obj;					//오브젝트
	RECT rc;					//렉트
	int terrainFrameX;			//지형 프레임번호
	int terrainFrameY;
	int objFrameX;				//오브젝트 프레임번호
	int objFrameY;
	int x, y;					//타일 중점좌표
	int strength;				//타일의 강도

	item* item;

	bool listOn;
	bool walkable;
	tagTile* parent;
	int F, G, H;
};

//셈플타일 구조체
struct tagSampleTile
{
	RECT rcTile;				//셈플타일 렉트
	int terrainFrameX;			//셈플타일 프레임 번호
	int terrainFrameY;
};

//현재타일(내가 클릭한 타일 정보 저장용)
struct tagCurrentTile
{
	int x;
	int y;
};