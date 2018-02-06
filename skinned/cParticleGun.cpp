#include "stdafx.h"
#include "cParticleGun.h"
#include "cCamera.h"

cParticleGun::cParticleGun()
{
}

cParticleGun::cParticleGun(cCamera * camera)
{
	_camera = camera;
	_size = 1.0f;
	_vbSize = 2048;
	_vbOffset = 0;
	_vbBatchSize = 512;

	//for (int i = 0; i < 512; i++)
		addParticle();
}


cParticleGun::~cParticleGun()
{
}

void cParticleGun::resetParticle(Attribute * attribute)
{
	attribute->isAlive = true;

	attribute->position = _camera->GetPos() /*+ (rand() % 1000 / 1000.0f*(1.5f - -0.5f) + -0.5f)*a*/;

	//attribute->position.x = rand()%1000/1000.0f*(1.5f - -1.5f)+ -1.5f;
	attribute->position.y = _camera->GetPos().y - 0.5f;
	//attribute->position.z = rand() % 1000 / 1000.0f*(6.0f - 0.0f) + 0.0f;
	attribute->velocity = _camera->GetDir() * 10.0f;


	attribute->color = D3DCOLOR_ARGB(255, 192, 192, 0);
	attribute->age = 0;
	attribute->lifeTime = 2.0f;

}

void cParticleGun::update(float timeDelta)
{
	std::list<Attribute>::iterator i;

	if (_particles.size() != 0)
	{
		for (i = _particles.begin(); i != _particles.end(); i++)
		{
			
			i->position += i->velocity * timeDelta;
			i->age += timeDelta;

			if (i->age > i->lifeTime)
			{
				i->isAlive = false;	
			}
		}
		removeDeadParticles();
	}
	if (GetKeyState(VK_RBUTTON) & 0x8000)
	{
		addParticle();
	}
}
