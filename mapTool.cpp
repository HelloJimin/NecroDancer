#include "stdafx.h"
#include "mapTool.h"

mapTool::mapTool() {}

mapTool::~mapTool() {}

HRESULT mapTool::init()
{
	setUp();
	setSampleBook();

	for (int i = 0; i < 12; i++)
	{
		sampleImage[i] = new image;
		sampleImage[i]->init("images/����_����.bmp", 104 * 2, 78 * 2, 4, 3, true, RGB(255, 0, 255));
	}
	//������ 1~7 ����
	//������ 8~14 ����
	//������ 15~16 ���̺�ε�
	first = false;
	mouse = false;

	for (int i = 0; i < 4; i++)
	{	
		_save[i].image = IMAGEMANAGER->findImage("���̺��ư");
		_load[i].image = IMAGEMANAGER->findImage("�ε��ư");
		_save[i].rc = RectMakeCenter(WINSIZEX / 2 + 300 + (i*40), WINSIZEY / 2 + 270, _save[i].image->getWidth(), _save[i].image->getHeight());
		_load[i].rc = RectMakeCenter(WINSIZEX / 2 + 300 + (i * 40), WINSIZEY / 2+300, _load[i].image->getWidth(), _load[i].image->getHeight());
	}

	mousePoint.x = CAMERAX + m_ptMouse.x;
	mousePoint.y = CAMERAY + m_ptMouse.y;

	return S_OK;
}

void mapTool::relaese() {}

void mapTool::update()
{
	mousePoint.x = CAMERAX + m_ptMouse.x;
	mousePoint.y = CAMERAY + m_ptMouse.y;

	if (PtInRect(&_sampleBook.rc, mousePoint))
	{
		mouse = true;
	}
	else
	{
		mouse = false;
	}

	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		_end.x = mousePoint.x;
		_end.y = mousePoint.y;

		drage();
	}
	save();
	load();
	cameraMove();
	controlSampleBook();
}

void mapTool::render()
{
	//Ÿ��
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (CAMERAX - 100 < _tiles[i].x && _tiles[i].x < CAMERAX + WINSIZEX + 100 && CAMERAY - 100 < _tiles[i].y&& _tiles[i].y < CAMERAY + WINSIZEY + 100)
		{
			if (_tiles[i].terrain == TERRAIN_NONE)
			{
				Rectangle(getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].rc.right, _tiles[i].rc.bottom);
			}
				
			IMAGEMANAGER->frameRender("��������", getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
			
			//if (_tiles[i].obj == OBJ_WALL) IMAGEMANAGER->frameRender("������", getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].terrainFrameX, _tiles[i].terrainFrameY);


			if (_tiles[i].obj == OBJ_NONE) continue;

			IMAGEMANAGER->frameRender("������", getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top-25, _tiles[i].objFrameX, _tiles[i].objFrameY);
		}
	}


	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (CAMERAX - 100 < _tiles[i].x && _tiles[i].x < CAMERAX + WINSIZEX + 100 && CAMERAY - 100 < _tiles[i].y&& _tiles[i].y < CAMERAY + WINSIZEY + 100)
		{
			if (KEYMANAGER->isToggleKey(VK_TAB))
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

	//���ú�

	if (_sampleBook.Summons)
	{
		for (int i = 0; i < 3; i++)
		{
			_sampleBook.bottun[i].img->render(CAMERAMANAGER->getCameraDC(), _sampleBook.bottun[i].rc.left, _sampleBook.bottun[i].rc.top);
		}
		for (int i = 0; i < 4; i++)
		{
			bottun[i].img->render(CAMERAMANAGER->getCameraDC(), bottun[i].rc.left, bottun[i].rc.top-20);
		}
		_sampleBook.img->render(CAMERAMANAGER->getCameraDC(), _sampleBook.rc.left, _sampleBook.rc.top);
		for (int i = 0; i < 12; i++)
		{
			sampleImage[i]->frameRender(CAMERAMANAGER->getCameraDC(), rc[i].left, rc[i].top);
		}
		for (int i = 0; i < 4; i++)
		{
			_save[i].image->render(CAMERAMANAGER->getCameraDC(), _save[i].rc.left, _save[i].rc.top);
			_load[i].image->render(CAMERAMANAGER->getCameraDC(), _load[i].rc.left, _load[i].rc.top);
		}
	}

}

//���̺�
void mapTool::save()
{
	for (int i = 0; i < 4; i++)
	{
		if (PtInRect(&_save[i].rc, mousePoint) && KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
		{
			tileAttribute();

			HANDLE file;
			DWORD write;
			int arrNum;
			arrNum = i;
			char save[128];
			wsprintf(save, "save/��%d.map", arrNum + 1);


			file = CreateFile
			(save,				//������ ���϶Ǵ� �� ��ġ�� �����̸�
				GENERIC_WRITE,			//�����̳� ��ġ�� ����ų� ���� ����� ����
				0,						//���� ���� ����Է�
				NULL,					//���϶Ǵ� ��ġ�� ���� ���� �� Ư��
				CREATE_ALWAYS,			//�����̳� ��ġ�� ���� ���� �ൿ
				FILE_ATTRIBUTE_NORMAL,  //�����̳� ��ġ�� ���� ���� �� Ư��
				NULL);					//������� ������ ���� �� Ư�� Ȯ�� Ư���� ���� ����

			WriteFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &write, NULL);
			CloseHandle(file);
		}
	}
}

//�ε�
void mapTool::load()
{
	//for (int i = 0; i < 4; i++)
	//{
	//	if (PtInRect(&_load[i].rc, mousePoint) && KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	//	{

	//		HANDLE file;
	//		DWORD read;
	//		int arrNum;
	//		arrNum = i;
	//		char save[128];
	//		wsprintf(save, "save/��%d.map", arrNum + 1);

	//		file = CreateFile
	//		(save,			//������ ���϶Ǵ� �� ��ġ�� �����̸�
	//			GENERIC_READ,		//�����̳� ��ġ�� ����ų� ���� ����� ����
	//			0,					//���� ���� ����Է�
	//			NULL,				//���϶Ǵ� ��ġ�� ���� ���� �� Ư��
	//			OPEN_EXISTING,		//�����̳� ��ġ�� ���� ���� �ൿ
	//			FILE_ATTRIBUTE_NORMAL, //�����̳� ��ġ�� ���� ���� �� Ư��
	//			NULL);				//������� ������ ���� �� Ư�� Ȯ�� Ư���� ���� ����

	//		ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);
	//		CloseHandle(file);
	//	}
	//}

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

//ī�޶� �̵�
void mapTool::cameraMove()
{
	if (KEYMANAGER->isStayKeyDown('A') && CAMERAMANAGER->getCameraCenter().x - WINSIZEX / 2 > 0)
	{
		CAMERAMANAGER->setCameraCenter(PointMake(CAMERAMANAGER->getCameraCenter().x - 50, CAMERAMANAGER->getCameraCenter().y));
	}

	if (KEYMANAGER->isStayKeyDown('D') && CAMERAMANAGER->getCameraCenter().x + WINSIZEX / 2 < TILESIZEX)
	{
		CAMERAMANAGER->setCameraCenter(PointMake(CAMERAMANAGER->getCameraCenter().x + 50, CAMERAMANAGER->getCameraCenter().y));
	}

	if (KEYMANAGER->isStayKeyDown('W') && CAMERAMANAGER->getCameraCenter().y - WINSIZEY / 2 > 0)
	{
		CAMERAMANAGER->setCameraCenter(PointMake(CAMERAMANAGER->getCameraCenter().x, CAMERAMANAGER->getCameraCenter().y - 50));
	}

	if (KEYMANAGER->isStayKeyDown('S') && CAMERAMANAGER->getCameraCenter().y + WINSIZEY / 2 < TILESIZEY)
	{
		CAMERAMANAGER->setCameraCenter(PointMake(CAMERAMANAGER->getCameraCenter().x, CAMERAMANAGER->getCameraCenter().y + 50));
	}
}

//Ÿ�� �¾�
void mapTool::setUp()
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

	mapInit();
}

//Ÿ�� �ʱ� ����
void mapTool::mapInit()
{
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		// ���� �ʱ⼳��
		_tiles[i].terrain = TERRAIN_NONE;

		_tiles[i].terrainFrameX = 0;
		_tiles[i].terrainFrameY = 0;

		//������Ʈ �ʱ� ����
		_tiles[i].obj = OBJ_NONE;

		_tiles[i].objFrameX = 0;
		_tiles[i].objFrameY = 0;

	}
}


//=================================================================================
//
//				��					��						��	
//
//=================================================================================

//���ú� ����
void mapTool::setSampleBook()
{
	_sampleBook.Summons = false;
	_sampleBook.img = IMAGEMANAGER->findImage("�����ú�");
	_sampleBook.x = WINSIZEX - _sampleBook.img->getWidth() / 2;
	_sampleBook.y = WINSIZEY / 2;
	_sampleBook.rc = RectMakeCenter(_sampleBook.x, _sampleBook.y, _sampleBook.img->getWidth(), _sampleBook.img->getHeight());
}
//���ú� Ŭ������ ����
void mapTool::controlSampleBook()
{
	sampleBookKey();

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (mouse)
		{
			 setSampleMap();
		}
		else
		{
			setMap();

			_start.x = mousePoint.x;
			_start.y = mousePoint.y;
		}

		if (PtInRect(&_sampleBook.rc, mousePoint))
		{
			_sampleBook.Summons = true;
			//_page = PAGE_TERRAIN;
		}

		if (_sampleBook.Summons)
		{
			_sampleBook.img = IMAGEMANAGER->findImage("����â");
			_sampleBook.x = WINSIZEX - _sampleBook.img->getWidth()/2;
			_sampleBook.y = WINSIZEY / 2+50;

		}
		else
		{
			_sampleBook.img = IMAGEMANAGER->findImage("�����ú�");
			_sampleBook.x = WINSIZEX - _sampleBook.img->getWidth() / 2;
			_sampleBook.y = WINSIZEY / 2;
		}


		if (_sampleBook.Summons)	sampleBookBottunControl();
	}

	if (_sampleBook.Summons) setSampleBookBottun();

	if (!_sampleBook.Summons)
	{
		//_page = PAGE_TERRAIN;
	}


	if (KEYMANAGER->isOnceKeyDown('H')) _page = ERASER;


	_sampleBook.rc = RectMakeCenter(_sampleBook.x, _sampleBook.y, _sampleBook.img->getWidth(), _sampleBook.img->getHeight());

}
//���ú� Ű����
void mapTool::sampleBookKey()
{
	if (KEYMANAGER->isOnceKeyDown('C'))
	{
		if (_sampleBook.Summons) _sampleBook.Summons = false;
		else _sampleBook.Summons = true;

		if (_sampleBook.Summons)
		{
			_sampleBook.img = IMAGEMANAGER->findImage("����â");
			_sampleBook.x = WINSIZEX - _sampleBook.img->getWidth() / 2;
			_sampleBook.y = WINSIZEY / 2+50;
		}
		else
		{
			_sampleBook.img = IMAGEMANAGER->findImage("�����ú�");
			_sampleBook.x = WINSIZEX - _sampleBook.img->getWidth() / 2;
			_sampleBook.y = WINSIZEY / 2;
		}
	}
}
//���ú� ��ư ����
void mapTool::setSampleBookBottun()
{
	//��ư ����
	if (_sampleBook.Summons)
	{
		bottun[0].img = IMAGEMANAGER->findImage("������ư");
		bottun[1].img = IMAGEMANAGER->findImage("����ư");
		bottun[2].img = IMAGEMANAGER->findImage("������Ʈ��ư");
		bottun[3].img = IMAGEMANAGER->findImage("���͹�ư");
		for (int i = 0; i < 4; i++)
		{
			bottun[i].x = _sampleBook.rc.left + (i*bottun[i].img->getWidth());
			bottun[i].y = _sampleBook.rc.top;
			switch (_page)
			{
			case 0: bottun[0].y -= 10;
				break;
			case 1: bottun[1].y -= 10;
				break;
			case 2: bottun[2].y -= 10;
				break;
			case 3: bottun[3].y -= 10;
				break;
			}
			bottun[i].rc = RectMakeCenter(bottun[i].x + 40, bottun[i].y, bottun[i].img->getWidth(), bottun[i].img->getHeight());
		}
		_sampleBook.bottun[0].img = IMAGEMANAGER->findImage("�ݱ�");
		_sampleBook.bottun[0].x = _sampleBook.rc.right - _sampleBook.bottun[0].img->getWidth()/2;
		_sampleBook.bottun[0].y = _sampleBook.rc.top + _sampleBook.bottun[0].img->getHeight()/2;
		_sampleBook.bottun[0].rc = RectMakeCenter(_sampleBook.bottun[0].x, _sampleBook.bottun[0].y, _sampleBook.bottun[0].img->getWidth(), _sampleBook.bottun[0].img->getHeight());

		_sampleBook.bottun[1].img = IMAGEMANAGER->findImage("�ڷ�");
		_sampleBook.bottun[1].x = _sampleBook.rc.left + _sampleBook.bottun[1].img->getWidth()-20;
		_sampleBook.bottun[1].y = _sampleBook.rc.bottom - _sampleBook.bottun[1].img->getHeight() +20;
		_sampleBook.bottun[1].rc = RectMakeCenter(_sampleBook.bottun[1].x, _sampleBook.bottun[1].y, _sampleBook.bottun[1].img->getWidth(), _sampleBook.bottun[1].img->getHeight());

		_sampleBook.bottun[2].img = IMAGEMANAGER->findImage("������");
		_sampleBook.bottun[2].x = _sampleBook.rc.right - _sampleBook.bottun[2].img->getWidth()+20;
		_sampleBook.bottun[2].y = _sampleBook.rc.bottom - _sampleBook.bottun[2].img->getHeight() + 20 ;
		_sampleBook.bottun[2].rc = RectMakeCenter(_sampleBook.bottun[2].x, _sampleBook.bottun[2].y, _sampleBook.bottun[2].img->getWidth(), _sampleBook.bottun[2].img->getHeight());
		
		setPageSample();
		sampleSetRc();
		
	}
}
//���ú� ���� ��ư
void mapTool::sampleBookBottunControl()
{
	if (PtInRect(&bottun[0].rc, m_ptMouse))
	{
		_page = PAGE_TERRAIN;
		for (int i = 0; i < 12; i++)
		{
			sampleImage[i] = new image;
			sampleImage[i]->init("images/����_����.bmp", 104 * 2, 78 * 2, 4, 3, true, RGB(255, 0, 255));
		}
	}
	if (PtInRect(&bottun[1].rc, m_ptMouse))
	{
		_page = PAGE_WALL;
		for (int i = 0; i < 12; i++)
		{
			sampleImage[i] = new image;
			sampleImage[i]->init("images/����_��.bmp", 104 * 2, 117 * 2, 4, 3, true, RGB(255, 0, 255));
		}
	}
	if (PtInRect(&bottun[2].rc, m_ptMouse))
	{
		_page = PAGE_OBJ;
	}
	if (PtInRect(&bottun[3].rc, m_ptMouse))
	{
		_page = PAGE_MONSTER;
	}
}
//������ �ѷ��� ��Ʈ
void mapTool::sampleSetRc()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			rc[i] = RectMakeCenter((_sampleBook.rc.left + 50) + i * 70, _sampleBook.rc.top + 150, sampleImage[j]->getFrameWidth(), sampleImage[j]->getFrameHeight());
			rc[i + 4] = RectMakeCenter((_sampleBook.rc.left + 50) + i * 70, _sampleBook.rc.top + 300, sampleImage[j]->getFrameWidth(), sampleImage[j]->getFrameHeight());
			rc[i + 8] = RectMakeCenter((_sampleBook.rc.left + 50) + i * 70, _sampleBook.rc.top + 450, sampleImage[j]->getFrameWidth(), sampleImage[j]->getFrameHeight());
		}
	}
}

void mapTool::setPageSample()
{
	for (int i = 0; i < 12; i++)
	{
		if (i < 4)
		{
			sampleImage[i]->setFrameX(i);
			sampleImage[i]->setFrameY(0);
		}
		else if(i<8)
		{
			sampleImage[i]->setFrameX(i-4);
			sampleImage[i]->setFrameY(1);
		}
		else
		{
			sampleImage[i]->setFrameX(i-8);
			sampleImage[i]->setFrameY(2);
		}
	}
}

void mapTool::setMap()
{
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (PtInRect(&_tiles[i].rc, mousePoint))
		{
			if (_page == PAGE_TERRAIN)
			{
				_tiles[i].terrainFrameX = _currnetTile.x;
				_tiles[i].terrainFrameY = _currnetTile.y;

				 _tiles[i].terrain = terrainSelect(_currnetTile.x, _currnetTile.y);
			}
			if (_page == PAGE_WALL)
			{
				_tiles[i].objFrameX = _currnetTile.x;
				_tiles[i].objFrameY = _currnetTile.y;

				_tiles[i].obj = objSelect(_currnetTile.x, _currnetTile.y);
			}
			if (_page == ERASER)
			{
				if (_tiles[i].obj != OBJ_NONE)
				{
					_tiles[i].objFrameX = NULL;
					_tiles[i].objFrameY = NULL;

					_tiles[i].obj = OBJ_NONE;
				}
				else
				{
					_tiles[i].terrainFrameX = NULL;
					_tiles[i].terrainFrameY = NULL;

					_tiles[i].terrain = TERRAIN_NONE;
				}
			}
		}
	}
}

void mapTool::setSampleMap() //å��� Ÿ��Ŭ��������
{
	mousePoint.x = CAMERAX + m_ptMouse.x;
	mousePoint.y = CAMERAY + m_ptMouse.y;
	for (int i = 0; i < 12; i++)
	{
		if (PtInRect(&rc[i], m_ptMouse))
		{
			_currnetTile.x = sampleImage[i]->getFrameX();
			_currnetTile.y = sampleImage[i]->getFrameY();
			break;
		}
	}
}

void mapTool::drage()
{
	if (_start.x == NULL && _start.y == NULL) return;

	POINT temp;

	if (_start.x > _end.x)
	{
		temp.x = _start.x;
		_start.x = _end.x;
		_end.x = temp.x;
	}

	if (_start.y > _end.y)
	{
		temp.y = _start.y;
		_start.y = _end.y;
		_end.y = temp.y;
	}

	RECT d_rc;

	SetRect(&d_rc, _start.x, _start.y, _end.x, _end.y);

	RECT tempRc;

	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (IntersectRect(&tempRc, &d_rc, &_tiles[i].rc))
		{
			if (_page == PAGE_TERRAIN)
			{
				_tiles[i].terrainFrameX = _currnetTile.x;
				_tiles[i].terrainFrameY = _currnetTile.y;

				_tiles[i].terrain = terrainSelect(_currnetTile.x, _currnetTile.y);
			}
			else if (_page == PAGE_WALL || _page==PAGE_OBJ)
			{
				_tiles[i].objFrameX = _currnetTile.x;
				_tiles[i].objFrameY = _currnetTile.y;

				_tiles[i].obj = objSelect(_currnetTile.x, _currnetTile.y);
			}
			else if (_page == ERASER)
			{
				if (_tiles[i].obj != OBJ_NONE)
				{
					_tiles[i].objFrameX = NULL;
					_tiles[i].objFrameY = NULL;

					_tiles[i].obj = OBJ_NONE;
				}
				else
				{
					_tiles[i].terrainFrameX = NULL;
					_tiles[i].terrainFrameY = NULL;

					_tiles[i].terrain = TERRAIN_NONE;
				}
			}
		}
	}

	_start.x = NULL;
	_start.y = NULL;
	_end.x = NULL;
	_end.y = NULL;
}

void mapTool::tileRender()
{
	//Ÿ��
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (CAMERAX - 100 < _tiles[i].x && _tiles[i].x < CAMERAX + WINSIZEX + 100 && CAMERAY - 100 < _tiles[i].y&& _tiles[i].y < CAMERAY + WINSIZEY + 100)
		{
			//if (_tiles[i].terrain == TERRAIN_NONE)
			//{
			//	Rectangle(getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].rc.right, _tiles[i].rc.bottom);
			//}

			if (_tiles[i].terrain == TERRAIN_NONE) IMAGEMANAGER->frameRender("��������", getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].terrainFrameX, _tiles[i].terrainFrameY);

			//if (_tiles[i].obj == OBJ_WALL) IMAGEMANAGER->frameRender("������", getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].terrainFrameX, _tiles[i].terrainFrameY);


			if (_tiles[i].obj == OBJ_NONE) continue;

			IMAGEMANAGER->frameRender("������", getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top - 25, _tiles[i].objFrameX, _tiles[i].objFrameY);
		}
	}

	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (CAMERAX - 100 < _tiles[i].x && _tiles[i].x < CAMERAX + WINSIZEX + 100 && CAMERAY - 100 < _tiles[i].y&& _tiles[i].y < CAMERAY + WINSIZEY + 100)
		{
			if (KEYMANAGER->isToggleKey(VK_TAB))
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

void mapTool::tileAttribute()
{
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (_tiles[i].obj == OBJ_NOMALWALL) _tiles[i].strength = 1;
		else if (_tiles[i].obj == OBJ_SKULLWALL) _tiles[i].strength = 2;
		else if (_tiles[i].obj == OBJ_WHITEWALL) _tiles[i].strength = 3;
		else if (_tiles[i].obj == OBJ_IRONWALL) _tiles[i].strength = 4;
		else if (_tiles[i].obj == OBJ_GOLDWALL) _tiles[i].strength = 5;

	}
}

TERRAIN mapTool::terrainSelect(int frameX, int frameY)
{
	for (int i = 0; i < 12; i++)
	{
		if (i == 2 || i == 3) return TERRAIN_DOOR;
		return TERRAIN_GROUND;
	}

	return TERRAIN_NONE;
}

OBJECT mapTool::objSelect(int frameX, int frameY)
{
	if (frameX == 0 && frameY == 0) return OBJ_NOMALWALL;
	if (frameX == 1 && frameY == 0) return OBJ_NOMALWALL;

	if (frameX == 2 && frameY == 0) return OBJ_SKULLWALL;
	if (frameX == 3 && frameY == 0) return OBJ_SKULLWALL;

	if (frameX == 0 && frameY == 1) return OBJ_WHITEWALL;
	if (frameX == 1 && frameY == 1) return OBJ_WHITEWALL;

	if (frameX == 2 && frameY == 1) return OBJ_IRONWALL;
	if (frameX == 3 && frameY == 1) return OBJ_IRONWALL;

	if (frameX == 0 && frameY == 2) return OBJ_GOLDWALL;
	if (frameX == 1 && frameY == 2) return OBJ_GOLDWALL;

	if (frameX == 2 && frameY == 2) return OBJ_GOLDWALL;
	if (frameX == 3 && frameY == 2) return OBJ_GOLDWALL;
	
	return OBJ_NONE;
}
