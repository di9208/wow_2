#include "stdafx.h"
#include "cBossRagController.h"
#include "cSkinnedMesh.h"
#include "cOBB.h"

cBossRagController::cBossRagController()
	: m_pSkinnedMesh_rag(NULL)
	, cBoss_rag_state(E_BOSS_RAG_START)
	, m_fBossRotY(0.f)
	, m_vBossDirX(1,0,0)
	, m_vBossDir(0,0,1)
	, m_vBossPos(5,0,0)
	, m_pSkinnedMesh_rag_skill1(NULL)
	, m_pSkinnedMesh_rag_skill2(NULL)
	, m_pBossRagOBB(NULL)
{
}


cBossRagController::~cBossRagController()
{
	SAFE_DELETE(m_pSkinnedMesh_rag);
	SAFE_DELETE(m_pSkinnedMesh_rag_skill1);
	SAFE_DELETE(m_pSkinnedMesh_rag_skill2);
	SAFE_DELETE(m_pBossRagOBB);
}

void cBossRagController::SetUp(std::vector<tagMon> Monster)
{
	for (int i = 0; i < Monster.size(); i++)
	{
		if (Monster[i].kind == KIND_BOSS_RAGNALOS)
		{
			m_vBossPos = Monster[i].pos;
		}
	}
	//g_pSkinnedMeshManager->Setup("라그나로스", "Monster/boss/ragnaros", "ragnaros2.X");
	m_pSkinnedMesh_rag = g_pSkinnedMeshManager->Find("라그나로스");
	
	//g_pSkinnedMeshManager->Setup("스킬1", "Monster/boss/ragnaros", "ragSkill1.x");
	m_pSkinnedMesh_rag_skill1 = g_pSkinnedMeshManager->Find("스킬1");
	m_pSkinnedMesh_rag_skill1->Play("rag1");

	//g_pSkinnedMeshManager->Setup("스킬2", "Monster/boss/ragnaros", "ragSkill2.x");
	m_pSkinnedMesh_rag_skill2 = g_pSkinnedMeshManager->Find("스킬2");
	m_pSkinnedMesh_rag_skill2->Play("rag2");


	D3DXMATRIXA16 matR, matS, matT, World;
	D3DXMatrixScaling(&matS, 0.0035f, 0.0035f, 0.0035f);
	D3DXMatrixTranslation(&matT, -2.8f, 0, 4.5f);
	D3DXMatrixRotationX(&matR, D3DX_PI / 2.3f);

	World = matS * matR * matT;

	m_pBossRagOBB = new cOBB();
	m_pBossRagOBB->Setup(m_pSkinnedMesh_rag, &World);
}

void cBossRagController::Update(E_BOSS_RAG_STATE * pStateRag)
{
	if (m_pSkinnedMesh_rag)
		m_pSkinnedMesh_rag->Update();

	if (m_pSkinnedMesh_rag_skill1) m_pSkinnedMesh_rag_skill1->Update();
	if (m_pSkinnedMesh_rag_skill2) m_pSkinnedMesh_rag_skill2->Update();

	if (m_pBossRagOBB)
		m_pBossRagOBB->Update(&m_obbw);

	if (m_pSkinnedMesh_rag->GetCheck() && *pStateRag != E_BOSS_RAG_DEATH)
	{
		(*pStateRag) = E_BOSS_RAG_STAND;
	}

	SetAnimation(pStateRag);
}

void cBossRagController::Render(D3DXMATRIXA16  &m_world)
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
	//D3DXMatrixTranspose(&matR2, &matR2);
	m_obbw = matR2 *matT2;
	if (m_pSkinnedMesh_rag)
		m_pSkinnedMesh_rag->Render(NULL, &World2);
	m_world = World2;
	if (m_pSkinnedMesh_rag_skill1) skillRender();
	if (m_pSkinnedMesh_rag_skill2) skillRender2();

	m_pBossRagOBB->Render_Debug(D3DCOLOR_XRGB(192, 0, 0), nullptr, nullptr);
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
				//m_pSkinnedMesh_rag->Play("STAND", 0.3f);
				break;
			}
		}
	}
}

void cBossRagController::skillRender()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);

	g_pD3DDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, true);
	g_pD3DDevice->SetRenderState(D3DRS_POINTSCALEENABLE, true);

	g_pD3DDevice->SetRenderState(D3DRS_POINTSCALE_A, 0.0f);
	g_pD3DDevice->SetRenderState(D3DRS_POINTSCALE_B, 0.0f);
	g_pD3DDevice->SetRenderState(D3DRS_POINTSCALE_C, 1.0f);

	g_pD3DDevice->SetRenderState(D3DRS_POINTSIZE, 1);
	g_pD3DDevice->SetRenderState(D3DRS_POINTSIZE_MIN, 0.2f);
	g_pD3DDevice->SetRenderState(D3DRS_POINTSIZE_MAX, 20.0f);

	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

	g_pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	D3DXMATRIXA16 matS, matR, matT, World;
	D3DXMatrixScaling(&matS, 0.25f, 0.25f, 0.25f);
	D3DXMatrixRotationX(&matR, D3DX_PI / 2.f);
	D3DXMatrixTranslation(&matT, m_vBossPos.x - 5, m_vBossPos.y + 0.1f, m_vBossPos.z);
	World = matS * matR * matT;
	m_pSkinnedMesh_rag_skill1->setAnimationSpeed(0.1f);
	m_pSkinnedMesh_rag_skill1->Render(NULL, &World);

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, false);
	g_pD3DDevice->SetRenderState(D3DRS_POINTSCALEENABLE, false);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	//g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);
}

void cBossRagController::skillRender2()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);

	g_pD3DDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, true);
	g_pD3DDevice->SetRenderState(D3DRS_POINTSCALEENABLE, true);

	g_pD3DDevice->SetRenderState(D3DRS_POINTSCALE_A, 0.0f);
	g_pD3DDevice->SetRenderState(D3DRS_POINTSCALE_B, 0.0f);
	g_pD3DDevice->SetRenderState(D3DRS_POINTSCALE_C, 1.0f);

	g_pD3DDevice->SetRenderState(D3DRS_POINTSIZE, 1);
	g_pD3DDevice->SetRenderState(D3DRS_POINTSIZE_MIN, 0.2f);
	g_pD3DDevice->SetRenderState(D3DRS_POINTSIZE_MAX, 20.0f);

	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

	g_pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	D3DXMATRIXA16 matS, matR, matT, World;

	D3DXMatrixScaling(&matS, 0.35f, 0.35f, 0.35f);
	D3DXMatrixRotationX(&matR, D3DX_PI / 2.f);
	D3DXMatrixTranslation(&matT, m_vBossPos.x - 5, m_vBossPos.y + 0.1f, m_vBossPos.z);
	World = matS * matR * matT;
	m_pSkinnedMesh_rag_skill2->Render(NULL, &World);

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, false);
	g_pD3DDevice->SetRenderState(D3DRS_POINTSCALEENABLE, false);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}

D3DXVECTOR3 cBossRagController::getOBBCenter()
{
	return m_pBossRagOBB->GetCenterPos();
}

float cBossRagController::getOBBhalf()
{
	return m_pBossRagOBB->getMax();
}
