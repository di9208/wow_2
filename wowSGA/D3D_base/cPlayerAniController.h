#pragma once
#include "cUnit.h"
class cSkinnedMesh;

class cPlayerAniController
{
	//cSkinnedMesh*		m_pSkinnedMesh;
	//condition			cPlayer_condition;
	SYNTHESIZE(condition, cPlayer_condition, condition);
	SYNTHESIZE(cSkinnedMesh*, m_pSkinnedMesh, SkinnedMesh);
	SYNTHESIZE_REF(D3DXMATRIXA16, m_World, World);
public:
	cPlayerAniController();
	~cPlayerAniController();

	void Setup();
	void Update(condition* pCondition);
	void Render(D3DXMATRIXA16* m_wolrd);

	void SetAnimation(condition* pCondition);
	void SetAnimationRotationSize(LPD3DXFRAME pFrame, LPD3DXFRAME pParent);

	ST_BONE* GetFindBONE(std::string boneName);
	cSkinnedMesh* GetFindSkinedMesh(std::string boneName);
	bool	GetAniCheck() { return m_pSkinnedMesh->GetCheck(); }
};

