#pragma once
#include "cSkinnedMesh.h"

class cEnemyHitEffect
{
private:
	cSkinnedMesh*	hitMesh;
public:
	void hit(D3DXVECTOR3 pos);
	cEnemyHitEffect();
	~cEnemyHitEffect();
};

