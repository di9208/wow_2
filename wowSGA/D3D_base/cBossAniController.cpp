#include "stdafx.h"
#include "cBossAniController.h"
#include "cSkinnedMesh.h"
#include "cOBB.h"

cBossAniController::cBossAniController()
	: m_pSkinnedMesh(NULL)
	, cBoss_STATE(E_BOSS_STAND)
	, m_fBossRotY(0.f)
	, m_vBossDirX(1,0,0)
	, m_vBossDir(0,0,1)
	, m_vBossPos(-5,0,0)
	, m_pSkinnedMeshSkill(NULL)
	, m_bSKill(false)

{
}

cBossAniController::~cBossAniController()
{
	SAFE_DELETE(m_pSkinnedMesh);
	SAFE_DELETE(m_pSkinnedMeshSkill);
}

void cBossAniController::SetUp()
{
	g_pSkinnedMeshManager->Setup("¸®Ä¡¿Õ", "Monster/boss/Arthaslichking", "arthas2.x");
	m_pSkinnedMesh = g_pSkinnedMeshManager->Find("¸®Ä¡¿Õ");
	
	g_pSkinnedMeshManager->Setup("½ºÅ³", "Monster/boss/Arthaslichking", "skill.x");
	m_pSkinnedMeshSkill = g_pSkinnedMeshManager->Find("½ºÅ³");

	D3DXMATRIXA16 matT;
	D3DXMatrixIdentity(&matT);
	D3DXMatrixTranslation(&matT, -3, 0, -17);
	D3DXMATRIXA16 matR, matS, World;
	D3DXMatrixScaling(&matS, 0.15f, 0.15f, 0.15f);

	D3DXMatrixRotationX(&matR, D3DX_PI / 2.f);

	World = matS * matT* matR;

}

void cBossAniController::Update(E_BOSS_STATE* pState)
{
	if (m_pSkinnedMesh)
		m_pSkinnedMesh->Update();

	if (m_pSkinnedMesh->GetCheck() && *pState != E_BOSS_DEATH)
	{
		(*pState) = E_BOSS_STAND;

	}

	/*if (g_pKeyManager->isStayKeyDown(VK_NUMPAD1))
	{
		m_fBossRotY -= 0.1f;
	}
	if (g_pKeyManager->isStayKeyDown(VK_NUMPAD3))
	{
		m_fBossRotY += 0.1f;
	}*/

	//float fSpeed = 0.1f;
	//if (g_pKeyManager->isStayKeyDown(VK_NUMPAD5))
	//{
	//	//if (*pState == E_BOSS_WALK || *pState == E_BOSS_STAND)
	//	{
	//		(*pState) = E_BOSS_WALK;
	//		m_vBossPos =  m_vBossPos + (m_vBossDir * fSpeed);
	//		
	//	} 
	//}
	//if (g_pKeyManager->isStayKeyDown(VK_NUMPAD2))
	//{
	//	if (*pState == E_BOSS_WALK || *pState == E_BOSS_STAND)
	//	{
	//		m_vBossPos = m_vBossPos - (m_vBossDir * fSpeed);
	//		(*pState) = E_BOSS_WALK;
	//	}
	//}
	//if (!(g_pKeyManager->isStayKeyDown(VK_NUMPAD5))
	//	&& !(g_pKeyManager->isStayKeyDown(VK_NUMPAD2)))
	//{ 
	//	if ((*pState) == E_BOSS_WALK)
	//		(*pState) = E_BOSS_STAND;
	//}

	SetAnimation(pState);
} 
 
void cBossAniController::Render(D3DXMATRIXA16 * m_world)
{
	D3DXMATRIXA16 matR, matS, matT, matX, matXX, World;
	D3DXMatrixScaling(&matS, 0.15f, 0.15f, 0.15f);
	
	//D3DXMatrixRotationX(&matR, D3DX_PI / 2.f);
	//D3DXMatrixRotationY(&matR, m_fBossRotY);

	D3DXMatrixIdentity(&matT);
	
	//D3DXMatrixRotationY(&matX, D3DX_PI/6.0f);
	D3DXMatrixRotationY(&matXX, -D3DX_PI / 2.0f);
	//D3DXVECTOR3 dir;
	//D3DXVec3TransformNormal(&dir, &m_vBossDir, &matR);

	D3DXVECTOR3 vUp(0, 1, 0);
	D3DXVECTOR3 vRight;
	D3DXVec3Cross(&vRight, &vUp, &m_vBossDir);
	D3DXVec3Normalize(&vRight, &vRight);
	D3DXVec3Cross(&vUp, &m_vBossDir, &vRight);
	D3DXMatrixLookAtLH(&matR, &D3DXVECTOR3(0, 0, 0), &m_vBossDir, &vUp);
	D3DXMatrixTranspose(&matR, &matR);
	D3DXMatrixTranslation(&matT, m_vBossPos.x, m_vBossPos.y, m_vBossPos.z);

	World = matS*matXX *matR*matT;

	if (m_pSkinnedMesh)
		m_pSkinnedMesh->Render(NULL, &World);


	if(cBoss_STATE == E_BOSS_SPELL1)
	m_pSkinnedMeshSkill->Render(NULL, &World);

}

void cBossAniController::SetAnimation(E_BOSS_STATE * pState)
{
	if (cBoss_STATE != (*pState))
	{
		cBoss_STATE= (*pState) ;
		switch (cBoss_STATE)
		{
		case E_BOSS_STAND:
			m_pSkinnedMesh->Play("STAND",0.3f);
			break;
		case E_BOSS_DEATH:
			m_pSkinnedMesh->PlayOneShotAfterHold("DEATH", 0.3f);	
			break;
		case E_BOSS_START:
			m_pSkinnedMesh->PlayOneShot("START", 0.3f,0.15f);
			break;
		case E_BOSS_ATT:
			m_pSkinnedMesh->PlayOneShot("ATT", 0.3f,0.03f);
			break;
		case E_BOSS_WHIRLWIND:
			m_pSkinnedMesh->Play("WHIRLWIND", 0.3f);
			break;
		case E_BOSS_SPELL1:
			m_bSKill = true;
			m_pSkinnedMesh->PlayOneShot("SPELL1", 0.03f,0.03f);
			m_pSkinnedMeshSkill->PlayOneShot("SKILL1");
			break;
		case E_BOSS_SPELL2:
			m_pSkinnedMesh->PlayOneShot("SPELL2", 0.3f,0.3f);
			break;
		case E_BOSS_WALK:
			m_pSkinnedMesh->Play("WALK", 0.3f);
			break;
		case E_BOSS_ATT2:
			m_pSkinnedMesh->PlayOneShot("ATT2", 0.3f,0.3f);
			break;

		default:
			m_pSkinnedMesh->Play("STAND", 0.3f);
			break;
		}
	}
}

void cBossAniController::Skill()
{
	m_pSkinnedMeshSkill->Update();
}



