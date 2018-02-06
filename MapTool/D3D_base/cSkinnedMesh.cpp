#include "stdafx.h"
#include "cSkinnedMesh.h"
#include "cAllocateHierarchy.h"

cSkinnedMesh::cSkinnedMesh()
	: m_pRoot(NULL)
	, m_pAnimationController(NULL)
	, m_fPassedBlendTime(0.0f)
	, m_fBlendTime(0.5f)
	, m_isBlend(false)
	, m_fPlay(true)
	, m_fLoop(false)
	, m_baseAniNUM(0)
{

}


cSkinnedMesh::~cSkinnedMesh()
{
	cAllocateHierarchy ah;
	D3DXFrameDestroy(m_pRoot, &ah);
	SAFE_RELEASE(m_pAnimationController);
}

void cSkinnedMesh::Setup(IN char* szFolder, IN char* szFile)
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

	SetupBoneMatrixPtrs(m_pRoot);
}

void cSkinnedMesh::Update()
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

		m_pAnimationController->AdvanceTime(
			g_pTimeManager->GetEllapsedTime(), NULL);
	}


	// frame & mesh
	Update(m_pRoot, NULL);
	UpdateSkinnedMesh(m_pRoot);
}

void cSkinnedMesh::Update(LPD3DXFRAME pFrame, LPD3DXFRAME pParent)
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

void cSkinnedMesh::Update_time(float time)
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
		}
	}
	m_AnimationPlayFactor = m_AnimationPlayFactor - (int)m_AnimationPlayFactor;
	if (m_fPlay)
	{
		m_pAnimationController->AdvanceTime(time, NULL);
	}
}

void cSkinnedMesh::Render(LPD3DXFRAME pFrame, D3DXMATRIXA16* m_Word)
{
	if (pFrame == NULL)
		pFrame = m_pRoot;

	ST_BONE* pBone = (ST_BONE*)pFrame;

	if (pBone->pMeshContainer)
	{
		ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pBone->pMeshContainer;
		if (pBoneMesh->MeshData.pMesh)
		{
			g_pD3DDevice->SetTransform(D3DTS_WORLD,
				&pBone->matCombinedTransformMatrix);
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

void cSkinnedMesh::ani_Play(int index)
{
	m_pAnimationController->SetTrackPosition(0, 0.0f);
	m_fPlay = true;
	m_fLoop = true;
	SetAnimationIndexBlend(index);
}

void cSkinnedMesh::ani_Play(char * name)
{
	m_pAnimationController->SetTrackPosition(0, 0.0f);
	m_fPlay = true;
	m_fLoop = true;
	SetAnimationIndexBlend(name);
}

void cSkinnedMesh::SetupBoneMatrixPtrs(LPD3DXFRAME pFrame)
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

void cSkinnedMesh::UpdateSkinnedMesh(LPD3DXFRAME pFrame)
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

void cSkinnedMesh::SetAnimationIndexBlend(int nIndex)
{
	m_isBlend = true;
	m_fPassedBlendTime = 0.0f;

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

void cSkinnedMesh::SetAnimationIndexBlend(char * name)
{
	int nIndex = 0;
	for (int i = 0; i < m_vecAnimSet.size(); i++)
	{
		LPD3DXANIMATIONSET animSet;
		m_pAnimationController->GetAnimationSet(i, &animSet);
		std::string Aniname = (char*)animSet->GetName();
		std::string IndexName = name;
		if (Aniname == IndexName)
		{
			nIndex = i;
		}
	}
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

void cSkinnedMesh::updateSetting(LPD3DXFRAME pFrame, D3DXMATRIXA16* m_Word)
{
	ST_BONE* pBone = (ST_BONE*)pFrame;
	if (m_Word)
	{
		pBone->matCombinedTransformMatrix *= (*m_Word);
	}
	if (pFrame->pFrameFirstChild)
	{
		updateSetting(pFrame->pFrameFirstChild, m_Word);
	}
	if (pFrame->pFrameSibling)
	{
		updateSetting(pFrame->pFrameSibling, m_Word);
	}
}

ST_BONE * cSkinnedMesh::GetFindBONE(std::string boneName)
{
	return (ST_BONE*)D3DXFrameFind(m_pRoot, boneName.c_str());
}

