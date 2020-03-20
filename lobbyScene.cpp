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
	setUp();
	load();

	SOUNDMANAGER->play("lobby");
	BEAT->setBeatOn(false);

	PLAYER->setMap(_tiles);
	return S_OK;
}

void lobbyScene::release()
{
}

void lobbyScene::update()
{
	BEAT->update();
	PLAYER->update();
	groundPattern();
	next();
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

	for (int i = 0; i < TILEX; i++)
	{
		for (int k = 0; k < TILEY; k++)
		{
			if (CAMERAX - 100 < _tiles[(i*TILEX) + k].x && _tiles[(i*TILEX) + k].x < CAMERAX + WINSIZEX + 100 && CAMERAY - 100 < _tiles[(i*TILEX) + k].y&& _tiles[(i*TILEX) + k].y < CAMERAY + WINSIZEY + 100 )
			{
				if (_tiles[(i*TILEX) + k].terrain != TERRAIN_NONE && _tiles[(i*TILEX) + k].look  )IMAGEMANAGER->frameRender("��������", getMemDC(), _tiles[(i*TILEX) + k].rc.left, _tiles[(i*TILEX) + k].rc.top, _tiles[(i*TILEX) + k].terrainFrameX, _tiles[(i*TILEX) + k].terrainFrameY);

				if (_tiles[(i*TILEX) + k].obj != OBJ_NONE && _tiles[(i*TILEX) + k].look) IMAGEMANAGER->frameRender("������", getMemDC(), _tiles[(i*TILEX) + k].rc.left, _tiles[(i*TILEX) + k].rc.top - 25, _tiles[(i*TILEX) + k].objFrameX, _tiles[(i*TILEX) + k].objFrameY);
			}
		}
		if ((i*TILEX) < p  && p < ((i + 1)*TILEX))  PLAYER->render(getMemDC());
	}
}

void lobbyScene::debugRender()
{
	//if (KEYMANAGER->isToggleKey(VK_TAB))
	//{
	//	for (int i = 0; i < TILEX * TILEY; i++)
	//	{
	//		if (CAMERAX - 100 < _tiles[i].x && _tiles[i].x < CAMERAX + WINSIZEX + 100 && CAMERAY - 100 < _tiles[i].y&& _tiles[i].y < CAMERAY + WINSIZEY + 100)
	//		{
	//			SetBkMode(getMemDC(), TRANSPARENT);
	//			//����
	//			SetTextColor(getMemDC(), RGB(255, 0, 0));

	//			char str[128];
	//			sprintf_s(str, "%d", i);
	//			TextOut(getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, str, strlen(str));
	//		}
	//	}
	//}
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

void lobbyScene::groundPattern()
{
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (_tiles[i].terrain == TERRAIN_GROUND && _tiles[i].ray > 0)
		{
			if (BEAT->getCnt() % 44 == 0) _tiles[i].terrainFrameX += 1;
			if (_tiles[i].terrainFrameX > 1)_tiles[i].terrainFrameX = 0;
		}

		if (_tiles[i].ray <= 0)
		{
			_tiles[i].terrainFrameX = 0;
		}
	}
}

void lobbyScene::next()
{
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (_tiles[i].obj == OBJ_NEXT && PLAYER->currentTile() == i)
		{
			SOUNDMANAGER->stop("lobby");
			SCENEMANAGER->changeScene("�׽�Ʈ��");
		}
	}
}
