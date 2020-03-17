#include "stdafx.h"
#include "player.h"

player::player(){}
player::~player(){}

HRESULT player::init()
{

	_bodyImg = IMAGEMANAGER->findImage("몸통R");
	_headImg = IMAGEMANAGER->findImage("케이던스R");

	//플레이어 시작위치
	_currentX = _collisionX = 494;
	_currentY = _collisionY = 390;
	
	_rc = RectMakeCenter(_currentX, _currentY, 50, 50);
	_collisionRc = RectMakeCenter(_collisionX, _collisionY, 50, 50);
	
	_currentTileIndex = 373;
	_nextTileIndex = 374;

	_direction = DOWN;

	_isMove = false;
	_moveSpeed = 13;
	_coin = _diamond = 0;

	_rhythm = 0;


	//스탯
	_hp.currentX = 2;
	_hp.img = IMAGEMANAGER->findImage("HP바");
	_hp.hp = 1.0f;

	_status.atk = 0;
	_status.def = 0;
	_status.minePower = 0;
	_status.vHp.push_back(_hp);
	_status.vHp.push_back(_hp);
	_status.vHp.push_back(_hp);

	HPbarSet();

	_inven = new inventory;
	_inven->init();

	return S_OK;
}

void player::release()
{
	SAFE_DELETE(_inven);
}

void player::update()
{
	//if (KEYMANAGER->isOnceKeyDown('C'))
	//{
	//	EFFECTMANAGER->play("드래곤브레스1", _pCurrentMap[_currentTileIndex + 1].x, _pCurrentMap[_currentTileIndex + 1].y);
	//	EFFECTMANAGER->play("드래곤브레스2", _pCurrentMap[_currentTileIndex + 1].x+48, _pCurrentMap[_currentTileIndex + 2].y);
	//	EFFECTMANAGER->play("드래곤브레스3", _pCurrentMap[_currentTileIndex + 1].x+48*2, _pCurrentMap[_currentTileIndex + 3].y);
	//	EFFECTMANAGER->play("드래곤브레스4", _pCurrentMap[_currentTileIndex + 1].x+48*3, _pCurrentMap[_currentTileIndex + 4].y);
	//	EFFECTMANAGER->play("드래곤브레스5", _pCurrentMap[_currentTileIndex + 1].x+48*4, _pCurrentMap[_currentTileIndex + 5].y);
	//}
	_inven->update();
	keyControl();
	move();
	animation();
}

void player::render(HDC hdc)
{
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

	//앞타일을 맞춰줌
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

	//타일 앞의 몬스터 판별 있을시 공격
	if (_equipWeapon)
	{
		_inven->getWeapon()->active();
		for (int i = 0; i < _status.atkRenge.size(); ++i)
		{
			for (int k = 0; k < MONSTERMANAGER->getMonster().size(); ++k)
			{
				if (_status.atkRenge[i] == MONSTERMANAGER->getMonster()[k]->currentTile())
				{
					MONSTERMANAGER->getMonster()[k]->hit(_status.atk);

					switch (_direction)
					{
					case LEFT:
						EFFECTMANAGER->play("단검L", MONSTERMANAGER->getMonster()[k]->getXY().x, MONSTERMANAGER->getMonster()[k]->getXY().y);
						break;
					case RIGHT:
						EFFECTMANAGER->play("단검R", MONSTERMANAGER->getMonster()[k]->getXY().x, MONSTERMANAGER->getMonster()[k]->getXY().y);
						break;
					case UP:
						EFFECTMANAGER->play("단검Up", MONSTERMANAGER->getMonster()[k]->getXY().x, MONSTERMANAGER->getMonster()[k]->getXY().y);
						break;
					case DOWN:
						EFFECTMANAGER->play("단검Down", MONSTERMANAGER->getMonster()[k]->getXY().x, MONSTERMANAGER->getMonster()[k]->getXY().y);
						break;
					}
					return;
				}
			}
		}
	}
	//앞타일 벽이 아니면 이동
	if (wallCheck())
	{
		if (_pCurrentMap[_nextTileIndex].item != NULL)
		{
			getItem();
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

void player::move()
{
	if (!_isMove)return;
	
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
			_collisionY -= _moveSpeed;
		}

		if (!_isDrop&& getDistance(_currentX, _currentY, _pCurrentMap[_nextTileIndex].x, _pCurrentMap[_nextTileIndex].y - 26) != 0)
		{
			_currentY -= _moveSpeed;
		}
		else _isDrop = true;

		if (_isDrop&& getDistance(_currentX, _currentY, _pCurrentMap[_nextTileIndex].x, _pCurrentMap[_nextTileIndex].y) != 0)
		{
			_currentY += _moveSpeed;
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
			_collisionY += _moveSpeed;
		}

		if (!_isDrop&& getDistance(_currentX, _currentY, _pCurrentMap[_nextTileIndex].x, _pCurrentMap[_nextTileIndex].y - 78) != 0)
		{
			_currentY -= _moveSpeed;
		}
		else _isDrop = true;

		if (_isDrop&& getDistance(_currentX, _currentY, _pCurrentMap[_nextTileIndex].x, _pCurrentMap[_nextTileIndex].y) != 0)
		{
			_currentY += _moveSpeed;
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

	for (int i = 0; i < _status.vHp.size(); i++)
	{
		_status.vHp[i].img->frameRender(CAMERAMANAGER->getCameraDC(), _status.vHp[i].rc.left, _status.vHp[i].rc.top, _status.vHp[i].currentX,0);
	}
	//인벤토리 렌더....
	_inven->render(hdc);

	//우상단 코인다이아 부분 렌더
	IMAGEMANAGER->render("코인다이아", CAMERAMANAGER->getCameraDC(), WINSIZEX - 50*3 , 20 );
	SetTextColor(CAMERAMANAGER->getCameraDC(), RGB(255, 255, 255));
	HFONT myFont = CreateFont(20, 0, 0, 0, 800, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, TEXT("굴림"));
	HFONT oldFont = (HFONT)SelectObject(CAMERAMANAGER->getCameraDC(), myFont);
	wsprintf(_str, "x%d", _coin);
	TextOut(CAMERAMANAGER->getCameraDC(), WINSIZEX - 60, 40 ,  _str, strlen(_str));
	wsprintf(_str, "x%d", _diamond);
	TextOut(CAMERAMANAGER->getCameraDC(), WINSIZEX - 60, 85, _str, strlen(_str));
	SelectObject(CAMERAMANAGER->getCameraDC(), oldFont);
	DeleteObject(myFont);

	wsprintf(_str, "박자맞춘 횟수%d", _rhythm);
	TextOut(CAMERAMANAGER->getCameraDC(), WINSIZEX - 60, 125, _str, strlen(_str));

}

void player::setMap(tagTile tile[])
{
	_pCurrentMap = NULL;
	_pCurrentMap = tile;
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (tile[i].startPoint == "플레이어")
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

	//if (KEYMANAGER->isOnceKeyDown('J')) //회복
	//{
	//	for (int i = _vHp.size()-1; i >= 0; i--)
	//	{
	//		if (_vHp[i].hp <= 0.5f)
	//		{
	//			_vHp[i].hp += 0.5f;
	//			break;
	//		}
	//		else continue;
	//	}
	//}
	//if (KEYMANAGER->isOnceKeyDown('K')) //추가
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
	}
	else _rhythm = 0;
}

void player::getItem()
{
	if (_pCurrentMap[_nextTileIndex].item->getName() == "코인")
	{
		_coin += _pCurrentMap[_nextTileIndex].item->getValue();
		_pCurrentMap[_nextTileIndex].item = NULL;
		return;
	}


	if (_inven->getItemList().empty())
	{
		_inven->addItem(_pCurrentMap[_nextTileIndex].item);
		_pCurrentMap[_nextTileIndex].item = NULL;
	}
	else
	{
		int check = 0;
		for (int i = 0; i < _inven->getItemList().size(); ++i)
		{
			if (_inven->getItemList()[i]->getType() != _pCurrentMap[_nextTileIndex].item->getType())
			{
				check++;
			}
			if (_inven->getItemList()[i]->getType() == _pCurrentMap[_nextTileIndex].item->getType())
			{
				_inven->swapItem(i, _pCurrentMap[_nextTileIndex].item);
				break;
			}

			if (check == _inven->getItemList().size())
			{
				_inven->addItem(_pCurrentMap[_nextTileIndex].item);
				_pCurrentMap[_nextTileIndex].item = NULL;
				break;
			}
		}
	}
}

void player::hit(float damege)
{
	for (int i = 0; i < _status.vHp.size(); i++)
	{
		if (_status.vHp[i].hp <= 0) continue;
		
		if (damege > 0)
		{
			float temp = _status.vHp[i].hp;
			_status.vHp[i].hp -= damege;
			damege -= temp;
		}
		else break;
	}

	_rhythm = 0;
	HPbarSet();
}

void player::keyControl()
{
	if (_isMove) return;
	
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		if (BEAT->getCheck())
		{
			_direction = LEFT;
			BEAT->removeNote();
			frontCheck();
		}
		else
		{
			BEAT->addMiss();
			_rhythm = 0;
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		if (BEAT->getCheck())
		{
			_direction = RIGHT;
			BEAT->removeNote();
			frontCheck();
		}
		else
		{
			BEAT->addMiss();
			_rhythm = 0;
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		if (BEAT->getCheck())
		{
			_direction = UP;
			BEAT->removeNote();
			frontCheck();
		}
		else
		{
			BEAT->addMiss();
			_rhythm = 0;
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		if (BEAT->getCheck())
		{
			_direction = DOWN;
			BEAT->removeNote();
			frontCheck();
		}
		else
		{
			BEAT->addMiss();
			_rhythm = 0;
		}
	}
}

void player::animation()
{
	switch (_direction)
	{
	case LEFT:
		_bodyImg = IMAGEMANAGER->findImage("몸통L");
		_headImg = IMAGEMANAGER->findImage("케이던스L");
		break;
	case RIGHT:
		_bodyImg = IMAGEMANAGER->findImage("몸통R");
		_headImg = IMAGEMANAGER->findImage("케이던스R");
		break;
	}

	//애니메이션 움직임
	if (BEAT->getCnt() % 12 == 0)
	{
		_frameX++;
		if (_frameX > _bodyImg->getMaxFrameX())_frameX = 0;
	}
}

bool player::wallCheck()
{
	if (_pCurrentMap[_nextTileIndex].walkable) return true;

	return false;
}

bool player::monsterCheck()
{
	if(!_inven->getWeapon()) return false;



}


