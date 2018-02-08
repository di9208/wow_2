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
	if (m_nAlpha > 0) {
		attribute->isAlive = true;
	}
	else if(m_nAlpha <= 0) attribute->isAlive = false;
	
	int a = rand() % 2;
	int b = rand() % 2;

	//x는 모름
	//y는 가로
	//z는 세로	
	if (a == 0)		attribute->position.x = rand() % 30;
	else if (a == 1)	attribute->position.x = -rand() % 50;
	if (b == 0)		attribute->position.y = rand() % 30;
	else if (b == 1)	attribute->position.y = -rand() % 50;
	attribute->position.z = -rand() % 100 + 20;
	
	attribute->velocity.x = 0;// (rand() % 1000) * 0.001f * -2.0f;
	attribute->velocity.y = 0;// (rand() % 10000) * 0.0001f* -10.0f;
	attribute->velocity.z = (-rand() % 1000) * 0.001f* -1.0f + 1;

	attribute->color = D3DCOLOR_ARGB(m_nAlpha, 0, 0, 0);
	
}

void cMonsterParticle::update(float timeDelta)
{
	std::list<Attribute>::iterator i;
	for (i = _particles.begin(); i != _particles.end(); i++)
	{
		i->position += i->velocity * timeDelta;
		if (i->position.z >= 100)
		{
			resetParticle(&(*i));
			m_nAlpha -= 0.01;
		}
	}
}
