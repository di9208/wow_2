#include "stdafx.h"
#include "cSkinnedMesh.h"
#include "cAllocateHierarchy.h"


cSkinnedMesh::cSkinnedMesh()
	: m_pRoot(NULL)
	, m_pAnimationController(NULL)
	, m_fPassedBlendTime(0.0f)
	, m_fBlendTime(0.5f)
	, m_isBlend(false)
	, m_bCheck(false)
{
}


cSkinnedMesh::~cSkinnedMesh()
{
	cAllocateHierarchy ah;
	D3DXFrameDestroy(m_pRoot, &ah);
	SAFE_RELEASE(m_pAnimationController);
}

void cSkinnedMesh::addMonsterPos(D3DXMATRIXA16* m_Word, float x, float y, float z, float size){
	fx = fy = fz = size;
	m_vPos.x = x;
	m_vPos.y = y;
	m_vPos.z = z;
	D3DXMatrixIdentity(m_Word);
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
		&m_pAnimationController);
	m_vMin = ah.GetMin();
	m_vMax = ah.GetMax();


	SetupBoneMatrixPtrs(m_pRoot);

	m_AnimNum = m_pAnimationController->GetNumAnimationSets();

	for (UINT i = 0; i < m_AnimNum; i++)
	{

		LPD3DXANIMATIONSET animSet;

		m_pAnimationController->GetAnimationSet(i, &animSet);

		this->m_vecAnimSet.push_back(animSet);

		this->m_mapAnimSet.insert(std::make_pair(
			animSet->GetName(),
			animSet));
	}

	this->Play(m_vecAnimSet.size() - 1); // Initial Animation

}

void cSkinnedMesh::Update()
{
	// animation
	//if (m_pAnimationController)
	//{
	//	if (m_isBlend)
	//	{
	//		m_fPassedBlendTime += g_pTimeManager->GetEllapsedTime();
	//		if (m_fPassedBlendTime >= m_fBlendTime)
	//		{
	//			m_pAnimationController->SetTrackWeight(0, 1.0f);
	//			m_pAnimationController->SetTrackEnable(1, false);
	//		}
	//		else
	//		{
	//			float fWeight = m_fPassedBlendTime / m_fBlendTime;
	//			m_pAnimationController->SetTrackWeight(0, fWeight);
	//			m_pAnimationController->SetTrackWeight(1, 1.0f - fWeight);
	//		}
	//	}
	//	
	//	m_pAnimationController->AdvanceTime(
	//		g_pTimeManager->GetEllapsedTime(), NULL);
	//}


	// frame & mesh
	Update(m_pRoot, NULL);
	UpdateSkinnedMesh(m_pRoot);
	Update(g_pTimeManager->GetEllapsedTime());
}

void cSkinnedMesh::Update(float timeDelta)
{
	LPD3DXANIMATIONSET aaa;
	m_pAnimationController->GetTrackDesc(0, &m_Track_Desc_0);
	m_pAnimationController->GetTrackAnimationSet(0, &aaa);
	m_AnimationPlayFactor = m_Track_Desc_0.Position / aaa->GetPeriod();

	if (m_AnimationPlayFactor >= 0.9f)
	{
		if (this->m_bLoop == false) {

			if (this->m_pPrevPlayAnimationSet != NULL)
			{
				m_fCrossFadeTime = m_fOutCrossFadeTime;
				m_fLeftCrossFadeTime = m_fOutCrossFadeTime;
				m_bLoop = true;
				m_bCheck = true;
				SetAnimation(aaa);
				this->m_pPrevPlayAnimationSet = NULL;

			}
			else
			{
				m_bCheck = true;
				this->Stop();
			}
		}
	}
	m_AnimationPlayFactor = m_AnimationPlayFactor - (int)m_AnimationPlayFactor;


	if (m_bPlay)
	{
		m_pAnimationController->AdvanceTime(timeDelta, NULL);
	}

	if (m_fLeftCrossFadeTime > 0.0f)
	{
		this->m_fLeftCrossFadeTime -= timeDelta;

		if (m_fLeftCrossFadeTime <= 0.0f)
		{
			m_pAnimationController->SetTrackWeight(0, 1);
			m_pAnimationController->SetTrackEnable(1, false);
		}

		else
		{
			float w1 = (m_fLeftCrossFadeTime / m_fCrossFadeTime);
			float w0 = 1.0f - w1;


			m_pAnimationController->SetTrackWeight(0, w0);
			m_pAnimationController->SetTrackWeight(1, w1);
		}
	}


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
			if (m_Word)
			{
				g_pD3DDevice->SetTransform(D3DTS_WORLD,
					&(pBone->matCombinedTransformMatrix *(*m_Word)));
			}
			else
			{
				g_pD3DDevice->SetTransform(D3DTS_WORLD,
					&pBone->matCombinedTransformMatrix);
			}
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

void cSkinnedMesh::Play(std::string animName, float crossFadeTime)
{
	m_bPlay = true;
	m_bLoop = true;
	m_bCheck = false;

	MAP_ANIMSET::iterator find = this->m_mapAnimSet.find(animName);
	if (find != this->m_mapAnimSet.end()) {

		m_fCrossFadeTime = crossFadeTime;
		m_fLeftCrossFadeTime = crossFadeTime;

		this->SetAnimation(find->second);
	}
}

void cSkinnedMesh::Play(int animIndex, float crossFadeTime)
{
	m_bPlay = true;
	m_bLoop = true;

	if (animIndex < this->m_AnimNum) {

		m_fCrossFadeTime = crossFadeTime;
		m_fLeftCrossFadeTime = crossFadeTime;

		this->SetAnimation(m_vecAnimSet[animIndex]);
	}
}

void cSkinnedMesh::Play(LPD3DXANIMATIONSET animSet, float crossFadeTime)
{
	m_bPlay = true;
	m_bLoop = true;

	m_fCrossFadeTime = crossFadeTime;
	m_fLeftCrossFadeTime = crossFadeTime;


	this->SetAnimation(animSet);
}

void cSkinnedMesh::PlayOneShot(std::string animName, float inCrossFadeTime, float outCrossFadeTime)
{
	m_bPlay = true;
	m_bLoop = false;
	m_bCheck = false;
	MAP_ANIMSET::iterator find = this->m_mapAnimSet.find(animName);
	if (find != this->m_mapAnimSet.end()) {

		this->m_pPrevPlayAnimationSet = this->m_pNowPlayAnimationSet;

		m_fCrossFadeTime = inCrossFadeTime;
		m_fLeftCrossFadeTime = inCrossFadeTime;

		m_fOutCrossFadeTime = outCrossFadeTime;

		this->SetAnimation(find->second);
	}
}

void cSkinnedMesh::PlayOneShotAfterHold(std::string animName, float crossFadeTime)
{
	m_bPlay = true;
	m_bLoop = false;
	m_bCheck = false;

	MAP_ANIMSET::iterator find = this->m_mapAnimSet.find(animName);
	if (find != this->m_mapAnimSet.end()) {

		this->m_pPrevPlayAnimationSet = NULL;

		m_fCrossFadeTime = crossFadeTime;
		m_fLeftCrossFadeTime = crossFadeTime;

		this->SetAnimation(find->second);
	}
}

void cSkinnedMesh::SetAnimation(LPD3DXANIMATIONSET animSet)
{
	if (this->m_pNowPlayAnimationSet != NULL &&
		animSet == this->m_pNowPlayAnimationSet)
		return;
	//m_pAnimationController->GetTrackDesc(0, &m_Track_Desc_0);
	if (this->m_fCrossFadeTime > 0.0f)
	{
		m_pAnimationController->SetTrackAnimationSet(1, m_pNowPlayAnimationSet);
		m_pAnimationController->SetTrackPosition(1, m_Track_Desc_0.Position);
		m_pAnimationController->SetTrackEnable(1, true);
		m_pAnimationController->SetTrackWeight(1, 1.0f);



		m_pNowPlayAnimationSet = animSet;
		m_pAnimationController->SetTrackAnimationSet(0, animSet);
		D3DXTRACK_DESC stTrackDesc;
		m_pAnimationController->GetTrackDesc(0, &stTrackDesc);
		m_pAnimationController->SetTrackPosition(0, 0.0f);
		m_pAnimationController->SetTrackWeight(0, 0.0f);
		m_pAnimationController->SetTrackSpeed(0, stTrackDesc.Speed);

	}
	else
	{
		this->m_pAnimationController->SetTrackPosition(
			0,
			0.0
		);

		this->m_pAnimationController->SetTrackAnimationSet(0, animSet);
		this->m_pNowPlayAnimationSet = animSet;
	}
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

void cSkinnedMesh::SetAnimationIndex(int nIndex)
{
	int nMax = m_pAnimationController->GetNumAnimationSets();
	if (nIndex > nMax)	nIndex = nIndex % nMax;

	LPD3DXANIMATIONSET	pAnimSet = NULL;
	m_pAnimationController->GetAnimationSet(nIndex, &pAnimSet);
	m_pAnimationController->SetTrackAnimationSet(0, pAnimSet);

	SAFE_RELEASE(pAnimSet);
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

ST_BONE * cSkinnedMesh::GetFindBONE(std::string boneName)
{
	return (ST_BONE*)D3DXFrameFind(m_pRoot, boneName.c_str());
}

cSkinnedMesh * cSkinnedMesh::GetFindSkinedMesh(std::string boneName)
{
	return (cSkinnedMesh*)D3DXFrameFind(m_pRoot, boneName.c_str());
}

void cSkinnedMesh::updateSetting(LPD3DXFRAME pFrame, D3DXMATRIXA16 * m_Word)
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
