#pragma once
class cSkinnedMesh
{
protected:
	SYNTHESIZE(LPD3DXFRAME, m_pRoot, Root);
	SYNTHESIZE(LPD3DXANIMATIONCONTROLLER, m_pAnimationController, AnimationController);

	float		m_fPassedBlendTime;
	float		m_fBlendTime;
	bool		m_isBlend;
	UINT							m_AnimNum;
	typedef std::map< std::string, LPD3DXANIMATIONSET >			MAP_ANIMSET;
	typedef std::vector< LPD3DXANIMATIONSET >					VEC_ANIMSET;
	SYNTHESIZE(MAP_ANIMSET, m_mapAnimSet, mapAnimSet);
	VEC_ANIMSET						m_vecAnimSet;
	LPD3DXANIMATIONSET				m_pNowPlayAnimationSet;		// Current Animation set
	D3DXTRACK_DESC					m_Track_Desc_0;				// Current Track
																//bool							m_bPlay;		
	SYNTHESIZE(bool, m_bPlay, Play);
	//bool							m_bLoop;	
	SYNTHESIZE(bool, m_bLoop, Loop);
	SYNTHESIZE(LPD3DXANIMATIONSET, m_pPrevPlayAnimationSet, PrevPlayAnimationSet);	// Standard Animation set or Prev Animation set
	float							m_fCrossFadeTime;
	float							m_fLeftCrossFadeTime;
	float							m_fOutCrossFadeTime;
	double							m_AnimationPlayFactor;		// Current Animation Frame Time
	float							m_fAnimDelta;				// Ellapsed Time
	SYNTHESIZE(bool, m_bCheck, Check);

	SYNTHESIZE(D3DXVECTOR3, m_vMin, Min);
	SYNTHESIZE(D3DXVECTOR3, m_vMax, Max);

private:
	//거미
	float	fx, fy, fz;
	int		m_changeTime;
	bool	bi;

	//움직여보자
	SYNTHESIZE(float, m_fRotY, fRotY);
	SYNTHESIZE(D3DXVECTOR3, m_vPos, Position);
	SYNTHESIZE(D3DXVECTOR3, m_vDir, Direction);
	SYNTHESIZE(D3DXVECTOR3, m_vPlayerPos, PlayerPos);

	SYNTHESIZE_REF(D3DXMATRIXA16, m_wrold, wrold);

public:
	cSkinnedMesh();
	~cSkinnedMesh();

	void Setup(IN char* szFolder, IN char* szFile);

	void Update();
	void Update(float timeDelta);
	void Update(LPD3DXFRAME pFrame, LPD3DXFRAME pParent);
	void Render(LPD3DXFRAME pFrame, D3DXMATRIXA16* m_Word);

	void Play(std::string animName, float crossFadeTime = 0.0); //Play Key
	void Play(int animIndex, float crossFadeTime = 0.0);		//Play Index
	void Play(LPD3DXANIMATIONSET animSet, float crossFadeTime = 0.0);	//Play Animation Set
	void PlayOneShot(std::string animName, float inCrossFadeTime = 0.0, float outCrossFadeTime = 0.0f); //Play Once and Return 
	void PlayOneShotAfterHold(std::string animName, float crossFadeTime = 0.0);	//Play Once and Saty 
	void Stop() {
		this->m_bPlay = false;
	}

	void SetAnimation(LPD3DXANIMATIONSET animSet);


	void SetupBoneMatrixPtrs(LPD3DXFRAME pFrame);
	void UpdateSkinnedMesh(LPD3DXFRAME pFrame);

	// animation
	void SetAnimationIndex(int nIndex);
	void SetAnimationIndexBlend(int nIndex);

	ST_BONE* GetFindBONE(std::string boneName);
	cSkinnedMesh* GetFindSkinedMesh(std::string boneName);
	void updateSetting(LPD3DXFRAME pFrame, D3DXMATRIXA16* m_Word);

	void addMonsterPos(D3DXMATRIXA16* m_Word, float x, float y, float z, float size);

	//animation speed
	void setAnimationSpeed(float fSpeed);
};

