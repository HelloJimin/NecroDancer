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
	//���ʱ�ȭ
	load("1-1");

	_cnt = 0;
	_anime = 0;
	_turn = 0;
	_okTime = 0;


	_heart = IMAGEMANAGER->findImage("����");
	_heartBox = RectMakeCenter(WINSIZEX / 2, WINSIZEY - 100, _heart->getFrameWidth(), _heart->getFrameHeight());
	_collisionHeart = RectMakeCenter(WINSIZEX / 2, WINSIZEY - 100, 100, 50 * 2);

	_miss.alpha = 0;
	_miss.img = IMAGEMANAGER->findImage("������");
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
	//���ںκ� ����
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
	if(map=="1-1") readFile.open("sound/1-1.txt"); // ���� ����
	else if(map=="1-2") readFile.open("sound/1-2.txt"); // ���� ����

	if (readFile.is_open()) // ������ ���������� �����ִٸ�
	{
		while (!readFile.eof()) // �о���� ������ ���� ���������� �ݺ�
		{
			char temp; // ���ڸ� �ϳ��� �̱� ���� ����
			readFile.get(temp); // ���� �ϳ� �̱� 
			if (temp == ',')
			{
				//++_countComma; // �޸� ����
				_vRenge.push_back(atoi(tempWord.c_str())); // ��ȯ ���� : ���ڿ� -> char*�� ��ȯ -> atoi�� char*�� int�� ��ȯ
				tempWord = ""; // string �ʱ�ȭ
				continue;
			}
			tempWord += temp; // �� ���ھ� string�� ��ħ
		}
		//_msTimeInfo.erase(_msTimeInfo.begin() + (_msTimeInfo.size() - 1)); // ���� ������ �� ������ �κп� 0�� �׻� �����ϹǷ� �� ������ ��Ҹ� ������
		readFile.close(); // ���� �ݱ�
	}

	_songLength = SOUNDMANAGER->getLength("1-1");
	//for (int i = 0; i < _vRenge.size() - 2; i++) // FMOD::SOUND�� getLength() �Լ��� �������� ������� �Ф�... �Ƹ� ������ �Լ��� ���� ���� Ȯ���ڿ� ���� �� �۵��Ǵ� �Լ��� �ִ� �ݸ� �ƴ� �Լ��� �ִ�. ���� ��� getVolume�Լ� ���� ��쿡�� �Ϻ� Ȯ���ڸ� �Լ� ����� ������
	//{
	//	int getMS = _vRenge[i + 1] - _vRenge[i]; // �� ���� ��Ʈ ������ �޾ƿ��� ���ؼ�..
	//	_songLength += getMS; // ���̸� ����ش�. ���߿� _songLength�� ���� �� ���̰� �ȴ�.
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
		TIMEMANAGER->setCountTimeResetSwitch(true); // ���� �ð� ����
		TIMEMANAGER->setCountTimeSwitch(true); // �ð� ���� ON
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

	//	_note.img = IMAGEMANAGER->findImage("��Ʈ");
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

	_note.img = IMAGEMANAGER->findImage("��Ʈ");
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
	_temp.img = IMAGEMANAGER->findImage("���ι�������");
	_temp.rc = RectMakeCenter(_heartBox.left, WINSIZEY/2, _temp.img->getWidth(), _temp.img->getHeight());
	_temp.speed = 1;
	_temp.max = WINSIZEY / 2 - 100;
	_vMiss.push_back(_temp);
}
