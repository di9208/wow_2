#pragma once
#include "cParticle.h"

class cArthasPaticle : public cParticle
{
private:
	int m_nSize;
public:
	cArthasPaticle(int num, int size);
	virtual ~cArthasPaticle();

	void resetParticle(Attribute* attribute);
	void update(float timeDelta);
};

