#include "stdafx.h"
#include "testScene.h"


testScene::testScene()
{
}


testScene::~testScene()
{
}

HRESULT testScene::init()
{
	setUp();
	load();

	SOUNDMANAGER->play("1-1");
	BEAT->setBeatOn(true);
	
	PLAYER->setMap(_tiles);
	MONSTERMANAGER->setMap(_tiles);
	ITEMMANAGER->setMap();
	return S_OK;
}

void testScene::release()
{
}

void testScene::update()
{
	BEAT->update();
	PLAYER->update();
	MONSTERMANAGER->update();
	ITEMMANAGER->update();
	groundPattern();
	for (int i = 0; i < _vTorch.size(); ++i)
	{
		_vTorch[i]->update();
	}
	for (int i = 0; i < _vTorch.size();)
	{
		if (_tiles[_vTorch[i]->getTileNum()].itemPoint != "��ȶ��")
		{
			_vTorch.erase(_vTorch.begin() + i);
		}
		else ++i;
	}

}

void testScene::render()
{
	allRender();

	debugRender();

	BEAT->render(getMemDC());

	PLAYER->UIrender(getMemDC());
}


void testScene::allRender()
{
	int p = PLAYER->currentTile();

	vector<int> monTile;
	vector<monster*> monster = MONSTERMANAGER->getMonster();
	for (int i = 0; i < monster.size(); i++)
	{
		monTile.push_back(monster[i]->currentTile());
	}

	vector<int> itemTile;
	vector<item*> item = ITEMMANAGER->getItemList();
	for (int i = 0; i < item.size(); i++)
	{
		itemTile.push_back(item[i]->getCurrentTile());
	}

	for (int i = 0; i < TILEX; i++)
	{
		//������Ʈ
		for (int k = 0; k < TILEY; k++)
		{
			if (CAMERAX - 100 >= _tiles[(i*TILEX) + k].x || _tiles[(i*TILEX) + k].x >= CAMERAX + WINSIZEX + 100 ||
				CAMERAY - 100 >= _tiles[(i*TILEX) + k].y || _tiles[(i*TILEX) + k].y >= CAMERAY + WINSIZEY + 100) continue;
			if (!_tiles[(i*TILEX) + k].look)continue;



			if (CAMERAX - 100 < _tiles[(i*TILEX) + k].x && _tiles[(i*TILEX) + k].x < CAMERAX + WINSIZEX + 100 && CAMERAY - 100 < _tiles[(i*TILEX) + k].y&& _tiles[(i*TILEX) + k].y < CAMERAY + WINSIZEY + 100)
			{
				if (_tiles[(i*TILEX) + k].terrain != TERRAIN_NONE && _tiles[(i*TILEX) + k].ray > 0)
				{
					IMAGEMANAGER->frameRender("��������", getMemDC(), _tiles[(i*TILEX) + k].rc.left, _tiles[(i*TILEX) + k].rc.top, _tiles[(i*TILEX) + k].terrainFrameX, _tiles[(i*TILEX) + k].terrainFrameY);
				}
				else if (_tiles[(i*TILEX) + k].terrain != TERRAIN_NONE && _tiles[(i*TILEX) + k].ray <= 0)
				{
					IMAGEMANAGER->frameRender("��������", getMemDC(), _tiles[(i*TILEX) + k].rc.left, _tiles[(i*TILEX) + k].rc.top, _tiles[(i*TILEX) + k].terrainFrameX, _tiles[(i*TILEX) + k].terrainFrameY+3);
				}
				if (_tiles[(i*TILEX) + k].obj != OBJ_NONE && _tiles[(i*TILEX) + k].ray > 0)
				{
					IMAGEMANAGER->frameRender("������", getMemDC(), _tiles[(i*TILEX) + k].rc.left, _tiles[(i*TILEX) + k].rc.top - 25, _tiles[(i*TILEX) + k].objFrameX, _tiles[(i*TILEX) + k].objFrameY);
				}
				else if (_tiles[(i*TILEX) + k].obj != OBJ_NONE && _tiles[(i*TILEX) + k].ray <= 0)
				{
					IMAGEMANAGER->frameRender("������", getMemDC(), _tiles[(i*TILEX) + k].rc.left, _tiles[(i*TILEX) + k].rc.top - 25, _tiles[(i*TILEX) + k].objFrameX, _tiles[(i*TILEX) + k].objFrameY+4);
				}
			}
		}
		//������
		for (int k = 0; k < itemTile.size(); k++)
		{
			if ((i*TILEX) < itemTile[k] && itemTile[k] < ((i + 1)*TILEX) && _tiles[itemTile[k]].look&& _tiles[itemTile[k]].ray > 0)
				item[k]->render(getMemDC());
		}
		//����
		for (int k = 0; k < monTile.size(); k++)
		{
			if ((i*TILEX) < monTile[k] && monTile[k] < ((i + 1)*TILEX) && _tiles[monTile[k]].look && _tiles[monTile[k]].ray > 0 ) monster[k]->render(getMemDC());
			if ((i*TILEX) < monTile[k] && monTile[k] < ((i + 1)*TILEX) && _tiles[monTile[k]].look && _tiles[monTile[k]].ray <= 0 ) monster[k]->silhouetteRender(getMemDC());
		}
		//�÷��̾�
		if ((i*TILEX) < p  && p < ((i + 1)*TILEX))  PLAYER->render(getMemDC());
	}

	for (int i = 0; i < _vTorch.size(); ++i)
	{
		_vTorch[i]->render(getMemDC());
	}
}

void testScene::debugRender()
{
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		for (int i = 0; i < TILEX * TILEY; i++)
		{
			if (CAMERAX - 100 >= _tiles[i].x || _tiles[i].x >= CAMERAX + WINSIZEX + 100 ||
				CAMERAY - 100 >= _tiles[i].y || _tiles[i].y >= CAMERAY + WINSIZEY + 100) continue;

			if (CAMERAX - 100 < _tiles[i].x && _tiles[i].x < CAMERAX + WINSIZEX + 100 && CAMERAY - 100 < _tiles[i].y&& _tiles[i].y < CAMERAY + WINSIZEY + 100)
			{
				SetBkMode(getMemDC(), TRANSPARENT);
				//����
				SetTextColor(getMemDC(), RGB(255, 0, 0));

				char str[128];
				sprintf_s(str, "%d", i);
				TextOut(getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, str, strlen(str));
				sprintf_s(str, "%d", _tiles[i].ray);
				TextOut(getMemDC(), _tiles[i].rc.left+20, _tiles[i].rc.top+20, str, strlen(str));
			}
		}
	}
}

void testScene::setUp()
{
	//Ÿ�� ����
	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			SetRect(&_tiles[i * TILEX + j].rc, j * TILESIZE, i * TILESIZE, j* TILESIZE + TILESIZE, i * TILESIZE + TILESIZE);
		}
	}

	for (int i = 0; i < TILEX * TILEY; i++)
	{
		_tiles[i].x = _tiles[i].rc.left + (_tiles[i].rc.right - _tiles[i].rc.left) / 2;
		_tiles[i].y = _tiles[i].rc.top + (_tiles[i].rc.bottom - _tiles[i].rc.top) / 2;
	}
}

void testScene::load()
{
	HANDLE file;
	DWORD read;
	file = CreateFile
	("save/��4.map",			//������ ���϶Ǵ� �� ��ġ�� �����̸�
		GENERIC_READ,		//�����̳� ��ġ�� ����ų� ���� ����� ����
		0,					//���� ���� ����Է�
		NULL,				//���϶Ǵ� ��ġ�� ���� ���� �� Ư��
		OPEN_EXISTING,		//�����̳� ��ġ�� ���� ���� �ൿ
		FILE_ATTRIBUTE_NORMAL, //�����̳� ��ġ�� ���� ���� �� Ư��
		NULL);				//������� ������ ���� �� Ư�� Ȯ�� Ư���� ���� ����

	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);
	CloseHandle(file);

	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (_tiles[i].itemPoint == "��ȶ��")
		{
			_vTorch.push_back(new wallTorch(i,_tiles));
		}
	}
}

void testScene::groundPattern()
{
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (_tiles[i].terrain == TERRAIN_GROUND)
		{
			if (BEAT->getCnt() % 58 == 0) _tiles[i].terrainFrameX += 1;
			if (_tiles[i].terrainFrameX > 1)_tiles[i].terrainFrameX = 0;
		}
	}
}
