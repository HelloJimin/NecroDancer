#include "stdafx.h"
#include "beat.h"


beat::beat()
{
}


beat::~beat()
{
}

HRESULT beat::init()
{
	//턴초기화
	//load("1-1");

	_currentMap = "lobby";

	_cnt = 0;
	_anime = 0;	
	_okTime = 0;

	_heart = IMAGEMANAGER->findImage("심장");
	_heartBox = RectMakeCenter(WINSIZEX / 2, WINSIZEY - 100, 90, _heart->getFrameHeight());
	_collisionHeart = RectMakeCenter(WINSIZEX / 2, WINSIZEY - 120, 130, 50 * 2);

	return S_OK;
}

void beat::release()
{
}

void beat::update()
{
	_cnt++;

	if (_currentMap == "lobby")
	{
		_okTime = 1;
		return;
	}
	SOUNDMANAGER->getPosition(_currentMap, _songPos);
	if (_songPos > 0)
	{
		beatStart();
		noteMove();
		checkBeat();

		if (_currentNoteCnt > _vRenge.size() - 5)
		{
			_currentNoteCnt = 3;
			_noteTiming = 0;
		}
	}
	missUpdate();
}

void beat::render(HDC hdc)
{
	//박자부분 렌더
	for (int i = 0; i < _vMiss.size(); i++)
	{
		_vMiss[i].img->render(CAMERAMANAGER->getCameraDC(), _vMiss[i].rc.left, _vMiss[i].rc.top);
	}
	for (int i = 0; i < _vNoteL.size(); i++)
	{
		if (!_vNoteL[i].render)continue;
		_vNoteL[i].img->alphaRender(CAMERAMANAGER->getCameraDC(), _vNoteL[i].rc.left, _vNoteL[i].rc.top, 255);
		_vNoteR[i].img->alphaRender(CAMERAMANAGER->getCameraDC(), _vNoteR[i].rc.left, _vNoteR[i].rc.top, 255);
	}
	_heart->frameRender(CAMERAMANAGER->getCameraDC(), _heartBox.left, _heartBox.top, _anime, 0);

	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		Rectangle(CAMERAMANAGER->getCameraDC(), _collisionHeart.left, _collisionHeart.top, _collisionHeart.right, _collisionHeart.bottom);
		Rectangle(CAMERAMANAGER->getCameraDC(), _heartBox.left, _heartBox.top, _heartBox.right, _heartBox.bottom);
		
		UINT b = SOUNDMANAGER->getPosition(_currentMap,b);
	
		char str[128];
		wsprintf(str, "%d", _songLength);
		TextOut(CAMERAMANAGER->getCameraDC(), WINSIZEX / 2, WINSIZEY / 2,str, strlen(str));
		wsprintf(str, "%d", b);
		TextOut(CAMERAMANAGER->getCameraDC(), WINSIZEX / 2, WINSIZEY / 2+100, str,strlen(str));
	}
}
void beat::load(string map)
{
	ifstream readFile;
	string tempWord;
	if(map=="1-1") readFile.open("sound/1-1.txt"); // 파일 열기
	else if(map=="1-2") readFile.open("sound/1-2.txt"); // 파일 열기
	else if(map=="boss") readFile.open("sound/boss.txt"); // 파일 열기
	
	if (readFile.is_open()) // 파일이 정상적으로 열려있다면
	{
		while (!readFile.eof()) // 읽어오는 파일의 끝을 만날때까지 반복
		{
			char temp; // 문자를 하나씩 뽑기 위한 변수
			readFile.get(temp); // 문자 하나 뽑기 
			if (temp == ',')
			{
				//++_countComma; // 콤마 세기
				_vRenge.push_back(atoi(tempWord.c_str())); // 변환 순서 : 문자열 -> char*로 변환 -> atoi는 char*을 int로 변환
				tempWord = ""; // string 초기화
				continue;
			}
			tempWord += temp; // 한 글자씩 string에 합침
		}
		//_msTimeInfo.erase(_msTimeInfo.begin() + (_msTimeInfo.size() - 1)); // 현재 구조상 맨 마지막 부분에 0을 항상 저장하므로 맨 마지막 요소를 제거함
		readFile.close(); // 파일 닫기
	}

	_songLength = SOUNDMANAGER->getLength(_currentMap);
}

void beat::setMap(string currentMap)
{
	_currentMap = currentMap;
	if (_currentMap != _oldMap)
	{
		_vRenge.clear();
		_vNoteL.clear();
		_vNoteR.clear();
		TIMEMANAGER->setCountTime(0);
		TIMEMANAGER->setCountTimeResetSwitch(true); // 세는 시간 리셋
		TIMEMANAGER->setCountTimeSwitch(true); // 시간 세기 ON
		_deltaTime = TIMEMANAGER->getElapsedTime();
		_currentNoteCnt = 0;
		_cnt = 0;
		_okTime = 0;
		_noteStartTiming = 0;

		load(currentMap);
		_oldMap = _currentMap;
		_noteTiming = 0;
		int tempMS = _vRenge[_currentNoteCnt + 1] - _vRenge[_currentNoteCnt];
		//int tempMS =  _vRenge[_currentNoteCnt+1] - _vRenge[_currentNoteCnt]+ lapse;
		int bpm = 60000 / tempMS;
		//spd1 = lerp(0, WINSIZEX / 2, (_deltaTime / ((tempMS+bpm) / 1000.0f)) / 4);
		//spd2 = lerp(WINSIZEX , WINSIZEX / 2, (_deltaTime / ((tempMS + bpm) / 1000.0f)) / 4);
	}

	//for (int i = 0; i < 3; i++)
	//{
	//	int tempMS = _vRenge[_currentNoteCnt + 1] - _vRenge[_currentNoteCnt];
	//	int bpm = 60000 / tempMS;

	//	note _note;

	//	_note.img = IMAGEMANAGER->findImage("노트");
	//	_note.x = (float)(WINSIZEX / 2 - (WINSIZEX / 2 / 4 * (i + 1)));
	//	_note.y = WINSIZEY - 100;
	//	_note.rc = RectMakeCenter(_note.x, _note.y, _note.img->getWidth(), _note.img->getHeight());
	//	_note.alpha = 0;
	//	_note.speed = lerp(_note.x, _note.x+WINSIZEX/2/3, (_deltaTime / ((tempMS + bpm) / 1000.0f)));
	//	_note.render = true;
	//	_vNoteL.push_back(_note);
	//	_noteTiming = tempMS / 1000.0f;
	//	_currentNoteCnt++;
	//}
}


void beat::beatStart()
{
	_noteStartTiming = TIMEMANAGER->getCountTime()*1000.0f;
	if (_noteStartTiming >= _noteTiming)
	{
		float lapse = (_noteStartTiming - _noteTiming);
		addNote(lapse);

		TIMEMANAGER->setCountTime(0);
		_noteStartTiming = 0;
	}
}

void beat::addNote(float lapse)
{
	int tempMS =  _vRenge[_currentNoteCnt+1] - _vRenge[_currentNoteCnt];
	//int tempMS =  _vRenge[_currentNoteCnt+1] - _vRenge[_currentNoteCnt]+ lapse;
	int bpm = 60000 / tempMS;

	note _note;

	_note.img = IMAGEMANAGER->findImage("노트");
	_note.x = 0;
	_note.y = WINSIZEY - 100;
	_note.rc = RectMakeCenter(_note.x, _note.y, _note.img->getWidth(), _note.img->getHeight());
	_note.alpha = 0;
	_note.colHeart = false;
	_note.render = true;
	_note.speed = lerp(0, WINSIZEX/2, (_deltaTime / ((tempMS) / 1000.0f)) /4);
	//_note.speed = _deltaTime * tempMS / 2;


	_vNoteL.push_back(_note);

	_note.x = WINSIZEX;
	_note.rc = RectMakeCenter(_note.x, _note.y, _note.img->getWidth(), _note.img->getHeight());
	_note.speed = lerp(WINSIZEX, WINSIZEX/2, (_deltaTime / ((tempMS) / 1000.0f)) /4);
	//_note.speed = _deltaTime * tempMS * (tempMS/1000.0f);


	_vNoteR.push_back(_note);

	//_noteTiming += tempMS;
	_noteTiming = tempMS;
	_currentNoteCnt++;

	MONSTERMANAGER->setMove(_currentNoteCnt);
	
}

void beat::noteMove()
{
	for (int i = 0; i < _vNoteL.size();)
	{
		_vNoteL[i].x += _vNoteL[i].speed;
		_vNoteL[i].rc = RectMakeCenter(_vNoteL[i].x, _vNoteL[i].y, _vNoteL[i].img->getWidth(), _vNoteL[i].img->getHeight());

		_vNoteR[i].x += _vNoteR[i].speed;
		_vNoteR[i].rc = RectMakeCenter(_vNoteR[i].x, _vNoteR[i].y, _vNoteR[i].img->getWidth(), _vNoteR[i].img->getHeight());

		if (IntersectRect(&_temp, &_vNoteL[i].rc, &_heartBox))
		{
			if (!_vNoteL[i].colHeart) _isBeat = true;
			_vNoteL[i].colHeart = true;
			_okTime++;
			PLAYER->setIsBeat(true);
		}
		if (_vNoteL[i].x > WINSIZEX / 2)
		{
			_vNoteL[i].render = false;
			_vNoteR[i].render = false;
		}
		//if (_vNoteL[i].x-(_collisionHeart.right-_collisionHeart.left)/2 > WINSIZEX/2)
		if (_vNoteL[i].x - (_heart->getFrameWidth() / 2) > WINSIZEX / 2)
		{
			_vNoteL.erase(_vNoteL.begin() + i);
			_vNoteR.erase(_vNoteR.begin() + i);
			_okTime = 0;
			PLAYER->setIsBeat(false);
		}
		else
		{
			++i;
		}
	}
}

void beat::checkBeat()
{
	if (_okTime > 0) _check = true;
	else _check = false;
	
	if (_isBeat)
	{
		_anime++;
		if (_anime > _heart->getMaxFrameX())
		{
			_anime = 0;
			_isBeat = false;
		}
	}
}

void beat::removeNote()
{

	for (int i = 0; i < _vNoteL.size(); i++)
	{
		if (IntersectRect(&_temp, &_vNoteL[i].rc, &_collisionHeart))
		{
			_check = false;
			_vNoteL.erase(_vNoteL.begin() + i);
			_vNoteR.erase(_vNoteR.begin() + i);
			PLAYER->setIsBeat(false);
			break;
		}
	}
}

void beat::missUpdate()
{
	for (int i = 0; i < _vMiss.size(); i++)
	{
		_vMiss[i].rc.top -= _vMiss[i].speed;
		_vMiss[i].rc.bottom -= _vMiss[i].speed;

		if (_vMiss[i].rc.top <= _vMiss[i].max)
		{
			_vMiss.erase(_vMiss.begin() + i);
			break;
		}
	}
}

void beat::addMiss()
{
	miss _miss;

	_miss.alpha = 0;
	_miss.img = IMAGEMANAGER->findImage("빗나감");
	_miss.rc = RectMake(_heartBox.left, _heartBox.top, _miss.img->getWidth(), _miss.img->getHeight());
	_miss.speed = 1;
	_miss.max = WINSIZEY / 2 + 150;

	_vMiss.push_back(_miss);
}

void beat::addHint(string keyname)
{
	miss _temp;

	_temp.alpha = 0;
	_temp.img = IMAGEMANAGER->findImage(keyname);
	_temp.rc = RectMakeCenter(WINSIZEX/2, WINSIZEY/2, _temp.img->getWidth(), _temp.img->getHeight());
	_temp.speed = 1;
	_temp.max = WINSIZEY/2 - 100;
	_vMiss.push_back(_temp);
}
