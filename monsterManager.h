#pragma once
#include"singletonBase.h"
class monsterManager : public singletonBase<monsterManager>
{
public:
	monsterManager();
	~monsterManager();
};

