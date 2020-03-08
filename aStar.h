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
	vector<tagTile*> _openList;
	vector<tagTile*> _closeList;

	ASTAR_STATE _astarState;

	int _startX, _startY;			//���������� i,j�ε���
	int _endX, _endY;			//���������� i,j�ε���
	int _lastIndex;				//���߿� �߰��� Ŭ���� ����Ʈ�� �ε���

	bool _startPointSet;			//���������� ��ġ �Ǿ���
	bool _endPointSet;				//���������� ��ġ �Ǿ���

	int _startPoint;
	int _endPoint;

	int Ci;
	int Cj;
	int Cg;

	RECT rc[6];

public:
	aStar();
	~aStar();

	HRESULT init();
	void release();
	void update();



	tagTile* aStarTile(tagTile tile[], RECT start, RECT end);
};

