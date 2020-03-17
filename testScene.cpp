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
	BEAT->setBeatOn(true);
	PLAYER->setMap(_tiles);
	MONSTERMANAGER->setMap(_tiles);
	//_vItem.push_back(ITEMMANAGER->addItem("�⺻��"));
	//_vItem.push_back(ITEMMANAGER->addItem("������"));
	//_vItem.push_back(ITEMMANAGER->addItem("�⺻��"));
	//_vItem[0]->setRect(_tiles[315].rc);
	//_vItem[1]->setRect(_tiles[316].rc);
	//_vItem[2]->setRect(_tiles[319].rc);
	_tiles[267].item = ITEMMANAGER->addItem("������");
	_tiles[268].item = ITEMMANAGER->addItem("ƼŸ���ܰ�");
	_tiles[269].item = ITEMMANAGER->addItem("ƼŸ�����");
	_tiles[270].item = ITEMMANAGER->addItem("�⺻Ȱ");
	_tiles[319].item = ITEMMANAGER->addItem("�⺻â");
	_tiles[320].item = ITEMMANAGER->addItem("�⺻ä��");
	_tiles[321].item = ITEMMANAGER->addItem("�谩��");



	//MONSTERMANAGER->summonGreenSlime("�׸�������", _tiles[322].x, _tiles[322].y);
	//MONSTERMANAGER->summonBlueSlime("��罽����", _tiles[323].x, _tiles[323].y);
	//MONSTERMANAGER->summonSkeleton("���̷���", _tiles[327].x, _tiles[327].y);
	//MONSTERMANAGER->summonGhost("�����ƮL", _tiles[582].x, _tiles[582].y);
	//MONSTERMANAGER->summonRedWraiths("���巹�̽�", _tiles[586].x, _tiles[586].y);

	//MONSTERMANAGER->summonSkeleton("���̷���", _tiles[160].x, _tiles[160].y);
	//MONSTERMANAGER->summonSkeleton("���̷���", _tiles[161].x, _tiles[161].y);
	//MONSTERMANAGER->summonSkeleton("���̷���", _tiles[162].x, _tiles[162].y);
	//MONSTERMANAGER->summonSkeleton("���̷���", _tiles[163].x, _tiles[163].y);
	//MONSTERMANAGER->summonGhost("�����ƮL", _tiles[583].x, _tiles[583].y);
	//MONSTERMANAGER->summonGhost("�����ƮL", _tiles[584].x, _tiles[584].y);
	//MONSTERMANAGER->summonGhost("�����ƮL", _tiles[586].x, _tiles[586].y);
	//MONSTERMANAGER->summonGhost("�����ƮL", _tiles[587].x, _tiles[587].y);

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
	allRender();
	debugRender();

	BEAT->render(getMemDC());

	PLAYER->UIrender(getMemDC());
}


void testScene::allRender()
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

				if (_tiles[(i*TILEX) + k].obj != OBJ_NONE) IMAGEMANAGER->frameRender("������", getMemDC(), _tiles[(i*TILEX) + k].rc.left, _tiles[(i*TILEX) + k].rc.top - 25, _tiles[(i*TILEX) + k].objFrameX, _tiles[(i*TILEX) + k].objFrameY);

				if (_tiles[(i*TILEX) + k].item != NULL)_tiles[(i*TILEX) + k].item->render(getMemDC());
			}
		}

		for (int k = 0; k < monTile.size(); k++)
		{
			if ((i*TILEX) < monTile[k] && monTile[k] < ((i + 1)*TILEX)) MONSTERMANAGER->getMonster()[k]->render(getMemDC());
		}
		if ((i*TILEX) < p  && p < ((i + 1)*TILEX))  PLAYER->render(getMemDC());
	}
}

void testScene::debugRender()
{
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		for (int i = 0; i < TILEX * TILEY; i++)
		{
			if (CAMERAX - 100 < _tiles[i].x && _tiles[i].x < CAMERAX + WINSIZEX + 100 && CAMERAY - 100 < _tiles[i].y&& _tiles[i].y < CAMERAY + WINSIZEY + 100)
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
}
