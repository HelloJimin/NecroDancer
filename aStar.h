#pragma once
#include"gameNode.h"
/*
	�־��� ��������� ��ǥ������ ���� �ִ� ��θ� ã�Ƴ��� �׷��� �˰��� �߿� �ϳ���.
	F=G+H
	F = ���(���������� ���� �� ��� ������� �̵��ϴ� �ɸ� ���� �������� ��ħ)
	G =�簢������ ���� ���ο� �簢�� ������ �̵����
	H = �簢�� ���κ��� ���������������� �����̵����
	(�밢�� �̵��� �ƴ� ���μ��� �̵��� ���� ������� ���, ��ֹ��� ���� ��Ҵ� ������� �ʴ´�.)

	���ۿ��� :  ���������� �̵��� �� �ִ� ������ ���¸���Ʈ�� �߰���.
	��ġ�� �ٽ� Ȯ���� �ʿ䰡 ���� ������ Ŭ���� ����Ʈ�� �߰�
	���� ����Ʈ���� ���� ����� ���� ��ġ�� ���� ��ġ�� ����(�� F�� ������)
	�� ������ �ݺ��Ѵ�.
	F���� �����ϴٸ� �ӵ����� �������� ���¸���Ʈ�� �� �ʰ� �߰� �Ȱ��� �����ϴ� ���� ������.
*/

class aStar : public gameNode
{
private:

	vector<int> openList;
	vector<int>closeList;
	vector<int>::iterator iter;

	const tagTile * tiles;

	int startTile;
	int endTile;
	int currentTile;
	bool isFind;
	bool noPath;
	//bool startAstar;

public:
	aStar();
	~aStar();

	int aStarStraight(tagTile tile[], int currentIndex, int endIndex);
	int aStarTile(tagTile tile[], int currentIndex, int endIndex);
	int aStarBoss(tagTile tile[], int currentIndex, int endIndex);
	void reset(tagTile tile[]);

	bool noPathCheck(tagTile tile[],int endIndex);

	int randomMove(int currentTile);
};

