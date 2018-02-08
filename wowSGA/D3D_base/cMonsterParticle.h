#pragma once
#include "cParticle.h"

class cMonsterParticle : public cParticle
{
private:
	int	m_nsize;
public:
	cMonsterParticle(int num, int size);
	virtual ~cMonsterParticle();


	void resetParticle(Attribute* attribute);
	void update(float timeDelta);


};
