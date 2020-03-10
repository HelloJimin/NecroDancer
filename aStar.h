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
	ASTAR_STATE_SEARCHING,	//�˻���
	ASTAR_STATE_FOUND,		//�߰�!
	ASTAR_STATE_NOWAY,		//�����
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

