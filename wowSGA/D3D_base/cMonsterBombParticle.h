#pragma once
#include "cParticle.h"

class cMonsterBombParticle : public cParticle
{
private:
	int	m_nsize;
public:
	cMonsterBombParticle(int num);
	virtual ~cMonsterBombParticle();


	void resetParticle(Attribute* attribute);
	void update(float timeDelta);
};
