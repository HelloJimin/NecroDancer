#include "stdafx.h"
#include "aStar.h"
aStar::aStar()
{
}


aStar::~aStar()
{
}

HRESULT aStar::init()
{

	_astarState = ASTAR_STATE_END;	//초기상태 =  타일 배치 완료전
	_selectType = TILE_TYPE_EMPTY;	//배치할 타일 속성 = 빈타일
	_selectedTypeColor = RGB(255, 255, 255);//배치할 타일 색상 =  하양

	_startPointSet = false;
	_endPointSet = false;

	for (int i = 0; i < TILE_Y; i++)
	{
		for (int j = 0; j < TILE_X; j++)
		{
			_tile[i][j].type = TILE_TYPE_EMPTY;//초기타일 속성 = 빈타일
			_tile[i][j].color = RGB(255, 255, 255);
			_tile[i][j].parent = NULL;	//부모타일
			_tile[i][j].F = BIGNUM;
			_tile[i][j].H = 0;			//계산전이므로 0
			_tile[i][j].i = i;
			_tile[i][j].j = j;
			_tile[i][j].rc = RectMake(WINSIZEX - (TILE_X + 1)* WIDTH + WIDTH * j,
				WINSIZEX / 2 - (TILE_Y) / 2 * HEIGHT + HEIGHT * i, WIDTH, HEIGHT);//렉트 할당
		}
	}

	for (int i = 0; i < 5; i++)
	{
		rc[i] = RectMake(15, 300 + i * 50, 25, 25);
	}


	return S_OK;
}

void aStar::release()
{
}

void aStar::update()
{
	//배치가 끝나지 않았다면
	if (_astarState == ASTAR_STATE_END)
	{
		//타일 배치
		tileComposition();
	}
	//시작지점 도착지점이 설치되어 있고 스페이스누르면 초기화
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE) && _startPointSet&& _endPointSet&& _astarState == ASTAR_STATE_END)
	{
		tileInitializing();
	}
	if (KEYMANAGER->isOnceKeyDown('5'))
	{
		_openList.clear();
		_closeList.clear();
		init();
	}
	//배치중이거나 발견했거나 길이 없으면 실행하지 마라
	if (_astarState == ASTAR_STATE_END || _astarState == ASTAR_STATE_FOUND || _astarState == ASTAR_STATE_NOWAY)return;
	
	addOpenList();
	calculateH();
	calculateF();
	addCloseList();
	checkArrive();
}

void aStar::render()
{
	TextOut(getMemDC(), 15, 75, "1 :지우개", strlen("1 :지우개"));
	TextOut(getMemDC(), 15, 95, "2 :시작", strlen("2 :시작"));
	TextOut(getMemDC(), 15, 115, "3 :끝", strlen("3 :끝"));
	TextOut(getMemDC(), 15, 135, "4 :장애물", strlen("4 :장애물"));
	TextOut(getMemDC(), 15, 155, "5 :초기화", strlen("5 :초기화"));

	char str[128];
	if (_astarState == ASTAR_STATE_END)sprintf_s(str, "스페이스 눌러");
	else if (_astarState == ASTAR_STATE_FOUND)sprintf_s(str, "찾음");
	else if (_astarState == ASTAR_STATE_NOWAY)sprintf_s(str, "길없음");
	else if (_astarState == ASTAR_STATE_SEARCHING)sprintf_s(str, "찾는중....");

	TextOut(getMemDC(), 15, 200, str, strlen(str));
	
	newFont = CreateFont(9, 0, 0, 0, FW_NORMAL, false, false, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, "굴림");
	oldFont = (HFONT)SelectObject(getMemDC(), newFont);

	for (int i = 0; i < TILE_Y; i++)
	{
		for (int j = 0; j < TILE_X; j++)
		{
			newBrush = CreateSolidBrush(_tile[i][j].color);
			oldBrush = (HBRUSH)SelectObject(getMemDC(), newBrush);
			RectangleMake(getMemDC(), _tile[i][j].rc);
			SelectObject(getMemDC(), oldBrush);
			DeleteObject(newBrush);

			if (_tile[i][j].parent == NULL)continue;
		}
	}
	SelectObject(getMemDC(), oldFont);
	DeleteObject(newFont);

	for (int i = 0; i < 5; i++)
	{
		if (i == 0)
		{
			BeginSolidColor(getMemDC(), &newBrush, RGB(0, 255, 0));
			RectangleMake(getMemDC(), rc[i]);
			sprintf_s(str, "시작점");
			DeleteObject(newBrush);
		}
		if (i == 1)
		{
			BeginSolidColor(getMemDC(), &newBrush, RGB(255, 0, 0));
			RectangleMake(getMemDC(), rc[i]);
			sprintf_s(str, "도착");
			DeleteObject(newBrush);
		}
		if (i == 2)
		{
			BeginSolidColor(getMemDC(), &newBrush, RGB(220, 255, 220));
			RectangleMake(getMemDC(), rc[i]);
			sprintf_s(str, "openList");
			DeleteObject(newBrush);
		}
		if (i == 3)
		{
			BeginSolidColor(getMemDC(), &newBrush, RGB(255, 0, 255));
			RectangleMake(getMemDC(), rc[i]);
			sprintf_s(str, "closeList");
			DeleteObject(newBrush);
		}
		if (i == 4)
		{
			BeginSolidColor(getMemDC(), &newBrush, RGB(255, 100, 100));
			RectangleMake(getMemDC(), rc[i]);
			sprintf_s(str, "path");
			DeleteObject(newBrush);
		}
		TextOut(getMemDC(), rc[i].right+ 15, rc[i].top + 5, str, strlen(str));
	}
}

void aStar::tileComposition()
{
	//비어있을때
	if (KEYMANAGER->isOnceKeyDown('1'))
	{
		_selectType = TILE_TYPE_EMPTY;
		_selectedTypeColor = RGB(255, 255, 255);
	}
	//스타트일때
	else if (KEYMANAGER->isOnceKeyDown('2'))
	{
		_selectType = TILE_TYPE_START;
		_selectedTypeColor = RGB(100, 255, 100);
	}
	//엔드일때
	else if (KEYMANAGER->isOnceKeyDown('3'))
	{
		_selectType = TILE_TYPE_END;
		_selectedTypeColor = RGB(255, 0, 0);
	}
	//장애물일때
	else if (KEYMANAGER->isOnceKeyDown('4'))
	{
		_selectType = TILE_TYPE_WALL;
		_selectedTypeColor = RGB(255, 255, 0);
	}
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < TILE_Y; i++)
		{
			for (int j = 0; j < TILE_X; j++)
			{
				if (PtInRect(&_tile[i][j].rc, m_ptMouse))
				{
					if (_tile[i][j].type == TILE_TYPE_START)_startPointSet = false;
					if (_tile[i][j].type == TILE_TYPE_END)_endPointSet = false;


					_tile[i][j].type = _selectType;
					_tile[i][j].color = _selectedTypeColor;

					if (_selectType == TILE_TYPE_START)
					{
						if (_startPointSet)
						{
							_tile[_startY][_startX].color = RGB(255, 255, 255);
							_tile[_startY][_startX].type = TILE_TYPE_EMPTY;
						}
						_startPointSet = true;
						_startX = j;
						_startY = i;
					}
					if (_selectType == TILE_TYPE_END)
					{
						if (_endPointSet)
						{
							_tile[_endY][_endX].color = RGB(255, 255, 255);
							_tile[_endY][_endX].type = TILE_TYPE_EMPTY;
						}
						_endPointSet = true;
						_endX = j;
						_endY = i;
					}
				}
			}
		}
	}
}

void aStar::tileInitializing()
{
	for (int i = 0; i < TILE_Y; i++)
	{
		for (int j = 0; j < TILE_X; j++)
		{
			if (_tile[i][j].type == TILE_TYPE_EMPTY)
			{
				_tile[i][j].walkable = true;
				_tile[i][j].listOn = false;
			}
			else if (_tile[i][j].type == TILE_TYPE_WALL)
			{
				_tile[i][j].walkable = false;
				_tile[i][j].listOn = false;
			}
			else if (_tile[i][j].type == TILE_TYPE_START)
			{
				_tile[i][j].walkable = true;
				_tile[i][j].listOn = true;

				_closeList.push_back(&_tile[i][j]);
			}
			else if (_tile[i][j].type == TILE_TYPE_END)
			{
				_endX = j;
				_endY = i;
				_tile[i][j].walkable = true;
				_tile[i][j].listOn = false;
			}
		}
	}
	_astarState = ASTAR_STATE_SEARCHING;
	_lastIndex = 0;
}

void aStar::addOpenList()
{
	Ci = _closeList[_lastIndex]->i;//마지막으로 추가된 클로즈리스트 i
	Cj = _closeList[_lastIndex]->j;
	Cg = _closeList[_lastIndex]->G;

	if (Ci != 0)//0번째 줄이 아니면 상단라인계산
	{
		if (_tile[Ci - 1][Cj].walkable)//상단 가운데 타일이 지나갈수 있다면
		{
			if (!_tile[Ci - 1][Cj].listOn)//오픈리스트에 포함이 안되어 있는 타일이라면
			{
				_tile[Ci - 1][Cj].listOn = true;//오픈리스트에 포함되었다
				_tile[Ci - 1][Cj].color = RGB(220, 255, 220);
				_tile[Ci - 1][Cj].G = Cg + 10;	//타일의 G값을 클로즈 리트의 누적 G+10
				_tile[Ci - 1][Cj].parent = _closeList[_lastIndex];//타일의 부모를 클로즈 리스트의 마지막으로 추가
				_openList.push_back(&_tile[Ci - 1][Cj]);//오픈리스트에 추가
			}
			else//오픈리스트에 포함이 되어 있던 타일이라면
			{
				if (Cg + 10 < _tile[Ci - 1][Cj].G)//기존G값보다 새로 계산한 G값이 작다면
				{
					_tile[Ci - 1][Cj].G = Cg + 10;//G값 새롭게 계산
					_tile[Ci - 1][Cj].parent = _closeList[_lastIndex];
				}
			}
		}
		if (Cj != 0)//좌상단 :0번째 열이 아니라면
		{
			//좌상단 타일의 왼쪽이나 아래에 벽이 없다면
			if (_tile[Ci - 1][Cj - 1].walkable && _tile[Ci][Cj].walkable && _tile[Ci][Cj - 1].walkable)
			{
				if (!_tile[Ci - 1][Cj - 1].walkable)
				{
					_tile[Ci - 1][Cj - 1].listOn = true;
					_tile[Ci - 1][Cj - 1].color = RGB(220, 255, 220);
					_tile[Ci - 1][Cj - 1].G = Cg + 14;//대각선이므로
					_tile[Ci - 1][Cj - 1].parent = _closeList[_lastIndex];
					_openList.push_back(&_tile[Ci - 1][Cj - 1]);
				}
				else
				{
					if (Cg + 14 < _tile[Ci - 1][Cj - 1].G)
					{
						_tile[Ci - 1][Cj - 1].G = Cg + 14;
						_tile[Ci - 1][Cj - 1].parent = _closeList[_lastIndex];
					}
				}
			}
		}
		if (Cj != TILE_X - 1)//우상단: 마지막열이 아니라면
		{
			//우상단 타일의 왼쪽이나 아래에 벽이 없다면
			if (_tile[Ci - 1][Cj + 1].walkable && _tile[Ci - 1][Cj].walkable&& _tile[Ci][Cj + 1].walkable)
			{
				if (!_tile[Ci - 1][Cj + 1].listOn)
				{
					_tile[Ci - 1][Cj + 1].listOn = true;
					_tile[Ci - 1][Cj + 1].color = RGB(220, 255, 220);
					_tile[Ci - 1][Cj + 1].G = Cg + 14;
					_tile[Ci - 1][Cj + 1].parent = _closeList[_lastIndex];
					_openList.push_back(&_tile[Ci - 1][Cj + 1]);
				}
				else
				{
					if (Cg + 14 < _tile[Ci - 1][Cj + 1].G)
					{
						_tile[Ci - 1][Cj + 1].G = Cg + 14;
						_tile[Ci - 1][Cj + 1].parent = _closeList[_lastIndex];
					}
				}
			}
		}
	}
	if (Cj != 0)//좌측 : 0번째 열이 아니라면
	{
		if (_tile[Ci][Cj - 1].walkable)//좌측타일이 이동가능하다면
		{
			if (!_tile[Ci][Cj - 1].listOn)
			{
				_tile[Ci][Cj - 1].listOn = true;
				_tile[Ci][Cj - 1].color = RGB(220, 255, 220);
				_tile[Ci][Cj - 1].G = Cg + 10;
				_tile[Ci][Cj - 1].parent = _closeList[_lastIndex];
				_openList.push_back(&_tile[Ci][Cj - 1]);
			}
			else
			{
				if (Cg + 10 < _tile[Ci][Cj - 1].G)
				{
					_tile[Ci][Cj - 1].G = Cg + 10;
					_tile[Ci][Cj - 1].parent = _closeList[_lastIndex];
				}
			}
		}
	}
	if (Cj != TILE_X - 1)//우측 :  마지막열이 아니라면
	{

		if (_tile[Ci][Cj + 1].walkable)//우측타일이 이동가능하다면
		{
			if (!_tile[Ci][Cj + 1].listOn)
			{
				_tile[Ci][Cj + 1].listOn = true;
				_tile[Ci][Cj + 1].color = RGB(220, 255, 220);
				_tile[Ci][Cj + 1].G = Cg + 10;
				_tile[Ci][Cj + 1].parent = _closeList[_lastIndex];
				_openList.push_back(&_tile[Ci][Cj + 1]);
			}
			else
			{
				if (Cg + 10 < _tile[Ci][Cj + 1].G)
				{
					_tile[Ci][Cj + 1].G = Cg + 10;
					_tile[Ci][Cj + 1].parent = _closeList[_lastIndex];
				}
			}
		}
	}
	if (Ci != TILE_Y - 1)//마지막행이 아니라면 하단 라인 계산
	{
		if (_tile[Ci + 1][Cj].walkable)//하단 가운데 타일이 이동가능하다면
		{
			if (!_tile[Ci + 1][Cj].listOn)
			{
				_tile[Ci + 1][Cj].listOn = true;
				_tile[Ci + 1][Cj].color = RGB(220, 255, 220);
				_tile[Ci + 1][Cj].G = Cg + 10;
				_tile[Ci + 1][Cj].parent = _closeList[_lastIndex];
				_openList.push_back(&_tile[Ci + 1][Cj]);
			}
			else
			{
				if (Cg + 10 < _tile[Ci + 1][Cj].G)
				{
					_tile[Ci + 1][Cj].G = Cg + 10;
					_tile[Ci + 1][Cj].parent = _closeList[_lastIndex];
				}
			}
		}
		if (Cj != 0)//좌하단 :  0번째 열이 아니라면
		{
			//좌하단 타일의 오른쪽이나 위에 벽이 없다면
			if (_tile[Ci + 1][Cj - 1].walkable && _tile[Ci + 1][Cj].walkable && _tile[Ci][Cj - 1].walkable)
			{
				if (!_tile[Ci + 1][Cj - 1].listOn)
				{
					_tile[Ci + 1][Cj - 1].listOn = true;
					_tile[Ci + 1][Cj - 1].color = RGB(220, 255, 220);
					_tile[Ci + 1][Cj - 1].G = Cg + 14;
					_tile[Ci + 1][Cj - 1].parent = _closeList[_lastIndex];
					_openList.push_back(&_tile[Ci + 1][Cj - 1]);
				}
				else
				{
					if (Cg + 14 < _tile[Ci + 1][Cj - 1].G)
					{
						_tile[Ci + 1][Cj - 1].G = Cg + 14;
						_tile[Ci + 1][Cj - 1].parent = _closeList[_lastIndex];
					}
				}
			}
		}
		if (Cj != TILE_X - 1)//우하단 :  마지막 열이 아니라면
		{
			//우하단 타일의 오른쪽이나 위가 이동가능하다면
			if (_tile[Ci + 1][Cj + 1].walkable && _tile[Ci + 1][Cj].walkable&& _tile[Ci][Cj + 1].walkable)
			{
				if (!_tile[Ci + 1][Cj + 1].listOn)
				{
					_tile[Ci + 1][Cj + 1].listOn = true;
					_tile[Ci + 1][Cj + 1].color = RGB(220, 255, 220);
					_tile[Ci + 1][Cj + 1].G = Cg + 14;
					_tile[Ci + 1][Cj + 1].parent = _closeList[_lastIndex];
					_openList.push_back(&_tile[Ci + 1][Cj + 1]);
				}
				else
				{
					if (Cg + 14 < _tile[Ci + 1][Cj + 1].G)
					{
						_tile[Ci + 1][Cj + 1].G = Cg + 14;
						_tile[Ci + 1][Cj + 1].parent = _closeList[_lastIndex];
					}
				}
			}
		}
	}
}

void aStar::calculateH()
{
	for (int i = 0; i < _openList.size(); i++)
	{
		int vertical = (_endX - _openList[i]->j) * 10;//가로 H값
		int horizontal = (_endY - _openList[i]->i) * 10;//세로 H값

		if (vertical < 0)vertical *= -1;//방향이 반대이면 음수부여
		if (horizontal < 0)horizontal *= -1;

		_openList[i]->H = vertical + horizontal;//총 H값 : 가로+세로 H
	}
}

void aStar::calculateF()
{
	for (int i = 0; i < _openList.size(); i++)
	{
		_openList[i]->F = _openList[i]->G + _openList[i]->H;//F값계산
	}
}

void aStar::addCloseList()
{
	if (_openList.size() == 0)//검색했는데도 openList의 사이즈가 0이면 더이상 찾을것이 없음
	{
		_astarState = ASTAR_STATE_NOWAY;//경로없다
		return;
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

	_openList[index]->color = RGB(180, 180, 255);
	_closeList.push_back(_openList[index]);
	_openList.erase(_openList.begin() + index);//오픈 리스트에 추가된 타일은 오픈리스트에서 제외
	_lastIndex++;//가장 나중에 추가된 클로즈의 인덱스
}

void aStar::checkArrive()
{
	if (_closeList[_lastIndex]->i == _endY && _closeList[_lastIndex]->j == _endX)//클로즈 리스트의 i,j가 도착지점과 같다면
	{
		_astarState = ASTAR_STATE_FOUND;
		_closeList[_lastIndex]->color = RGB(255, 100, 100);
		showWay(_closeList[_lastIndex]);
	}
}

void aStar::showWay(aStarTile * tile)
{
	if (!(tile->i == _endY && tile->j == _endX))//도착지점이 아니라면
	tile->color = RGB(255, 180, 180);
	tile = tile->parent;//타일의 부모를 참조해서showWay함수에 다시 넣는다.

	if (tile->parent == NULL)//타일의 부모가 시작지점이면 그만 끝내라
		return;
	else
		showWay(tile);//다시 호출
}
