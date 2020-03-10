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
	return S_OK;
}

void aStar::release()
{
}

void aStar::update()
{
}

void aStar::render()
{
}

void aStar::Astar()
{
}


int aStar::aStarTile(tagTile * tile, RECT start, RECT end, int currentIndex, int endIndex)
{
	isFind = false;
	noPath = false;
	startAstar = false;
	startTile = endTile = -1;
	currentSelect = SELECT_START;
	openList.clear();
	closeList.clear();
	tiles = tile;
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		tile[i].parent = NULL;
		tile[i].walkable = true;
		tile[i].listOn = false;
		tile[i].f = BIGNUM;
		tile[i].h = 0;			//������̹Ƿ� 0
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
	startTile = currentIndex;
	endTile = endIndex;
	int currentTile =  currentIndex;
	int endX = endTile % TILEX;
	int endY = endTile / TILEX;

	while (!isFind)
	{

		int currentX = currentTile % TILEX;
		int currentY = currentTile / TILEX;
	
		// left, right, up, down
		int dx[] = { -1, 1, 0, 0 };
		int dy[] = { 0, 0, -1, 1 };
		bool tempBlock[4];
	
		// ���� ã�� �ݺ���
		for (int i = 0; i < 4; i++)
		{
			int x = currentX + dx[i];
			int y = currentY + dy[i];
			tempBlock[i] = false;
	
			// �ش� �������� ������ Ÿ���� ��ȿ�� Ÿ������ Ȯ��
			if (0 <= x && x < TILEX && 0 <= y && y < TILEY)
			{
				bool isOpen;
				// �밢�� Ÿ���� �̵� ������ (�ֺ��� ��������� ����) �ӽ÷� ��� ���� ����
				if (!tile[y * TILEX + x].walkable) tempBlock[i] = true;
				else {
					// check closeList z
					bool isClose = false;
					for (int j = 0; j < closeList.size(); j++)
					{
						if (closeList[j] == y * TILEX + x)
						{
							isClose = true;
							break;
						}
					}
					if (isClose) continue;
	
					if (i < 4)
					{
						tile[y * TILEX + x].g = 10;
					}
					else
					{
						// leftup�� ��� left�� up�� ��������� �ȵ�
						if (i == DIRECTION_LEFTUP &&
							tempBlock[DIRECTION_LEFT] || tempBlock[DIRECTION_UP]) continue;
						// rightdown�� ��� right�� down�� ��������� �ȵ�
						if (i == DIRECTION_RIGHTDOWN &&
							tempBlock[DIRECTION_RIGHT] || tempBlock[DIRECTION_DOWN]) continue;
						// rightup�� ��� right�� up�� ��������� �ȵ�
						if (i == DIRECTION_RIGHTUP &&
							tempBlock[DIRECTION_RIGHT] || tempBlock[DIRECTION_UP]) continue;
						// leftdown�� ��� left�� down�� ��������� �ȵ�
						if (i == DIRECTION_LEFTDOWN &&
							tempBlock[DIRECTION_LEFT] || tempBlock[DIRECTION_DOWN]) continue;
						tiles[y * TILEX + x].g = 14;

					}
					//abs���밪
	
					tile[y * TILEX + x].h = (abs(endX - x) + abs(endY - y)) * 10;
					tile[y * TILEX + x].f = tile[y * TILEX + x].g + tile[y * TILEX + x].h;
	
					// ���¸���Ʈ�� ������ g ��� �� �� ó��
					isOpen = false;
					for (int i = 0; i < openList.size(); i++)
					{
						if (openList[i] == y * TILEX + x)
						{
							isOpen = true;
							if (tile[openList[i]].g > tile[y * TILEX + x].g)
							{
								tile[openList[i]].h = tile[y * TILEX + x].h;
								tile[openList[i]].g = tile[y * TILEX + x].g;
								tile[openList[i]].f = tile[y * TILEX + x].f;
								tile[openList[i]].node = currentTile;
							}
						}
					}
					// ������ �׳� �ְ� �θ� ����
					if (!isOpen)
					{
						openList.push_back(y * TILEX + x);
						tile[y * TILEX + x].node = currentTile;
					}
	
					// find
					if (y * TILEX + x == endTile) 
						isFind = true;
				}
			}
		}
		
		// ���� ���� ������Ͽ��� ����
		for (iter = openList.begin(); iter != openList.end(); ++iter)
		{
			if ((*iter) == currentTile)
			{
				iter = openList.erase(iter);
				break;
			}
		}
	
		// not Find
		if (openList.size() == 0)
		{
			noPath = true;
		}
	
		// ���� Ÿ�� Ŭ�����Ʈ�� �ֱ�
		closeList.push_back(currentTile);
	
		if (openList.size() != 0)
		{
			// find minimum f cost in openList
			int min = tile[*openList.begin()].h;
			currentTile = *openList.begin();
			for (iter = openList.begin(); iter != openList.end(); ++iter)
			{
				if (min > tile[(*iter)].h)
				{
					min = tile[(*iter)].h;
					currentTile = *iter;
				}
			}
		}
	}
	int tempTile = endTile;
	while (tiles[tempTile].node != startTile && isFind)
	{
		tempTile = tiles[tempTile].node;

	}
	 return tempTile;
}

	