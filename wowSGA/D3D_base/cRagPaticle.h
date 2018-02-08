#pragma once
#include "cParticle.h"

class cRagPaticle:public cParticle
{
private:
	int m_nSize;
public:
	cRagPaticle(int num, int size);
	virtual ~cRagPaticle();

	void resetParticle(Attribute* attribute);
	void update(float timeDelta);
};

