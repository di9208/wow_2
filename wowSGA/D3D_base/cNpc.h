#pragma once
#include "cCharacter.h"
#include "cUnit.h"

class cNpc_AniController;
class cNpcInfo;

class cNpc //: public cCharacter
{
private:
	cNpc_AniController * m_npcAnicontroller;
	cNpcInfo* m_npc_info;
	NPC_State	Npc_State;
	D3DXMATRIXA16 m_matWorld;

	D3DXVECTOR3		m_playerPos;

	SYNTHESIZE(ST_SPHERE, PmeshInfo, M_info);
	LPD3DXMESH m_mesh;
	SYNTHESIZE(bool, ispickinged, RAYPICK);
public:
	cNpc();
	~cNpc();

	void Setup();
	void update();
	void render();

	void setPlayerPos(D3DXVECTOR3 playerpos) { m_playerPos = playerpos; }
};

