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
	PLAYER->getInven()->init();
	SOUNDMANAGER->init();
	setUp();
	load();

	torchInit();

	BEAT->init();
	SOUNDMANAGER->play("lobby");

	PLAYER->setMap(_tiles, "lobby");
	ITEMMANAGER->init();
	MONSTERMANAGER->init();

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
	torchUpdate();
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
				if (_tiles[(i*TILEX) + k].terrain != TERRAIN_NONE && _tiles[(i*TILEX) + k].look  )IMAGEMANAGER->frameRender("맵툴지형", getMemDC(), _tiles[(i*TILEX) + k].rc.left, _tiles[(i*TILEX) + k].rc.top, _tiles[(i*TILEX) + k].terrainFrameX, _tiles[(i*TILEX) + k].terrainFrameY);

				if (_tiles[(i*TILEX) + k].obj != OBJ_NONE && _tiles[(i*TILEX) + k].look) IMAGEMANAGER->frameRender("맵툴벽", getMemDC(), _tiles[(i*TILEX) + k].rc.left, _tiles[(i*TILEX) + k].rc.top - 25, _tiles[(i*TILEX) + k].objFrameX, _tiles[(i*TILEX) + k].objFrameY);
			}
		}
		if ((i*TILEX) < p  && p < ((i + 1)*TILEX))  PLAYER->render(getMemDC());
	}
	for (int i = 0; i < _vTorch.size(); ++i)
	{
		_vTorch[i]->render(getMemDC());
	}
}

void lobbyScene::debugRender()
{
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		//SetBkMode(getMemDC(), TRANSPARENT);
		//SetTextColor(getMemDC(), RGB(255, 0, 0));

		char str[128];
		for (int i = 0; i < TILEX * TILEY; i++)
		{
			if (_tiles[i].ray == 0)continue;

			sprintf_s(str, "%d", i);
			TextOut(getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, str, strlen(str));
			sprintf_s(str, "%d", _tiles[i].ray);
			TextOut(getMemDC(), _tiles[i].rc.left + 20, _tiles[i].rc.top + 20, str, strlen(str));
		}
	}
}

void lobbyScene::setUp()
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

void lobbyScene::load()
{
	memset(&_tiles, 0, sizeof(tagTile) * TILEX * TILEY);
	HANDLE file;
	DWORD read;
	file = CreateFile
	("save/맵1.map",			//생성할 파일또는 열 장치나 파일이름
		GENERIC_READ,		//파일이나 장치를 만들거나 열때 사용할 권한
		0,					//파일 공유 모드입력
		NULL,				//파일또는 장치를 열때 보안 및 특성
		OPEN_EXISTING,		//파일이나 장치를 열때 취할 행동
		FILE_ATTRIBUTE_NORMAL, //파일이나 장치를 열때 갖게 될 특성
		NULL);				//만들어질 파일이 갖게 될 특성 확장 특성에 대한 정보

	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);
	CloseHandle(file);
}

void lobbyScene::groundPattern()
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

void lobbyScene::next()
{
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (_tiles[i].obj == OBJ_NEXT && PLAYER->currentTile() == i)
		{
			SOUNDMANAGER->stop("lobby");
			SCENEMANAGER->changeScene("테스트신");
		}
	}

	if (KEYMANAGER->isOnceKeyDown('K'))
	{
		SOUNDMANAGER->stop("lobby");
		SCENEMANAGER->changeScene("테스트신");
	}
}

void lobbyScene::torchUpdate()
{
	for (int i = 0; i < _vTorch.size(); ++i)
	{
		_vTorch[i]->update();
	}

	for (int i = 0; i < _vTorch.size();)
	{
		if (_tiles[_vTorch[i]->getTileNum()].itemPoint != "벽횃불")
		{
			_vTorch.erase(_vTorch.begin() + i);
		}
		else ++i;
	}
}

void lobbyScene::torchInit()
{
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (_tiles[i].itemPoint == "벽횃불")
		{
			_vTorch.push_back(new wallTorch(i, _tiles));
		}
	}
}
