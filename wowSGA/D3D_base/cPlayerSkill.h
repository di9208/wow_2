#pragma once
#include "cUnit.h"
class cPlayerSkill
{
public:
	cPlayerSkill();
	~cPlayerSkill();

	void Setup();
	void Update(condition* pCondition,bool animCheck);
	void combo(condition* pCondition, bool animCheck);
};

