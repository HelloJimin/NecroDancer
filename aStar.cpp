#include "stdafx.h"
#include "aStar.h"
aStar::aStar()
{
	_lastIndex = 0;
}


aStar::~aStar()
{
}

HRESULT aStar::init()
{


	return S_OK;
}

void aStar::release()
{
}

void aStar::update()
{
}


tagTile* aStar::aStarTile(tagTile tile[], RECT start, RECT end)
{
	_openList.clear();
	_closeList.clear();
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		tile[i].parent = NULL;
		tile[i].walkable = true;
		tile[i].listOn = false;
		tile[i].F = BIGNUM;
		tile[i].H = 0;			//������̹Ƿ� 0
		if (tile[i].obj == OBJ_NOMALWALL)
		{
			tile[i].strength = 1;
			tile[i].walkable = false;
		}
		else if (tile[i].obj == OBJ_SKULLWALL)
		{
			tile[i].strength = 2;
			tile[i].walkable = false;
		}
		else if (tile[i].obj == OBJ_WHITEWALL)
		{
			tile[i].strength = 3;
			tile[i].walkable = false;
		}
		else if (tile[i].obj == OBJ_IRONWALL)
		{
			tile[i].strength = 4;
			tile[i].walkable = false;
		}
		else if (tile[i].obj == OBJ_GOLDWALL)
		{
			tile[i].strength = 5;
			tile[i].walkable = false;
		}
		else if (tile[i].obj == OBJ_DOOR)
		{
			tile[i].strength = 0;
			tile[i].walkable = false;
		}
	}

	int _tileX, _tileY;
	_tileX = start.left / TILESIZE;
	_tileY = start.top / TILESIZE;

	_startPoint = _tileX + _tileY * TILEX;
	_endPoint = end.left / TILESIZE + end.top / TILESIZE * TILEX;

	tile[_startPoint].listOn = true;
	_closeList.push_back(&tile[_startPoint]);

	_astarState = ASTAR_STATE_SEARCHING;
	_lastIndex = 0;

	Cj = _closeList[_lastIndex]->x;
	Ci = _closeList[_lastIndex]->y;
	Cg = _closeList[_lastIndex]->G;

	if (Ci != 0)//0��° ���� �ƴϸ� ��ܶ��ΰ��
	{
		if (tile[_tileX + (_tileY - 1) * TILEX].walkable)//��� ��� Ÿ���� �������� �ִٸ�
		{
			if (!tile[_tileX + (_tileY - 1) * TILEX].listOn)//���¸���Ʈ�� ������ �ȵǾ� �ִ� Ÿ���̶��
			{
				tile[_tileX + (_tileY - 1) * TILEX].listOn = true;//���¸���Ʈ�� ���ԵǾ���
				tile[_tileX + (_tileY - 1) * TILEX].G = Cg + 10;	//Ÿ���� G���� Ŭ���� ��Ʈ�� ���� G+10
				tile[_tileX + (_tileY - 1) * TILEX].parent = _closeList[_lastIndex];//Ÿ���� �θ� Ŭ���� ����Ʈ�� ���������� �߰�
				_openList.push_back(&tile[_tileX + (_tileY - 1) * TILEX]);//���¸���Ʈ�� �߰�
			}
			else//���¸���Ʈ�� ������ �Ǿ� �ִ� Ÿ���̶��
			{
				if (Cg + 10 < tile[_tileX + (_tileY - 1) * TILEX].G)//����G������ ���� ����� G���� �۴ٸ�
				{
					tile[_tileX + (_tileY - 1) * TILEX].G = Cg + 10;//G�� ���Ӱ� ���
					tile[_tileX + (_tileY - 1) * TILEX].parent = _closeList[_lastIndex];
				}
			}
		}
		if (Cj != 0)//�»�� :0��° ���� �ƴ϶��
		{
			//�»�� Ÿ���� �����̳� �Ʒ��� ���� ���ٸ�
			if (tile[_tileX + (_tileY - 1) * TILEX - 1].walkable && tile[_tileX + (_tileY - 1) * TILEX].walkable && tile[_tileX + _tileY * TILEX - 1].walkable)
			{
				if (!tile[_tileX + (_tileY - 1) * TILEX - 1].walkable)
				{
					tile[_tileX + (_tileY - 1) * TILEX - 1].listOn = true;
					tile[_tileX + (_tileY - 1) * TILEX - 1].G = Cg + 14;//�밢���̹Ƿ�
					tile[_tileX + (_tileY - 1) * TILEX - 1].parent = _closeList[_lastIndex];
					_openList.push_back(&tile[_tileX + (_tileY - 1) * TILEX - 1]);
				}
				else
				{
					if (Cg + 14 < tile[_tileX + (_tileY - 1) * TILEX - 1].G)
					{
						tile[_tileX + (_tileY - 1) * TILEX - 1].G = Cg + 14;
						tile[_tileX + (_tileY - 1) * TILEX - 1].parent = _closeList[_lastIndex];
					}
				}
			}
		}
		if (Cj != TILESIZEX - 1)//����: ���������� �ƴ϶��
		{
			//���� Ÿ���� �����̳� �Ʒ��� ���� ���ٸ�
			if (tile[_tileX + (_tileY - 1) * TILEX + 1].walkable && tile[_tileX + (_tileY - 1) * TILEX].walkable&& tile[_tileX + _tileY * TILEX + 1].walkable)
			{
				if (!tile[_tileX + (_tileY - 1) * TILEX + 1].listOn)
				{
					tile[_tileX + (_tileY - 1) * TILEX + 1].listOn = true;
					tile[_tileX + (_tileY - 1) * TILEX + 1].G = Cg + 14;
					tile[_tileX + (_tileY - 1) * TILEX + 1].parent = _closeList[_lastIndex];
					_openList.push_back(&tile[_tileX + (_tileY - 1) * TILEX + 1]);
				}
				else
				{
					if (Cg + 14 < tile[_tileX + (_tileY - 1) * TILEX + 1].G)
					{
						tile[_tileX + (_tileY - 1) * TILEX + 1].G = Cg + 14;
						tile[_tileX + (_tileY - 1) * TILEX + 1].parent = _closeList[_lastIndex];
					}
				}
			}
		}
	}
	if (Cj != 0)//���� : 0��° ���� �ƴ϶��
	{
		if (tile[_tileX + _tileY * TILEX - 1].walkable)//����Ÿ���� �̵������ϴٸ�
		{
			if (!tile[_tileX + _tileY * TILEX - 1].listOn)
			{
				tile[_tileX + _tileY * TILEX - 1].listOn = true;
				tile[_tileX + _tileY * TILEX - 1].G = Cg + 10;
				tile[_tileX + _tileY * TILEX - 1].parent = _closeList[_lastIndex];
				_openList.push_back(&tile[_tileX + _tileY * TILEX - 1]);
			}
			else
			{
				if (Cg + 10 < tile[_tileX + _tileY * TILEX - 1].G)
				{
					tile[_tileX + _tileY * TILEX - 1].G = Cg + 10;
					tile[_tileX + _tileY * TILEX - 1].parent = _closeList[_lastIndex];
				}
			}
		}
	}
	if (Cj != TILESIZEX - 1)//���� :  ���������� �ƴ϶��
	{

		if (tile[_tileX + _tileY * TILEX + 1].walkable)//����Ÿ���� �̵������ϴٸ�
		{
			if (!tile[_tileX + _tileY * TILEX + 1].listOn)
			{
				tile[_tileX + _tileY * TILEX + 1].listOn = true;
				tile[_tileX + _tileY * TILEX + 1].G = Cg + 10;
				tile[_tileX + _tileY * TILEX + 1].parent = _closeList[_lastIndex];
				_openList.push_back(&tile[_tileX + _tileY * TILEX + 1]);
			}
			else
			{
				if (Cg + 10 < tile[_tileX + _tileY * TILEX + 1].G)
				{
					tile[_tileX + _tileY * TILEX + 1].G = Cg + 10;
					tile[_tileX + _tileY * TILEX + 1].parent = _closeList[_lastIndex];
				}
			}
		}
	}
	if (Ci != TILESIZEY - 1)//���������� �ƴ϶�� �ϴ� ���� ���
	{
		if (tile[_tileX + (_tileY + 1) * TILEX].walkable)//�ϴ� ��� Ÿ���� �̵������ϴٸ�
		{
			if (!tile[_tileX + (_tileY + 1) * TILEX].listOn)
			{
				tile[_tileX + (_tileY + 1) * TILEX].listOn = true;
				tile[_tileX + (_tileY + 1) * TILEX].G = Cg + 10;
				tile[_tileX + (_tileY + 1) * TILEX].parent = _closeList[_lastIndex];
				_openList.push_back(&tile[_tileX + (_tileY + 1) * TILEX]);
			}
			else
			{
				if (Cg + 10 < tile[_tileX + (_tileY + 1) * TILEX].G)
				{
					tile[_tileX + (_tileY + 1) * TILEX].G = Cg + 10;
					tile[_tileX + (_tileY + 1) * TILEX].parent = _closeList[_lastIndex];
				}
			}
		}
		if (Cj != 0)//���ϴ� :  0��° ���� �ƴ϶��
		{
			//���ϴ� Ÿ���� �������̳� ���� ���� ���ٸ�
			if (tile[_tileX + (_tileY + 1) * TILEX - 1].walkable && tile[_tileX + (_tileY + 1) * TILEX].walkable && tile[_tileX + _tileY * TILEX - 1].walkable)
			{
				if (!tile[_tileX + (_tileY + 1) * TILEX - 1].listOn)
				{
					tile[_tileX + (_tileY + 1) * TILEX - 1].listOn = true;
					tile[_tileX + (_tileY + 1) * TILEX - 1].G = Cg + 14;
					tile[_tileX + (_tileY + 1) * TILEX - 1].parent = _closeList[_lastIndex];
					_openList.push_back(&tile[_tileX + (_tileY + 1) * TILEX - 1]);
				}
				else
				{
					if (Cg + 14 < tile[_tileX + (_tileY + 1) * TILEX - 1].G)
					{
						tile[_tileX + (_tileY + 1) * TILEX - 1].G = Cg + 14;
						tile[_tileX + (_tileY + 1) * TILEX - 1].parent = _closeList[_lastIndex];
					}
				}
			}
		}
		if (Cj != TILESIZEX - 1)//���ϴ� :  ������ ���� �ƴ϶��
		{
			//���ϴ� Ÿ���� �������̳� ���� �̵������ϴٸ�
			if (tile[_tileX + (_tileY + 1) * TILEX + 1].walkable && tile[_tileX + (_tileY + 1) * TILEX].walkable&& tile[_tileX + _tileY * TILEX + 1].walkable)
			{
				if (!tile[_tileX + (_tileY + 1) * TILEX + 1].listOn)
				{
					tile[_tileX + (_tileY + 1) * TILEX + 1].listOn = true;
					tile[_tileX + (_tileY + 1) * TILEX + 1].G = Cg + 14;
					tile[_tileX + (_tileY + 1) * TILEX + 1].parent = _closeList[_lastIndex];
					_openList.push_back(&tile[_tileX + (_tileY + 1) * TILEX + 1]);
				}
				else
				{
					if (Cg + 14 < tile[_tileX + (_tileY + 1) * TILEX + 1].G)
					{
						tile[_tileX + (_tileY + 1) * TILEX + 1].G = Cg + 14;
						tile[_tileX + (_tileY + 1) * TILEX + 1].parent = _closeList[_lastIndex];
					}
				}
			}
		}
	}
	for (int i = 0; i < _openList.size(); i++)
	{
		int vertical = (tile[_endPoint].y - _openList[i]->y) * 10;//���� H��
		int horizontal = (tile[_endPoint].x - _openList[i]->x) * 10;//���� H��

		if (vertical < 0)vertical *= -1;//������ �ݴ��̸� �����ο�
		if (horizontal < 0)horizontal *= -1;

		_openList[i]->H = vertical + horizontal;//�� H�� : ����+���� H
	}

	for (int i = 0; i < _openList.size(); i++)
	{
		_openList[i]->F = _openList[i]->G + _openList[i]->H;//F�����
	}
	if (_openList.size() == 0)//�˻��ߴµ��� openList�� ����� 0�̸� ���̻� ã������ ����
	{
		_astarState = ASTAR_STATE_NOWAY;//��ξ���
		//return;
	}
	int index = 0;			//���� ����Ʈ�� ���� F�� ���� Ÿ���� �ε���
	int lowest = BIGNUM;

	for (int i = 0; i < _openList.size(); i++)
	{
		if (_openList[i]->F < lowest)
		{
			lowest = _openList[i]->F;
			index = i;
		}
	}

	_closeList.push_back(_openList[index]);
	_openList.erase(_openList.begin() + index);//���� ����Ʈ�� �߰��� Ÿ���� ���¸���Ʈ���� ����
	_lastIndex++;//���� ���߿� �߰��� Ŭ������ �ε���
	return _closeList[_lastIndex];
}

