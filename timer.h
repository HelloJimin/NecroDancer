#pragma once
class timer
{
private :

	bool		_isHardware;			//고성능 타이머를 지원하냐
	float		_timeScale;				//시간경과량
	float		_timeElapsed;			//한프레임당 경과량
	__int64		_curTime;				//현재시간
	__int64		_lastTime;				//마지막시간
	__int64		_periodFrequency;	    //시간주기

	unsigned long _frameRate;			//FPS
	unsigned long _FPSFrameCount;		//FPS카운트


	float _FPStimeElapsed;					//FPS마지막 시간과 현재시간의 경과량
	float _worldTime;					//전체시간 경과량
	float _countTime; // 원하는 지점에서 시간을 재기 위해 만든 변수

	bool _countTimeResetSwitch; // _countTime 리셋(0으로 초기화) 판단하는 bool
	bool _countTimeSwitch; // _countTime을 셀 수 있는지 판단하는 bool
public:
	timer();
	~timer();

	HRESULT init();
	//현재시간 계산
	void tick(float lockFPS = 0.0f);
	//현재FPS가져오기
	unsigned long getFrameRate(char* str = nullptr)const;
	//한프레임당 경과시간
	float getElapsedTime()const { return _timeElapsed; }
	//전체 경과시간 가져오기
	float getWorldTime()const { return _worldTime; }


	inline float getCountTime() { return _countTime; }
	inline void setCountTime(float countTime) { _countTime = countTime; }

	void setCountTimeResetSwitch(bool resetSwitch) { _countTimeResetSwitch = resetSwitch; }
	void countTimeSwitch(bool ONOff_Switch) { _countTimeSwitch = ONOff_Switch; }

	float* getCountTimePt() { return &_countTime; }
	bool* getCountTimeResetSwitchPt() { return &_countTimeResetSwitch; }
	bool* getCountTimeSwitchPt() { return &_countTimeSwitch; }
};

