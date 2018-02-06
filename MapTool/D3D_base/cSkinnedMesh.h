#pragma once


class cSkinnedMesh
{
protected:

	SYNTHESIZE(LPD3DXFRAME, m_pRoot, Root);
	LPD3DXANIMATIONCONTROLLER	m_pAnimationController;
	LPD3DXANIMATIONSET m_pNowPlayAnimationSet;
	float		m_fPassedBlendTime;
	float		m_fBlendTime;
	bool		m_isBlend;
	std::vector<LPD3DXANIMATIONSET> m_vecAnimSet;

	SYNTHESIZE(bool, m_fPlay, Play);
	SYNTHESIZE(bool, m_fLoop, Loop);
	SYNTHESIZE(int, m_baseAniNUM, baseAniNUM);
public:
	cSkinnedMesh();
	~cSkinnedMesh();

	void Setup(IN char* szFolder, IN char* szFile);
	void Update();
	void Update(LPD3DXFRAME pFrame, LPD3DXFRAME pParent);
	void Update_time(float time);
	void Render(LPD3DXFRAME pFrame, D3DXMATRIXA16* m_Word);
	void ani_Play(int index);
	void ani_Play(char* name);

	void SetupBoneMatrixPtrs(LPD3DXFRAME pFrame);
	void UpdateSkinnedMesh(LPD3DXFRAME pFrame);

	// animation
	void SetAnimationIndexBlend(int nIndex);
	void SetAnimationIndexBlend(char* name);
	void updateSetting(LPD3DXFRAME pFrame, D3DXMATRIXA16* m_Word);

	ST_BONE* GetFindBONE(std::string boneName);
};

