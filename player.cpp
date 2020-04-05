#include "stdafx.h"
#include "player.h"

player::player(){}
player::~player(){}

HRESULT player::init()
{
	_bodyImg = IMAGEMANAGER->findImage("����R");
	_headImg = IMAGEMANAGER->findImage("���̴���R");

	//�÷��̾� ������ġ
	_currentX = _collisionX = 494;
	_currentY = _collisionY = 390;
	
	_rc = RectMakeCenter(_currentX, _currentY, 50, 50);
	_collisionRc = RectMakeCenter(_collisionX, _collisionY, 50, 50);
	
	_currentTileIndex = 373;
	_nextTileIndex = 374;

	_direction = DOWN;
	
	_moveSpeed = 6.5f;
	_isMove = false;
	_coin = _diamond = 0;

	_rhythm = 0;
	_isFever = false;

	//����
	_hp.currentX = 2;
	_hp.img = IMAGEMANAGER->findImage("HP��");
	_hp.hp = 1.0f;

	_status.vHp.clear();
	_status.atk = 0;
	_status.def = 0;
	_status.minePower = 0;
	_status.vHp.push_back(_hp);
	_status.vHp.push_back(_hp);
	_status.vHp.push_back(_hp);

	HPbarSet();

	_inven = new inventory;
	_inven->init();

	_ray = new raycast;
	_rayPower = 0;

	for (int i = 0; i < 3; i++)
	{
		_coinUI.coinImg[i].img = IMAGEMANAGER->findImage("����");
		_diamondUI.coinImg[i].img = IMAGEMANAGER->findImage("����");
	}
	_diamondUI.x = IMAGEMANAGER->findImage("x��ư");
	_coinUI.x = IMAGEMANAGER->findImage("x��ư");
	_coinFeverImg = IMAGEMANAGER->findImage("���ι��");
	_coinFeverNumImg = IMAGEMANAGER->findImage("����");


	_gameEnd = new gameEnd;
	_gameEnd->init();

	return S_OK;
}

void player::release()
{
	SAFE_DELETE(_inven);
	SAFE_DELETE(_gameEnd);
}

void player::update()
{
	if (_isDie)
	{
		_gameEnd->update();
		return;
	}


	_inven->update();
	keyControl();

	attack();
	move();

	animation();
	_ray->playerRay(_currentTileIndex, _rayPower);

	coinUIupdate();
	feverTime();
}

void player::render(HDC hdc)
{
	if (_isDie)
	{
		_gameEnd->render(_coin);
		return;
	}

	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		Rectangle(hdc, _collisionRc.left, _collisionRc.top, _collisionRc.right, _collisionRc.bottom);
	}

	int x, y;
	x = _collisionRc.left + (_collisionRc.right - _collisionRc.left) / 2;
	y = _collisionRc.top + (_collisionRc.bottom - _collisionRc.top) / 2;
	CAMERAMANAGER->setCameraCenter(PointMake(x, y));

	_bodyImg->frameRender(hdc, _rc.left, _rc.top - 28, _frameX, _frameY);
	_headImg->frameRender(hdc, _rc.left, _rc.top - 33, _frameX, 0);
}

void player::frontCheck()
{
	_rhythm++;

	//��Ÿ���� ������
	_tileX = _rc.left / TILESIZE;
	_tileY = _rc.top / TILESIZE;
	_currentTileIndex = _tileX + _tileY * TILEX;

	switch (_direction)
	{
	case LEFT:
		_nextTileIndex = _tileX + _tileY * TILEX - 1;
		break;
	case RIGHT:
		_nextTileIndex = _tileX + _tileY * TILEX + 1;
		break;
	case UP:
		_nextTileIndex = _tileX + (_tileY - 1) * TILEX;
		break;
	case DOWN:
		_nextTileIndex = _tileX + (_tileY + 1) * TILEX;
		break;
	}

	//Ÿ�� ���� ���� �Ǻ� ������ ����
	if (_inven->getWeapon() != NULL)
	{
		//������
		if (_inven->getWeapon()->getBool())
		{
			_isAttack = true;
			return;
		}

		//��Ÿ
		attackCheck();

		if (_isAttack) return;
	}
	//��Ÿ�� ���� �ƴϸ� �̵�
	moveCheck();
}

void player::attack()
{
	if (!_isAttack) return;


	//������ �����̸�
	if (_inven->getWeapon()->getBool())
	{
		isThrow();
		return;
	} //������ �� 

	//��Ÿ

	for (int i = 0; i < _vTarget.size(); ++i)
	{
		MONSTERMANAGER->getMonster()[_vTarget[i]]->hit(_status.atk);
		if (_isTaekwondo)MONSTERMANAGER->getMonster()[_vTarget[i]]->hit(_status.atk);

		if (!_isFever && MONSTERMANAGER->getMonster()[_vTarget[i]]->die())
		{
			for (int i = 0; i < TILEX * TILEY; i++)
			{
				if (_pCurrentMap[i].terrain != TERRAIN_GROUND) continue;
				if (_pCurrentMap[i].terrainFrameX == 0)
				{
					_pCurrentMap[i].terrainFrameY = 4;
				}
				else if (_pCurrentMap[i].terrainFrameX == 2)
				{
					_pCurrentMap[i].terrainFrameY = 5;
				}
			}
			_isFever = true;
		}

		 effectControl(_equipWeaponType, 0, _vTarget[i]);

	}
	SOUNDMANAGER->play("atk");
	_isAttack = false;
}

void player::move()
{
	if (!_isMove)return;
	//float a;
	//float a1;
	//float b;
	//float b1;


	//	a1 = _pCurrentMap[_nextTileIndex].x -26;
	//	b1 = _pCurrentMap[_nextTileIndex].y -26 ;

	//	a = _pCurrentMap[_nextTileIndex].x;
	//	b = _pCurrentMap[_nextTileIndex].y;

	//	float x1speed= lerp(_pCurrentMap[_nextTileIndex].x, _pCurrentMap[_nextTileIndex].x - 26, TIMEMANAGER->getElapsedTime() / 0.3f);
	//	float x2speed= lerp(0, 26, TIMEMANAGER->getElapsedTime() / 0.3f);
	//	float y1speed= lerp(_pCurrentMap[_nextTileIndex].y, _pCurrentMap[_nextTileIndex].y - 26, TIMEMANAGER->getElapsedTime() / 0.3f);
	//	float y2speed= lerp(0, 26, TIMEMANAGER->getElapsedTime() / 0.3f);



	//if (_currentX == _pCurrentMap[_nextTileIndex].x && _currentY == _pCurrentMap[_nextTileIndex].y)
	//{
	//	_isMove = false;
	//	_isTurn = false;
	//}
	//switch (_direction)
	//{
	//case LEFT:
	//	if (!_isTurn)
	//	{
	//		_currentX += x1speed;
	//		_collisionX += x1speed;
	//		_currentY += y1speed;
	//	}
	//	else
	//	{
	//		_currentX -= x2speed;
	//		_collisionX -= x2speed;
	//		_currentY += y2speed;
	//	}

	//	if (_currentY == b1)
	//		_isTurn = true;



	//	break;
	//case RIGHT:

	//	break;
	//case UP:
	//	break;
	//case DOWN:
	//	break;
	//}
	switch (_direction)
	{
	case LEFT:
		if (getDistance(_collisionX, _collisionY, _pCurrentMap[_nextTileIndex].x, _pCurrentMap[_nextTileIndex].y ) != 0)
		{
			_collisionX -= _moveSpeed;
		}
		if (!_isDrop&& getDistance(_currentX, _currentY, _pCurrentMap[_nextTileIndex].x + 26, _pCurrentMap[_nextTileIndex].y - 26) != 0)
		{
			_currentX -= _moveSpeed;
			_currentY -= _moveSpeed;
		}
		else _isDrop = true;
	
		if (_isDrop&& getDistance(_currentX, _currentY, _pCurrentMap[_nextTileIndex].x, _pCurrentMap[_nextTileIndex].y) != 0)
		{
			_currentX -= _moveSpeed;
			_currentY += _moveSpeed;
		}
		else if(_isDrop&& getDistance(_currentX, _currentY, _pCurrentMap[_nextTileIndex].x, _pCurrentMap[_nextTileIndex].y) == 0)
		{
			_isDrop = false;
			_isMove = false;
		}
		break;
	case RIGHT:
		if (getDistance(_collisionX, _collisionY, _pCurrentMap[_nextTileIndex].x, _pCurrentMap[_nextTileIndex].y) != 0)
		{
			_collisionX += _moveSpeed;
		}
		if (!_isDrop&& getDistance(_currentX, _currentY, _pCurrentMap[_nextTileIndex].x - 26, _pCurrentMap[_nextTileIndex].y - 26) != 0)
		{
			_currentX += _moveSpeed;
			_currentY -= _moveSpeed;
		}
		else _isDrop = true;

		if (_isDrop&& getDistance(_currentX, _currentY, _pCurrentMap[_nextTileIndex].x, _pCurrentMap[_nextTileIndex].y) != 0)
		{
			_currentX += _moveSpeed;
			_currentY += _moveSpeed;
		}
		else if (_isDrop&& getDistance(_currentX, _currentY, _pCurrentMap[_nextTileIndex].x, _pCurrentMap[_nextTileIndex].y) == 0)
		{
			_isDrop = false;
			_isMove = false;
		}
		break;
	case UP:
		if (getDistance(_collisionX, _collisionY, _pCurrentMap[_nextTileIndex].x, _pCurrentMap[_nextTileIndex].y) != 0)
		{
			_collisionY -= _moveSpeed + 6.5f;
		}

		if (!_isDrop&& getDistance(_currentX, _currentY, _pCurrentMap[_nextTileIndex].x, _pCurrentMap[_nextTileIndex].y - 26) != 0)
		{
			_currentY -= _moveSpeed + 6.5f;
		}
		else _isDrop = true;

		if (_isDrop&& getDistance(_currentX, _currentY, _pCurrentMap[_nextTileIndex].x, _pCurrentMap[_nextTileIndex].y) != 0)
		{
			_currentY += _moveSpeed+6.5f;
		}
		else if (_isDrop&& getDistance(_currentX, _currentY, _pCurrentMap[_nextTileIndex].x, _pCurrentMap[_nextTileIndex].y) == 0)
		{
			_isDrop = false;
			_isMove = false;
		}
		break;
	case DOWN:
		if (getDistance(_collisionX, _collisionY, _pCurrentMap[_nextTileIndex].x, _pCurrentMap[_nextTileIndex].y) != 0)
		{
			_collisionY += _moveSpeed + 6.5f;
		}

		if (!_isDrop&& getDistance(_currentX, _currentY, _pCurrentMap[_nextTileIndex].x, _pCurrentMap[_nextTileIndex].y - 78) != 0)
		{
			_currentY -= _moveSpeed + 6.5f;
		}
		else _isDrop = true;

		if (_isDrop&& getDistance(_currentX, _currentY, _pCurrentMap[_nextTileIndex].x, _pCurrentMap[_nextTileIndex].y) != 0)
		{
			_currentY += _moveSpeed + 6.5f;
		}
		else if (_isDrop&& getDistance(_currentX, _currentY, _pCurrentMap[_nextTileIndex].x, _pCurrentMap[_nextTileIndex].y) == 0)
		{
			_isDrop = false;
			_isMove = false;
		}
		break;
	}
	_rc = RectMakeCenter(_currentX, _currentY, 50, 50);
	_collisionRc = RectMakeCenter(_collisionX, _collisionY, 50, 50);
}

void player::UIrender(HDC hdc)
{
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		if (_pCurrentMap[_nextTileIndex].obj != OBJ_NONE)
		{
			HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(255, 0, 0));
			HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);
			Rectangle(hdc, _pCurrentMap[_nextTileIndex].rc.left, _pCurrentMap[_nextTileIndex].rc.top, _pCurrentMap[_nextTileIndex].rc.right, _pCurrentMap[_nextTileIndex].rc.bottom);
			SelectObject(hdc, oldBrush);
			DeleteObject(myBrush);
		}

		for (int i = 0; i < _status.atkRenge.size(); i++)
		{
			Rectangle(hdc, _pCurrentMap[_status.atkRenge[i]].rc.left, _pCurrentMap[_status.atkRenge[i]].rc.top, _pCurrentMap[_status.atkRenge[i]].rc.right, _pCurrentMap[_status.atkRenge[i]].rc.bottom);
		}
		HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0));
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);
		Rectangle(hdc, _pCurrentMap[_currentTileIndex].rc.left, _pCurrentMap[_currentTileIndex].rc.top, _pCurrentMap[_currentTileIndex].rc.right, _pCurrentMap[_currentTileIndex].rc.bottom);
		SelectObject(hdc, oldBrush);
		DeleteObject(myBrush);

	}
	if (_isFever)
	{
		_coinFeverImg->render(CAMERAMANAGER->getCameraDC(), WINSIZEX / 2 - _coinFeverImg->getWidth(), WINSIZEY - _coinFeverImg->getHeight());
		_coinFeverNumImg->frameRender(CAMERAMANAGER->getCameraDC(), WINSIZEX / 2+ _coinFeverNumImg->getFrameWidth(), WINSIZEY - _coinFeverNumImg->getFrameHeight()-10, _coinMultiplier, 0);
	}

	for (int i = 0; i < _status.vHp.size(); i++)
	{
		_status.vHp[i].img->frameRender(CAMERAMANAGER->getCameraDC(), _status.vHp[i].rc.left, _status.vHp[i].rc.top, _status.vHp[i].currentX,0);
	}

	//�κ��丮 ����....
	_inven->render(hdc);

	coinUIrender();

	//HFONT myFont = CreateFont(20, 0, 0, 0, 800, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, TEXT("����"));
	//HFONT oldFont = (HFONT)SelectObject(CAMERAMANAGER->getCameraDC(), myFont);
	//SelectObject(CAMERAMANAGER->getCameraDC(), oldFont);
	//DeleteObject(myFont);
	//wsprintf(_str, "���ڸ��� Ƚ��%d", _rhythm);
	//TextOut(CAMERAMANAGER->getCameraDC(), WINSIZEX - 60, 125, _str, strlen(_str));

	miniMap();
}

void player::setMap(tagTile tile[], string map)
{
	_currentMap = map;
	_pCurrentMap = NULL;
	_pCurrentMap = tile;
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (tile[i].startPoint == "�÷��̾�")
		{
			_currentTileIndex = i;
			_nextTileIndex = i + 1;
			_collisionX = _currentX = tile[i].x;
			_collisionY = _currentY = tile[i].y;
			_rc = RectMakeCenter(_currentX, _currentY, 50, 50);
			_collisionRc = RectMakeCenter(_collisionX, _collisionY, 50, 50);
			break;
		}
	}
	_direction = DOWN;
	_tileX = _rc.left / TILESIZE;
	_tileY = _rc.top / TILESIZE;
	_currentTileIndex = _tileX + _tileY * TILEX;
	_nextTileIndex = _tileX + (_tileY + 1) * TILEX;
	_isMove = false;
	_rhythm = 0;
	_isFever = false;
	_ray->init(_pCurrentMap);
	_ray->playerRay(_currentTileIndex,_rayPower);
}

void player::HPbarSet()
{ 
	for (int i = 0; i < _status.vHp.size(); i++)
	{
		if (_status.vHp[i].hp <= 0.0f) _status.vHp[i].currentX = 2;
		if (_status.vHp[i].hp == 0.5f) _status.vHp[i].currentX = 1;
		if (_status.vHp[i].hp == 1.0f) _status.vHp[i].currentX = 0;

		_status.vHp[i].rc = RectMakeCenter(WINSIZEX - 50 * (4+i), 50, _hp.img->getFrameWidth(), _hp.img->getFrameHeight());
	}

	//if (KEYMANAGER->isOnceKeyDown('J')) //ȸ��
	//{
		//for (int i = _vHp.size()-1; i >= 0; i--)
		//{
		//	if (_vHp[i].hp <= 0.5f)
		//	{
		//		_vHp[i].hp += 0.5f;
		//		break;
		//	}
		//	else continue;
		//}
	//}
	//if (KEYMANAGER->isOnceKeyDown('K')) //�߰�
	//{
	//	_hp.rc = RectMakeCenter(WINSIZEX - 50 * 7, 50, _hp.img->getFrameWidth(), _hp.img->getFrameHeight());
	//	_vHp.push_back(_hp);
	//}

}

void player::mine()
{
	if(_pCurrentMap[_nextTileIndex].obj == OBJ_NOMALWALL||
		_pCurrentMap[_nextTileIndex].obj == OBJ_SKULLWALL ||
		_pCurrentMap[_nextTileIndex].obj == OBJ_WHITEWALL ||
		_pCurrentMap[_nextTileIndex].obj == OBJ_IRONWALL ||
		_pCurrentMap[_nextTileIndex].obj == OBJ_GOLDWALL ||
		_pCurrentMap[_nextTileIndex].obj == OBJ_NEVERWALL)
		EFFECTMANAGER->play(_inven->getShovel()->getName(), _pCurrentMap[_nextTileIndex].x, _pCurrentMap[_nextTileIndex].y - 25);

	if (_status.minePower >= _pCurrentMap[_nextTileIndex].strength)
	{
		_pCurrentMap[_nextTileIndex].obj = OBJ_NONE;
		_pCurrentMap[_nextTileIndex].strength = 0;
		_pCurrentMap[_nextTileIndex].walkable = true;
		_pCurrentMap[_nextTileIndex].itemPoint = "";


		if (_pCurrentMap[_nextTileIndex].obj == OBJ_DOOR) 		SOUNDMANAGER->play("openDoor");
		else 		SOUNDMANAGER->play("mineOK");
		//SOUNDMANAGER->play("dig");
	}
	else
	{
		_rhythm = 0;
		SOUNDMANAGER->play("mineFAIL");
	}
}

void player::getItem(int itemTile)
{
	SOUNDMANAGER->play("pickup_general");
	//������ �Ծ����� ���θ԰� ��
	if (ITEMMANAGER->getItemList()[itemTile]->getName() == "HP����")
	{
		hp _temp;
		_temp.currentX = 2;
		_temp.img = IMAGEMANAGER->findImage("HP��");
		_temp.hp = 0.0f;
		//_status.vHp.push_back(_temp);
		_status.vHp.insert(_status.vHp.begin(), _temp);
		HPbarSet();
		ITEMMANAGER->removeItem(itemTile);
		return;
	}

	if (ITEMMANAGER->getItemList()[itemTile]->getName() == "����")
	{
		if (_isFever)
		{
			_coin+= ITEMMANAGER->getItemList()[itemTile]->getValue()*_coinMultiplier;
		}
		else
		{
			_coin += ITEMMANAGER->getItemList()[itemTile]->getValue();
		}

		if (_coin > 999) _coin = 999;

		ITEMMANAGER->removeItem(itemTile);
		return;
	}

	if (_inven->getItemList().empty())
	{
		_inven->addItem(ITEMMANAGER->addItem(ITEMMANAGER->getItemList()[itemTile]->getName(), 1, 1));
		ITEMMANAGER->removeItem(itemTile);
	}
	else
	{
		int check = 0;
		for (int i = 0; i < _inven->getItemList().size(); ++i)
		{
			if (_inven->getItemList()[i]->getType() != ITEMMANAGER->getItemList()[itemTile]->getType())
			{
				check++;
			}
			if (_inven->getItemList()[i]->getType() == ITEMMANAGER->getItemList()[itemTile]->getType())
			{
				_inven->swapItem(i, ITEMMANAGER->getItemList_ref()[itemTile] , itemTile);
				break;
			}

			if (check == _inven->getItemList().size())
			{
				_inven->addItem(ITEMMANAGER->addItem(ITEMMANAGER->getItemList()[itemTile]->getName(), 1, 1));
				ITEMMANAGER->removeItem(itemTile);
				break;
			}
		}
	}
}

void player::hit(float damege, image* name)
{
	float _damege = damege - _status.def;
	if (_isTaekwondo) _damege *= 2;
	_isHit = true;
	for (int i = 0; i < _status.vHp.size(); i++)
	{
		if (_status.vHp[i].hp <= 0) continue;
		
		if (_damege > 0)
		{
			float temp = _status.vHp[i].hp;
			_status.vHp[i].hp -= _damege;
			if (_status.vHp[i].hp < 0) _status.vHp[i].hp = 0;
			_damege -= temp;
		}
		else break;
	}
	_monsterName = name;
	feverTimeReset();
	HPbarSet();
	if (dieCheck())
	{
		_isDie = true;
		_currentTileIndex = 999;
		_nextTileIndex = 999;
		_currentX = 999;
		_currentY = 999;
		_collisionX = 999;
		_collisionY = 999;
		SOUNDMANAGER->play("death");
		_rc = RectMakeCenter(_currentX, _currentY, 50, 50);
		_collisionRc = RectMakeCenter(_collisionX, _collisionY, 50, 50);
	}
}

void player::keyControl()
{
	if (_isMove) return;
	//_isBeat = true;
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		if (BEAT->getOkTime())
		{
			_direction = LEFT;
			BEAT->removeNote();
			BEAT->okTimeReset();
			frontCheck();
		}
		else
		{
			BEAT->removeNote();
			BEAT->addMiss();
			if(!_isBallet)feverTimeReset();
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		if (BEAT->getOkTime())
		{
			_direction = RIGHT;
			BEAT->removeNote();
			BEAT->okTimeReset();
			frontCheck();
		}
		else
		{
			BEAT->removeNote();
			BEAT->addMiss();
			if (!_isBallet)feverTimeReset();
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		if (BEAT->getOkTime())
		{
			_direction = UP;
			BEAT->removeNote();
			BEAT->okTimeReset();
			frontCheck();
		}
		else
		{
			BEAT->removeNote();
			BEAT->addMiss();
			if (!_isBallet)feverTimeReset();
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		if (BEAT->getOkTime())
		{
			_direction = DOWN;
			BEAT->removeNote();
			BEAT->okTimeReset();
			frontCheck();
		}
		else
		{
			BEAT->removeNote();
			BEAT->addMiss();
			if (!_isBallet)feverTimeReset();
		}
	}
}

void player::animation()
{
	switch (_direction)
	{
	case LEFT:
		_bodyImg = IMAGEMANAGER->findImage("����L");
		_headImg = IMAGEMANAGER->findImage("���̴���L");
		break;
	case RIGHT:
		_bodyImg = IMAGEMANAGER->findImage("����R");
		_headImg = IMAGEMANAGER->findImage("���̴���R");
		break;
	}

	//�ִϸ��̼� ������
	if (BEAT->getCnt() % 12 == 0)
	{
		_frameX++;
		if (_frameX > _bodyImg->getMaxFrameX())_frameX = 0;
	}
}

bool player::walkableCheck()
{
	if (_pCurrentMap[_nextTileIndex].walkable) return true;

	return false;
}

bool player::wallCheck(int tile)
{
	if (_pCurrentMap[tile].obj == OBJ_NOMALWALL) return true;
	if (_pCurrentMap[tile].obj == OBJ_SKULLWALL) return true;
	if (_pCurrentMap[tile].obj == OBJ_WHITEWALL) return true;
	if (_pCurrentMap[tile].obj == OBJ_GOLDWALL) return true;
	if (_pCurrentMap[tile].obj == OBJ_IRONWALL) return true;
	if (_pCurrentMap[tile].obj == OBJ_NEVERWALL) return true;
	if (_pCurrentMap[tile].obj == OBJ_DOOR) return true;

	return false;
}

bool player::dieCheck()
{
	for (int i = 0; i < _status.vHp.size(); i++)
	{
		if (_status.vHp[i].hp > 0) return false;
	}
	return true;
}

void player::effectControl(attackForm form, int rengeArrNum, int monArrNum)
{
	switch (form)
	{
	case FORM_SHORT: //�ܰ�
		switch (_direction)
		{
		case LEFT:
			EFFECTMANAGER->play("�ܰ�L", _pCurrentMap[_status.atkRenge[0]].x, _pCurrentMap[_status.atkRenge[0]].y);
			break;
		case RIGHT:
			EFFECTMANAGER->play("�ܰ�R", _pCurrentMap[_status.atkRenge[0]].x, _pCurrentMap[_status.atkRenge[0]].y);
			break;
		case UP:
			EFFECTMANAGER->play("�ܰ�Up", _pCurrentMap[_status.atkRenge[0]].x, _pCurrentMap[_status.atkRenge[0]].y);
			break;
		case DOWN:
			EFFECTMANAGER->play("�ܰ�Down", _pCurrentMap[_status.atkRenge[0]].x, _pCurrentMap[_status.atkRenge[0]].y);
			break;
		}
		break;
	case FORM_BIG: //���
		switch (_direction)
		{
		case LEFT:
			EFFECTMANAGER->play("���L",_pCurrentMap[_status.atkRenge[0]].x , _pCurrentMap[_status.atkRenge[0]].y);
			break;				 
		case RIGHT:				 
			EFFECTMANAGER->play("���R", _pCurrentMap[_status.atkRenge[0]].x, _pCurrentMap[_status.atkRenge[0]].y);
			break;				 
		case UP:				 
			EFFECTMANAGER->play("���Up", _pCurrentMap[_status.atkRenge[0]].x, _pCurrentMap[_status.atkRenge[0]].y);
			break;				 
		case DOWN:				 
			EFFECTMANAGER->play("���Down", _pCurrentMap[_status.atkRenge[0]].x, _pCurrentMap[_status.atkRenge[0]].y);
			break;
		}
		break;
	case FORM_SPEAR: //â
		arrowEffect(form,monArrNum);
		break;
	case FORM_BOW: //Ȱ
		arrowEffect(form, monArrNum);
		break;
	case FORM_WHIP: //ä��
		int renge;
		for (int i = 0; i < _status.atkRenge.size(); ++i)
		{
			if (MONSTERMANAGER->getMonster()[monArrNum]->currentTile() == _status.atkRenge[i])
			{
				renge = i;
			}
		}
		switch (_direction)
		{
		case LEFT:
			if		(renge == 0)EFFECTMANAGER->play("ä��L0", _collisionX-30,_collisionY);
			else if (renge == 1)EFFECTMANAGER->play("ä��L1", _collisionX-30,_collisionY);
			else if (renge == 2)EFFECTMANAGER->play("ä��L2", _collisionX-30,_collisionY);
			else if (renge == 3)EFFECTMANAGER->play("ä��L3", _collisionX-30,_collisionY);
			else if (renge == 4)EFFECTMANAGER->play("ä��L4", _collisionX-30,_collisionY);
			break;													
		case RIGHT:													
			if		(renge == 3)EFFECTMANAGER->play("ä��R0", _collisionX+30,_collisionY+30);
			else if (renge == 1)EFFECTMANAGER->play("ä��R1", _collisionX+30,_collisionY);
			else if (renge == 0)EFFECTMANAGER->play("ä��R2", _collisionX+30,_collisionY);
			else if (renge == 2)EFFECTMANAGER->play("ä��R3", _collisionX+30,_collisionY);
			else if (renge == 4)EFFECTMANAGER->play("ä��R4", _collisionX+30,_collisionY-30);
			break;													
		case UP:													
			if		(renge == 0)EFFECTMANAGER->play("ä��U0", _collisionX,_collisionY-30);
			else if (renge == 1)EFFECTMANAGER->play("ä��U1", _collisionX,_collisionY-30);
			else if (renge == 2)EFFECTMANAGER->play("ä��U2", _collisionX,_collisionY-30);
			else if (renge == 3)EFFECTMANAGER->play("ä��U3", _collisionX,_collisionY-30);
			else if (renge == 4)EFFECTMANAGER->play("ä��U4", _collisionX,_collisionY-30);
			break;													
		case DOWN:													
			if		(renge == 3)EFFECTMANAGER->play("ä��D0", _collisionX,_collisionY+30);
			else if (renge == 1)EFFECTMANAGER->play("ä��D1", _collisionX,_collisionY+30);
			else if (renge == 0)EFFECTMANAGER->play("ä��D2", _collisionX,_collisionY+30);
			else if (renge == 2)EFFECTMANAGER->play("ä��D3", _collisionX,_collisionY+30);
			else if (renge == 4)EFFECTMANAGER->play("ä��D4", _collisionX,_collisionY+30);
			break;
		}
		
		break;
	}
}

bool player::rengeCheck(int monArrNum, int tile)
{
	if (MONSTERMANAGER->getMonster()[monArrNum]->currentTile() == tile) return false;
	else return true;
}

bool player::throwRengeCheck(int nextTile)
{
	if (_pCurrentMap[nextTile].obj == OBJ_NOMALWALL)return false;
	if (_pCurrentMap[nextTile].obj == OBJ_SKULLWALL)return false;
	if (_pCurrentMap[nextTile].obj == OBJ_WHITEWALL)return false;
	if (_pCurrentMap[nextTile].obj == OBJ_GOLDWALL)return false;
	if (_pCurrentMap[nextTile].obj == OBJ_IRONWALL)return false;
	if (_pCurrentMap[nextTile].obj == OBJ_NEVERWALL)return false;
	if (_pCurrentMap[nextTile].obj == OBJ_DOOR)return false;

	else return true;
}

void player::arrowEffect(attackForm form, int monArrNum)
{
	int arrowRenge = 0;
	int temp = _nextTileIndex;

	switch (_direction)
	{
	case LEFT:
		EFFECTMANAGER->play("ȭ�쳡L", MONSTERMANAGER->getMonster()[monArrNum]->getXY().x+52, MONSTERMANAGER->getMonster()[monArrNum]->getXY().y);
		while (rengeCheck(monArrNum, temp))
		{
			arrowRenge++;
			temp--;
		}
		break;
	case RIGHT:
		EFFECTMANAGER->play("ȭ�쳡R", MONSTERMANAGER->getMonster()[monArrNum]->getXY().x-52, MONSTERMANAGER->getMonster()[monArrNum]->getXY().y);
		while (rengeCheck(monArrNum, temp))
		{
			arrowRenge++;
			temp++;
		}
		break;
	case UP:
		EFFECTMANAGER->play("ȭ�쳡Up", MONSTERMANAGER->getMonster()[monArrNum]->getXY().x, MONSTERMANAGER->getMonster()[monArrNum]->getXY().y+52);
		while (rengeCheck(monArrNum, temp))
		{
			arrowRenge++;
			temp -= TILEY;
		}
		break;
	case DOWN:
		EFFECTMANAGER->play("ȭ�쳡Down", MONSTERMANAGER->getMonster()[monArrNum]->getXY().x, MONSTERMANAGER->getMonster()[monArrNum]->getXY().y-52);
		while (rengeCheck(monArrNum, temp))
		{
			arrowRenge++;
			temp += TILEY;
		}
		break;
	}

	for (int i = 0; i < arrowRenge; i++)
	{
		switch (_direction)
		{
		case LEFT:
			EFFECTMANAGER->play("ȭ����ΰ���", _pCurrentMap[_nextTileIndex].x - (i * 52), _pCurrentMap[_nextTileIndex].y);
			break;
		case RIGHT:
			EFFECTMANAGER->play("ȭ����ΰ���", _pCurrentMap[_nextTileIndex].x + (i * 52), _pCurrentMap[_nextTileIndex].y);
			break;
		case UP:
			EFFECTMANAGER->play("ȭ����μ���", _pCurrentMap[_nextTileIndex].x, _pCurrentMap[_nextTileIndex].y - (i * 52));
			break;
		case DOWN:
			EFFECTMANAGER->play("ȭ����μ���", _pCurrentMap[_nextTileIndex].x, _pCurrentMap[_nextTileIndex].y + (i * 52));
			break;
		}
	}
}

void player::throwEffect(int endTile, int throwRenge)
{
	switch (_direction)
	{
	case LEFT:
		EFFECTMANAGER->play("ȭ�쳡L", _pCurrentMap[endTile].x+104, _pCurrentMap[endTile].y);
		break;
	case RIGHT:
		EFFECTMANAGER->play("ȭ�쳡R", _pCurrentMap[endTile].x-104, _pCurrentMap[endTile].y);
		break;
	case UP:
		EFFECTMANAGER->play("ȭ�쳡Up", _pCurrentMap[endTile].x, _pCurrentMap[endTile].y+104);
		break;
	case DOWN:
		EFFECTMANAGER->play("ȭ�쳡Down", _pCurrentMap[endTile].x, _pCurrentMap[endTile].y-104);
		break;
	}

	for (int i = 0; i < throwRenge; i++)
	{
		switch (_direction)
		{
		case LEFT:
			EFFECTMANAGER->play("ȭ����ΰ���", _pCurrentMap[_nextTileIndex].x - (i * 52), _pCurrentMap[_nextTileIndex].y);
			break;
		case RIGHT:
			EFFECTMANAGER->play("ȭ����ΰ���", _pCurrentMap[_nextTileIndex].x + (i * 52), _pCurrentMap[_nextTileIndex].y);
			break;
		case UP:
			EFFECTMANAGER->play("ȭ����μ���", _pCurrentMap[_nextTileIndex].x, _pCurrentMap[_nextTileIndex].y - (i * 52));
			break;
		case DOWN:
			EFFECTMANAGER->play("ȭ����μ���", _pCurrentMap[_nextTileIndex].x , _pCurrentMap[_nextTileIndex].y + (i * 52));
			break;
		}
	}
}

void player::moveCheck()
{
	if (walkableCheck())
	{
		for (int i = 0; i < ITEMMANAGER->getItemList().size(); ++i)
		{
			if (_nextTileIndex == ITEMMANAGER->getItemList()[i]->getCurrentTile())
			{
				if (ITEMMANAGER->getItemList()[i]->getIsShop())
				{
					buyItem(i);
					return;
				}
				else getItem(i);
			}
		}

		_isMove = true;
		_currentTileIndex = _nextTileIndex;
	}
	else
	{
		mine();
		_nextTileIndex = _currentTileIndex;
	}
}

void player::buyItem(int itemTile)
{
	if (_coin < ITEMMANAGER->getItemList()[itemTile]->getPrice())
	{
		_nextTileIndex = _currentTileIndex;
		return;
	}

	_coin -= ITEMMANAGER->getItemList()[itemTile]->getPrice();
	_isMove = true;
	_currentTileIndex = _nextTileIndex;

	if (_inven->getItemList().empty())
	{
		_inven->addItem(ITEMMANAGER->addItem(ITEMMANAGER->getItemList()[itemTile]->getName(), 1, 1));
		ITEMMANAGER->removeItem(itemTile);
	}
	else
	{
		int check = 0;
		for (int i = 0; i < _inven->getItemList().size(); ++i)
		{
			if (_inven->getItemList()[i]->getType() != ITEMMANAGER->getItemList()[itemTile]->getType())
			{
				check++;
			}
			if (_inven->getItemList()[i]->getType() == ITEMMANAGER->getItemList()[itemTile]->getType())
			{
				_inven->swapItem(i, ITEMMANAGER->getItemList_ref()[itemTile], itemTile);
				break;
			}

			if (check == _inven->getItemList().size())
			{
				_inven->addItem(ITEMMANAGER->addItem(ITEMMANAGER->getItemList()[itemTile]->getName(), 1, 1));
				ITEMMANAGER->removeItem(itemTile);
				break;
			}
		}
	}
}

void player::feverTime()
{
	if (_rhythm > 0 && _isFever)
	{
		_coinMultiplier = 2;
		if (_rhythm > 10) _coinMultiplier = 3;
	}
}

void player::coinUIupdate()
{
	_coinUI.coinImg[0].frameX = _coin % 1000 / 100;
	_coinUI.coinImg[1].frameX = _coin % 100 / 10;
	_coinUI.coinImg[2].frameX = _coin % 10;

	_diamondUI.coinImg[0].frameX = _diamond % 1000 / 100;
	_diamondUI.coinImg[1].frameX = _diamond % 100 / 10;
	_diamondUI.coinImg[2].frameX = _diamond % 10;
}

void player::coinUIrender()
{
	_coinUI.x->render(CAMERAMANAGER->getCameraDC(), WINSIZEX - 100, 45);
	_diamondUI.x->render(CAMERAMANAGER->getCameraDC(), WINSIZEX - 100, 100);

	int temp = 0;
	for (int i = 0; i < 3; i++)
	{
		if (_coin < 100 && i == 0)continue;
		if (_coin < 10 && i == 1)continue;
		_coinUI.coinImg[i].img->frameRender(CAMERAMANAGER->getCameraDC(), WINSIZEX - 80 + (temp*_coinUI.coinImg[i].img->getFrameWidth()), 40, _coinUI.coinImg[i].frameX, 0);
		temp++;
	}
	temp = 0;
	for (int i = 0; i < 3; i++)
	{
		if (_diamond < 100 && i == 0)continue;
		if (_diamond < 10 && i == 1)continue;
		_diamondUI.coinImg[i].img->frameRender(CAMERAMANAGER->getCameraDC(), WINSIZEX - 80 + (temp*_diamondUI.coinImg[i].img->getFrameWidth()), 95, _diamondUI.coinImg[i].frameX, 0);
		temp++;
	}

	//���� ���δ��̾� �κ� ����
	IMAGEMANAGER->render("���δ��̾�", CAMERAMANAGER->getCameraDC(), WINSIZEX - 50 * 3, 20);
	SetTextColor(CAMERAMANAGER->getCameraDC(), RGB(255, 255, 255));
}

void player::attackCheck()
{
	_inven->getWeapon()->active();

	bool whipCheck = false;
	int check = 0;
	int breakCheck = 0;
	_vTarget.clear();

	for (int i = 0; i < _status.atkRenge.size(); ++i)
	{
		if (whipCheck && i == check + 2) continue;

		if (wallCheck(_status.atkRenge[i]))
		{
			if (_equipWeaponType == FORM_WHIP)
			{
				whipCheck = true;
				check = i;
				breakCheck++;

				if (breakCheck == 2) break;
				continue;
			}
			if (_equipWeaponType == FORM_BIG && _equipWeaponType == FORM_SPEAR) continue;

			break;
		}

		for (int k = 0; k < MONSTERMANAGER->getMonster().size(); ++k)
		{
			if (_status.atkRenge[i] == MONSTERMANAGER->getMonster()[k]->currentTile())
			{
				_vTarget.push_back(k);
				_isAttack = true;
				if (_equipWeaponType == FORM_SHORT || _equipWeaponType == FORM_BOW || _equipWeaponType == FORM_WHIP)
				{
					return;
				}
			}
		}
	}
}

void player::isThrow()
{
	SOUNDMANAGER->play("throw");
	int arrowRenge = 0;
	int temp = _nextTileIndex;

	switch (_direction)
	{
	case LEFT:
		while (throwRengeCheck(temp))
		{
			arrowRenge++;
			temp--;
		}
		break;
	case RIGHT:
		while (throwRengeCheck(temp))
		{
			arrowRenge++;
			temp++;
		}
		break;
	case UP:
		while (throwRengeCheck(temp))
		{
			arrowRenge++;
			temp -= TILEY;
		}
		break;
	case DOWN:
		while (throwRengeCheck(temp))
		{
			arrowRenge++;
			temp += TILEY;
		}
		break;
	}
	throwEffect(temp, arrowRenge);

	int monsterSize = MONSTERMANAGER->getMonster().size();

	for (int i = 0; i < arrowRenge; ++i)
	{
		for (int k = 0; k < monsterSize; ++k)
		{
			int pRenge;
			switch (_direction)
			{
			case LEFT:
				pRenge = _nextTileIndex - i;
				break;
			case RIGHT:
				pRenge = _nextTileIndex + i;
				break;
			case UP:
				pRenge = _nextTileIndex - (i*TILEX);
				break;
			case DOWN:
				pRenge = _nextTileIndex + (i*TILEX);
				break;
			}
			int mTile = MONSTERMANAGER->getMonster()[k]->currentTile();

			if (pRenge == mTile)
			{
				MONSTERMANAGER->getMonster()[k]->hit(_status.atk);
				if (_isTaekwondo)MONSTERMANAGER->getMonster()[k]->hit(_status.atk);

				if (MONSTERMANAGER->getMonster()[k]->die())
				{
					if (!_isFever)
					{
						for (int i = 0; i < TILEX * TILEY; i++)
						{
							if (_pCurrentMap[i].terrain != TERRAIN_GROUND) continue;
							if (_pCurrentMap[i].terrainFrameX == 0)
							{
									_pCurrentMap[i].terrainFrameY = 4;
							}
							else if (_pCurrentMap[i].terrainFrameX == 2)
							{
								_pCurrentMap[i].terrainFrameY = 5;
							}
						}
						_isFever = true;
					}
				}
			}
		}
	}
	switch (_direction)
	{
	case LEFT:
		ITEMMANAGER->addItemList(_inven->getWeapon()->getName(), _pCurrentMap[temp + 1].x, _pCurrentMap[temp + 1].y);
		break;
	case RIGHT:
		ITEMMANAGER->addItemList(_inven->getWeapon()->getName(), _pCurrentMap[temp - 1].x, _pCurrentMap[temp - 1].y);
		break;
	case UP:
		ITEMMANAGER->addItemList(_inven->getWeapon()->getName(), _pCurrentMap[temp + TILEX].x, _pCurrentMap[temp + TILEX].y);
		break;
	case DOWN:
		ITEMMANAGER->addItemList(_inven->getWeapon()->getName(), _pCurrentMap[temp - TILEX].x, _pCurrentMap[temp - TILEX].y);
		break;
	}
	_inven->throwItem();
	_inven->itemPosionSet();
	_isAttack = false;

}

void player::heal(float healPower)
{
	for (int i = _status.vHp.size()-1; i >=0; i--)
	{
		if (_status.vHp[i].hp >= 1) continue;

		float temp;
		if (_status.vHp[i].hp == 0.5f) temp = 0.5f;
		else if (_status.vHp[i].hp == 0) temp = 1;
		_status.vHp[i].hp += healPower;

		if (_status.vHp[i].hp >= 1) _status.vHp[i].hp = 1;
		healPower -= temp;

		if (healPower > 0) continue;
		else break;
	}
	HPbarSet();
	//for (int i = 0; i < _status.vHp.size(); i++)
	//{
	//	if (_status.vHp[i].hp <= 0.5f)
	//	{
	//		_status.vHp[i].hp += 0.5f;
	//		break;
	//	}
	//	else continue;
	//}
}

void player::gameReset(string map)
{
	SOUNDMANAGER->stop("1-1shop");
	SOUNDMANAGER->stop(_currentMap);

	playerInfoInit();

	SCENEMANAGER->changeScene(map);
}

void player::feverTimeReset(string hintName)
{
	_rhythm = 0;
	//_isFever = false;

	if (_rhythm == 0 && _isFever)
	{
		BEAT->addHint(hintName);
		if (_currentMap != "boss")
		{
			for (int i = 0; i < TILEX * TILEY; i++)
			{
				if (_pCurrentMap[i].terrain != TERRAIN_GROUND) continue;
				if (_pCurrentMap[i].terrainFrameY == 0) continue;
				_pCurrentMap[i].terrainFrameY = 0;
			}
		}
		else
		{
			for (int i = 0; i < TILEX * TILEY; i++)
			{
				if (_pCurrentMap[i].terrain != TERRAIN_GROUND) continue;
				if (_pCurrentMap[i].terrainFrameY == 1) continue;
				_pCurrentMap[i].terrainFrameY = 1;
			}
		}
		_isFever = false;
	}
}

void player::playerInfoInit()
{
	_status.vHp.clear();
	_coin = _diamond = 0;
	_status.atk = 0;
	_status.def = 0;
	_status.minePower = 0;
	_status.vHp.push_back(_hp);
	_status.vHp.push_back(_hp);
	_status.vHp.push_back(_hp);
	_inven->init();
	HPbarSet();
	_isDie = false;
	_isMove = false;
	_coin = _diamond = 0;
	_rhythm = 0;
	_isFever = false;

	_isHit = false;
	_isTaekwondo = false;
	_isFly = false;
	_isBallet = false;
}

void player::miniMap()
{
	HPEN h_null_pen = CreatePen(PS_NULL, 0, RGB(0, 0, 0));
	HGDIOBJ h_old_pen = SelectObject(CAMERAMANAGER->getCameraDC(), h_null_pen);
	int renge = 1;
	for (int i = 0; i < TILEX*TILEY; ++i)
	{
		if (!_pCurrentMap[i].look)continue;

		if (_pCurrentMap[i].terrain != TERRAIN_NONE)
		{
			HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(207, 196, 170));
			HBRUSH oldBrush = (HBRUSH)SelectObject(CAMERAMANAGER->getCameraDC(), myBrush);
			Rectangle(CAMERAMANAGER->getCameraDC(), _pCurrentMap[i].rc.left / 6 + WINSIZEX/2 + 200- renge, _pCurrentMap[i].rc.top / 6 + WINSIZEX/2-100- renge, _pCurrentMap[i].rc.right / 6 + WINSIZEX/2 + 200 + renge, _pCurrentMap[i].rc.bottom / 6 + WINSIZEX/2-100+ renge);
			SelectObject(CAMERAMANAGER->getCameraDC(), oldBrush);
			DeleteObject(myBrush);
		}

		if (_pCurrentMap[i].obj == OBJ_NONE) continue;

		int r, g, b;
		switch (_pCurrentMap[i].obj)
		{
		case OBJ_NOMALWALL:
			r = 161; g = 116; b = 40;
			break;
		case OBJ_SKULLWALL:
			r = 127; g = 82; b = 29;
			break;
		case OBJ_WHITEWALL:
			r = 144; g = 142; b = 141;
			break;
		case OBJ_GOLDWALL:
			r = 255; g = 230; b = 148;
			break;
		case OBJ_NEVERWALL:
			r = 70; g = 70; b = 70;
			break;
		case OBJ_TRAP:
			r = 218; g = 218; b = 218;
			break;
		case OBJ_BOMBTRAP:
			r = 218; g = 218; b = 218;
			break;
		case OBJ_LEFT:
			r = 218; g = 218; b = 218;
			break;
		case OBJ_RIGHT:
			r = 218; g = 218; b = 218;
			break;
		case OBJ_UP:
			r = 218; g = 218; b = 218;
			break;
		case OBJ_DOWN:
			r = 218; g = 218; b = 218;
			break;
		case OBJ_DOOR:
			r = 130; g = 255; b = 0;
			break;
		default:
			r = 161; g = 116; b = 40;
			break;
		}
		
		HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(r, g, b));
		HBRUSH oldBrush = (HBRUSH)SelectObject(CAMERAMANAGER->getCameraDC(), myBrush);
		Rectangle(CAMERAMANAGER->getCameraDC(), _pCurrentMap[i].rc.left / 6 + WINSIZEX/2 + 200- renge, _pCurrentMap[i].rc.top / 6 + WINSIZEX/2-100- renge, _pCurrentMap[i].rc.right / 6 + WINSIZEX/2 + 200 + renge, _pCurrentMap[i].rc.bottom / 6 + WINSIZEX/2-100+ renge);
		SelectObject(CAMERAMANAGER->getCameraDC(), oldBrush);
		DeleteObject(myBrush);
	}
	for (int i = 0; i < MONSTERMANAGER->getMonster().size(); i++)
	{
		if (!_pCurrentMap[MONSTERMANAGER->getMonster()[i]->currentTile()].look)continue;
	
		HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(255, 0, 0));
		HBRUSH oldBrush = (HBRUSH)SelectObject(CAMERAMANAGER->getCameraDC(), myBrush);
		Rectangle(CAMERAMANAGER->getCameraDC(), _pCurrentMap[MONSTERMANAGER->getMonster()[i]->currentTile()].rc.left / 6 + WINSIZEX/2 + 200 - renge, _pCurrentMap[MONSTERMANAGER->getMonster()[i]->currentTile()].rc.top / 6 + WINSIZEX/2-100 - renge, _pCurrentMap[MONSTERMANAGER->getMonster()[i]->currentTile()].rc.right / 6 + WINSIZEX/2 + 200 + renge, _pCurrentMap[MONSTERMANAGER->getMonster()[i]->currentTile()].rc.bottom / 6 + WINSIZEX/2-100 + renge);
		SelectObject(CAMERAMANAGER->getCameraDC(), oldBrush);
		DeleteObject(myBrush);
	}
	for (int i = 0; i < ITEMMANAGER->getItemList().size(); i++)
	{
		if (!_pCurrentMap[ITEMMANAGER->getItemList()[i]->getCurrentTile()].look)continue;
		HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(69, 137, 92));
		HBRUSH oldBrush = (HBRUSH)SelectObject(CAMERAMANAGER->getCameraDC(), myBrush);
		Rectangle(CAMERAMANAGER->getCameraDC(), _pCurrentMap[ITEMMANAGER->getItemList()[i]->getCurrentTile()].rc.left / 6 + WINSIZEX/2 + 200 - renge, _pCurrentMap[ITEMMANAGER->getItemList()[i]->getCurrentTile()].rc.top / 6 + WINSIZEX/2-100 - renge, _pCurrentMap[ITEMMANAGER->getItemList()[i]->getCurrentTile()].rc.right / 6 + WINSIZEX/2 + 200 + renge, _pCurrentMap[ITEMMANAGER->getItemList()[i]->getCurrentTile()].rc.bottom / 6 + WINSIZEX/2-100 + renge);
		SelectObject(CAMERAMANAGER->getCameraDC(), oldBrush);
		DeleteObject(myBrush);
	}

	HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(0, 0, 255));
	HBRUSH oldBrush = (HBRUSH)SelectObject(CAMERAMANAGER->getCameraDC(), myBrush);
	Rectangle(CAMERAMANAGER->getCameraDC(), _pCurrentMap[_currentTileIndex].rc.left / 6 + WINSIZEX/2 + 200 - renge, _pCurrentMap[_currentTileIndex].rc.top / 6 + WINSIZEX/2-100 - renge, _pCurrentMap[_currentTileIndex].rc.right / 6 + WINSIZEX/2 + 200 + renge, _pCurrentMap[_currentTileIndex].rc.bottom / 6 + WINSIZEX/2-100 + renge);
	SelectObject(CAMERAMANAGER->getCameraDC(), oldBrush);
	DeleteObject(myBrush);

	SelectObject(CAMERAMANAGER->getCameraDC(), h_old_pen);
	DeleteObject(h_null_pen);
}
