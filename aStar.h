#pragma once
#include"gameNode.h"
/*
	주어진 출발점에서 목표점까지 가는 최단 경로를 찾아내는 그래프 알고리즘 중에 하나임.
	F=G+H
	F = 비용(목적지까지 가는 총 비용 현재까지 이동하는 걸린 비용과 예상비용을 합침)
	G =사각형으로 부터 새로운 사각형 까지의 이동비용
	H = 사각형 으로부터 최종목적지까지의 예상이동비용
	(대각선 이동이 아닌 가로세로 이동에 대한 비용으로 계산, 장애물에 대한 요소는 고려하지 않는다.)

	동작원리 :  시작점에서 이동할 수 있는 지점을 오픈리스트에 추가함.
	위치를 다시 확인할 필요가 없는 지점을 클로즈 리스트에 추가
	오픈 리스트에서 가장 비용이 적은 위치를 현재 위치로 지정(즉 F가 작은곳)
	위 과정을 반복한다.
	F값이 동일하다면 속도상의 목적으로 오픈리스트에 더 늦게 추가 된것을 선택하는 것이 빠르다.
*/
enum Select
{
	SELECT_START,
	SELECT_END,
	SELECT_BLOCK
};
enum Direction
{
	DIRECTION_LEFT,
	DIRECTION_RIGHT,
	DIRECTION_UP,
	DIRECTION_DOWN,
	DIRECTION_LEFTUP,
	DIRECTION_RIGHTDOWN,
	DIRECTION_LEFTDOWN,
	DIRECTION_RIGHTUP
};

enum State
{
	STATE_NONE,
	STATE_OPEN,
	STATE_CLOSE,
	STATE_PATH
};

enum ASTAR_STATE
{
	ASTAR_STATE_SEARCHING,	//검색중
	ASTAR_STATE_FOUND,		//발견!
	ASTAR_STATE_NOWAY,		//길없음
	ASTAR_STATE_END
};

class aStar : public gameNode
{
private:

	//tagTile tiles[TILESIZE];
	tagTile* tiles;

	vector<int> openList;
	vector<int>closeList;
	vector<int>::iterator iter;


	Select currentSelect;

	int startTile;
	int endTile;
	int currentTile;
	bool isFind;
	bool noPath;
	bool startAstar;

	RECT rc[6];


	HBRUSH brush;
	HFONT font, oldFont;
	char str[128];
	int temp;

public:
	aStar();
	~aStar();

	HRESULT init();
	void release();
	void update();
	void render();

	void Astar();

	int aStarTile(tagTile tile[], RECT start, RECT end, int currentIndex, int endIndex);
};

