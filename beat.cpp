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
	TIMEMANAGER->setCountTime(0);
	TIMEMANAGER->setCountTimeResetSwitch(true); // 세는 시간 리셋
	TIMEMANAGER->setCountTimeSwitch(true); // 시간 세기 ON

	//턴초기화
	_cnt = 0;
	_speed = 6;
	_anime = 0;
	_turn = 0;
	_heart = IMAGEMANAGER->findImage("심장");
	_heartBox = RectMakeCenter(WINSIZEX / 2, WINSIZEY - 100, _heart->getFrameWidth(), _heart->getFrameHeight());
	_collisionHeart = RectMakeCenter(WINSIZEX / 2, WINSIZEY - 100, 120, 50 * 2);
	for (int i = 0; i < 2; i++)
	{
		_note.img[i] = IMAGEMANAGER->findImage("노트");
		_note.x[0] = 0;
		_note.x[1] = WINSIZEX;
		_note.y = WINSIZEY - 100;
		_note.rc[i] = RectMakeCenter(_note.x[i], _note.y, _note.img[i]->getWidth(), _note.img[i]->getHeight());
		_note.alpha = 0;
	}

	_miss.alpha = 0;
	_miss.img = IMAGEMANAGER->findImage("빗나감");
	_miss.rc = RectMake(_heartBox.left, _heartBox.top, _miss.img->getWidth(), _miss.img->getHeight());
	_miss.speed = 1;
	_miss.max = WINSIZEY / 2 + 150;

	_vNote.push_back(_note);
	_deltaTime = TIMEMANAGER->getElapsedTime();
	return S_OK;
}

void beat::release()
{
}

void beat::update()
{
	SOUNDMANAGER->getPosition("1-1", _songPos);
	if (_songPos > 0)
	{
		_deltaTime = TIMEMANAGER->getElapsedTime();
	}
	checkBeat();
	missUpdate();
	if (!_beatOn)
	{
		_check = true;
	}

}

void beat::render(HDC hdc)
{
	//박자부분 렌더
	for (int i = 0; i < _vMiss.size(); i++)
	{
		_vMiss[i].img->render(CAMERAMANAGER->getCameraDC(), _vMiss[i].rc.left, _vMiss[i].rc.top);
	}
	for (int i = 0; i < _vNote.size(); i++)
	{
		if (_vNote[i].rc[0].right <= _heartBox.right - 40) _vNote[i].img[0]->alphaRender(CAMERAMANAGER->getCameraDC(), _vNote[i].rc[0].left, _vNote[i].rc[0].top, 255);
		if (_vNote[i].rc[1].left >= _heartBox.left + 40) _vNote[i].img[1]->alphaRender(CAMERAMANAGER->getCameraDC(), _vNote[i].rc[1].left, _vNote[i].rc[1].top, 255);
	}
	_heart->frameRender(CAMERAMANAGER->getCameraDC(), _heartBox.left, _heartBox.top, _anime, 0);

	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		Rectangle(CAMERAMANAGER->getCameraDC(), _collisionHeart.left, _collisionHeart.top, _collisionHeart.right, _collisionHeart.bottom);
		UINT a = SOUNDMANAGER->getLength("1-1");
		UINT b = SOUNDMANAGER->getPosition("1-1",b);
		char str[128];
		wsprintf(str, "%d", a);
		TextOut(CAMERAMANAGER->getCameraDC(), WINSIZEX / 2, WINSIZEY / 2,str, strlen(str));
		wsprintf(str, "%d", b);
		TextOut(CAMERAMANAGER->getCameraDC(), WINSIZEX / 2, WINSIZEY / 2+100, str,strlen(str));
	}
}
void beat::load()
{
	ifstream readFile;
	string tempWord;
	readFile.open("sound/1-1.txt"); // 파일 열기

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

void beat::checkBeat()
{
	_speed = 521 * _deltaTime;
	int tempMS = 521;
	int bpm = 60000 / tempMS;
	_speed = lerp(0, WINSIZEX/2, (_deltaTime / ((tempMS + bpm) / 1000.0f)) / 3);
	noteTimeInterval = 521/ 1000.0f;
	noteTimeIntervalCount = TIMEMANAGER->getCountTime();

	if (noteTimeIntervalCount > noteTimeInterval)
	{
		TIMEMANAGER->setCountTime(0);
		noteTimeIntervalCount = 0;
		_vNote.push_back(_note);
	}
	//_speed = _collisionHeart.left / 43;
	_cnt++;
	UINT b;
	SOUNDMANAGER->getPosition("1-1", b);
	//UINT a = SOUNDMANAGER->getLength("1-1");
	//UINT b = SOUNDMANAGER->getPosition("1-1",b) % 521;
	//if (_cnt+1 == 30)
	//a = SOUNDMANAGER->getPosition("1-1");

	//if (_cnt % 29 == 0)
	//{
	//	_turn++;
	//	_vNote.push_back(_note);
	//}


	for (int i = 0; i < _vNote.size(); i++)
	{
		_vNote[i].alpha += 7;
		_vNote[i].x[0] += _speed;
		_vNote[i].x[1] -= _speed;

		_vNote[i].rc[0] = RectMakeCenter(_vNote[i].x[0], _vNote[i].y, _vNote[i].img[0]->getWidth(), _vNote[i].img[0]->getHeight());
		_vNote[i].rc[1] = RectMakeCenter(_vNote[i].x[1], _vNote[i].y, _vNote[i].img[1]->getWidth(), _vNote[i].img[1]->getHeight());

		if (IntersectRect(&_temp, &_vNote[i].rc[0], &_collisionHeart))
		{
			_check = true;
		}

		if (_vNote[i].rc[0].right >= _collisionHeart.right)
		{
			//if (!KEYMANAGER->isOnceKeyDown(VK_DOWN) && !KEYMANAGER->isOnceKeyDown(VK_UP) &&
			//	!KEYMANAGER->isOnceKeyDown(VK_LEFT) && !KEYMANAGER->isOnceKeyDown(VK_RIGHT))
			_check = false;
			_vNote.erase(_vNote.begin() + i);
			break;
		}

		if (_check)_anime = 1;
		if (!_check)_anime = 0;
	}
}

void beat::removeNote()
{
	for (int i = 0; i < _vNote.size(); i++)
	{
		if (IntersectRect(&_temp, &_vNote[i].rc[0], &_collisionHeart))
		{
			_check = false;
			_vNote.erase(_vNote.begin() + i);
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
