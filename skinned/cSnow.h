#pragma once
#include "cParticle.h"

class cSnow:public cParticle
{
private:

public:
	cSnow(int num);
	virtual ~cSnow();

	
	void resetParticle(Attribute* attribute);
	void update(float timeDelta);


};

