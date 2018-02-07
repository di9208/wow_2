#include "stdafx.h"
#include "cArthasOBB.h"
#include "cOBB.h"

cArthasOBB::cArthasOBB()
	: m_arthasOBB(NULL)
{
}

cArthasOBB::~cArthasOBB()
{
	SAFE_DELETE(m_arthasOBB);
}

void cArthasOBB::Setup(cSkinnedMesh * bskinned, D3DXMATRIXA16 * bWorld)
{
	m_arthasOBB = new cOBB();
	m_arthasOBB->Setup(bskinned, bWorld);
}

void cArthasOBB::Update(D3DXMATRIXA16 * pMatWorld)
{
	if (m_arthasOBB)
		m_arthasOBB->Update(pMatWorld);
}

void cArthasOBB::Render(D3DXMATRIXA16 * bWorld, D3DXMATRIXA16 * pMatWorld)
{
	D3DCOLOR c = D3DCOLOR_XRGB(0, 255, 255);
	if (m_arthasOBB)
		m_arthasOBB->Render_Debug(c, bWorld, pMatWorld);

}

void cArthasOBB::Collision(cOBB * box)
{
	if (box)
	{
		if (box->getCheck(0).x != 431602080 && m_arthasOBB->getCheck(0).x != -431602080)
		{
			if (m_arthasOBB->IsCollision(m_arthasOBB, box))
			{

			}
			else
			{

			}
		}
	}
}
