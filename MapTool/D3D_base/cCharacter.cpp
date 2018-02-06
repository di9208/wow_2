#include "stdafx.h"
#include "cCharacter.h"
#include "iMap.h"


cCharacter::cCharacter()
	: m_fRotY(0.0f)
{
	D3DXMatrixIdentity(&m_matWorld);
}


cCharacter::~cCharacter()
{
}

void cCharacter::Setup()
{
}

void cCharacter::Update(iMap* pMap)
{
	if (GetKeyState('A') & 0x8000)
	{
		m_fRotY -= 0.1f;
	}
	if (GetKeyState('D') & 0x8000)
	{
		m_fRotY += 0.1f;
	}

	D3DXVECTOR3 vTempPos = m_vPos;
	if (GetKeyState('W') & 0x8000)
	{
		//m_vPos = m_vPos + (m_vDir * 0.1f);
		vTempPos = m_vPos + (m_vDir * 0.1f);
	}
	if (GetKeyState('S') & 0x8000)
	{
		//m_vPos = m_vPos - (m_vDir * 0.1f);
		vTempPos = m_vPos - (m_vDir * 0.1f);
	}

	D3DXMATRIXA16 matR, matT;
	D3DXMatrixIdentity(&matT);
	D3DXMatrixRotationY(&matR, m_fRotY);
	m_vDir = D3DXVECTOR3(0, 0, 1);
	D3DXVec3TransformNormal(&m_vDir, &m_vDir, &matR);
	//D3DXMatrixTranslation(&matT, m_vPos.x, m_vPos.y, m_vPos.z);
	m_matWorld = matR * matT;

	if (pMap)
	{
		if (pMap->GetHeight(vTempPos.x, vTempPos.y, vTempPos.z))
		{
			m_vPos = vTempPos;
		}
	}


	//D3DXVECTOR3 vUp(0, 1, 0);
	//D3DXVECTOR3 vRight;
	//D3DXVec3Cross(&vRight, &vUp, &m_vDir);
	//D3DXVec3Normalize(&vRight, &vRight);
	//D3DXVec3Cross(&vUp, &m_vDir, &vRight);
	//D3DXMatrixLookAtLH(&matR, &D3DXVECTOR3(0, 0, 0), &m_vDir, &vUp);
	//D3DXMatrixTranspose(&matR, &matR);

	D3DXMatrixTranslation(&matT, m_vPos.x, m_vPos.y + 0.8f, m_vPos.z);
	m_matWorld = matR * matT;
}
