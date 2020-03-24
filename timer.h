#pragma once
class timer
{
private :

	bool		_isHardware;			//���� Ÿ�̸Ӹ� �����ϳ�
	float		_timeScale;				//�ð������
	float		_timeElapsed;			//�������Ӵ� �����
	__int64		_curTime;				//����ð�
	__int64		_lastTime;				//�������ð�
	__int64		_periodFrequency;	    //�ð��ֱ�

	unsigned long _frameRate;			//FPS
	unsigned long _FPSFrameCount;		//FPSī��Ʈ


	float _FPStimeElapsed;					//FPS������ �ð��� ����ð��� �����
	float _worldTime;					//��ü�ð� �����
	float _countTime; // ���ϴ� �������� �ð��� ��� ���� ���� ����

	bool _countTimeResetSwitch; // _countTime ����(0���� �ʱ�ȭ) �Ǵ��ϴ� bool
	bool _countTimeSwitch; // _countTime�� �� �� �ִ��� �Ǵ��ϴ� bool
public:
	timer();
	~timer();

	HRESULT init();
	//����ð� ���
	void tick(float lockFPS = 0.0f);
	//����FPS��������
	unsigned long getFrameRate(char* str = nullptr)const;
	//�������Ӵ� ����ð�
	float getElapsedTime()const { return _timeElapsed; }
	//��ü ����ð� ��������
	float getWorldTime()const { return _worldTime; }


	inline float getCountTime() { return _countTime; }
	inline void setCountTime(float countTime) { _countTime = countTime; }

	void setCountTimeResetSwitch(bool resetSwitch) { _countTimeResetSwitch = resetSwitch; }
	void countTimeSwitch(bool ONOff_Switch) { _countTimeSwitch = ONOff_Switch; }

	float* getCountTimePt() { return &_countTime; }
	bool* getCountTimeResetSwitchPt() { return &_countTimeResetSwitch; }
	bool* getCountTimeSwitchPt() { return &_countTimeSwitch; }
};

