#pragma once
#include "cUnit.h"
class cPlayerSound
{
	bool attack;
	float attack_time;
	bool swing;

public:
	cPlayerSound();
	~cPlayerSound();

	void Setup();
	void Update(condition* pCondition);
};

