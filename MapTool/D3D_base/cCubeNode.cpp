#include "stdafx.h"
#include "cCubeNode.h"


cCubeNode::cCubeNode()
	: m_pParentWorldTM(NULL)
	, m_vLocalPos(0, 0, 0)
	, m_fRotX(0.0f)
	, m_fRotDeltaX(0.0f)
{
	D3DXMatrixIdentity(&m_matLocalTM);
	D3DXMatrixIdentity(&m_matWorldTM);
}


cCubeNode::~cCubeNode()
{
	int a = 0;
}

void cCubeNode::AddChild(cCubeNode* pChild)
{
	m_vecChild.push_back(pChild);
	pChild->m_pParentWorldTM = &m_matWorldTM;
}

void cCubeNode::Destroy()
{
	for each(auto child in m_vecChild)
	{
		child->Destroy();
	}
	delete this;
}

void cCubeNode::Setup()
{
	cCubePTN::Setup();
}

void cCubeNode::Update()
{
	cCubePTN::Update();

	// animation
	m_fRotX += m_fRotDeltaX;

	if (m_fRotX > D3DX_PI / 6.0f)
	{
		m_fRotX = D3DX_PI / 6.0f;
		m_fRotDeltaX *= -1;
	}

	if (m_fRotX < -D3DX_PI / 6.0f)
	{
		m_fRotX = -D3DX_PI / 6.0f;
		m_fRotDeltaX *= -1;
	}

	D3DXMATRIXA16	matR, matT;
	D3DXMatrixRotationX(&matR, m_fRotX);

	D3DXMatrixTranslation(&matT, m_vLocalPos.x, m_vLocalPos.y, m_vLocalPos.z);

	m_vDir = D3DXVECTOR3(0, 0, 1);
	D3DXVec3TransformNormal(&m_vDir, &m_vDir, &matR);

	m_matLocalTM = matR * matT;
	m_matWorldTM = m_matLocalTM;
	if (m_pParentWorldTM)
	{
		m_matWorldTM *= (*m_pParentWorldTM);
	}

	for each(auto child in m_vecChild)
	{
		child->Update();
	}
}

void cCubeNode::Render()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorldTM);
	cCubePTN::Render();

	for each (auto child in m_vecChild)
	{
		child->Render();
	}
}
