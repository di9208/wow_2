#pragma once
#include "cUnit.h"
class cSkinnedMesh;

class cNpc_AniController
{

private:
	SYNTHESIZE(NPC_State, cNpc_State, State);
	SYNTHESIZE(cSkinnedMesh*, m_NPC_SkinnedMesh, NPC_SkinnedMesh);
	SYNTHESIZE_REF(D3DXMATRIXA16, m_world, world);

public:
	cNpc_AniController();
	~cNpc_AniController();

	void Setup();
	void Update(NPC_State* Nstate);
	void Render(D3DXMATRIXA16* Update_world);

	void SetAnimation(NPC_State* Nstate);
	void SetAnimationRotationSize(LPD3DXFRAME nFrame, LPD3DXFRAME nParent);

	ST_BONE* GetFindBONE(std::string boneName);
	cSkinnedMesh* GetFindSkinedMesh(std::string boneName);
	bool GetAniCheck() { return m_NPC_SkinnedMesh->GetCheck(); }

};

