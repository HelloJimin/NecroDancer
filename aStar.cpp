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
		tile[i].H = 0;			//계산전이므로 0
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

	if (Ci != 0)//0번째 줄이 아니면 상단라인계산
	{
		if (tile[_tileX + (_tileY - 1) * TILEX].walkable)//상단 가운데 타일이 지나갈수 있다면
		{
			if (!tile[_tileX + (_tileY - 1) * TILEX].listOn)//오픈리스트에 포함이 안되어 있는 타일이라면
			{
				tile[_tileX + (_tileY - 1) * TILEX].listOn = true;//오픈리스트에 포함되었다
				tile[_tileX + (_tileY - 1) * TILEX].G = Cg + 10;	//타일의 G값을 클로즈 리트의 누적 G+10
				tile[_tileX + (_tileY - 1) * TILEX].parent = _closeList[_lastIndex];//타일의 부모를 클로즈 리스트의 마지막으로 추가
				_openList.push_back(&tile[_tileX + (_tileY - 1) * TILEX]);//오픈리스트에 추가
			}
			else//오픈리스트에 포함이 되어 있던 타일이라면
			{
				if (Cg + 10 < tile[_tileX + (_tileY - 1) * TILEX].G)//기존G값보다 새로 계산한 G값이 작다면
				{
					tile[_tileX + (_tileY - 1) * TILEX].G = Cg + 10;//G값 새롭게 계산
					tile[_tileX + (_tileY - 1) * TILEX].parent = _closeList[_lastIndex];
				}
			}
		}
		if (Cj != 0)//좌상단 :0번째 열이 아니라면
		{
			//좌상단 타일의 왼쪽이나 아래에 벽이 없다면
			if (tile[_tileX + (_tileY - 1) * TILEX - 1].walkable && tile[_tileX + (_tileY - 1) * TILEX].walkable && tile[_tileX + _tileY * TILEX - 1].walkable)
			{
				if (!tile[_tileX + (_tileY - 1) * TILEX - 1].walkable)
				{
					tile[_tileX + (_tileY - 1) * TILEX - 1].listOn = true;
					tile[_tileX + (_tileY - 1) * TILEX - 1].G = Cg + 14;//대각선이므로
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
		if (Cj != TILESIZEX - 1)//우상단: 마지막열이 아니라면
		{
			//우상단 타일의 왼쪽이나 아래에 벽이 없다면
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
	if (Cj != 0)//좌측 : 0번째 열이 아니라면
	{
		if (tile[_tileX + _tileY * TILEX - 1].walkable)//좌측타일이 이동가능하다면
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
	if (Cj != TILESIZEX - 1)//우측 :  마지막열이 아니라면
	{

		if (tile[_tileX + _tileY * TILEX + 1].walkable)//우측타일이 이동가능하다면
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
	if (Ci != TILESIZEY - 1)//마지막행이 아니라면 하단 라인 계산
	{
		if (tile[_tileX + (_tileY + 1) * TILEX].walkable)//하단 가운데 타일이 이동가능하다면
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
		if (Cj != 0)//좌하단 :  0번째 열이 아니라면
		{
			//좌하단 타일의 오른쪽이나 위에 벽이 없다면
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
		if (Cj != TILESIZEX - 1)//우하단 :  마지막 열이 아니라면
		{
			//우하단 타일의 오른쪽이나 위가 이동가능하다면
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
		int vertical = (tile[_endPoint].y - _openList[i]->y) * 10;//가로 H값
		int horizontal = (tile[_endPoint].x - _openList[i]->x) * 10;//세로 H값

		if (vertical < 0)vertical *= -1;//방향이 반대이면 음수부여
		if (horizontal < 0)horizontal *= -1;

		_openList[i]->H = vertical + horizontal;//총 H값 : 가로+세로 H
	}

	for (int i = 0; i < _openList.size(); i++)
	{
		_openList[i]->F = _openList[i]->G + _openList[i]->H;//F값계산
	}
	if (_openList.size() == 0)//검색했는데도 openList의 사이즈가 0이면 더이상 찾을것이 없음
	{
		_astarState = ASTAR_STATE_NOWAY;//경로없다
		//return;
	}
	int index = 0;			//오픈 리스트중 가장 F가 작은 타일의 인덱스
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
	_openList.erase(_openList.begin() + index);//오픈 리스트에 추가된 타일은 오픈리스트에서 제외
	_lastIndex++;//가장 나중에 추가된 클로즈의 인덱스
	return _closeList[_lastIndex];
}

