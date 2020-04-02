#include "stdafx.h"
#include "mapTool.h"

mapTool::mapTool() {}

mapTool::~mapTool() {}

HRESULT mapTool::init()
{
	setUp();
	setSampleWindow();

	for (int i = 0; i < 16; i++)
	{
		_sampleImage[i].image = new image;
		_sampleImage[i].image->init("images/maptool/����_����.bmp", 104 * 2, 104 * 2 * 4, 4, 4 * 4, true, RGB(255, 0, 255));
	}
	_mouse = false;
	
	for (int i = 0; i < 4; i++)
	{	
		_save[i].image = IMAGEMANAGER->findImage("���̺��ư");
		_load[i].image = IMAGEMANAGER->findImage("�ε��ư");
		_save[i].rc = RectMakeCenter(WINSIZEX / 2 + 300 + (i*40), WINSIZEY / 2 + 270, _save[i].image->getWidth(), _save[i].image->getHeight());
		_load[i].rc = RectMakeCenter(WINSIZEX / 2 + 300 + (i * 40), WINSIZEY / 2+300, _load[i].image->getWidth(), _load[i].image->getHeight());
	}

	_mousePoint.x = CAMERAX + m_ptMouse.x;
	_mousePoint.y = CAMERAY + m_ptMouse.y;

	_button[0].img = IMAGEMANAGER->findImage("������ư");
	_button[1].img = IMAGEMANAGER->findImage("����ư");
	_button[2].img = IMAGEMANAGER->findImage("������Ʈ��ư");
	_button[3].img = IMAGEMANAGER->findImage("���͹�ư");

	return S_OK;
}

void mapTool::relaese() {}

void mapTool::update()
{
	_mousePoint.x = CAMERAX + m_ptMouse.x;
	_mousePoint.y = CAMERAY + m_ptMouse.y;

	if (_sampleWindow.open && PtInRect(&_sampleWindow.rc, m_ptMouse) || PtInRect(&_button[0].rc, m_ptMouse) ||
		PtInRect(&_button[1].rc, m_ptMouse) || PtInRect(&_button[2].rc, m_ptMouse) || PtInRect(&_button[3].rc, m_ptMouse))
	{
		_mouse = true;
	}
	else
	{
		_mouse = false;
	}

	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		_end.x = _mousePoint.x;
		_end.y = _mousePoint.y;

		drage();
	}
	controlSampleWindow();
	cameraMove();

	if (KEYMANAGER->isOnceKeyDown('V'))
	{
		SCENEMANAGER->changeScene("��Ʈ�ν�");
	}
}

void mapTool::render()
{
	//Ÿ�Ϸ���
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (CAMERAX - 100 < _tiles[i].x && _tiles[i].x < CAMERAX + WINSIZEX + 100 && CAMERAY - 100 < _tiles[i].y&& _tiles[i].y < CAMERAY + WINSIZEY + 100)
		{
			if (_tiles[i].terrain == TERRAIN_NONE) Rectangle(getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].rc.right, _tiles[i].rc.bottom);
			
			if (_tiles[i].terrain != TERRAIN_NONE)IMAGEMANAGER->frameRender("��������", getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
			

			if (_tiles[i].obj != OBJ_NONE)IMAGEMANAGER->frameRender("������", getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top-25, _tiles[i].objFrameX, _tiles[i].objFrameY);
		}
	}

	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (CAMERAX - 100 < _tiles[i].x && _tiles[i].x < CAMERAX + WINSIZEX + 100 && CAMERAY - 100 < _tiles[i].y&& _tiles[i].y < CAMERAY + WINSIZEY + 100)
		{
			if (_tiles[i].startPoint == "" || _tiles[i].startPoint == "�÷��̾�")continue;
			 IMAGEMANAGER->frameRender("��������", getMemDC(), _tiles[i].rc.left - 20, _tiles[i].rc.top - 54, _tiles[i].g, _tiles[i].h);
		}
	}
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (CAMERAX - 100 < _tiles[i].x && _tiles[i].x < CAMERAX + WINSIZEX + 100 && CAMERAY - 100 < _tiles[i].y&& _tiles[i].y < CAMERAY + WINSIZEY + 100)
		{
			if (_tiles[i].startPoint == "�÷��̾�")	IMAGEMANAGER->frameRender("������Ÿ", getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].g, _tiles[i].h);

			if (_tiles[i].itemPoint != "" && _tiles[i].itemPoint != "��ȶ��" )IMAGEMANAGER->frameRender("������Ÿ", getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].g, _tiles[i].h);
			
			if (_tiles[i].itemPoint == "��ȶ��")IMAGEMANAGER->frameRender("������Ÿ", getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top-40, _tiles[i].g, _tiles[i].h);
		}
	}
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

	//���ú�
	if (_sampleWindow.open)
	{
		for (int i = 0; i < 3; i++)
		{
			_sampleWindow.button[i].img->render(CAMERAMANAGER->getCameraDC(), _sampleWindow.button[i].rc.left, _sampleWindow.button[i].rc.top);
		}
		for (int i = 0; i < 4; i++)
		{
			_button[i].img->render(CAMERAMANAGER->getCameraDC(), _button[i].rc.left, _button[i].rc.top-20);
		}
		_sampleWindow.img->render(CAMERAMANAGER->getCameraDC(), _sampleWindow.rc.left, _sampleWindow.rc.top);
		for (int i = 0; i < 16; i++)
		{
			_sampleImage[i].image->frameRender(CAMERAMANAGER->getCameraDC(), _sampleImage[i].rc.left, _sampleImage[i].rc.top);
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
		if (PtInRect(&_save[i].rc, _mousePoint) && KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
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
	for (int i = 0; i < 4; i++)
	{
		if (PtInRect(&_load[i].rc, _mousePoint) && KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
		{

			HANDLE file;
			DWORD read;
			int arrNum;
			arrNum = i;
			char save[128];
			wsprintf(save, "save/��%d.map", arrNum + 1);

			file = CreateFile
			(save,			//������ ���϶Ǵ� �� ��ġ�� �����̸�
				GENERIC_READ,		//�����̳� ��ġ�� ����ų� ���� ����� ����
				0,					//���� ���� ����Է�
				NULL,				//���϶Ǵ� ��ġ�� ���� ���� �� Ư��
				OPEN_EXISTING,		//�����̳� ��ġ�� ���� ���� �ൿ
				FILE_ATTRIBUTE_NORMAL, //�����̳� ��ġ�� ���� ���� �� Ư��
				NULL);				//������� ������ ���� �� Ư�� Ȯ�� Ư���� ���� ����

			ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);
			CloseHandle(file);
		}
	}

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

		//����
		_tiles[i].strength = 0;

		_tiles[i].parent = NULL;
		_tiles[i].walkable = true;
		_tiles[i].f = BIGNUM;
		_tiles[i].h = 0;			//������̹Ƿ� 0
		_tiles[i].g = 0;
		_tiles[i].node = 0;

		_tiles[i].startPoint = "";
		_tiles[i].itemPoint = "";
		_tiles[i].look - false;
		_tiles[i].ray = 0;
	}
}

//����â ����
void mapTool::setSampleWindow()
{
	_sampleWindow.open = false;
	_sampleWindow.img = IMAGEMANAGER->findImage("����â");
	_sampleWindow.x = WINSIZEX - _sampleWindow.img->getWidth() / 2;
	_sampleWindow.y = WINSIZEY / 2 + 50;
	_sampleWindow.rc = RectMakeCenter(_sampleWindow.x, _sampleWindow.y, _sampleWindow.img->getWidth(), _sampleWindow.img->getHeight());
}
//����â Ŭ������ ����
void mapTool::controlSampleWindow()
{
	sampleWindowKey();
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (_mouse)
		{
			 setSampleMap();
		}
		else
		{
			setMap();

			_start.x = _mousePoint.x;
			_start.y = _mousePoint.y;
		}
	}

	if (_sampleWindow.open) setSampleWindowBottun();

	if (KEYMANAGER->isOnceKeyDown('H')) _page = ERASER;

	_sampleWindow.rc = RectMakeCenter(_sampleWindow.x, _sampleWindow.y, _sampleWindow.img->getWidth(), _sampleWindow.img->getHeight());
	save();
	load();
}
//���ú� Ű����
void mapTool::sampleWindowKey()
{
	if (KEYMANAGER->isOnceKeyDown('C'))
	{
		if (_sampleWindow.open) _sampleWindow.open = false;
		else _sampleWindow.open = true;
	}
	if (KEYMANAGER->isOnceKeyDown('1') || (PtInRect(&_button[0].rc, m_ptMouse)&&KEYMANAGER->isOnceKeyDown(VK_LBUTTON)))
	{
		_page = PAGE_TERRAIN;
		pageControl();
	}
	if (KEYMANAGER->isOnceKeyDown('2') || (PtInRect(&_button[1].rc, m_ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON)))
	{
		_page = PAGE_OBJ;
		pageControl();
	}
	if (KEYMANAGER->isOnceKeyDown('3') || (PtInRect(&_button[2].rc, m_ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON)))
	{
		_page = PAGE_MONSTER;
		pageControl();
	}
	if (KEYMANAGER->isOnceKeyDown('4') || (PtInRect(&_button[3].rc, m_ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON)))
	{
		_page = PAGE_ETC;
		pageControl();
	}
}
//���ú� ��ư ����
void mapTool::setSampleWindowBottun()
{
	//��ư ����
	if (_sampleWindow.open)
	{
		for (int i = 0; i < 4; i++)
		{
			_button[i].x = _sampleWindow.rc.left + (i*_button[i].img->getWidth());
			_button[i].y = _sampleWindow.rc.top;
			_button[i].rc = RectMakeCenter(_button[i].x + 40, _button[i].y, _button[i].img->getWidth(), _button[i].img->getHeight());
		}

		//���� �������� �༮ �ణ ���� �÷���
		switch (_page)
		{
		case 0: _button[0].y -= 10;
			break;
		case 1: _button[1].y -= 10;
			break;
		case 2: _button[2].y -= 10;
			break;
		case 3: _button[3].y -= 10;
			break;
		}

		_button[_page].rc = RectMakeCenter(_button[_page].x + 40, _button[_page].y, _button[_page].img->getWidth(), _button[_page].img->getHeight());

		_sampleWindow.button[0].img = IMAGEMANAGER->findImage("�ݱ�");
		_sampleWindow.button[0].x = _sampleWindow.rc.right - _sampleWindow.button[0].img->getWidth()/2;
		_sampleWindow.button[0].y = _sampleWindow.rc.top + _sampleWindow.button[0].img->getHeight()/2;
		_sampleWindow.button[0].rc = RectMakeCenter(_sampleWindow.button[0].x, _sampleWindow.button[0].y, _sampleWindow.button[0].img->getWidth(), _sampleWindow.button[0].img->getHeight());

		_sampleWindow.button[1].img = IMAGEMANAGER->findImage("�ڷ�");
		_sampleWindow.button[1].x = _sampleWindow.rc.left + _sampleWindow.button[1].img->getWidth()-20;
		_sampleWindow.button[1].y = _sampleWindow.rc.bottom - _sampleWindow.button[1].img->getHeight() +20;
		_sampleWindow.button[1].rc = RectMakeCenter(_sampleWindow.button[1].x, _sampleWindow.button[1].y, _sampleWindow.button[1].img->getWidth(), _sampleWindow.button[1].img->getHeight());

		_sampleWindow.button[2].img = IMAGEMANAGER->findImage("������");
		_sampleWindow.button[2].x = _sampleWindow.rc.right - _sampleWindow.button[2].img->getWidth()+20;
		_sampleWindow.button[2].y = _sampleWindow.rc.bottom - _sampleWindow.button[2].img->getHeight() + 20 ;
		_sampleWindow.button[2].rc = RectMakeCenter(_sampleWindow.button[2].x, _sampleWindow.button[2].y, _sampleWindow.button[2].img->getWidth(), _sampleWindow.button[2].img->getHeight());
		
		setSamplePage();
		sampleSetRc();
		
	}
}

//������ �ѷ��� ��Ʈ
void mapTool::sampleSetRc()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			_sampleImage[i].rc = RectMakeCenter((_sampleWindow.rc.left + 50) + i * 70, _sampleWindow.rc.top + 100, _sampleImage[j].image->getFrameWidth(), _sampleImage[j].image->getFrameHeight());
			_sampleImage[i + 4].rc = RectMakeCenter((_sampleWindow.rc.left + 50) + i * 70, _sampleWindow.rc.top + 200, _sampleImage[j].image->getFrameWidth(), _sampleImage[j].image->getFrameHeight());
			_sampleImage[i + 8].rc = RectMakeCenter((_sampleWindow.rc.left + 50) + i * 70, _sampleWindow.rc.top + 300, _sampleImage[j].image->getFrameWidth(), _sampleImage[j].image->getFrameHeight());
			_sampleImage[i + 12].rc = RectMakeCenter((_sampleWindow.rc.left + 50) + i * 70, _sampleWindow.rc.top + 400, _sampleImage[j].image->getFrameWidth(), _sampleImage[j].image->getFrameHeight());
		}
	}
}

void mapTool::setSamplePage()
{
	for (int i = 0; i < 16; i++)
	{
		if (i < 4)
		{
			_sampleImage[i].image->setFrameX(i);
			_sampleImage[i].image->setFrameY(0);
		}
		else if(i<8)
		{
			_sampleImage[i].image->setFrameX(i-4);
			_sampleImage[i].image->setFrameY(1);
		}
		else if (i < 12)
		{
			_sampleImage[i].image->setFrameX(i - 8);
			_sampleImage[i].image->setFrameY(2);
		}
		else
		{
			_sampleImage[i].image->setFrameX(i-12);
			_sampleImage[i].image->setFrameY(3);
		}
	}
}

//�׸��׸����Լ�
void mapTool::setMap()
{
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (PtInRect(&_tiles[i].rc, _mousePoint))
		{
			if (_page == PAGE_TERRAIN)
			{
				_tiles[i].terrainFrameX = _currnetTile.x;
				_tiles[i].terrainFrameY = _currnetTile.y;

				_tiles[i].terrain = terrainSelect(_currnetTile.x, _currnetTile.y);
			}
			else if (_page == PAGE_OBJ)
			{
				_tiles[i].objFrameX = _currnetTile.x;
				_tiles[i].objFrameY = _currnetTile.y;

				_tiles[i].obj = objSelect(_currnetTile.x, _currnetTile.y);
			}
			else if (_page == PAGE_MONSTER)
			{
				_tiles[i].g = _currnetTile.x;
				_tiles[i].h = _currnetTile.y;
				_tiles[i].startPoint = monsterSelect(_currnetTile.x, _currnetTile.y);
			}
			else if (_page == PAGE_ETC)
			{
				_tiles[i].g = _currnetTile.x;
				_tiles[i].h = _currnetTile.y;

				if(etcSelect(_currnetTile.x, _currnetTile.y)=="�÷��̾�")_tiles[i].startPoint = etcSelect(_currnetTile.x, _currnetTile.y);
				else _tiles[i].itemPoint = etcSelect(_currnetTile.x, _currnetTile.y);
			}
			else if (_page == ERASER)
			{
				_tiles[i].terrain = TERRAIN_NONE;

				_tiles[i].terrainFrameX = 0;
				_tiles[i].terrainFrameY = 0;

				//������Ʈ �ʱ� ����
				_tiles[i].obj = OBJ_NONE;

				_tiles[i].objFrameX = 0;
				_tiles[i].objFrameY = 0;

				//����
				_tiles[i].strength = 0;

				_tiles[i].parent = NULL;
				_tiles[i].walkable = true;
				_tiles[i].f = BIGNUM;
				_tiles[i].h = 0;			//������̹Ƿ� 0
				_tiles[i].g = 0;
				_tiles[i].node = 0;

				_tiles[i].startPoint = "";
				_tiles[i].itemPoint = "";
				_tiles[i].look - false;
				_tiles[i].ray = 0;
			}
		}
	}
}

void mapTool::setSampleMap() //å��� Ÿ��Ŭ��������
{
	for (int i = 0; i < 16; i++)
	{
		if (PtInRect(&_sampleImage[i].rc, m_ptMouse))
		{
			_currnetTile.x = _sampleImage[i].image->getFrameX();
			_currnetTile.y = _sampleImage[i].image->getFrameY();
			break;
		}
	}
}

//�巡�׺κ� �Լ�
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
			else if (_page==PAGE_OBJ)
			{
				_tiles[i].objFrameX = _currnetTile.x;
				_tiles[i].objFrameY = _currnetTile.y;

				_tiles[i].obj = objSelect(_currnetTile.x, _currnetTile.y);
			}
			else if (_page == PAGE_MONSTER)
			{
				_tiles[i].g = _currnetTile.x;
				_tiles[i].h = _currnetTile.y;

				_tiles[i].startPoint = monsterSelect(_currnetTile.x, _currnetTile.y);
			}
			else if (_page == PAGE_ETC)
			{
				_tiles[i].g = _currnetTile.x;
				_tiles[i].h = _currnetTile.y;

				if (etcSelect(_currnetTile.x, _currnetTile.y) == "�÷��̾�")_tiles[i].startPoint = etcSelect(_currnetTile.x, _currnetTile.y);
				else _tiles[i].itemPoint = etcSelect(_currnetTile.x, _currnetTile.y);
			}
			else if (_page == ERASER)
			{
				_tiles[i].terrain = TERRAIN_NONE;

				_tiles[i].terrainFrameX = 0;
				_tiles[i].terrainFrameY = 0;

				//������Ʈ �ʱ� ����
				_tiles[i].obj = OBJ_NONE;

				_tiles[i].objFrameX = 0;
				_tiles[i].objFrameY = 0;

				//����
				_tiles[i].strength = 0;

				_tiles[i].parent = NULL;
				_tiles[i].walkable = true;
				_tiles[i].f = BIGNUM;
				_tiles[i].h = 0;			//������̹Ƿ� 0
				_tiles[i].g = 0;
				_tiles[i].node = 0;

				_tiles[i].startPoint = "";
				_tiles[i].itemPoint = "";
				_tiles[i].look - false;
				_tiles[i].ray = 0;
			}
		}
	}

	_start.x = NULL;
	_start.y = NULL;
	_end.x = NULL;
	_end.y = NULL;
}

void mapTool::pageControl()
{
	switch (_page)
	{
	case PAGE_TERRAIN:
		for (int i = 0; i < 16; i++)
		{
			_sampleImage[i].image = new image;
			_sampleImage[i].image->init("images/maptool/����_����.bmp", 104 * 2, 104 * 2 * 4, 4, 4 * 4, true, RGB(255, 0, 255));
		}
		break;
	case PAGE_OBJ:
		for (int i = 0; i < 16; i++)
		{
			_sampleImage[i].image = new image;
			_sampleImage[i].image->init("images/maptool/����_��.bmp", 104 * 2, 156 * 2*2, 4, 8, true, RGB(255, 0, 255));
		}
		break;
	case PAGE_MONSTER:
		for (int i = 0; i < 16; i++)
		{
			_sampleImage[i].image = new image;
			_sampleImage[i].image->init("images/maptool/����_����.bmp", 216 * 2, 204 * 2, 4, 4, true, RGB(255, 0, 255));
		}
		break;
	case PAGE_ETC:
		for (int i = 0; i < 16; i++)
		{
			_sampleImage[i].image = new image;
			_sampleImage[i].image->init("images/maptool/����_ETC.bmp", 104 * 2, 104 * 2, 4, 4, true, RGB(255, 0, 255));
		}
		break;
	case ERASER:
		break;
	}
}

//Ÿ�Ͽ� ���� �ֱ�
//Ÿ�Ͽ� ���� �ֱ�
void mapTool::tileAttribute()
{
	for (int i = 0; i < TILEX; i++)
	{
		for (int k = 0; k < TILEY; k++)
		{
			if (_tiles[(i*TILEX) + k].terrain != TERRAIN_GROUND) continue;
			
			if (i % 2 == 0) _tiles[(i*TILEX) + k].terrainFrameX = k % 2;
			else
			{
				_tiles[(i*TILEX) + k].terrainFrameX = (k+1) % 2;
			}
		}
	}
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (_tiles[i].obj == OBJ_NOMALWALL)
		{
			_tiles[i].strength = 1;
			_tiles[i].walkable = false;
		}
		else if (_tiles[i].obj == OBJ_SKULLWALL)
		{
			_tiles[i].strength = 2;
			_tiles[i].walkable = false;
		}
		else if (_tiles[i].obj == OBJ_WHITEWALL)
		{
			_tiles[i].strength = 3;
			_tiles[i].walkable = false;
		}
		else if (_tiles[i].obj == OBJ_IRONWALL)
		{
			_tiles[i].strength = 4;
			_tiles[i].walkable = false;
		}
		else if (_tiles[i].obj == OBJ_GOLDWALL)
		{
			_tiles[i].strength = 5;
			_tiles[i].walkable = false;
		}
		else if (_tiles[i].obj == OBJ_NEVERWALL)
		{
			_tiles[i].strength = 6;
			_tiles[i].walkable = false;
		}
		else if (_tiles[i].obj == OBJ_DOOR)
		{
			_tiles[i].strength = 0;
			_tiles[i].walkable = false;
		}
	}
}

TERRAIN mapTool::terrainSelect(int frameX, int frameY)
{
	if (frameX == 0 && frameY == 2) return TERRAIN_SHOP;

	for (int i = 0; i < 4; i++)
	{
		for (int k = 0; k < 4; k++)
		{
			if (frameX == i && frameY == k) return TERRAIN_GROUND;
		}
	}

	return TERRAIN_NONE;
}


OBJECT mapTool::objSelect(int frameX, int frameY)
{
	if (frameX == 0 && frameY == 0) return OBJ_NOMALWALL;
	if (frameX == 1 && frameY == 0) return OBJ_SKULLWALL;

	if (frameX == 2 && frameY == 0) return OBJ_WHITEWALL;
	if (frameX == 3 && frameY == 0) return OBJ_IRONWALL;

	if (frameX == 0 && frameY == 1) return OBJ_GOLDWALL;
	if (frameX == 1 && frameY == 1) return OBJ_NEVERWALL;

	if (frameX == 2 && frameY == 1) return OBJ_DOOR;
	if (frameX == 3 && frameY == 1) return OBJ_DOOR;

	if (frameX == 0 && frameY == 2) return OBJ_UP;
	if (frameX == 1 && frameY == 2) return OBJ_DOWN;

	if (frameX == 2 && frameY == 2) return OBJ_LEFT;
	if (frameX == 3 && frameY == 2) return OBJ_RIGHT;

	if (frameX == 0 && frameY == 3) return OBJ_TRAP;
	if (frameX == 1 && frameY == 3) return OBJ_BOMBTRAP;

	if (frameX == 2 && frameY == 3) return OBJ_BLOCK;
	if (frameX == 3 && frameY == 3) return OBJ_NEXT;
	
	return OBJ_NONE;
}

const char* mapTool::monsterSelect(int frameX, int frameY)
{
	if (frameX == 0 && frameY == 0) return "�׸�������";
	if (frameX == 1 && frameY == 0) return "��罽����";

	if (frameX == 2 && frameY == 0) return "�����ƮL";
	if (frameX == 3 && frameY == 0) return "���巹�̽�";

	if (frameX == 0 && frameY == 1) return "���̷���";
	if (frameX == 1 && frameY == 1) return "����";

	if (frameX == 2 && frameY == 1) return "����";
	if (frameX == 3 && frameY == 1) return "";

	if (frameX == 0 && frameY == 2) return "�̳�Ÿ��ν�";
	if (frameX == 1 && frameY == 2) return "����巡��";

	if (frameX == 2 && frameY == 2) return "��������";
	if (frameX == 3 && frameY == 2) return "������Ż1";

	if (frameX == 0 && frameY == 3) return "";
	if (frameX == 1 && frameY == 3) return "";

	if (frameX == 2 && frameY == 3) return "";
	if (frameX == 3 && frameY == 3) return "";

	return "";
}

const char* mapTool::etcSelect(int frameX, int frameY)
{
	if (frameX == 0 && frameY == 0)
	{
		for (int k = 0; k < TILEX * TILEY; k++)
		{
			if (_tiles[k].startPoint == "�÷��̾�") _tiles[k].startPoint = "";
		}
		return "�÷��̾�";
	}
	if (frameX == 1 && frameY == 0) return "HP����";

	if (frameX == 2 && frameY == 0) return "��ȶ��";
	if (frameX == 3 && frameY == 0) return "������ȶ��";

	if (frameX == 0 && frameY == 1) return "ƼŸ���ܰ�";
	if (frameX == 1 && frameY == 1) return "�⺻���";

	if (frameX == 2 && frameY == 1) return "ƼŸ��Ȱ";
	if (frameX == 3 && frameY == 1) return "ƼŸ��â";

	if (frameX == 0 && frameY == 2) return "ƼŸ��ä��";
	if (frameX == 1 && frameY == 2) return "ƼŸ����";

	if (frameX == 2 && frameY == 2) return "�谩��";
	if (frameX == 3 && frameY == 2) return "����";
	 
	if (frameX == 0 && frameY == 3) return "������ȭ";
	if (frameX == 1 && frameY == 3) return "�߷�����";

	if (frameX == 2 && frameY == 3) return "��ź";
	if (frameX == 3 && frameY == 3) return "ġŲ";

	return "";
}
