#include "stdafx.h"
#include "cNpc_AniController.h"

#include "cSkinnedMesh.h"

cNpc_AniController::cNpc_AniController()
	: m_NPC_SkinnedMesh(NULL)
	, cNpc_State(NOTHING)
{

}


cNpc_AniController::~cNpc_AniController()
{
	SAFE_DELETE(m_NPC_SkinnedMesh);
}

void cNpc_AniController::Setup()
{

	m_NPC_SkinnedMesh = g_pSkinnedMeshManager->Find("NPC");
}

void cNpc_AniController::Update(NPC_State * Nstate)
{
	if (m_NPC_SkinnedMesh)
		m_NPC_SkinnedMesh->Update();
	SetAnimation(Nstate);
	m_NPC_SkinnedMesh->GetCheck() == true;
}

void cNpc_AniController::Render(D3DXMATRIXA16 * Update_world)
{
	D3DXMATRIXA16 matR, matS, m_world;
	D3DXMatrixRotationX(&matR, D3DX_PI / 2.0f);
	D3DXMatrixScaling(&matS, 0.1f, 0.1f, 0.1f);
	m_world = matR * matS;
	m_NPC_SkinnedMesh->updateSetting(m_NPC_SkinnedMesh->GetRoot(), &m_world);
	if (m_NPC_SkinnedMesh)
		m_NPC_SkinnedMesh->Render(NULL, Update_world);
}

void cNpc_AniController::SetAnimation(NPC_State * Nstate)
{
	if (cNpc_State != (*Nstate))
	{
		cNpc_State = (*Nstate);
		switch (cNpc_State)
		{
		case TALK:
			m_NPC_SkinnedMesh->Play("TALK", 0.3f);
			break;
		case YES:
			m_NPC_SkinnedMesh->Play("YES", 0.3f);
			break;
		case NO:
			m_NPC_SkinnedMesh->Play("NO", 0.3f);
			break;
		}
	}
}

void cNpc_AniController::SetAnimationRotationSize(LPD3DXFRAME nFrame, LPD3DXFRAME nParent)
{
	ST_BONE* nBone = (ST_BONE*)nFrame;
	nBone->matCombinedTransformMatrix = nBone->TransformationMatrix;
	if (nBone)
	{
		nBone->matCombinedTransformMatrix *=
			((ST_BONE*)nParent)->matCombinedTransformMatrix;
	}

	if (nFrame->pFrameFirstChild)
	{
		SetAnimationRotationSize(nFrame->pFrameFirstChild, nFrame);
	}

	if (nFrame->pFrameSibling)
	{
		SetAnimationRotationSize(nFrame->pFrameSibling, nParent);
	}
}

ST_BONE * cNpc_AniController::GetFindBONE(std::string boneName)
{
	return (ST_BONE*)D3DXFrameFind(m_NPC_SkinnedMesh->GetRoot(), boneName.c_str());
}

cSkinnedMesh * cNpc_AniController::GetFindSkinedMesh(std::string boneName)
{
	return (cSkinnedMesh*)D3DXFrameFind(m_NPC_SkinnedMesh->GetRoot(), boneName.c_str());
}
