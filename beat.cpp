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
	load("1-1");

	_cnt = 0;
	_anime = 0;
	_turn = 0;
	_okTime = 0;


	_heart = IMAGEMANAGER->findImage("심장");
	_heartBox = RectMakeCenter(WINSIZEX / 2, WINSIZEY - 100, _heart->getFrameWidth(), _heart->getFrameHeight());
	_collisionHeart = RectMakeCenter(WINSIZEX / 2, WINSIZEY - 100, 100, 50 * 2);

	_miss.alpha = 0;
	_miss.img = IMAGEMANAGER->findImage("빗나감");
	_miss.rc = RectMake(_heartBox.left, _heartBox.top, _miss.img->getWidth(), _miss.img->getHeight());
	_miss.speed = 1;
	_miss.max = WINSIZEY / 2 + 150;

	return S_OK;
}

void beat::release()
{
}

void beat::update()
{
	_cnt++;

	SOUNDMANAGER->getPosition(_currentMap, _songPos);
	if (_songPos > 0)
	{
		checkBeat();
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
	}
	_heart->frameRender(CAMERAMANAGER->getCameraDC(), _heartBox.left, _heartBox.top, _anime, 0);

	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		Rectangle(CAMERAMANAGER->getCameraDC(), _collisionHeart.left, _collisionHeart.top, _collisionHeart.right, _collisionHeart.bottom);
		UINT a = SOUNDMANAGER->getLength(_currentMap);
		UINT b = SOUNDMANAGER->getPosition(_currentMap,b);
		char str[128];
		wsprintf(str, "%d", a);
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

	_songLength = SOUNDMANAGER->getLength("1-1");
	//for (int i = 0; i < _vRenge.size() - 2; i++) // FMOD::SOUND에 getLength() 함수가 망가져서 만들었음 ㅠㅠ... 아마 원인이 함수도 음악 파일 확장자에 따라서 잘 작동되는 함수가 있는 반면 아닌 함수도 있다. 예를 들어 getVolume함수 같은 경우에도 일부 확장자만 함수 사용이 가능함
	//{
	//	int getMS = _vRenge[i + 1] - _vRenge[i]; // 한 개의 비트 간격을 받아오기 위해서..
	//	_songLength += getMS; // 길이를 담아준다. 나중엔 _songLength가 곡의 총 길이가 된다.
	//}
}

void beat::setMap(string currentMap)
{
	_currentMap = currentMap;
	if (_currentMap != _oldMap)
	{
		_vRenge.clear();
		_vNoteL.clear();
		TIMEMANAGER->setCountTime(0);
		TIMEMANAGER->setCountTimeResetSwitch(true); // 세는 시간 리셋
		TIMEMANAGER->setCountTimeSwitch(true); // 시간 세기 ON
		_deltaTime = TIMEMANAGER->getElapsedTime();
		_currentNoteCnt = 0;
		_cnt = 0;
		_okTime = 0;
		noteTimeIntervalCount = 0;

		_oldMap = _currentMap;
		load(currentMap);
	}


	//for (int i = 0; i < 3; i++)
	//{
	//	int tempMS = _vRenge[_currentNoteCnt + 1] - _vRenge[_currentNoteCnt];
	//	int bpm = 60000 / tempMS;

	//	note _note;

	//	_note.img = IMAGEMANAGER->findImage("노트");
	//	_note.x = WINSIZEX / 2 - (WINSIZEX / 2 / 3 * (i + 1));
	//	_note.y = WINSIZEY - 100;
	//	_note.rc = RectMakeCenter(_note.x, _note.y, _note.img->getWidth(), _note.img->getHeight());
	//	_note.alpha = 0;
	//	_note.speed = lerp(_note.x, _note.x+WINSIZEX/2/3, (_deltaTime / ((tempMS + bpm) / 1000.0f)));
	//	_note.render = true;
	//	_vNoteL.push_back(_note);
	//	noteTimeInterval = tempMS / 1000.0f;
	//	_currentNoteCnt++;
	//}

}


void beat::addNote(float x)
{

	int tempMS = _vRenge[_currentNoteCnt+1] - _vRenge[_currentNoteCnt]-x;
	int bpm = 60000 / tempMS;

	note _note;

	_note.img = IMAGEMANAGER->findImage("노트");
	_note.x = 0;
	_note.y = WINSIZEY - 100;
	_note.rc = RectMakeCenter(_note.x, _note.y, _note.img->getWidth(), _note.img->getHeight());
	_note.alpha = 0;
	_note.colHeart = false;

	_note.speed = lerp(_note.x, _heartBox.right, (_deltaTime / ((tempMS + bpm) / 1000.0f)) / 3);
	_note.render = true;
	_vNoteL.push_back(_note);

	noteTimeInterval = tempMS / 1000.0f;
	_currentNoteCnt++;

}

void beat::checkBeat()
{
	noteTimeIntervalCount = TIMEMANAGER->getCountTime();
	if (noteTimeIntervalCount >= noteTimeInterval)
	{
		float lapse = (noteTimeIntervalCount - noteTimeInterval)*1000.0f;
		addNote(lapse);
		_turn++;

		TIMEMANAGER->setCountTime(0);
		noteTimeIntervalCount = 0;
	}

	for (int i = 0; i < _vNoteL.size();)
	{
		_vNoteL[i].x += _vNoteL[i].speed;
		_vNoteL[i].rc = RectMakeCenter(_vNoteL[i].x, _vNoteL[i].y, _vNoteL[i].img->getWidth(), _vNoteL[i].img->getHeight());

		if (IntersectRect(&_temp, &_vNoteL[i].rc, &_collisionHeart))
		{
			if(!_vNoteL[i].colHeart)
				_isBeat = true;
			_vNoteL[i].colHeart = true;
			_okTime ++;
		}
		if (_vNoteL[i].x > WINSIZEX / 2)
		{
			//_vNoteL[i].render = false;
		}
		//if (_vNoteL[i].x-(_collisionHeart.right-_collisionHeart.left)/2 > WINSIZEX/2)
		if (_vNoteL[i].x-(_heart->getFrameWidth()/2) > WINSIZEX/2)
		{
			_vNoteL.erase(_vNoteL.begin() + i);
			_okTime = 0;
		}
		else
		{
			++i;
		}
	}
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
	_vMiss.push_back(_miss);
}

void beat::addCoinMiss()
{
	miss _temp;

	_temp.alpha = 0;
	_temp.img = IMAGEMANAGER->findImage("코인배수사라짐");
	_temp.rc = RectMakeCenter(_heartBox.left, WINSIZEY/2, _temp.img->getWidth(), _temp.img->getHeight());
	_temp.speed = 1;
	_temp.max = WINSIZEY / 2 - 100;
	_vMiss.push_back(_temp);
}
