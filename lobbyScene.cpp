#include "stdafx.h"
#include "lobbyScene.h"


lobbyScene::lobbyScene()
{
}


lobbyScene::~lobbyScene()
{
}

HRESULT lobbyScene::init()
{
	SOUNDMANAGER->play("lobby");

	setUp();
	load();
	BEAT->setBeatOn(false);
	PLAYER->setMap(_tiles);
	MONSTERMANAGER->setMap(_tiles);
	return S_OK;
}

void lobbyScene::release()
{
}

void lobbyScene::update()
{
	BEAT->update();
	PLAYER->update();
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (_tiles[i].terrain == TERRAIN_GROUND)
		{
			if (BEAT->getCnt() % 44 == 0) _tiles[i].terrainFrameX += 1;
			if (_tiles[i].terrainFrameX > 1)_tiles[i].terrainFrameX = 0;
		}
		if (_tiles[i].obj == OBJ_NEXT && PLAYER->currentTile() == i)
		{
			SOUNDMANAGER->stop("lobby");
			SCENEMANAGER->changeScene("�׽�Ʈ��");
		}
	}
}

void lobbyScene::render()
{
	allRender();
	debugRender();

	PLAYER->UIrender(getMemDC());
}

void lobbyScene::allRender()
{
	int p = PLAYER->currentTile();
	vector<int> monTile;
	for (int i = 0; i < MONSTERMANAGER->getMonster().size(); i++)
	{
		monTile.push_back(MONSTERMANAGER->getMonster()[i]->currentTile());
	}

	for (int i = 0; i < TILEX; i++)
	{
		for (int k = 0; k < TILEY; k++)
		{
			if (CAMERAX - 100 < _tiles[(i*TILEX) + k].x && _tiles[(i*TILEX) + k].x < CAMERAX + WINSIZEX + 100 && CAMERAY - 100 < _tiles[(i*TILEX) + k].y&& _tiles[(i*TILEX) + k].y < CAMERAY + WINSIZEY + 100)
			{
				if (_tiles[(i*TILEX) + k].terrain != TERRAIN_NONE)IMAGEMANAGER->frameRender("��������", getMemDC(), _tiles[(i*TILEX) + k].rc.left, _tiles[(i*TILEX) + k].rc.top, _tiles[(i*TILEX) + k].terrainFrameX, _tiles[(i*TILEX) + k].terrainFrameY);

				if (_tiles[(i*TILEX) + k].item != NULL)_tiles[(i*TILEX) + k].item->render(getMemDC());

				if (_tiles[(i*TILEX) + k].obj != OBJ_NONE) IMAGEMANAGER->frameRender("������", getMemDC(), _tiles[(i*TILEX) + k].rc.left, _tiles[(i*TILEX) + k].rc.top - 25, _tiles[(i*TILEX) + k].objFrameX, _tiles[(i*TILEX) + k].objFrameY);
			}
		}
		if ((i*TILEX) < p  && p < ((i + 1)*TILEX))  PLAYER->render(getMemDC());
	}
}

void lobbyScene::debugRender()
{
}

void lobbyScene::setUp()
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

void lobbyScene::load()
{
	HANDLE file;
	DWORD read;
	file = CreateFile
	("save/��1.map",			//������ ���϶Ǵ� �� ��ġ�� �����̸�
		GENERIC_READ,		//�����̳� ��ġ�� ����ų� ���� ����� ����
		0,					//���� ���� ����Է�
		NULL,				//���϶Ǵ� ��ġ�� ���� ���� �� Ư��
		OPEN_EXISTING,		//�����̳� ��ġ�� ���� ���� �ൿ
		FILE_ATTRIBUTE_NORMAL, //�����̳� ��ġ�� ���� ���� �� Ư��
		NULL);				//������� ������ ���� �� Ư�� Ȯ�� Ư���� ���� ����

	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);
	CloseHandle(file);
}
