#include "stdafx.h"
#include "cMonsterBombParticle.h"

cMonsterBombParticle::cMonsterBombParticle(int num)
{
	_size = 0.5f;
	_vbSize = 2048;
	_vbOffset = 0;
	_vbBatchSize = 512;
	for (int i = 0; i < num; i++)
		addParticle();
}


cMonsterBombParticle::~cMonsterBombParticle()
{
}

void cMonsterBombParticle::resetParticle(Attribute* attribute)
{
	int a = rand() % 2;
	int b = rand() % 2;
	int c = rand() % 2;

	//x는 모름
	//y는 가로
	//z는 세로	
	attribute->position.x = 0;
	attribute->position.z = 0;
	attribute->position.y = 0;


	if (a == 0)			attribute->velocity.x = (rand() % 1000) * 0.0001f* -1.0f;
	else if (a == 1)	attribute->velocity.x = (-rand() % 1000) * 0.0001f* -1.0f;
	if (b == 0)			attribute->velocity.y = (rand() % 1000) * 0.0001f* -1.0f;
	else if (b == 1)	attribute->velocity.y = (-rand() % 1000) * 0.0001f* -1.0f;
	if (c == 0)			attribute->velocity.z = (rand() % 1000) * 0.0001f* -1.0f;
	else if (c == 1)	attribute->velocity.z = (-rand() % 1000) * 0.0001f* -1.0f;

	attribute->color = D3DCOLOR_ARGB(255, 0, 255, 0);
}

void cMonsterBombParticle::update(float timeDelta)
{
	std::list<Attribute>::iterator i;
	for (i = _particles.begin(); i != _particles.end(); i++)
	{
		i->position += i->velocity * timeDelta;

		if (i->position.y >= 2 ||
			i->position.x >= 2 ||
			i->position.z >= 2)
		{
			i->position = D3DXVECTOR3(0, 0, 0);
		}
	}
	//removeDeadParticles();
}
