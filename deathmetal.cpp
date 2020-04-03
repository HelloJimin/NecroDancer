#include "stdafx.h"
#include "deathmetal.h"


deathmetal::deathmetal()
{
}


deathmetal::~deathmetal()
{
}

HRESULT deathmetal::init(string name, int x, int y, int coin, tagTile * map)
{
	monster::init(name, x, y, coin, map);
	_monsterNameImg = IMAGEMANAGER->findImage("µ•Ω∫∏ﬁ≈ª¿Ã∏ß");
	_aStar = new aStar;
	_isBoss = true;

	_atk = 1.5f;
	for(int i = 0 ; i<12; i++)
	{
		addHp();
	}

	_direction = LEFT;
	_phase = PHASE_ONE;
	_turnSpeed = 3;
	for (int i = 0; i < 737; ++i)
	{
		if (_pCurrentMap[i].terrain != TERRAIN_GROUND) continue;
		_field.push_back(i);
	}
	for (int i = 0; i < 12; i++)
	{
		_phaseThreeField.push_back(253 + (i*TILEX));
		_phaseThreeField.push_back(263 + (i*TILEX));
	}
	summon("π⁄¡„");
	summon("π⁄¡„");
	summon("π⁄¡„");

	return S_OK;
}

void deathmetal::update()
{
	if (_isBeat)
	{
		_isSkill = false;
		_turnCnt++;
	}

	_pCurrentMap[_currentTileIndex].walkable = false;

	choiceAction();

	attack();
	move();

	animation();
	hpSet();

	if (_delay && _isBeat)
	{
		_isBreath = true;
		_isAttack = true;
	}
}

void deathmetal::frontCheck()
{
	switch (_phase)
	{
	case PHASE_ONE:
		_nextTileIndex = _aStar->aStarTile(_pCurrentMap, _currentTileIndex, PLAYER->currentTile());

		break;
	case PHASE_TWO:
		_nextTileIndex = _aStar->randomMove(_pCurrentMap,_currentTileIndex);
			//aStarReverse(_pCurrentMap, _currentTileIndex, endTileFind());

		break;
	case PHASE_THREE:
		int metal;
		int player;
		for (int i = 0; i < _phaseThreeField.size(); i += 2)
		{
			if (_phaseThreeField[i] <= PLAYER->currentTile() && PLAYER->currentTile() <= _phaseThreeField[i + 1])
			{
				player = i;
			}
			if (_phaseThreeField[i] <= _currentTileIndex && _currentTileIndex <= _phaseThreeField[i + 1])
			{
				metal = i;
			}
		}

		if (metal == player)
		{
			_nextTileIndex = _currentTileIndex;
			_isSkill = true;
			_delay = true;
			SOUNDMANAGER->play("deathmetal_fireball");
			return;
		}

		if (endLineCheck())
		{
			if (metal > player) _nextTileIndex = _currentTileIndex - TILEX;
			else if (metal < player) _nextTileIndex = _currentTileIndex + TILEX;
		}
		else
		{
			_nextTileIndex = _aStar->aStarReverse(_pCurrentMap, _currentTileIndex, endTileFind());
		}

		break;
	}
	aniCheck();
}

void deathmetal::choiceAction()
{
	if (_isMove) return;
	if (_delay) return;

	if (_isBeat)
	{
		_isBeat = false;
		frontCheck();
		switch (_phase)
		{
		case PHASE_ONE:
			if (playerCheck())
			{
				_isAttack = true;
				_nextTileIndex = _currentTileIndex;
				return;
			}
			break;
		case PHASE_TWO:
			if (_turnCnt % 6 == 0 )
			{
				_isSkill = true;
				summon("Ω∫ƒÃ∑π≈Ê");
				summon("Ω∫ƒÃ∑π≈Ê");
				summon("Ω∫ƒÃ∑π≈Ê");
				SOUNDMANAGER->play("deathmetal_fireball");
				return;
			}
			break;
		case PHASE_THREE:
			if (_isBreath)
			{
				_isSkill = true;
				_isAttack = true;
				return;
			}

			if (playerCheck())
			{
				_isAttack = true;
				_nextTileIndex = _currentTileIndex;
				return;
			}
			break;		
		}

		if (walkableCheck())
		{
			_isMove = true;
			if (_currentTileIndex == _nextTileIndex)_isMove = false;

			_pCurrentMap[_currentTileIndex].walkable = true;
			_pCurrentMap[_nextTileIndex].walkable = false;
			EFFECTMANAGER->play("¡°«¡∏’¡ˆ", _currentX, _currentY);
			_currentTileIndex = _nextTileIndex;
		}
		else
		{
			_isMove = false;
			_nextTileIndex = _currentTileIndex;
		}
	}
}

void deathmetal::animation()
{
	if (BEAT->getCnt() % 12 == 0)
	{
		_frameX++;
		if (_frameX > _monsterImg->getMaxFrameX())_frameX = 0;
	}
}

void deathmetal::hpSet()
{
	for (int i = 0; i < _vHp.size(); ++i)
	{
		if (_vHp[i].hp <= 0.0f) _vHp[i].currentX = 2;
		if (_vHp[i].hp == 0.5f) _vHp[i].currentX = 1;
		if (_vHp[i].hp == 1.0f) _vHp[i].currentX = 0;

		_vHp[i].rc = RectMakeCenter(_collisionRc.right + _vHp[i].img->getFrameWidth() - (i*_vHp[i].img->getFrameWidth()) / 2, _collisionRc.top - _vHp[i].img->getFrameHeight() * 3, _vHp[i].img->getFrameWidth(), _vHp[i].img->getFrameHeight());


		/*	if(i<4) _vHp[i].rc = RectMakeCenter(_collisionRc.left+(i*_vHp[i].img->getFrameWidth())/2, _collisionRc.top - _vHp[i].img->getFrameHeight()*3, _vHp[i].img->getFrameWidth(), _vHp[i].img->getFrameHeight());
			else   _vHp[i].rc = RectMakeCenter(_collisionRc.left + ((i-4)*_vHp[i].img->getFrameWidth()) / 2, _collisionRc.top - _vHp[i].img->getFrameHeight()*2, _vHp[i].img->getFrameWidth(), _vHp[i].img->getFrameHeight());*/
	}
}

bool deathmetal::die()
{
	for (int i = 0; i < _vHp.size(); ++i)
	{
		if (_vHp[i].hp > 0.0f) return false;
	}
	for (int i = 97; i < 100; i++)
	{
		for (int k = 0; k < 4; k++)
		{
			_pCurrentMap[i + (k*TILEX)].walkable = true;
		}
	}
	for (int i = 217; i < 220; i++)
	{
		_pCurrentMap[i].obj = OBJ_NONE;
		_pCurrentMap[i].objFrameX = 0;
		_pCurrentMap[i].objFrameY = 0;

	}

	BEAT->addHint("Ω¬∏Æ");
	SOUNDMANAGER->play("deathmetal_death");
	return true;
}

void deathmetal::render(HDC hdc)
{
	if (KEYMANAGER->isToggleKey(VK_TAB)) Rectangle(hdc, _collisionRc.left, _collisionRc.top, _collisionRc.right, _collisionRc.bottom);
	//switch (_direction)
	//{
	//case LEFT:
	//	_monsterImg->frameRender(hdc, _collisionRc.left - TILEX * 2 - TILEX / 2, _collisionRc.top - _monsterImg->getFrameHeight() + TILEX, _frameX, _frameY);

	//	break;
	//case RIGHT:
	//	_monsterImg->frameRender(hdc, _collisionRc.left - TILEX * 2 , _collisionRc.top - _monsterImg->getFrameHeight() + TILEX, _frameX, _frameY);

	//	break;
	//case UP:
	//	_monsterImg->frameRender(hdc, _collisionRc.left - TILEX * 2 , _collisionRc.top - _monsterImg->getFrameHeight() + TILEX, _frameX, _frameY);

	//	break;
	//case DOWN:
	//	_monsterImg->frameRender(hdc, _collisionRc.left - TILEX * 2 - TILEX / 2, _collisionRc.top - _monsterImg->getFrameHeight() + TILEX, _frameX, _frameY);

	//	break;
	//}
	if (_isSkill)
	{
		_monsterImg->frameRender(hdc, _collisionRc.left - TILEX * 2 - TILEX / 2, _collisionRc.top - _monsterImg->getFrameHeight() + TILEX + TILEX / 2-10 , _frameX, _frameY + 2);
	}
	else
	{
		_monsterImg->frameRender(hdc, _collisionRc.left - TILEX * 2 - TILEX / 2, _collisionRc.top - _monsterImg->getFrameHeight() + TILEX + TILEX / 2-10, _frameX, _frameY);
	}
	hpRender(hdc);
}

void deathmetal::silhouetteRender(HDC hdc)
{
	if (KEYMANAGER->isToggleKey(VK_TAB)) Rectangle(hdc, _collisionRc.left, _collisionRc.top, _collisionRc.right, _collisionRc.bottom);
	if (_isSkill)
	{
		_monsterImg->frameRender(hdc, _collisionRc.left - TILEX * 2 - TILEX / 2, _collisionRc.top - _monsterImg->getFrameHeight() + TILEX + TILEX / 2-10, _frameX, _frameY + 6);
	}
	else
	{
		_monsterImg->frameRender(hdc, _collisionRc.left - TILEX * 2 - TILEX / 2, _collisionRc.top - _monsterImg->getFrameHeight() + TILEX + TILEX / 2-10, _frameX, _frameY+4);
	}
	hpRender(hdc);
}

void deathmetal::attack()
{
	if (!_isAttack) return;

	if (_isBreath)
	{
		_delay = false;
		_isSkill = false;
		_isAttack = false;
		_isBreath = false;
		int _breathRengeL = 0;
		int _breathRengeR = 0;
		int _leftTile = _currentTileIndex - 1;
		int _rightTile = _currentTileIndex + 1;


		EFFECTMANAGER->play("µÂ∑°∞Ô∫Í∑πΩ∫1L", _pCurrentMap[_leftTile].x, _pCurrentMap[_leftTile].y);
		while (rengeCheck(_leftTile))
		{
			_breathRengeL++;
			_leftTile--;
		}

		EFFECTMANAGER->play("µÂ∑°∞Ô∫Í∑πΩ∫1R", _pCurrentMap[_rightTile].x, _pCurrentMap[_rightTile].y);
		while (rengeCheck(_rightTile))
		{
			_breathRengeR++;
			_rightTile++;
		}
	
		char breath[128];
		//2,3,4,5

		for (int i = 0; i < _breathRengeL; i++)
		{
			wsprintf(breath, "µÂ∑°∞Ô∫Í∑πΩ∫%d", i % 4 + 2);

			EFFECTMANAGER->play(breath, _pCurrentMap[_currentTileIndex - 1].x - ((i + 1) * 52), _pCurrentMap[_currentTileIndex - 1].y);
			if (_currentTileIndex - 1 - i == PLAYER->currentTile()) PLAYER->hit(_atk , _monsterNameImg);
			_isAttack = false;
		}
		for (int i = 0; i < _breathRengeR; i++)
		{
			wsprintf(breath, "µÂ∑°∞Ô∫Í∑πΩ∫%d", i % 4 + 2);

			EFFECTMANAGER->play(breath, _pCurrentMap[_currentTileIndex + 1].x + ((i + 1) * 52), _pCurrentMap[_currentTileIndex + 1].y);
			if (_currentTileIndex + 1 + i == PLAYER->currentTile()) PLAYER->hit(_atk , _monsterNameImg);
			_isAttack = false;
		}

		return;
	}

	monster::attack();
}

bool deathmetal::rengeCheck(int tile)
{
	if (_pCurrentMap[tile].obj == OBJ_NOMALWALL)return false;
	if (_pCurrentMap[tile].obj == OBJ_SKULLWALL)return false;
	if (_pCurrentMap[tile].obj == OBJ_WHITEWALL)return false;
	if (_pCurrentMap[tile].obj == OBJ_GOLDWALL)return false;
	if (_pCurrentMap[tile].obj == OBJ_IRONWALL)return false;
	if (_pCurrentMap[tile].obj == OBJ_NEVERWALL)return false;

	else return true;
}

void deathmetal::move()
{
	if (!_isMove) return;
	switch (_direction)
	{
	case LEFT:
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
		else if (_isDrop&& getDistance(_currentX, _currentY, _pCurrentMap[_nextTileIndex].x, _pCurrentMap[_nextTileIndex].y) == 0)
		{
			_isDrop = false;
			_isMove = false;
		}
		break;
	case RIGHT:
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
	_collisionRc = RectMakeCenter(_currentX, _currentY, 50, 50);
}

void deathmetal::aniCheck()
{

	if (_nextTileIndex == _currentTileIndex - 1) _direction = LEFT;
	else if (_nextTileIndex == _currentTileIndex + 1) _direction = RIGHT;
	else if (_nextTileIndex == _currentTileIndex + TILEX)_direction = DOWN;
	else if (_nextTileIndex == _currentTileIndex - TILEX)_direction = UP;

	if (_phase == PHASE_ONE)
	{
		switch (_direction)
		{
		case LEFT:_frameY = 0;
			break;
		case RIGHT:_frameY = 1;
			break;
		case UP:_frameY = 3;
			break;
		case DOWN:_frameY = 2;
			break;
		}
	}
	else
	{
		switch (_direction)
		{
		case LEFT:_frameY = 0;
			break;
		case RIGHT:_frameY = 1;
			break;
		}

	}
}

void deathmetal::hit(float damage)
{
	if (_phase == PHASE_ONE)
	{
		DIRECTION pDirection = PLAYER->getPlayerDir();
		if (_direction == 0 && pDirection == 1 || _direction == 1 && pDirection == 0 ||
			_direction == 2 && pDirection == 3 || _direction == 3 && pDirection == 2)
		{
			if (_isMove)return;
			summon("π⁄¡„");
			summon("π⁄¡„");
			summon("π⁄¡„");
			//π⁄¡„º“»ØΩ∫≈≥ º“∏Æ √ﬂ∞°§°§°
			SOUNDMANAGER->play("deathmetal_shieldhit");
			BEAT->addHint("∫∏»£∏∑ø°∏∑»˚");
			switch (_direction)
			{
			case LEFT:
				_nextTileIndex = _currentTileIndex + 1;
				_direction = RIGHT;
				break;
			case RIGHT:
				_nextTileIndex = _currentTileIndex - 1;
				_direction = LEFT;
				break;
			case UP:
				_nextTileIndex = _currentTileIndex + TILEX;
				_direction = DOWN;
				break;
			case DOWN:
				_nextTileIndex = _currentTileIndex - TILEX;
				_direction = UP;
				break;
			}
			if (walkableCheck())
			{
				_isMove = true;
				_pCurrentMap[_currentTileIndex].walkable = true;
				_pCurrentMap[_nextTileIndex].walkable = false;
				_currentTileIndex = _nextTileIndex;
			}
			return;
		}
	}
	SOUNDMANAGER->play("deathmetal_hit");
	_delay = false;
	_isSkill = false;
	_isHit = true;
	_hitCnt++;

	//if (_hitCnt == 1)
	//{
	//	_turnSpeed = 2;
	//	_phase = PHASE_THREE;
	//	_monsterImg = IMAGEMANAGER->findImage("µ•Ω∫∏ﬁ≈ª2");
	//}
	if (currentHpCheck()<= 5)
	{
		_turnSpeed = 2;
		_phase = PHASE_THREE;
	}
	else if (currentHpCheck() <= 9)
	{
		_turnSpeed = 2;
		_phase = PHASE_TWO;
		_monsterImg = IMAGEMANAGER->findImage("µ•Ω∫∏ﬁ≈ª2");
	}
	//if (_hitCnt == 6) _phase = PHASE_THREE;

	for (int i = 0; i < _vHp.size(); i++)
	{
		if (_vHp[i].hp <= 0) continue;

		if (damage > 0)
		{
			float temp = _vHp[i].hp;
			_vHp[i].hp -= damage;
			damage -= temp;
		}
		else break;
	}

	if (_phase != PHASE_ONE && !_isMove)
	{
		teleport();
	}
}

void deathmetal::teleport()
{
	int summonPosition;
	bool ok = true;

	while (ok)
	{
		int random = RND->getInt(_field.size());
		summonPosition = _field[random];

		if (_pCurrentMap[_field[random]].walkable) ok = false;
	}

	_pCurrentMap[_currentTileIndex].walkable = true;

	_currentTileIndex = summonPosition;
	_currentX = _pCurrentMap[_currentTileIndex].x;
	_currentY = _pCurrentMap[_currentTileIndex].y;
	_nextTileIndex = summonPosition + TILEX;
	_direction = DOWN;
	_collisionRc = RectMakeCenter(_currentX, _currentY, 50, 50);

	//_isMove = true;
}

void deathmetal::summon(string name)
{
	if (MONSTERMANAGER->getMonster().size() > 6) return;
	int summonPosition;
	bool ok = true;

	while (ok)
	{
		int random = RND->getInt(_field.size());
		summonPosition = _field[random];

		if (_pCurrentMap[_field[random]].walkable) ok = false;
	}

	if(name == "Ω∫ƒÃ∑π≈Ê") MONSTERMANAGER->summonSkeleton("Ω∫ƒÃ∑π≈Ê", _pCurrentMap[summonPosition].x, _pCurrentMap[summonPosition].y);
	else if(name == "π⁄¡„") MONSTERMANAGER->summonBat("π⁄¡„", _pCurrentMap[summonPosition].x, _pCurrentMap[summonPosition].y);
}

int deathmetal::endTileFind()
{
	int check = 20000;
	int endTile;
	if (_phase == PHASE_TWO)
	{
		int currentIndex = _currentTileIndex;
		int endIndex = PLAYER->currentTile();

		endTile = currentIndex + (currentIndex - endIndex) * 3;
		if (endTile < 0) endTile = 0;

		int dx[] = { 703, 693, 253, 263 };
		int end = 0;

		for (int i = 0; i < 4; i++)
		{
			if (dx[i] == endIndex) continue;
			int endt = abs(endTile - dx[i]);
			if (endt < check)
			{
				check = endt;
				end = dx[i];
			}
		}
		endTile = end;
		return endTile;
	}

	for (int i = 0; i < _phaseThreeField.size(); ++i)
	{
		int endt = abs(_currentTileIndex - _phaseThreeField[i]);
		if (endt < check)
		{
			check = endt;
			endTile = _phaseThreeField[i];
		}
	}
	return endTile;
	
}

bool deathmetal::endLineCheck()
{
	for (int i = 0; i < _phaseThreeField.size(); i++)
	{
		if (_currentTileIndex == _phaseThreeField[i]) return true;
	}

	return false;
}

int deathmetal::currentHpCheck()
{
	float hp = 0;
	for (int i = 0; i < _vHp.size(); ++i)
	{
		if (_vHp[i].hp > 0) hp += _vHp[i].hp;
	}

	return hp;
}
