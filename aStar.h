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

class aStar : public gameNode
{
private:

	vector<int> openList;
	vector<int>closeList;
	vector<int>::iterator iter;

	int startTile;
	int endTile;
	int currentTile;
	bool isFind;
	//bool startAstar;

public:
	aStar();
	~aStar();

	int aStarTile(tagTile * tile, int currentIndex, int endIndex);
	void reset(tagTile * tile);
};

