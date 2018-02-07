#include "stdafx.h"
#include "cMonsterParticle.h"


cMonsterParticle::cMonsterParticle(int num)
{
	_size = 0.25f;
	_vbSize = 2048;
	_vbOffset = 0;
	_vbBatchSize = 512;
	m_nAlpha = 255;

	for (int i = 0; i < num; i++)
		addParticle();
}


cMonsterParticle::~cMonsterParticle()
{
}

void cMonsterParticle::resetParticle(Attribute* attribute)
{
	attribute->isAlive = true;

	//x는 모름
	//y는 가로
	//z는 세로
	if (rand() % 2 == 0)		attribute->position.x = rand() % 40;
	else if (rand() % 2 == 1)	attribute->position.x = -rand() % 30;
	if (rand() % 2 == 0)		attribute->position.y = rand() % 40;
	else if (rand() % 2 == 1)	attribute->position.y = -rand() % 30;
	attribute->position.z = -20;

	attribute->velocity.x = 0;// (rand() % 1000) * 0.001f * -2.0f;
	attribute->velocity.y = 0;// (rand() % 10000) * 0.0001f* -10.0f;
	attribute->velocity.z = (-rand() % 1000) * 0.001f* -1.0f;

	attribute->color = D3DCOLOR_ARGB(m_nAlpha, 255, 255, 255);
}

void cMonsterParticle::update(float timeDelta)
{
	std::list<Attribute>::iterator i;
	for (i = _particles.begin(); i != _particles.end(); i++)
	{
		if (i->position.z < 100) i->position += i->velocity * timeDelta;
		else if (i->position.z >= 100)
		{
			resetParticle(&(*i));
		}
	}
}
