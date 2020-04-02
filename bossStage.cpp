#include "stdafx.h"
#include "bossStage.h"


bossStage::bossStage()
{
}


bossStage::~bossStage()
{
}

HRESULT bossStage::init()
{
	memset(&_tiles, 0, sizeof(tagTile) * TILEX * TILEY);

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

	for (int i = 97; i < 100; i++)
	{
		for (int k = 0; k < 4; k++)
		{
			_tiles[i + (k*TILEX)].walkable = false;
		}
	}


	string map = "boss";
	SOUNDMANAGER->play(map);
	SOUNDMANAGER->play("deathmetal_welcome");
	BEAT->setMap(map);

	PLAYER->setMap(_tiles, map);
	MONSTERMANAGER->setMap(_tiles);
	ITEMMANAGER->setMap();

	torchInit();
	trapInit();
	_close = false;

	for (int i = 0; i < TILEX*TILEY; i++)
	{
		if (_tiles[i].terrain == TERRAIN_NONE)continue;
		_tiles[i].terrainFrameX += 2;
		_tiles[i].terrainFrameY += 1;
		
	}
	return S_OK;
}

void bossStage::release()
{
}

void bossStage::update()
{
	BEAT->update();
	PLAYER->update();
	MONSTERMANAGER->update();

	ITEMMANAGER->update();

	groundPattern();

	torchUpdate();
	trapUpdate();

	addBomb();
	bombUpdate();
	close();
	doorUpdate();
}

void bossStage::render()
{
	allRender();
	hitRender();
	debugRender();


	BEAT->render(getMemDC());

	PLAYER->UIrender(getMemDC());
}

void bossStage::allRender()
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
		for (int k = 0; k < TILEY; k++)
		{
			if (!_tiles[(i*TILEX) + k].look)continue;

			if (CAMERAX - 100 >= _tiles[(i*TILEX) + k].x || _tiles[(i*TILEX) + k].x >= CAMERAX + WINSIZEX + 100 ||
				CAMERAY - 100 >= _tiles[(i*TILEX) + k].y || _tiles[(i*TILEX) + k].y >= CAMERAY + WINSIZEY + 100) continue;

			//�ٴ�
			if (_tiles[(i*TILEX) + k].terrain != TERRAIN_NONE)
			{
				if (_tiles[(i*TILEX) + k].ray > 0)
				{
					IMAGEMANAGER->frameRender("��������", getMemDC(), _tiles[(i*TILEX) + k].rc.left, _tiles[(i*TILEX) + k].rc.top, _tiles[(i*TILEX) + k].terrainFrameX, _tiles[(i*TILEX) + k].terrainFrameY);

				}
				else
				{
					IMAGEMANAGER->frameRender("��������", getMemDC(), _tiles[(i*TILEX) + k].rc.left, _tiles[(i*TILEX) + k].rc.top, _tiles[(i*TILEX) + k].terrainFrameX, _tiles[(i*TILEX) + k].terrainFrameY + 8);
				}
			}

			//����
			for (int z = 0; z < _vTrap.size(); ++z)
			{
				if (_vTrap[z]->getTileNum() == (i*TILEX) + k)
				{
					_vTrap[z]->render(getMemDC());
				}
			}

			//��ź
			for (int z = 0; z < _vBomb.size(); ++z)
			{
				if (_vBomb[z]->getTileNum() == (i*TILEX) + k)
				{
					_vBomb[z]->render(getMemDC());
				}
			}

			//��
			if (isWall((i*TILEX) + k))
			{
				if (_tiles[(i*TILEX) + k].ray > 0)
				{
					IMAGEMANAGER->frameRender("������", getMemDC(), _tiles[(i*TILEX) + k].rc.left, _tiles[(i*TILEX) + k].rc.top - 25, _tiles[(i*TILEX) + k].objFrameX, _tiles[(i*TILEX) + k].objFrameY);
				}
				else
				{
					IMAGEMANAGER->frameRender("������", getMemDC(), _tiles[(i*TILEX) + k].rc.left, _tiles[(i*TILEX) + k].rc.top - 25, _tiles[(i*TILEX) + k].objFrameX, _tiles[(i*TILEX) + k].objFrameY + 4);
				}
			}
		}

		//������
		for (int k = 0; k < itemTile.size(); k++)
		{
			if ((i*TILEX) < itemTile[k] && itemTile[k] < ((i + 1)*TILEX) && _tiles[itemTile[k]].look&& _tiles[itemTile[k]].ray > 0)
				item[k]->render(getMemDC());
		}

		//����
		for (int k = 0; k < monTile.size(); k++)
		{
			if ((i*TILEX) < monTile[k] && monTile[k] < ((i + 1)*TILEX) && _tiles[monTile[k]].look && _tiles[monTile[k]].ray > 0) monster[k]->render(getMemDC());
			if ((i*TILEX) < monTile[k] && monTile[k] < ((i + 1)*TILEX) && _tiles[monTile[k]].look && _tiles[monTile[k]].ray <= 0) monster[k]->silhouetteRender(getMemDC());
		}

		//�÷��̾�
		if ((i*TILEX) < p  && p < ((i + 1)*TILEX))  PLAYER->render(getMemDC());
	}

	//ȶ��
	for (int i = 0; i < _vTorch.size(); ++i)
	{
		_vTorch[i]->render(getMemDC());
	}
}

void bossStage::debugRender()
{
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
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

void bossStage::hitRender()
{
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

void bossStage::close()
{
	if (_close) return;
	if (PLAYER->currentTile() < 737)
	{
		SOUNDMANAGER->play("bossStart");
		_close = true;
		for (int i = 737; i < 740; ++i)
		{
			_tiles[i].obj = OBJ_IRONWALL;
			_tiles[i].strength = 5;
			_tiles[i].objFrameX = 3;
			_tiles[i].objFrameY = 0;
		}

		for (int i = 0; i < TILEX*TILEY; ++i)
		{
			if (_tiles[i].terrain != TERRAIN_GROUND) _tiles[i].walkable = false;
			if (_tiles[i].obj == OBJ_IRONWALL) _tiles[i].walkable = false;
			
			if (i >= 737)
			{
				_tiles[i].ray = 0;
				_tiles[i].look = false;
				_tiles[i].walkable = false;
			}
		}
	}
}


void bossStage::torchInit()
{
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (_tiles[i].itemPoint == "��ȶ��")
		{
			_vTorch.push_back(new wallTorch(i, _tiles));
		}
	}
}

void bossStage::torchUpdate()
{
	for (int i = 0; i < _vTorch.size(); ++i)
	{
		_vTorch[i]->update();
	}
	for (int i = 0; i < _vTorch.size();)
	{
		if (_tiles[_vTorch[i]->getTileNum()].itemPoint != "��ȶ��")
		{
			_vTorch.erase(_vTorch.begin() + i);
		}
		else ++i;
	}
}

void bossStage::trapInit()
{
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (_tiles[i].obj == OBJ_LEFT || _tiles[i].obj == OBJ_RIGHT || _tiles[i].obj == OBJ_UP ||
			_tiles[i].obj == OBJ_DOWN || _tiles[i].obj == OBJ_TRAP || _tiles[i].obj == OBJ_BOMBTRAP)
		{
			_vTrap.push_back(new trap(_tiles[i].obj, i, _tiles));
		}
	}
}

void bossStage::trapUpdate()
{
	for (int i = 0; i < _vTrap.size(); i++)
	{
		_vTrap[i]->update();
	}
	for (int i = 0; i < _vTrap.size();)
	{
		if (_tiles[_vTrap[i]->getTileNum()].obj == OBJ_NONE)
		{
			_vTrap.erase(_vTrap.begin() + i);
		}
		else ++i;
	}
}

void bossStage::groundPattern()
{
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (_tiles[i].terrain == TERRAIN_GROUND)
		{
			if (BEAT->getCnt() % 29 == 0)
			{
				_tiles[i].terrainFrameX += 1;

				if (_tiles[i].terrainFrameX > 3)
				{
					_tiles[i].terrainFrameX = 2;
				}

				if (!PLAYER->getFever())continue;

				_tiles[i].terrainFrameX += 1;

				if (_tiles[i].terrainFrameX > 3)
				{
					_tiles[i].terrainFrameX = 2;
				}

				if (_tiles[i].terrainFrameY == 1) _tiles[i].terrainFrameY = 5;
				else _tiles[i].terrainFrameY = 1;
			}
		}
	}

}

void bossStage::addBomb()
{
	if (PLAYER->getBomb())
	{
		_vBomb.push_back(new bombExplosion(PLAYER->currentTile(), _tiles));
		PLAYER->getBomb() = false;
	}
}

void bossStage::bombUpdate()
{
	for (int i = 0; i < _vBomb.size(); ++i)
	{
		_vBomb[i]->update();
	}

	for (int i = 0; i < _vBomb.size();)
	{
		if (_vBomb[i]->getTrigger())
		{
			_vBomb.erase(_vBomb.begin() + i);
		}
		else ++i;
	}
}

bool bossStage::isWall(int arrNum)
{
	if (_tiles[arrNum].obj == OBJ_NOMALWALL) return true;
	if (_tiles[arrNum].obj == OBJ_SKULLWALL) return true;
	if (_tiles[arrNum].obj == OBJ_WHITEWALL) return true;
	if (_tiles[arrNum].obj == OBJ_NEVERWALL) return true;
	if (_tiles[arrNum].obj == OBJ_GOLDWALL) return true;
	if (_tiles[arrNum].obj == OBJ_IRONWALL) return true;
	if (_tiles[arrNum].obj == OBJ_DOOR) return true;
	if (_tiles[arrNum].obj == OBJ_BLOCK) return true;
	if (_tiles[arrNum].obj == OBJ_NEXT) return true;

	return false;
}

void bossStage::doorUpdate()
{
	if (PLAYER->currentTile() == 138)
	{
		SOUNDMANAGER->stop("boss");
		SCENEMANAGER->changeScene("�κ��");

	}

}
