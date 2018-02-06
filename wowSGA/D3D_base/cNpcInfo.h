#pragma once

#include "cUnit.h"

class cNpcInfo
{
private:
	TagUnit	NpcInfo;
	LPD3DXFONT m_pfont;

	LPD3DXSPRITE m_psprite;
	D3DXIMAGE_INFO m_stImageinfo;
	LPDIRECT3DTEXTURE9 m_ptexture;

public:
	cNpcInfo();
	~cNpcInfo();

	void setup();
	void update(NPC_State* npcstate);
	
	void setfont();
	void setUI();
	void renderUI();
	void renderfont();
	void render();
};

