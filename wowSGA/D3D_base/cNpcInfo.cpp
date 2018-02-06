#include "stdafx.h"
#include "cNpcInfo.h"


cNpcInfo::cNpcInfo()
	:m_ptexture(NULL)
	, m_psprite(NULL)
{
}


cNpcInfo::~cNpcInfo()
{
	//SAFE_RELEASE(m_pfont);
	//SAFE_RELEASE(m_ptexture);
	//SAFE_RELEASE(m_psprite);
}

void cNpcInfo::setup()
{
	setfont();
	setUI();
	NpcInfo.LV = 99;
}

void cNpcInfo::update(NPC_State * npcstate)
{
}

void cNpcInfo::setfont()
{
}

void cNpcInfo::setUI()
{
}

void cNpcInfo::renderUI()
{
}

void cNpcInfo::renderfont()
{
}

void cNpcInfo::render()
{
}
