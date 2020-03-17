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
	//_vItem.push_back(ITEMMANAGER->addItem("기본삽"));
	//_vItem.push_back(ITEMMANAGER->addItem("유리삽"));
	//_vItem.push_back(ITEMMANAGER->addItem("기본삽"));
	//_vItem[0]->setRect(_tiles[315].rc);
	//_vItem[1]->setRect(_tiles[316].rc);
	//_vItem[2]->setRect(_tiles[319].rc);
	_tiles[267].item = ITEMMANAGER->addItem("유리삽");
	_tiles[268].item = ITEMMANAGER->addItem("티타늄단검");
	_tiles[269].item = ITEMMANAGER->addItem("티타늄대검");
	_tiles[270].item = ITEMMANAGER->addItem("기본활");
	_tiles[319].item = ITEMMANAGER->addItem("기본창");
	_tiles[320].item = ITEMMANAGER->addItem("기본채찍");
	_tiles[321].item = ITEMMANAGER->addItem("쇠갑옷");



	//MONSTERMANAGER->summonGreenSlime("그린슬라임", _tiles[322].x, _tiles[322].y);
	//MONSTERMANAGER->summonBlueSlime("블루슬라임", _tiles[323].x, _tiles[323].y);
	//MONSTERMANAGER->summonSkeleton("스켈레톤", _tiles[327].x, _tiles[327].y);
	//MONSTERMANAGER->summonGhost("투명고스트L", _tiles[582].x, _tiles[582].y);
	//MONSTERMANAGER->summonRedWraiths("레드레이스", _tiles[586].x, _tiles[586].y);

	//MONSTERMANAGER->summonSkeleton("스켈레톤", _tiles[160].x, _tiles[160].y);
	//MONSTERMANAGER->summonSkeleton("스켈레톤", _tiles[161].x, _tiles[161].y);
	//MONSTERMANAGER->summonSkeleton("스켈레톤", _tiles[162].x, _tiles[162].y);
	//MONSTERMANAGER->summonSkeleton("스켈레톤", _tiles[163].x, _tiles[163].y);
	//MONSTERMANAGER->summonGhost("투명고스트L", _tiles[583].x, _tiles[583].y);
	//MONSTERMANAGER->summonGhost("투명고스트L", _tiles[584].x, _tiles[584].y);
	//MONSTERMANAGER->summonGhost("투명고스트L", _tiles[586].x, _tiles[586].y);
	//MONSTERMANAGER->summonGhost("투명고스트L", _tiles[587].x, _tiles[587].y);

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

	//반짝이느부분
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
				if (_tiles[(i*TILEX) + k].terrain != TERRAIN_NONE)IMAGEMANAGER->frameRender("맵툴지형", getMemDC(), _tiles[(i*TILEX) + k].rc.left, _tiles[(i*TILEX) + k].rc.top, _tiles[(i*TILEX) + k].terrainFrameX, _tiles[(i*TILEX) + k].terrainFrameY);

				if (_tiles[(i*TILEX) + k].obj != OBJ_NONE) IMAGEMANAGER->frameRender("맵툴벽", getMemDC(), _tiles[(i*TILEX) + k].rc.left, _tiles[(i*TILEX) + k].rc.top - 25, _tiles[(i*TILEX) + k].objFrameX, _tiles[(i*TILEX) + k].objFrameY);

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
				//색상
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
