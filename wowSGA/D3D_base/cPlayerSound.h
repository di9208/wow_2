#pragma once
#include "cUnit.h"
class cPlayerSound
{
	bool attack;
	float attack_time;
	bool swing;

	bool attack2;
	float attack_time2;
	bool swing2;

	bool attack3;
	float attack_time3;
	bool swing3;


public:
	cPlayerSound();
	~cPlayerSound();

	void Setup();
	void Update(condition* pCondition);
};

