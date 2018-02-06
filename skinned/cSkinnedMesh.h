#pragma once
class cSkinnedMesh
{
protected:
	LPD3DXFRAME		m_pRoot;
	LPD3DXANIMATIONCONTROLLER m_pAnimController;
	UINT m_AnimNum;

	std::vector<LPD3DXANIMATIONSET> m_vecAnimSet;


	bool							m_bPlay;					
	bool							m_bLoop;					
	LPD3DXANIMATIONSET				m_pPrevPlayAnimationSet;	

	float							m_fCrossFadeTime;			
	float							m_fLeftCrossFadeTime;		
	float							m_fOutCrossFadeTime;
	double							m_AnimationPlayFactor;
	LPD3DXANIMATIONSET				m_pNowPlayAnimationSet;

	D3DXTRACK_DESC					m_Track_Desc_0;
public:
	cSkinnedMesh();
	~cSkinnedMesh();

	void Setup(IN char* szFolder, IN char* szFile);
	void Update();
	void Update(LPD3DXFRAME pFrame, LPD3DXFRAME pParent);
	void Update(float time);

	void Render(LPD3DXFRAME pFrame);


	void Play(int animIndex, float crossFadeTime = 0.0);
	void Stop() {
		this->m_bPlay = false;
	}

	UINT GetAnimationNums();

	void SetPlaySpeed(float speed);
	void SetAnimation(LPD3DXANIMATIONSET animSet);

	void SetupBoneMatrixPtrs(LPD3DXFRAME pFrame);
	void UpdateSkinnedMesh(LPD3DXFRAME pFrame);
};

