#include "stdafx.h"
#include "aStar.h"
aStar::aStar()
{
}


aStar::~aStar()
{
}


int aStar::aStarStraight(tagTile tile[], int currentIndex, int endIndex)
{
	reset(tile);

	startTile = currentIndex;
	currentTile = currentIndex;
	endTile = endIndex;

	int endX = endTile % TILEX;
	int endY = endTile / TILEX;

	while (!isFind && !noPath)
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
					{
						isFind = true;
						break;
					}

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
		if (isFind) continue;
		// not Find
		if (openList.size() == 0 || noPathCheck(tile, endIndex) || closeList.size() > 50)
		{
			noPath = true;
			continue;
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

	if (noPath) return currentIndex;

	int nextTile = endTile;
	while (tile[nextTile].node != startTile && isFind)
	{
		nextTile = tile[nextTile].node;
	}
	return nextTile;
}

int aStar::aStarTile(tagTile tile[], int currentIndex, int endIndex)
{
	reset(tile);
	
	startTile = currentIndex;
	currentTile =  currentIndex;
	endTile = endIndex;

	int endX = endTile % TILEX;
	int endY = endTile / TILEX;

	while (!isFind && !noPath)
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
					{
						isFind = true;
						break;
					}

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
		if (isFind) continue;
		// not Find
		if (openList.size() == 0 || noPathCheck(tile, endIndex) || closeList.size() > 50)
		{
			noPath = true;
			continue;
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

	if (noPath) return randomMove(currentIndex);
	int check = 0;
	int nextTile = endTile;
	while (tile[nextTile].node != startTile && isFind)
	{
		check++;
		nextTile = tile[nextTile].node;
	}
	if (check > 5) return randomMove(currentIndex);
	else return nextTile;
}

int aStar::aStarBoss(tagTile tile[], int currentIndex, int endIndex)
{
	reset(tile);

	startTile = currentIndex;
	currentTile = currentIndex;
	endTile = endIndex;

	int endX = endTile % TILEX;
	int endY = endTile / TILEX;

	while (!isFind && !noPath)
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
				if (!tile[y * TILEX + x].walkable) tempBlock[i] = false;
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
					{
						isFind = true;
						break;
					}

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
		if (isFind) continue;
		// not Find
		if (openList.size() == 0 || noPathCheck(tile, endIndex) || closeList.size() > 50)
		{
			noPath = true;
			continue;
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

	if (noPath) return randomMove(currentIndex);
	int check = 0;
	int nextTile = endTile;
	while (tile[nextTile].node != startTile && isFind)
	{
		check++;
		nextTile = tile[nextTile].node;
	}
	if (check > 5) return randomMove(currentIndex);
	else return nextTile;
}

void aStar::reset(tagTile tile[])
{
	isFind = false;
	noPath = false;
	openList.clear();
	closeList.clear();

	for (int i = 0; i < TILEX * TILEY; i++)
	{
		tile[i].parent = NULL;
		tile[i].h = 0;			//������̹Ƿ� 0
	}
}

bool aStar::noPathCheck(tagTile tile[], int endIndex)
{
	if (!tile[endIndex - 1].walkable &&
		!tile[endIndex + 1].walkable &&
		!tile[endIndex + TILEX].walkable &&
		!tile[endIndex - TILEX].walkable) return true;
	
	return false;
}

int aStar::randomMove(int currentTile)
{
	int rnd = RND->getInt(4);
	switch (rnd)
	{
	case 0:
		return currentTile - 1;
		break;
	case 1:
		return currentTile + 1;
		break;
	case 2:
		return currentTile - TILEX;
		break;
	case 3:
		return currentTile + TILEX;
		break;
	}
}

	