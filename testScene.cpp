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
	MONSTERMANAGER->setMap(_tiles);
	//_vItem.push_back(ITEMMANAGER->addItem("�⺻��"));
	//_vItem.push_back(ITEMMANAGER->addItem("������"));
	//_vItem.push_back(ITEMMANAGER->addItem("�⺻��"));
	//_vItem[0]->setRect(_tiles[315].rc);
	//_vItem[1]->setRect(_tiles[316].rc);
	//_vItem[2]->setRect(_tiles[319].rc);
	_tiles[319].item = ITEMMANAGER->addItem("�⺻��");
	_tiles[320].item = ITEMMANAGER->addItem("������");
	_tiles[318].item = ITEMMANAGER->addItem("�⺻�ܰ�");
	_tiles[317].item = ITEMMANAGER->addItem("�谩��");

	MONSTERMANAGER->summonGreenSlime("�׸�������", _tiles[322].x, _tiles[322].y);
	MONSTERMANAGER->summonSkeleton("�׸�������", _tiles[327].x, _tiles[327].y);
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

	//for (int i = 0; i < _vItem.size(); i++)
	//{
	//	_vItem[i]->update();
	//	RECT temp;
	//	if (IntersectRect(&temp, &PLAYER->getCollisionRc(), &_vItem[i]->getRc()))
	//	{
	//		PLAYER->getInven()->addItem(ITEMMANAGER->addItem(_vItem[i]->getName()));
	//		_vItem.erase(_vItem.begin() + i);
	//		break;
	//	}
	//}

	//��¦�̴��κ�
		for (int i = 0; i < TILEX * TILEY; i++)
		{
			if (_tiles[i].terrain == TERRAIN_GROUND)
			{
				if(BEAT->getCnt() %58==0) _tiles[i].terrainFrameX += 1;
				if (_tiles[i].terrainFrameX > 1)_tiles[i].terrainFrameX = 0;
			}
			if (_tiles[i].item != NULL)
			{
				_tiles[i].item->setInven(false);
				_tiles[i].item->setRect(PointMake(_tiles[i].x,_tiles[i].y));
				_tiles[i].item->update();
			}
		}
	
}

void testScene::render()
{
	frontTileRender();
	MONSTERMANAGER->frontRender(getMemDC());

	PLAYER->render(getMemDC());

	backTileRender();
	MONSTERMANAGER->backRender(getMemDC());
	BEAT->render(getMemDC());
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

void testScene::frontTileRender()
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

			if(_tiles[i].item !=NULL && PLAYER->currentTile() >= i )_tiles[i].item->render(getMemDC());
			//if (_tiles[i].obj == OBJ_WALL) IMAGEMANAGER->frameRender("������", getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].terrainFrameX, _tiles[i].terrainFrameY);

			if (_tiles[i].obj == OBJ_NONE) continue;

			if (PLAYER->currentTile() >= i)
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
				if (PLAYER->currentTile() >= i)
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

void testScene::backTileRender()
{
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (PLAYER->currentTile() < i)
		{
			if (_tiles[i].item != NULL)_tiles[i].item->render(getMemDC());
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
				if (PLAYER->currentTile() < i)
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
	("save/��4.map",			//������ ���϶Ǵ� �� ��ġ�� �����̸�
		GENERIC_READ,		//�����̳� ��ġ�� ����ų� ���� ����� ����
		0,					//���� ���� ����Է�
		NULL,				//���϶Ǵ� ��ġ�� ���� ���� �� Ư��
		OPEN_EXISTING,		//�����̳� ��ġ�� ���� ���� �ൿ
		FILE_ATTRIBUTE_NORMAL, //�����̳� ��ġ�� ���� ���� �� Ư��
		NULL);				//������� ������ ���� �� Ư�� Ȯ�� Ư���� ���� ����

	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);
	CloseHandle(file);
}
