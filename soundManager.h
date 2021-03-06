#pragma once
#include"singletonBase.h"
#include"inc/fmod.hpp"
#pragma comment(lib,"lib/fmodex_vc.lib")
using namespace FMOD;

#define EXTRACHANNELBUFFER 5
#define SOUNDBUFFER 100

#define TOTALSOUNDBUFFER SOUNDBUFFER+ EXTRACHANNELBUFFER
class soundManager : public singletonBase<soundManager>
{
private:

	typedef map<string, Sound**>arrSounds;
	typedef map<string, Sound**>::iterator arrSoundIter;

	System* m_system;		


	Sound** m_sound;		//사운드
	Channel** m_channel;		//채널


	arrSounds m_totalSounds;



public:
	soundManager();
	~soundManager();

	HRESULT init();
	void release();
	void update();
	void render();
	//키값, 파일 이름, BGM, LOOP
	void addSound(string keyName, string soundName, bool bgm = FALSE, bool loop = FALSE);

	//사운드 플레이	(키값, 볼륨 0.0~1.0f)
	void play(string keyName, float volume = 1.0f);
	void volumeSet(string keyName, float volume);
	void stop(string keyName);
	void pause(string keyName);
	void resume(string keyName);

	//플레이 중이냐
	bool isPlaySound(string keyName);
	//일시 정지 중이냐
	bool isPauseSound(string keyName);


	int getPosition(string keyName, unsigned int& pos);						//현재길이 받아옴
	int getLength(string keyName);
};

