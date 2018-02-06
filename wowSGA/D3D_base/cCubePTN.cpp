#include "stdafx.h"
#include "cCubePTN.h"


cCubePTN::cCubePTN()
{
}


cCubePTN::~cCubePTN()
{
}

void cCubePTN::Setup()
{
	std::vector<ST_PTN_VERTEX>	vecVertex;
	vecVertex.resize(8);

	vecVertex[0].p = D3DXVECTOR3(-0.5f, -0.5f, -0.5f);
	vecVertex[1].p = D3DXVECTOR3(-0.5f,  0.5f, -0.5f);
	vecVertex[2].p = D3DXVECTOR3( 0.5f,  0.5f, -0.5f);
	vecVertex[3].p = D3DXVECTOR3( 0.5f, -0.5f, -0.5f);

	vecVertex[4].p = D3DXVECTOR3(-0.5f, -0.5f,  0.5f);
	vecVertex[5].p = D3DXVECTOR3(-0.5f,  0.5f,  0.5f);
	vecVertex[6].p = D3DXVECTOR3( 0.5f,  0.5f,  0.5f);
	vecVertex[7].p = D3DXVECTOR3( 0.5f, -0.5f,  0.5f);

	std::vector<DWORD> vecIndex;

	vecIndex.push_back(0);
	vecIndex.push_back(1);
	vecIndex.push_back(2);

	vecIndex.push_back(0);
	vecIndex.push_back(2);
	vecIndex.push_back(3);

	vecIndex.push_back(4);
	vecIndex.push_back(6);
	vecIndex.push_back(5);

	vecIndex.push_back(4);
	vecIndex.push_back(7);
	vecIndex.push_back(6);

	vecIndex.push_back(4);
	vecIndex.push_back(5);
	vecIndex.push_back(1);

	vecIndex.push_back(4);
	vecIndex.push_back(1);
	vecIndex.push_back(0);

	vecIndex.push_back(3);
	vecIndex.push_back(2);
	vecIndex.push_back(6);

	vecIndex.push_back(3);
	vecIndex.push_back(6);
	vecIndex.push_back(7);

	vecIndex.push_back(1);
	vecIndex.push_back(5);
	vecIndex.push_back(6);

	vecIndex.push_back(1);
	vecIndex.push_back(6);
	vecIndex.push_back(2);

	vecIndex.push_back(4);
	vecIndex.push_back(0);
	vecIndex.push_back(3);

	vecIndex.push_back(4);
	vecIndex.push_back(3);
	vecIndex.push_back(7);

	m_vecVertex.resize(36);
	for (size_t i = 0; i < vecIndex.size(); i+=3)
	{
		m_vecVertex[i] = vecVertex[vecIndex[i]];
		m_vecVertex[i + 1] = vecVertex[vecIndex[i + 1]];
		m_vecVertex[i + 2] = vecVertex[vecIndex[i + 2]];
	}

	D3DXVECTOR3	v1, v2, n;
	for (size_t i = 0; i < m_vecVertex.size(); i += 3)
	{
		v1 = m_vecVertex[i + 1].p - m_vecVertex[i].p;
		v2 = m_vecVertex[i + 2].p - m_vecVertex[i].p;

		D3DXVec3Cross(&n, &v1, &v2);
		D3DXVec3Normalize(&n, &n);

		m_vecVertex[i].n = n;
		m_vecVertex[i + 1].n = n;
		m_vecVertex[i + 2].n = n;
	}
}

void cCubePTN::Render()
{
	//g_pD3DDevice->SetTexture(0, NULL);
	g_pD3DDevice->SetFVF(ST_PTN_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		m_vecVertex.size() / 3,
		&m_vecVertex[0],
		sizeof(ST_PTN_VERTEX));
}

void cCubePTN::Update()
{
}
