#include "stdafx.h"
#include "cBossRagController.h"
#include "cSkinnedMesh.h"

cBossRagController::cBossRagController()
	: m_pSkinnedMesh_rag(NULL)
	, cBoss_rag_state(E_BOSS_RAG_START)
	, m_fBossRotY(0.f)
	, m_vBossDirX(1,0,0)
	, m_vBossDir(0,0,1)
	, m_vBossPos(5,0,0)
{
}


cBossRagController::~cBossRagController()
{
	SAFE_DELETE(m_pSkinnedMesh_rag);
}

void cBossRagController::SetUp()
{
	g_pSkinnedMeshManager->Setup("라그나로스", "Monster/boss/ragnaros", "ragnaros2.X");
	m_pSkinnedMesh_rag = g_pSkinnedMeshManager->Find("라그나로스");
	
}

void cBossRagController::Update(E_BOSS_RAG_STATE * pStateRag)
{
	if (m_pSkinnedMesh_rag)
		m_pSkinnedMesh_rag->Update();

	if (m_pSkinnedMesh_rag->GetCheck() && *pStateRag != E_BOSS_RAG_DEATH)
	{
		(*pStateRag) = E_BOSS_RAG_STAND;
	}

	SetAnimation(pStateRag);
}

void cBossRagController::Render(D3DXMATRIXA16 * m_world)
{
	D3DXMATRIXA16 matR2, matS2, matT2, matX2, World2;
	D3DXMatrixScaling(&matS2, 0.025f, 0.025f, 0.025f);

	D3DXMatrixRotationX(&matR2, D3DX_PI / 2.f);
	D3DXMatrixRotationY(&matR2, m_fBossRotY);

	D3DXMatrixIdentity(&matT2);
	D3DXMatrixTranslation(&matT2, m_vBossPos.x, m_vBossPos.y, m_vBossPos.z);
	D3DXMatrixRotationY(&matR2, D3DX_PI / -2.3f);
	D3DXVECTOR3 dir2;
	D3DXVec3TransformNormal(&dir2, &m_vBossDir, &matR2);
	D3DXVECTOR3 vUp2(0, 1, 0);
	D3DXVECTOR3 vRight2;
	D3DXVec3Cross(&vRight2, &vUp2, &dir2);
	D3DXVec3Normalize(&vRight2, &vRight2);
	D3DXVec3Cross(&vUp2, &dir2, &vRight2);
	D3DXMatrixLookAtLH(&matR2, &D3DXVECTOR3(0, 0, 0), &dir2, &vUp2);
	D3DXMatrixTranspose(&matR2, &matR2);

	World2 = matS2 * matR2 * matT2;
	if (m_pSkinnedMesh_rag)
		m_pSkinnedMesh_rag->Render(NULL, &World2);
}

void cBossRagController::SetAnimation(E_BOSS_RAG_STATE * pStateRag)
{
	if (cBoss_rag_state != (*pStateRag))
	{
		if (cBoss_rag_state != (*pStateRag))
		{
			cBoss_rag_state = (*pStateRag);
			switch (cBoss_rag_state)
			{
			case E_BOSS_RAG_STAND:
				m_pSkinnedMesh_rag->Play("STAND", 0.3f);
				break;
			case E_BOSS_RAG_START:
				m_pSkinnedMesh_rag->PlayOneShot("START", 0.3f);
				break;
			case E_BOSS_RAG_DEATH:
				m_pSkinnedMesh_rag->PlayOneShotAfterHold("DEATH", 0.3f);
				break;
			case E_BOSS_RAG_ATT:
				m_pSkinnedMesh_rag->PlayOneShot("ATT", 0.3f, 0.03f);
				break;
			case E_BOSS_RAG_SPELL:
				m_pSkinnedMesh_rag->PlayOneShot("SPELL", 0.3f, 0.3f);
				break;
			case E_BOSS_RAG_MERGE:
				m_pSkinnedMesh_rag->PlayOneShot("MERGE", 0.3f, 0.3f);
				break;
			default:
				m_pSkinnedMesh_rag->Play("STAND", 0.3f);
				break;
			}
		}
	}
}
