#include "stdafx.h"
#include "cSkinnedMesh.h"
#include "cAllocateHierarchy.h"


cSkinnedMesh::cSkinnedMesh()
	: m_pRoot(NULL)
	, m_pNowPlayAnimationSet(NULL)
{
}


cSkinnedMesh::~cSkinnedMesh()
{
	for (int i = 0; i < this->m_vecAnimSet.size(); i++)
		SAFE_RELEASE(m_vecAnimSet[i]);
	SAFE_RELEASE(m_pAnimController);
	cAllocateHierarchy ah;
	D3DXFrameDestroy(m_pRoot, &ah);
}

void cSkinnedMesh::Setup(IN char * szFolder, IN char * szFile)
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
		&m_pAnimController);

	SetupBoneMatrixPtrs(m_pRoot);


	m_AnimNum = m_pAnimController->GetNumAnimationSets();
	ID3DXAnimationSet * ani;
	m_pAnimController->GetAnimationSet(0, &ani);
	m_pAnimController->SetTrackAnimationSet(0, ani);
	m_pAnimController->SetTrackEnable(0, true);
	m_pAnimController->ResetTime();

	for (UINT i = 0; i < m_AnimNum; i++)
	{
		
		LPD3DXANIMATIONSET animSet;
		m_pAnimController->GetAnimationSet(i, &animSet);
		this->m_vecAnimSet.push_back(animSet);

	
	}
	
	this->Play(0);
}

void cSkinnedMesh::Update()
{
	Update(m_pRoot, NULL);
	UpdateSkinnedMesh(m_pRoot);
	Update(g_pTimeManager->GetEllapsedTime());
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

void cSkinnedMesh::Update(float time)
{
	m_pAnimController->GetTrackDesc(0, &m_Track_Desc_0);

	m_AnimationPlayFactor = m_Track_Desc_0.Position / m_pNowPlayAnimationSet->GetPeriod();

	if (m_AnimationPlayFactor >= 1.0)
	{
		if (this->m_bLoop == false)
		{
			this->Stop();
		}
	}
	m_AnimationPlayFactor = m_AnimationPlayFactor - (int)m_AnimationPlayFactor;	//정수부분 안생기게....

	if (m_bPlay)
	{
		m_pAnimController->AdvanceTime(time, NULL);
	}



}

void cSkinnedMesh::Render(LPD3DXFRAME pFrame)
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
				D3DXMATRIXA16 matS;
				D3DXMatrixScaling(&matS, 0.008f, 0.008f, 0.008f);
				g_pD3DDevice->SetTransform(D3DTS_WORLD, &matS);
				g_pD3DDevice->SetTexture(0, pBoneMesh->vecTexture[i]);
				g_pD3DDevice->SetMaterial(&pBoneMesh->vecMtl[i]);
				pBoneMesh->MeshData.pMesh->DrawSubset(i);
			}
		}
	}

	if (pFrame->pFrameFirstChild)
	{
		Render(pFrame->pFrameFirstChild);
	}

	if (pFrame->pFrameSibling)
	{
		Render(pFrame->pFrameSibling);
	}
}

void cSkinnedMesh::Play(int animIndex, float crossFadeTime)
{

	m_bPlay = true;
	m_bLoop = true;

	if (animIndex < this->m_AnimNum) {

		SetAnimation(m_vecAnimSet[animIndex]);
	}
}

UINT cSkinnedMesh::GetAnimationNums()
{
	return m_AnimNum;
}

void cSkinnedMesh::SetPlaySpeed(float speed)
{
	m_pAnimController->SetTrackSpeed(0, speed);
}

void cSkinnedMesh::SetAnimation(LPD3DXANIMATIONSET animSet)
{
	if (m_pNowPlayAnimationSet != NULL &&
		animSet == m_pNowPlayAnimationSet)
		return;

	m_pAnimController->SetTrackPosition(0, 0.0f);

	m_pAnimController->SetTrackAnimationSet(0, animSet);

	m_pNowPlayAnimationSet = animSet;
	
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
