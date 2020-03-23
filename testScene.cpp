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
	setUp();
	load();

	torchInit();
	trapInit();

	SOUNDMANAGER->play("1-1");
	BEAT->setBeatOn(true);
	
	PLAYER->setMap(_tiles);
	MONSTERMANAGER->setMap(_tiles);
	ITEMMANAGER->setMap();

	_hitCnt = 0;
	return S_OK;
}

void testScene::release()
{
}

void testScene::update()
{
	BEAT->update();
	torchUpdate();
	trapUpdate();
	PLAYER->update();
	MONSTERMANAGER->update();
	ITEMMANAGER->update();
	groundPattern();
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
	vector<monster*> monster = MONSTERMANAGER->getMonster();
	for (int i = 0; i < monster.size(); i++)
	{
		monTile.push_back(monster[i]->currentTile());
	}

	vector<int> itemTile;
	vector<item*> item = ITEMMANAGER->getItemList();
	for (int i = 0; i < item.size(); i++)
	{
		itemTile.push_back(item[i]->getCurrentTile());
	}

	for (int i = 0; i < TILEX; i++)
	{
		//오브젝트
		for (int k = 0; k < TILEY; k++)
		{
			if (CAMERAX - 100 >= _tiles[(i*TILEX) + k].x || _tiles[(i*TILEX) + k].x >= CAMERAX + WINSIZEX + 100 ||
				CAMERAY - 100 >= _tiles[(i*TILEX) + k].y || _tiles[(i*TILEX) + k].y >= CAMERAY + WINSIZEY + 100) continue;
			if (!_tiles[(i*TILEX) + k].look)continue;



			if (CAMERAX - 100 < _tiles[(i*TILEX) + k].x && _tiles[(i*TILEX) + k].x < CAMERAX + WINSIZEX + 100 && CAMERAY - 100 < _tiles[(i*TILEX) + k].y&& _tiles[(i*TILEX) + k].y < CAMERAY + WINSIZEY + 100)
			{
				if (_tiles[(i*TILEX) + k].terrain != TERRAIN_NONE && _tiles[(i*TILEX) + k].ray > 0)
				{
					IMAGEMANAGER->frameRender("맵툴지형", getMemDC(), _tiles[(i*TILEX) + k].rc.left, _tiles[(i*TILEX) + k].rc.top, _tiles[(i*TILEX) + k].terrainFrameX, _tiles[(i*TILEX) + k].terrainFrameY);
				}
				else if (_tiles[(i*TILEX) + k].terrain != TERRAIN_NONE && _tiles[(i*TILEX) + k].ray <= 0)
				{
					IMAGEMANAGER->frameRender("맵툴지형", getMemDC(), _tiles[(i*TILEX) + k].rc.left, _tiles[(i*TILEX) + k].rc.top, _tiles[(i*TILEX) + k].terrainFrameX, _tiles[(i*TILEX) + k].terrainFrameY+8);
				}
				if (_tiles[(i*TILEX) + k].obj != OBJ_NONE && _tiles[(i*TILEX) + k].ray > 0)
				{
					IMAGEMANAGER->frameRender("맵툴벽", getMemDC(), _tiles[(i*TILEX) + k].rc.left, _tiles[(i*TILEX) + k].rc.top - 25, _tiles[(i*TILEX) + k].objFrameX, _tiles[(i*TILEX) + k].objFrameY);
				}
				else if (_tiles[(i*TILEX) + k].obj != OBJ_NONE && _tiles[(i*TILEX) + k].ray <= 0)
				{
					IMAGEMANAGER->frameRender("맵툴벽", getMemDC(), _tiles[(i*TILEX) + k].rc.left, _tiles[(i*TILEX) + k].rc.top - 25, _tiles[(i*TILEX) + k].objFrameX, _tiles[(i*TILEX) + k].objFrameY+4);
				}
			}
		}
		//아이템
		for (int k = 0; k < itemTile.size(); k++)
		{
			if ((i*TILEX) < itemTile[k] && itemTile[k] < ((i + 1)*TILEX) && _tiles[itemTile[k]].look&& _tiles[itemTile[k]].ray > 0)
				item[k]->render(getMemDC());
		}
		//몬스터
		for (int k = 0; k < monTile.size(); k++)
		{
			if ((i*TILEX) < monTile[k] && monTile[k] < ((i + 1)*TILEX) && _tiles[monTile[k]].look && _tiles[monTile[k]].ray > 0 ) monster[k]->render(getMemDC());
			if ((i*TILEX) < monTile[k] && monTile[k] < ((i + 1)*TILEX) && _tiles[monTile[k]].look && _tiles[monTile[k]].ray <= 0 ) monster[k]->silhouetteRender(getMemDC());
		}
		//플레이어
		if ((i*TILEX) < p  && p < ((i + 1)*TILEX))  PLAYER->render(getMemDC());
	}

	for (int i = 0; i < _vTorch.size(); ++i)
	{
		_vTorch[i]->render(getMemDC());
	}

	if (PLAYER->getHit())
	{
		_hitCnt++;
		IMAGEMANAGER->alphaRender("hit", getMemDC(), CAMERAX, CAMERAY, 100);
		if (_hitCnt > 10)
		{
			PLAYER->getHit() = false;
			_hitCnt = 0;
		}
	}
}

void testScene::debugRender()
{
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		for (int i = 0; i < TILEX * TILEY; i++)
		{
			if (CAMERAX - 100 >= _tiles[i].x || _tiles[i].x >= CAMERAX + WINSIZEX + 100 ||
				CAMERAY - 100 >= _tiles[i].y || _tiles[i].y >= CAMERAY + WINSIZEY + 100) 
				continue;


			SetBkMode(getMemDC(), TRANSPARENT);
			//색상
			SetTextColor(getMemDC(), RGB(255, 0, 0));

			char str[128];
			sprintf_s(str, "%d", i);
			TextOut(getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, str, strlen(str));
			sprintf_s(str, "%d", _tiles[i].ray);
			TextOut(getMemDC(), _tiles[i].rc.left+20, _tiles[i].rc.top+20, str, strlen(str));
			
		}
	}
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

void testScene::load()
{
	HANDLE file;
	DWORD read;
	file = CreateFile
	("save/맵4.map",			//생성할 파일또는 열 장치나 파일이름
		GENERIC_READ,		//파일이나 장치를 만들거나 열때 사용할 권한
		0,					//파일 공유 모드입력
		NULL,				//파일또는 장치를 열때 보안 및 특성
		OPEN_EXISTING,		//파일이나 장치를 열때 취할 행동
		FILE_ATTRIBUTE_NORMAL, //파일이나 장치를 열때 갖게 될 특성
		NULL);				//만들어질 파일이 갖게 될 특성 확장 특성에 대한 정보

	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);
	CloseHandle(file);
}

void testScene::torchUpdate()
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

void testScene::torchInit()
{
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (_tiles[i].itemPoint == "벽횃불")
		{
			_vTorch.push_back(new wallTorch(i, _tiles));
		}
	}
}

void testScene::trapInit()
{
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (_tiles[i].obj == OBJ_LEFT || _tiles[i].obj==OBJ_RIGHT || _tiles[i].obj==OBJ_UP||
			_tiles[i].obj ==OBJ_DOWN || _tiles[i].obj == OBJ_TRAP)
		{
			_vTrap.push_back(new trap(_tiles[i].obj, i, _tiles));
		}
	}
}

void testScene::trapUpdate()
{
	for (int i = 0; i < _vTrap.size(); i++)
	{
		_vTrap[i]->update();
	}
	for (int i = 0; i < _vTrap.size();)
	{
		if (_tiles[_vTrap[i]->getTileNum()].obj==OBJ_NONE)
		{
			_vTrap.erase(_vTrap.begin() + i);
		}
		else ++i;
	}
}

void testScene::groundPattern()
{
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (_tiles[i].terrain == TERRAIN_GROUND)
		{
			if (BEAT->getCnt() % 29 == 0)
			{
				_tiles[i].terrainFrameX += 1;
				if (_tiles[i].terrainFrameX > 1)
				{
					_tiles[i].terrainFrameX = 0;
				}

				//if (!PLAYER->getFever())continue;
				//
				//_tiles[i].terrainFrameX += 1;
				//if (_tiles[i].terrainFrameX > 1)
				//{
				//	_tiles[i].terrainFrameX = 0;
				//}

				//if (_tiles[i].terrainFrameY == 0) _tiles[i].terrainFrameY = 4;
				//else _tiles[i].terrainFrameY = 0;
			}
		}
	}
}
