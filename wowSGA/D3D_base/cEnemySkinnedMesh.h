#pragma once

class cEnemySkinnedMesh
{
protected:
	LPD3DXFRAME		m_pRoot;
	LPD3DXANIMATIONSET m_pNowPlayAnimationSet;
	float		m_fPassedBlendTime;
	float		m_fBlendTime;
	bool		m_isBlend;
	std::vector<LPD3DXANIMATIONSET> m_vecAnimSet;

	//거미
	float fx, fy, fz;
	int m_changeTime;
	bool	bi;

	//움직여보자
	SYNTHESIZE(float, m_fRotY, fRotY);
	SYNTHESIZE(D3DXVECTOR3, m_vPos, Position);
	SYNTHESIZE(D3DXVECTOR3, m_vDir, Direction);
	SYNTHESIZE(D3DXVECTOR3, m_vPlayerPos, PlayerPos);

	SYNTHESIZE_REF(D3DXMATRIXA16, m_wrold, wrold);
	SYNTHESIZE(LPD3DXANIMATIONCONTROLLER, m_pAnimationController, AnimationController);

	SYNTHESIZE(bool, m_fPlay, Play);
	SYNTHESIZE(bool, m_fLoop, Loop);
	SYNTHESIZE(int, m_baseAniNUM, baseAniNUM);
public:
	cEnemySkinnedMesh();
	~cEnemySkinnedMesh();

	void Setup(IN char* szFolder, IN char* szFile);
	void Update();
	void Update(LPD3DXFRAME pFrame, LPD3DXFRAME pParent);
	void Update_time(float time);
	void Render(LPD3DXFRAME pFrame, D3DXMATRIXA16* m_Word);
	void ani_Play(int index);

	void GetMatRFromDir(D3DXMATRIXA16& matR, D3DXVECTOR3& vNext);

	void SetupBoneMatrixPtrs(LPD3DXFRAME pFrame);
	void UpdateSkinnedMesh(LPD3DXFRAME pFrame);

	void addMonsterPos(D3DXMATRIXA16* m_Word, float x, float y, float z, float size);
	// animation
	void SetAnimationIndex(int nIndex);
	void SetAnimationIndexBlend(int nIndex);
};
