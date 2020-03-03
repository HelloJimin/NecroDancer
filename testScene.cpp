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
	SOUNDMANAGER->play("1-1");
	setUp();
	load();
	PLAYER->setCurrentTile(_tiles);
	_vItem.push_back(ITEMMANAGER->addItem("�⺻��"));
	_vItem.push_back(ITEMMANAGER->addItem("������"));
	_vItem.push_back(ITEMMANAGER->addItem("�⺻��"));
	_vItem[0]->setRect(_tiles[315].rc);
	_vItem[1]->setRect(_tiles[316].rc);
	_vItem[2]->setRect(_tiles[319].rc);


	return S_OK;
}

void testScene::release()
{
}

void testScene::update()
{
	PLAYER->update();

	for (int i = 0; i < _vItem.size(); i++)
	{
		_vItem[i]->update();
		RECT temp;
		if (IntersectRect(&temp, &PLAYER->getCollisionRc(), &_vItem[i]->getRc()))
		{
			PLAYER->getInven()->addItem(ITEMMANAGER->addItem(_vItem[i]->getName()));
			_vItem.erase(_vItem.begin() + i);
			break;
		}
	}
}

void testScene::render()
{
	tileRender();

	for (int i = 0; i < _vItem.size(); i++)
	{
		_vItem[i]->render(getMemDC());
	}

	PLAYER->render(getMemDC());

	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (PLAYER->playerTile() < i)
		{
			if (_tiles[i].obj == OBJ_NONE) continue;

			IMAGEMANAGER->frameRender("������", getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top - 25, _tiles[i].objFrameX, _tiles[i].objFrameY);
		}
	}
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		for (int i = 0; i < TILEX * TILEY; i++)
		{
			if (CAMERAX - 100 < _tiles[i].x && _tiles[i].x < CAMERAX + WINSIZEX + 100 && CAMERAY - 100 < _tiles[i].y&& _tiles[i].y < CAMERAY + WINSIZEY + 100)
			{
				if (PLAYER->playerTile() < i)
				{
					SetBkMode(getMemDC(), TRANSPARENT);
					//����
					SetTextColor(getMemDC(), RGB(255, 0, 0));

					char str[128];
					sprintf_s(str, "%d", i);
					TextOut(getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, str, strlen(str));
				}
			}
		}
	}
	PLAYER->UIrender(getMemDC());
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

void testScene::tileRender()
{
	//Ÿ�Ϸ���
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (CAMERAX - 100 < _tiles[i].x && _tiles[i].x < CAMERAX + WINSIZEX + 100 && CAMERAY - 100 < _tiles[i].y&& _tiles[i].y < CAMERAY + WINSIZEY + 100)
		{
			if (_tiles[i].terrain == TERRAIN_NONE)
			{
				Rectangle(getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].rc.right, _tiles[i].rc.bottom);
			}

			if (_tiles[i].terrain != TERRAIN_NONE)IMAGEMANAGER->frameRender("��������", getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].terrainFrameX, _tiles[i].terrainFrameY);

			//if (_tiles[i].obj == OBJ_WALL) IMAGEMANAGER->frameRender("������", getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].terrainFrameX, _tiles[i].terrainFrameY);

			if (_tiles[i].obj == OBJ_NONE) continue;

			if (PLAYER->playerTile() >= i)
			{
				IMAGEMANAGER->frameRender("������", getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top - 25, _tiles[i].objFrameX, _tiles[i].objFrameY);
			}

		}
	}

	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		for (int i = 0; i < TILEX * TILEY; i++)
		{
			if (CAMERAX - 100 < _tiles[i].x && _tiles[i].x < CAMERAX + WINSIZEX + 100 && CAMERAY - 100 < _tiles[i].y&& _tiles[i].y < CAMERAY + WINSIZEY + 100)
			{
				if (PLAYER->playerTile() >= i)
				{
					SetBkMode(getMemDC(), TRANSPARENT);
					//����
					SetTextColor(getMemDC(), RGB(255, 0, 0));

					char str[128];
					sprintf_s(str, "%d", i);
					TextOut(getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, str, strlen(str));

				}
			}
		}
	}
}

void testScene::load()
{
	HANDLE file;
	DWORD read;
	file = CreateFile
	("save/��2.map",			//������ ���϶Ǵ� �� ��ġ�� �����̸�
		GENERIC_READ,		//�����̳� ��ġ�� ����ų� ���� ����� ����
		0,					//���� ���� ����Է�
		NULL,				//���϶Ǵ� ��ġ�� ���� ���� �� Ư��
		OPEN_EXISTING,		//�����̳� ��ġ�� ���� ���� �ൿ
		FILE_ATTRIBUTE_NORMAL, //�����̳� ��ġ�� ���� ���� �� Ư��
		NULL);				//������� ������ ���� �� Ư�� Ȯ�� Ư���� ���� ����

	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);
	CloseHandle(file);
}
