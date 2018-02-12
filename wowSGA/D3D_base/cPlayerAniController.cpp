#include "stdafx.h"
#include "cPlayerAniController.h"

#include "cSkinnedMesh.h"

cPlayerAniController::cPlayerAniController()
	: m_pSkinnedMesh(NULL)
	, cPlayer_condition(NONE)
{
}


cPlayerAniController::~cPlayerAniController()
{
	//SAFE_DELETE(m_pSkinnedMesh);
}

void cPlayerAniController::Setup(float x, float y, float z)
{
	m_pSkinnedMesh = g_pSkinnedMeshManager->Find("player");
	initPos.x = x;
	initPos.y = y;
	initPos.z = z;
}

void cPlayerAniController::Update(condition * pCondition)
{
	if (m_pSkinnedMesh)
		m_pSkinnedMesh->Update();
	SetAnimation(pCondition);
	if ((*pCondition) != IDLE)
	{
		if (m_pSkinnedMesh->GetCheck() == true && 
			(*pCondition) != DEATH && 
			(*pCondition) != JUMP_UP &&
			(*pCondition) != ROLL_START &&
			(*pCondition) != ROLL&&
			(*pCondition) != SKILL_2
			)
		{
			(*pCondition) = IDLE;
		}
	}
}

void cPlayerAniController::Render(D3DXMATRIXA16 * m_wolrd)
{
	D3DXMATRIXA16  matR, matS, World,matRY;
	D3DXMatrixRotationX(&matR, D3DX_PI / 2.0f);
	D3DXMatrixRotationY(&matRY, D3DX_PI / 2.0f);
	D3DXMatrixScaling(&matS, 0.1f, 0.1f, 0.1f);
	m_World = matS* matR;
	m_pSkinnedMesh->updateSetting(m_pSkinnedMesh->GetRoot(), &m_World);
	if (m_pSkinnedMesh)
		m_pSkinnedMesh->Render(NULL, m_wolrd);
}

void cPlayerAniController::SetAnimation(condition * pCondition)
{
	if (cPlayer_condition != (*pCondition))
	{
		cPlayer_condition = (*pCondition);
		switch (cPlayer_condition)
		{
		case IDLE:
			m_pSkinnedMesh->Play("IDLE", 0.3f);//idle
			break;
		case RUN:
			m_pSkinnedMesh->Play("RUN", 0.3f);//run
			break;
		case ATTACK:
			m_pSkinnedMesh->PlayOneShot("ATTACK", 0.3f, 0.3f);
			break;
		case BREATH:
			m_pSkinnedMesh->PlayOneShot("BREATH", 0.3f, 0.3f);
			break;
		case BUFF:
			m_pSkinnedMesh->PlayOneShot("BUFF_0", 0.3f, 0.3f);
			break;
		case DEATH:
			m_pSkinnedMesh->PlayOneShotAfterHold("DEATH", 0.3f);
			break;
		case JUMP_UP:
			m_pSkinnedMesh->PlayOneShot("JUMP_START", 0.3f, 0.3f);
			break;
		case JUMP_ING:
			m_pSkinnedMesh->PlayOneShot("JUMP_ING", 0.3f, 0.3f);
			break;
		case JUMP_DOWN:
			m_pSkinnedMesh->PlayOneShot("JUMP_END", 0.3f, 0.3f);
			break;
		case ROLL_START:
			m_pSkinnedMesh->PlayOneShot("ROLL_START", 0.1f, 0.1f);
			break;
		case ROLL:
			m_pSkinnedMesh->PlayOneShot("ROLL", 0.1f, 0.1f);//부드럽게 끊기나 안끊기냐
			break;
		case ROLL_END:
			m_pSkinnedMesh->PlayOneShotAfterHold("ROLL_END",0.1f);
			break;
		case HURT:
			m_pSkinnedMesh->PlayOneShot("HURT", 0.3f, 0.3f);
			break;
		case SKILL_1:
			m_pSkinnedMesh->PlayOneShot("SKILL_1", 0.3f, 0.3f);
			break;
		case SKILL_2:
			m_pSkinnedMesh->PlayOneShot("SKILL_2", 0.3f, 0.3f);
			break;
		case SKILL_3:
			m_pSkinnedMesh->PlayOneShot("SKILL_3", 0.3f, 0.3f);
			break;
		case BACKWALK:
			m_pSkinnedMesh->Play("BACKWALK", 0.3f);
			break;
		}
	}
}

void cPlayerAniController::SetAnimationRotationSize(LPD3DXFRAME pFrame, LPD3DXFRAME pParent)
{
	ST_BONE* pBone = (ST_BONE*)pFrame;
	pBone->matCombinedTransformMatrix = pBone->TransformationMatrix;
	if (pBone)
	{
		pBone->matCombinedTransformMatrix *=
			((ST_BONE*)pParent)->matCombinedTransformMatrix;
	}

	if (pFrame->pFrameFirstChild)
	{
		SetAnimationRotationSize(pFrame->pFrameFirstChild, pFrame);
	}

	if (pFrame->pFrameSibling)
	{
		SetAnimationRotationSize(pFrame->pFrameSibling, pParent);
	}
}

ST_BONE * cPlayerAniController::GetFindBONE(std::string boneName)
{
	return (ST_BONE*)D3DXFrameFind(m_pSkinnedMesh->GetRoot(), boneName.c_str());
}

cSkinnedMesh * cPlayerAniController::GetFindSkinedMesh(std::string boneName)
{
	return (cSkinnedMesh*)D3DXFrameFind(m_pSkinnedMesh->GetRoot(), boneName.c_str());
}

