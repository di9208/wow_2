#include "stdafx.h"
#include "cSnow.h"


cSnow::cSnow(int num)
{
	_size = 0.25f;
	_vbSize = 2048;
	_vbOffset = 0;
	_vbBatchSize = 512;

	for (int i = 0; i < num; i++)
		addParticle();
}


cSnow::~cSnow()
{
}

void cSnow::resetParticle(Attribute * attribute)
{
	attribute->isAlive = true;

	attribute->position.x = (rand() % 10000) * 0.0001f*(15.0f - (-10.0f)) + -10.0f;
	attribute->position.z = (rand() % 10000) * 0.0001f*(10.0f - (-10.0f)) + -10.0f;
	// no randomness for height (y-coordinate).  Snow flake
	// always starts at the top of bounding box.
	attribute->position.y = 50.0f;

	// snow flakes fall downwards and slightly to the left
	attribute->velocity.x = (rand() % 10000) * 0.0001f * -2.0f;
	attribute->velocity.y = (rand() % 10000) * 0.0001f* -10.0f;
	attribute->velocity.z = 0.0f;

	// white snow flake
	attribute->color = D3DCOLOR_XRGB(255, 255, 255);
}

void cSnow::update(float timeDelta)
{
	std::list<Attribute>::iterator i;
	for (i = _particles.begin(); i != _particles.end(); i++)
	{
		i->position += i->velocity * timeDelta;
		// is the point outside bounds?
		if (i->position.y<-10)
		{
			// nope so kill it, but we want to recycle dead 
			// particles, so respawn it instead.
			resetParticle(&(*i));
		}
	}
}
