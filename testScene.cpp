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
	return S_OK;
}

void testScene::release()
{
}

void testScene::update()
{
	PLAYER->update();
}

void testScene::render()
{
	tileRender();
	PLAYER->render(getMemDC());

	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (PLAYER->playerTile() < i)
		{
			if (_tiles[i].obj == OBJ_NONE) continue;

			IMAGEMANAGER->frameRender("맵툴벽", getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top - 25, _tiles[i].objFrameX, _tiles[i].objFrameY);
		}
	}
	PLAYER->UIrender(getMemDC());
}


void testScene::setUp()
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
}

void testScene::tileRender()
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

			if (PLAYER->playerTile() >= i)
			{
				IMAGEMANAGER->frameRender("맵툴벽", getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top - 25, _tiles[i].objFrameX, _tiles[i].objFrameY);
			}

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
}

void testScene::load()
{
	HANDLE file;
	DWORD read;
	file = CreateFile
	("save/맵2.map",			//생성할 파일또는 열 장치나 파일이름
		GENERIC_READ,		//파일이나 장치를 만들거나 열때 사용할 권한
		0,					//파일 공유 모드입력
		NULL,				//파일또는 장치를 열때 보안 및 특성
		OPEN_EXISTING,		//파일이나 장치를 열때 취할 행동
		FILE_ATTRIBUTE_NORMAL, //파일이나 장치를 열때 갖게 될 특성
		NULL);				//만들어질 파일이 갖게 될 특성 확장 특성에 대한 정보

	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);
	CloseHandle(file);
}
