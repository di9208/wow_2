#pragma once
#include "cParticle.h"

class cMonsterParticle : public cParticle
{
private:
	SYNTHESIZE(int, m_nAlpha, Alpah);
public:
	cMonsterParticle(int num);
	virtual ~cMonsterParticle();


	void resetParticle(Attribute* attribute);
	void update(float timeDelta);


};
