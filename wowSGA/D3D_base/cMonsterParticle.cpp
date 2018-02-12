#include "stdafx.h"
#include "cMonsterParticle.h"


cMonsterParticle::cMonsterParticle(int num, int size)
{
	_size = 0.2f;
	_vbSize = 2048;
	_vbOffset = 0;
	_vbBatchSize = 512;
	m_nsize = size;
	for (int i = 0; i < num; i++)
		addParticle();
}


cMonsterParticle::~cMonsterParticle()
{
}

void cMonsterParticle::resetParticle(Attribute* attribute)
{
	int a = rand() % 2;
	int b = rand() % 2;

	//x는 모름
	//y는 가로
	//z는 세로	
	if (a == 0)			attribute->position.x = rand() % m_nsize;
	else if (a == 1)	attribute->position.x = -rand() % m_nsize;
	if (b == 0)			attribute->position.z = rand() % m_nsize;
	else if (b == 1)	attribute->position.z = -rand() % m_nsize;
	attribute->position.y =-rand() % 100 - 20;

	attribute->velocity.x = 0;
	attribute->velocity.y = (-rand() % 1000) * 0.001f* -1.0f + 1 ;
	attribute->velocity.z =0;

	attribute->color = D3DCOLOR_ARGB(255, 0, 0, 0);
}

void cMonsterParticle::update(float timeDelta)
{
	std::list<Attribute>::iterator i;
	for (i = _particles.begin(); i != _particles.end(); i++)
	{
		i->position += i->velocity * timeDelta;

		if (i->position.y >= 70 + (rand() % 30))
		{
			i->isAlive = false;
		}
	}
	removeDeadParticles();
}
