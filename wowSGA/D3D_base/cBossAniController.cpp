#include "stdafx.h"
#include "cBossAniController.h"
#include "cSkinnedMesh.h"
#include "cOBB.h"
#include "cParticle.h"


cBossAniController::cBossAniController()
	: m_pSkinnedMesh(NULL)
	, cBoss_STATE(E_BOSS_STAND)
	, m_fBossRotY(0.f)
	, m_vBossDirX(1,0,0)
	, m_vBossDir(0,0,1)
	, m_vBossPos(-5,0,0)
	, m_pSkinnedMeshSkill(NULL)
	, m_bSKill(false)
	, m_pBossOBB(NULL)
	, m_pSkinnedMeshSkill2(NULL)
{
}

cBossAniController::~cBossAniController()
{
	//SAFE_DELETE(m_pSkinnedMesh);
	//SAFE_DELETE(m_pSkinnedMeshSkill);
	//SAFE_DELETE(m_pSkinnedMeshSkill2);
	SAFE_DELETE(m_pBossOBB);
	SAFE_DELETE(m_Wind);
}

void cBossAniController::SetUp(std::vector<tagMon> Monster)
{
	
	for (int i = 0; i < Monster.size(); i++)
	{
		if (Monster[i].kind == KIND_BOSS_ARTHAS)
		{
			m_vBossPos = Monster[i].pos;
		}
	}
	m_pSkinnedMesh = g_pSkinnedMeshManager->Find("리치왕");
	m_pSkinnedMeshSkill = g_pSkinnedMeshManager->Find("스킬");
	m_pSkinnedMeshSkill2 = g_pSkinnedMeshManager->Find("아이스노바");
	

	m_Wind = g_pSkinnedMeshManager->Find("휠윈드");

	D3DXMATRIXA16 matT;
	D3DXMatrixIdentity(&matT);
	//D3DXMatrixTranslation(&matT, -3, 0, -17);
	D3DXMATRIXA16 matR, matS, World;
	D3DXMatrixScaling(&matS, 0.02f, 0.02f, 0.02f);

	D3DXMatrixRotationX(&matR, D3DX_PI / 2.f);

	World = matS * matR;

	m_pBossOBB = new cOBB();
	m_pBossOBB->Setup(m_pSkinnedMesh, &World);
	m_pSkinnedMeshSkill2->Play("SKILL2");
}

void cBossAniController::Update(E_BOSS_STATE* pState)
{
	if (m_pSkinnedMesh)
		m_pSkinnedMesh->Update();

	//if (*pState == E_BOSS_WHIRLWIND)
		m_Wind->Update();

	m_pSkinnedMeshSkill2->Update();

	if (m_pBossOBB)
		m_pBossOBB->Update(&m_obbw);

	if (m_pSkinnedMesh->GetCheck() && *pState != E_BOSS_DEATH)
	{
		(*pState) = E_BOSS_STAND;

	}

	

	SetAnimation(pState);
} 
 
void cBossAniController::Render(D3DXMATRIXA16  &m_world)
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
	m_obbw = matXX * matR*matT;
	if (m_pSkinnedMesh)
		m_pSkinnedMesh->Render(NULL, &World);
	m_world = World;
	D3DXCOLOR c = D3DCOLOR_XRGB(255, 255, 255);
	//if (m_pBossOBB)
	//	m_pBossOBB->Render_Debug(c, &World, NULL);

	if(cBoss_STATE == E_BOSS_SPELL1)
	m_pSkinnedMeshSkill->Render(NULL, &World);

	D3DXMATRIXA16 matRRR, matWWW, matR1;
	D3DXMatrixRotationX(&matRRR, D3DX_PI / 2.0f);
	static float hh = 0.1f;

	D3DXMatrixRotationY(&matR1, hh);
	hh += 0.3f;
	matWWW = matS * matRRR*matR1*matT;
	m_Wind->setAnimationSpeed(100.0f);
	if (cBoss_STATE == E_BOSS_WHIRLWIND)
	m_Wind->Render(NULL, &matWWW);


	m_pBossOBB->Render_Debug(D3DCOLOR_XRGB(192, 0, 0),nullptr , nullptr);
	
	skillRender();
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
			m_Wind->Play("WIND", 0.3f);
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

void cBossAniController::Collision(cOBB * PlayerBox)
{
	//m_pBossOBB->IsCollision(PlayerBox);
}

void cBossAniController::skillRender()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);

	g_pD3DDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, true);
	g_pD3DDevice->SetRenderState(D3DRS_POINTSCALEENABLE, true);

	g_pD3DDevice->SetRenderState(D3DRS_POINTSCALE_A, cParticle::FtoDw(0.0f));
	g_pD3DDevice->SetRenderState(D3DRS_POINTSCALE_B, cParticle::FtoDw(0.0f));
	g_pD3DDevice->SetRenderState(D3DRS_POINTSCALE_C, cParticle::FtoDw(1.0f));

	g_pD3DDevice->SetRenderState(D3DRS_POINTSIZE, cParticle::FtoDw(0.5f));
	g_pD3DDevice->SetRenderState(D3DRS_POINTSIZE_MIN, cParticle::FtoDw(0.2f));
	g_pD3DDevice->SetRenderState(D3DRS_POINTSIZE_MAX, cParticle::FtoDw(20.0f));

	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

	g_pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	D3DXMATRIXA16 matS, matR, matT, World;
	D3DXMatrixScaling(&matS, 0.005f, 0.005f, 0.005f);
	D3DXMatrixRotationX(&matR, D3DX_PI / 2.f);
	D3DXMatrixTranslation(&matT, m_vBossPos.x, m_vBossPos.y, m_vBossPos.z);
	World = matS * matR * matT;
	m_pSkinnedMeshSkill2->setAnimationSpeed(0.1f);
	m_pSkinnedMeshSkill2->Render(NULL, &World);

	//if (cBoss_STATE == E_BOSS_WHIRLWIND)
		

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, false);
	g_pD3DDevice->SetRenderState(D3DRS_POINTSCALEENABLE, false);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	//g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);
}

D3DXVECTOR3 cBossAniController::getOBBCenter()
{
	return m_pBossOBB->GetCenterPos();
}

float cBossAniController::getOBBhalf()
{
	return m_pBossOBB->getMax();
}

