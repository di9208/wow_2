#include "stdafx.h"
#include "cEnemySkinnedMesh.h"
#include "cAllocateHierarchy.h"

cEnemySkinnedMesh::cEnemySkinnedMesh()
: m_pRoot(NULL)
, m_pAnimationController(NULL)
, m_fPassedBlendTime(0.0f)
, m_fBlendTime(0.5f)
, m_isBlend(false)
, m_fPlay(true)
, m_fLoop(false)
, m_baseAniNUM(0)
, m_fRotY(0)
, m_vDir(0, 0, 1)
, m_vPos(0, 0, 0)
, bi(false)
{
	//D3DXMatrixIdentity(&m_wrold);
}


cEnemySkinnedMesh::~cEnemySkinnedMesh()
{
	cAllocateHierarchy ah;
	D3DXFrameDestroy(m_pRoot, &ah);
	SAFE_RELEASE(m_pAnimationController);
}

void cEnemySkinnedMesh::addMonsterPos(D3DXMATRIXA16* m_Word, float x, float y, float z, float size){
	fx = fy = fz = size;
	m_vPos.x = x;
	m_vPos.y = y;
	m_vPos.z = z;
	D3DXMatrixIdentity(m_Word);
}

void cEnemySkinnedMesh::Setup(IN char * szFolder, IN char * szFile)
{
	std::string sFullPath(szFolder);
	sFullPath = sFullPath + std::string("/") + std::string(szFile);

	cAllocateHierarchy ah;
	ah.SetFolder(std::string(szFolder));

	D3DXLoadMeshHierarchyFromX(sFullPath.c_str(),
		D3DXMESH_MANAGED | D3DXMESH_32BIT,
		g_pD3DDevice,
		&ah,
		NULL,
		&m_pRoot,
		&m_pAnimationController);

	float m_AnimNum = m_pAnimationController->GetNumAnimationSets();
	//m_AnimNum에 애니메이션 갯수를 담는다
	ID3DXAnimationSet * ani;
	m_pAnimationController->GetAnimationSet(0, &ani);
	m_pAnimationController->SetTrackAnimationSet(0, ani);
	m_pAnimationController->SetTrackEnable(0, true);
	m_pAnimationController->ResetTime();

	for (UINT i = 0; i < m_AnimNum; i++)
	{
		LPD3DXANIMATIONSET animSet;
		m_pAnimationController->GetAnimationSet(i, &animSet);
		this->m_vecAnimSet.push_back(animSet);
	}

	ani_Play(m_baseAniNUM);
	SetupBoneMatrixPtrs(m_pRoot);
}

void cEnemySkinnedMesh::Update()
{
	// animation
	if (m_pAnimationController)
	{
		if (m_isBlend)
		{
			m_fPassedBlendTime += g_pTimeManager->GetEllapsedTime();
			if (m_fPassedBlendTime >= m_fBlendTime)
			{
				m_pAnimationController->SetTrackWeight(0, 1.0f);
				m_pAnimationController->SetTrackEnable(1, false);
			}
			else
			{
				float fWeight = m_fPassedBlendTime / m_fBlendTime;
				m_pAnimationController->SetTrackWeight(0, fWeight);
				m_pAnimationController->SetTrackWeight(1, 1.0f - fWeight);
			}
		}
	}

	// frame & mesh
	Update_time(g_pTimeManager->GetEllapsedTime());
	Update(m_pRoot, NULL);
	UpdateSkinnedMesh(m_pRoot);
}

void cEnemySkinnedMesh::Update(LPD3DXFRAME pFrame, LPD3DXFRAME pParent)
{
	ST_BONE* pBone = (ST_BONE*)pFrame;
	pBone->matCombinedTransformMatrix = pBone->TransformationMatrix;
	if (pParent)
	{
		pBone->matCombinedTransformMatrix *=
			((ST_BONE*)pParent)->matCombinedTransformMatrix;
	}

	if (pFrame->pFrameFirstChild)
	{
		Update(pFrame->pFrameFirstChild, pFrame);
	}

	if (pFrame->pFrameSibling)
	{
		Update(pFrame->pFrameSibling, pParent);
	}
}

void cEnemySkinnedMesh::Update_time(float time)
{
	D3DXTRACK_DESC stTrackDesc;
	m_pAnimationController->GetTrackDesc(0, &stTrackDesc);

	float m_AnimationPlayFactor
		= stTrackDesc.Position / m_pNowPlayAnimationSet->GetPeriod();

	if (m_AnimationPlayFactor >= 1.0)
	{
		if (m_fLoop == false)
		{
			m_fPlay = false;
			//ani_Play(m_baseAniNUM);
		}
	}
	m_AnimationPlayFactor = m_AnimationPlayFactor - (int)m_AnimationPlayFactor;
	if (m_fPlay)
	{
		m_pAnimationController->AdvanceTime(time, NULL);
	}
}

void cEnemySkinnedMesh::Render(LPD3DXFRAME pFrame, D3DXMATRIXA16* m_Word)
{
	if (pFrame == NULL)
		pFrame = m_pRoot;

	ST_BONE* pBone = (ST_BONE*)pFrame;

	//D3DXMATRIXA16 matR, matS, matT;
	//D3DXMatrixScaling(&matS, fx, fy, fz);
	//
	//D3DXMatrixRotationY(&matR, D3DX_PI / 2.0f);
	//D3DXVec3TransformNormal(&m_vDir, &m_vDir, &matR);

	//GetMatRFromDir(matR, m_vDir);

	////D3DXVec3Normalize(&m_vDir, &m_vDir);
	////D3DXMatrixLookAtLH(&matRx, &D3DXVECTOR3(0, 0, 0), &m_vPlayerPos, &D3DXVECTOR3(0, 0, 0));

	//D3DXMatrixIdentity(&matT);
	//D3DXMatrixTranslation(&matT, m_vPos.x, m_vPos.y, m_vPos.z);
	//
	//pBone->matCombinedTransformMatrix = matS * matR * matT * m_wrold;

	if (pBone->pMeshContainer)
	{
		ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pBone->pMeshContainer;
		if (pBoneMesh->MeshData.pMesh)
		{
			g_pD3DDevice->SetTransform(D3DTS_WORLD,
				&(pBone->matCombinedTransformMatrix *(*m_Word)));
			for (size_t i = 0; i < pBoneMesh->vecMtl.size(); i++)
			{
				g_pD3DDevice->SetTexture(0, pBoneMesh->vecTexture[i]);
				g_pD3DDevice->SetMaterial(&pBoneMesh->vecMtl[i]);
				pBoneMesh->MeshData.pMesh->DrawSubset(i);
			}
		}
	}

	if (pFrame->pFrameFirstChild)
	{
		Render(pFrame->pFrameFirstChild, m_Word);
	}

	if (pFrame->pFrameSibling)
	{
		Render(pFrame->pFrameSibling, m_Word);
	}
}

void cEnemySkinnedMesh::ani_Play(int index)
{
	m_pAnimationController->SetTrackPosition(0, 0.0f);
	m_fPlay = true;
	m_fLoop = true;
	SetAnimationIndexBlend(index);
}

void cEnemySkinnedMesh::SetupBoneMatrixPtrs(LPD3DXFRAME pFrame)
{
	if (pFrame && pFrame->pMeshContainer)
	{
		ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pFrame->pMeshContainer;
		if (pBoneMesh->pSkinInfo)
		{
			DWORD dwBoneNum = pBoneMesh->pSkinInfo->GetNumBones();
			for (DWORD i = 0; i < dwBoneNum; i++)
			{
				ST_BONE* pBone = (ST_BONE*)D3DXFrameFind(m_pRoot,
					pBoneMesh->pSkinInfo->GetBoneName(i));

				pBoneMesh->ppBoneMatrixPtrs[i] =
					&(pBone->matCombinedTransformMatrix);
			}
		}
	}

	if (pFrame->pFrameFirstChild)
	{
		SetupBoneMatrixPtrs(pFrame->pFrameFirstChild);
	}

	if (pFrame->pFrameSibling)
	{
		SetupBoneMatrixPtrs(pFrame->pFrameSibling);
	}
}

void cEnemySkinnedMesh::UpdateSkinnedMesh(LPD3DXFRAME pFrame)
{
	// pCurrBoneMarix = pBoneOffsetMatrix * ppBoneMatrixPtrs

	if (pFrame && pFrame->pMeshContainer)
	{
		ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pFrame->pMeshContainer;
		if (pBoneMesh->pSkinInfo)
		{
			DWORD dwBoneNum = pBoneMesh->pSkinInfo->GetNumBones();
			for (DWORD i = 0; i < dwBoneNum; i++)
			{
				pBoneMesh->pCurrBoneMarixs[i] =
					pBoneMesh->pBoneOffsetMatrixs[i] *
					(*pBoneMesh->ppBoneMatrixPtrs[i]);
			}
		}

		BYTE* src = NULL;
		BYTE* dest = NULL;

		pBoneMesh->pOrigMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&src);
		pBoneMesh->MeshData.pMesh->LockVertexBuffer(0, (void**)&dest);

		pBoneMesh->pSkinInfo->UpdateSkinnedMesh(
			pBoneMesh->pCurrBoneMarixs, NULL, src, dest);

		pBoneMesh->pOrigMesh->UnlockVertexBuffer();
		pBoneMesh->MeshData.pMesh->UnlockVertexBuffer();
	}

	if (pFrame->pFrameFirstChild)
	{
		UpdateSkinnedMesh(pFrame->pFrameFirstChild);
	}

	if (pFrame->pFrameSibling)
	{
		UpdateSkinnedMesh(pFrame->pFrameSibling);
	}

}

void cEnemySkinnedMesh::SetAnimationIndex(int nIndex)
{
	int nMax = m_pAnimationController->GetNumAnimationSets();
	if (nIndex > nMax)	nIndex = nIndex % nMax;

	LPD3DXANIMATIONSET	pAnimSet = NULL;
	m_pAnimationController->GetAnimationSet(nIndex, &pAnimSet);
	m_pAnimationController->SetTrackAnimationSet(0, pAnimSet);

	SAFE_RELEASE(pAnimSet);
}

void cEnemySkinnedMesh::SetAnimationIndexBlend(int nIndex)
{
	m_isBlend = true;
	m_fPassedBlendTime = 0.0f;

	m_pNowPlayAnimationSet = m_vecAnimSet[nIndex];
	int nMax = m_pAnimationController->GetNumAnimationSets();
	if (nIndex > nMax)	nIndex = nIndex % nMax;

	LPD3DXANIMATIONSET	pPrevAnimSet = NULL;
	LPD3DXANIMATIONSET	pNextAnimSet = NULL;

	D3DXTRACK_DESC stTrackDesc;
	m_pAnimationController->GetTrackDesc(0, &stTrackDesc);

	m_pAnimationController->GetTrackAnimationSet(0, &pPrevAnimSet);
	m_pAnimationController->SetTrackAnimationSet(1, pPrevAnimSet);
	m_pAnimationController->SetTrackDesc(1, &stTrackDesc);

	m_pAnimationController->GetAnimationSet(nIndex, &pNextAnimSet);
	m_pAnimationController->SetTrackAnimationSet(0, pNextAnimSet);

	m_pAnimationController->SetTrackWeight(0, 0.0f);
	m_pAnimationController->SetTrackWeight(1, 1.0f);

	SAFE_RELEASE(pPrevAnimSet);
	SAFE_RELEASE(pNextAnimSet);
}

void cEnemySkinnedMesh::GetMatRFromDir(D3DXMATRIXA16& matR, D3DXVECTOR3& vNext){
	D3DXVECTOR3 vUp(0, 1, 0);
	D3DXVECTOR3 vRight;
	D3DXVec3Cross(&vRight, &vUp, &vNext);
	D3DXVec3Normalize(&vRight, &vRight);
	D3DXVec3Cross(&vUp, &vNext, &vRight);
	D3DXMatrixLookAtLH(&matR, &D3DXVECTOR3(0, 0, 0), &vNext, &vUp);
	D3DXMatrixTranspose(&matR, &matR);
}