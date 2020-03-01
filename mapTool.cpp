#include "stdafx.h"
#include "mapTool.h"

mapTool::mapTool() {}

mapTool::~mapTool() {}

HRESULT mapTool::init()
{
	setUp();
	setSampleWindow();

	for (int i = 0; i < 12; i++)
	{
		_sampleImage[i].image = new image;
		_sampleImage[i].image->init("images/maptool/맵툴_지형.bmp", 104 * 2, 78 * 2, 4, 3, true, RGB(255, 0, 255));
	}
	_mouse = false;
	
	for (int i = 0; i < 4; i++)
	{	
		_save[i].image = IMAGEMANAGER->findImage("세이브버튼");
		_load[i].image = IMAGEMANAGER->findImage("로드버튼");
		_save[i].rc = RectMakeCenter(WINSIZEX / 2 + 300 + (i*40), WINSIZEY / 2 + 270, _save[i].image->getWidth(), _save[i].image->getHeight());
		_load[i].rc = RectMakeCenter(WINSIZEX / 2 + 300 + (i * 40), WINSIZEY / 2+300, _load[i].image->getWidth(), _load[i].image->getHeight());
	}

	_mousePoint.x = CAMERAX + m_ptMouse.x;
	_mousePoint.y = CAMERAY + m_ptMouse.y;

	_button[0].img = IMAGEMANAGER->findImage("지형버튼");
	_button[1].img = IMAGEMANAGER->findImage("벽버튼");
	_button[2].img = IMAGEMANAGER->findImage("오브젝트버튼");
	_button[3].img = IMAGEMANAGER->findImage("몬스터버튼");

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
}

void mapTool::render()
{
	//타일렌더
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (CAMERAX - 100 < _tiles[i].x && _tiles[i].x < CAMERAX + WINSIZEX + 100 && CAMERAY - 100 < _tiles[i].y&& _tiles[i].y < CAMERAY + WINSIZEY + 100)
		{
			if (_tiles[i].terrain == TERRAIN_NONE)
			{
				Rectangle(getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].rc.right, _tiles[i].rc.bottom);
			}
				
			if (_tiles[i].terrain != TERRAIN_NONE)IMAGEMANAGER->frameRender("맵툴지형", getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
			
			//if (_tiles[i].obj == OBJ_WALL) IMAGEMANAGER->frameRender("맵툴벽", getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].terrainFrameX, _tiles[i].terrainFrameY);


			if (_tiles[i].obj == OBJ_NONE) continue;

			IMAGEMANAGER->frameRender("맵툴벽", getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top-25, _tiles[i].objFrameX, _tiles[i].objFrameY);
		}
	}

	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		for (int i = 0; i < TILEX * TILEY; i++)
		{
			if (CAMERAX - 100 < _tiles[i].x && _tiles[i].x < CAMERAX + WINSIZEX + 100 && CAMERAY - 100 < _tiles[i].y&& _tiles[i].y < CAMERAY + WINSIZEY + 100)
			{
	
				SetBkMode(getMemDC(), TRANSPARENT);
				//색상
				SetTextColor(getMemDC(), RGB(255, 0, 0));

				char str[128];
				sprintf_s(str, "%d", i);
				TextOut(getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, str, strlen(str));
		
			}
		}
	}

	//셈플북
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
		for (int i = 0; i < 12; i++)
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

//세이브
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
			wsprintf(save, "save/맵%d.map", arrNum + 1);


			file = CreateFile
			(save,				//생성할 파일또는 열 장치나 파일이름
				GENERIC_WRITE,			//파일이나 장치를 만들거나 열때 사용할 권한
				0,						//파일 공유 모드입력
				NULL,					//파일또는 장치를 열때 보안 및 특성
				CREATE_ALWAYS,			//파일이나 장치를 열때 취할 행동
				FILE_ATTRIBUTE_NORMAL,  //파일이나 장치를 열때 갖게 될 특성
				NULL);					//만들어질 파일이 갖게 될 특성 확장 특성에 대한 정보

			WriteFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &write, NULL);
			CloseHandle(file);
		}
	}
}

//로드
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
			wsprintf(save, "save/맵%d.map", arrNum + 1);

			file = CreateFile
			(save,			//생성할 파일또는 열 장치나 파일이름
				GENERIC_READ,		//파일이나 장치를 만들거나 열때 사용할 권한
				0,					//파일 공유 모드입력
				NULL,				//파일또는 장치를 열때 보안 및 특성
				OPEN_EXISTING,		//파일이나 장치를 열때 취할 행동
				FILE_ATTRIBUTE_NORMAL, //파일이나 장치를 열때 갖게 될 특성
				NULL);				//만들어질 파일이 갖게 될 특성 확장 특성에 대한 정보

			ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);
			CloseHandle(file);
		}
	}

}

//카메라 이동
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

//타일 셋업
void mapTool::setUp()
{
	//타일 셋팅
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

//타일 초기 설정
void mapTool::mapInit()
{
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		// 지형 초기설정
		_tiles[i].terrain = TERRAIN_NONE;

		_tiles[i].terrainFrameX = 0;
		_tiles[i].terrainFrameY = 0;

		//오브젝트 초기 설정
		_tiles[i].obj = OBJ_NONE;

		_tiles[i].objFrameX = 0;
		_tiles[i].objFrameY = 0;

		//강도
		_tiles[i].strength = 0;
	}
}


//=================================================================================
//
//				샘					플						북	
//
//=================================================================================

//샘플북 설정
void mapTool::setSampleWindow()
{
	_sampleWindow.open = false;
	_sampleWindow.img = IMAGEMANAGER->findImage("샘플창");
	_sampleWindow.x = WINSIZEX - _sampleWindow.img->getWidth() / 2;
	_sampleWindow.y = WINSIZEY / 2 + 50;
	_sampleWindow.rc = RectMakeCenter(_sampleWindow.x, _sampleWindow.y, _sampleWindow.img->getWidth(), _sampleWindow.img->getHeight());
}
//샘플북 클릭으로 조종
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
//샘플북 키조종
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
		_page = PAGE_WALL;
		pageControl();
	}
	if (KEYMANAGER->isOnceKeyDown('3') || (PtInRect(&_button[2].rc, m_ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON)))
	{
		_page = PAGE_OBJ;
		pageControl();
	}
	if (KEYMANAGER->isOnceKeyDown('4') || (PtInRect(&_button[3].rc, m_ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON)))
	{
		_page = PAGE_MONSTER;
		pageControl();
	}
}
//샘플북 버튼 설정
void mapTool::setSampleWindowBottun()
{
	//버튼 설정
	if (_sampleWindow.open)
	{
		for (int i = 0; i < 4; i++)
		{
			_button[i].x = _sampleWindow.rc.left + (i*_button[i].img->getWidth());
			_button[i].y = _sampleWindow.rc.top;
			_button[i].rc = RectMakeCenter(_button[i].x + 40, _button[i].y, _button[i].img->getWidth(), _button[i].img->getHeight());
		}

		//현재 페이지인 녀석 약간 위로 올려줌
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


		_sampleWindow.button[0].img = IMAGEMANAGER->findImage("닫기");
		_sampleWindow.button[0].x = _sampleWindow.rc.right - _sampleWindow.button[0].img->getWidth()/2;
		_sampleWindow.button[0].y = _sampleWindow.rc.top + _sampleWindow.button[0].img->getHeight()/2;
		_sampleWindow.button[0].rc = RectMakeCenter(_sampleWindow.button[0].x, _sampleWindow.button[0].y, _sampleWindow.button[0].img->getWidth(), _sampleWindow.button[0].img->getHeight());

		_sampleWindow.button[1].img = IMAGEMANAGER->findImage("뒤로");
		_sampleWindow.button[1].x = _sampleWindow.rc.left + _sampleWindow.button[1].img->getWidth()-20;
		_sampleWindow.button[1].y = _sampleWindow.rc.bottom - _sampleWindow.button[1].img->getHeight() +20;
		_sampleWindow.button[1].rc = RectMakeCenter(_sampleWindow.button[1].x, _sampleWindow.button[1].y, _sampleWindow.button[1].img->getWidth(), _sampleWindow.button[1].img->getHeight());

		_sampleWindow.button[2].img = IMAGEMANAGER->findImage("앞으로");
		_sampleWindow.button[2].x = _sampleWindow.rc.right - _sampleWindow.button[2].img->getWidth()+20;
		_sampleWindow.button[2].y = _sampleWindow.rc.bottom - _sampleWindow.button[2].img->getHeight() + 20 ;
		_sampleWindow.button[2].rc = RectMakeCenter(_sampleWindow.button[2].x, _sampleWindow.button[2].y, _sampleWindow.button[2].img->getWidth(), _sampleWindow.button[2].img->getHeight());
		
		setSamplePage();
		sampleSetRc();
		
	}
}

//샘플을 뿌려줄 렉트
void mapTool::sampleSetRc()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			_sampleImage[i].rc = RectMakeCenter((_sampleWindow.rc.left + 50) + i * 70, _sampleWindow.rc.top + 150, _sampleImage[j].image->getFrameWidth(), _sampleImage[j].image->getFrameHeight());
			_sampleImage[i + 4].rc = RectMakeCenter((_sampleWindow.rc.left + 50) + i * 70, _sampleWindow.rc.top + 300, _sampleImage[j].image->getFrameWidth(), _sampleImage[j].image->getFrameHeight());
			_sampleImage[i + 8].rc = RectMakeCenter((_sampleWindow.rc.left + 50) + i * 70, _sampleWindow.rc.top + 450, _sampleImage[j].image->getFrameWidth(), _sampleImage[j].image->getFrameHeight());
		}
	}
}

void mapTool::setSamplePage()
{
	for (int i = 0; i < 12; i++)
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
		else
		{
			_sampleImage[i].image->setFrameX(i-8);
			_sampleImage[i].image->setFrameY(2);
		}
	}
}

//그림그리는함수
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

void mapTool::setSampleMap() //책열어서 타일클릭했을때
{
	for (int i = 0; i < 12; i++)
	{
		if (PtInRect(&_sampleImage[i].rc, m_ptMouse))
		{
			_currnetTile.x = _sampleImage[i].image->getFrameX();
			_currnetTile.y = _sampleImage[i].image->getFrameY();
			break;
		}
	}
}

//드래그부분 함수
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

void mapTool::pageControl()
{
	switch (_page)
	{
	case PAGE_TERRAIN:
		for (int i = 0; i < 12; i++)
		{
			_sampleImage[i].image = new image;
			_sampleImage[i].image->init("images/maptool/맵툴_지형.bmp", 104 * 2, 78 * 2, 4, 3, true, RGB(255, 0, 255));
		}
		break;
	case PAGE_WALL:
		for (int i = 0; i < 12; i++)
		{
			_sampleImage[i].image = new image;
			_sampleImage[i].image->init("images/maptool/맵툴_벽.bmp", 104 * 2, 117 * 2, 4, 3, true, RGB(255, 0, 255));
		}
		break;
	case PAGE_OBJ:
		break;
	case PAGE_MONSTER:
		break;
	case ERASER:
		break;
	default:
		break;
	}
}

//타일에 강도 넣기
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
