#include "stdafx.h"
#include "cEnemyHitEffect.h"


cEnemyHitEffect::cEnemyHitEffect()
{
}


cEnemyHitEffect::~cEnemyHitEffect()
{
}

void cEnemyHitEffect::hit(D3DXVECTOR3 pos){
	D3DXMATRIXA16 matWorld;

	hitMesh = new cSkinnedMesh;
	hitMesh->Setup("Monster/lightningworg", "1.x");
	D3DXMatrixIdentity(&matWorld);
	D3DXMATRIXA16 matT, matS;
	D3DXMatrixScaling(&matS, 1.0f, 1.0f, 1.0f);
	D3DXMatrixTranslation(&matT, pos.x, pos.y + 0.45, pos.z);
	matWorld = matS * matT;

	hitMesh->Render(NULL, &matWorld);
	hitMesh->PlayOneShotAfterHold("Anim1");
}