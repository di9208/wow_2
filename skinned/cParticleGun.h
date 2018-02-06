#pragma once
#include "cParticle.h"

class cCamera;

class cParticleGun:public cParticle
{
private:
	cCamera * _camera;
public:
	cParticleGun();
	cParticleGun(cCamera * camera);
	~cParticleGun();

	void resetParticle(Attribute* attribute);
	void update(float timeDelta);
};

