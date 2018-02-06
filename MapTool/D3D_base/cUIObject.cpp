#include "stdafx.h"
#include "cUIObject.h"


cUIObject::cUIObject()
	: m_pParent(NULL)
	, m_stSize(0, 0)
	, m_vPos(0, 0, 0)
	, m_Scale(1, 1, 1)
	, m_isHidden(false)
{
	D3DXMatrixIdentity(&m_matWorld);
}


cUIObject::~cUIObject()
{
}

void cUIObject::AddChild(cUIObject * pChild)
{
	m_vecChild.push_back(pChild);
	pChild->SetParent(this);
}

void cUIObject::Destroy()
{
	for each (auto child in m_vecChild)
	{
		child->Destroy();
	}
	this->Release();
}

void cUIObject::Update()
{
	if (m_isHidden)	return;

	D3DXMatrixIdentity(&m_matWorld);
	m_matWorld._11 = m_Scale.x;
	m_matWorld._22 = m_Scale.y;
	m_matWorld._41 = m_vPos.x;
	m_matWorld._42 = m_vPos.y;
	m_matWorld._43 = m_vPos.z;

	if (m_pParent)
	{
		m_matWorld._11 *= m_pParent->m_matWorld._11;
		m_matWorld._22 *= m_pParent->m_matWorld._22;
		m_matWorld._41 += m_pParent->m_matWorld._41;
		m_matWorld._42 += m_pParent->m_matWorld._42;
		m_matWorld._43 += m_pParent->m_matWorld._43;
	}

	for each (auto child in m_vecChild)
	{
		child->Update();
	}
}

void cUIObject::Render(LPD3DXSPRITE pSprite)
{
	if (m_isHidden)	return;

	for each (auto child in m_vecChild)
	{
		child->Render(pSprite);
	}
}
