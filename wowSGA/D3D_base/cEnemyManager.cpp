#include "stdafx.h"
#include "cEnemyManager.h"



cEnemyManager::cEnemyManager()
: m_fRotY(0.f)
, m_fRotX(0.f)
{
}

cEnemyManager::~cEnemyManager()
{
}

void cEnemyManager::SetUp(){
	
}

void cEnemyManager::Update(){
	BossPos();
}

void cEnemyManager::Render(){
	
}


void cEnemyManager::BossPos()
{
	/*D3DXVECTOR3 vTempPos = m_vPos;




	D3DXMATRIXA16 matR, matT, matX;
	D3DXMatrixIdentity(&matT);
	D3DXMatrixRotationX(&matX, -D3DX_PI / 2.f);
	D3DXMatrixRotationY(&matR, m_fRotY);
	m_vDir = D3DXVECTOR3(1, 0, 0);
	D3DXVec3TransformNormal(&m_vDir, &m_vDir, &matR);

	D3DXMatrixTranslation(&matT, m_vPos.x, m_vPos.y, m_vPos.z);
	m_matWorld = matR * matT * matX;*/

}
