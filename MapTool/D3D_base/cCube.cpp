#include "stdafx.h"
#include "cCube.h"


cCube::cCube()
{
}


cCube::~cCube()
{
	int a = 0;
}

void cCube::Setup()
{
	ST_PT_VERTEX v;
	//v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	v.p = D3DXVECTOR3(-0.5f, -0.5f, -0.5f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-0.5f, 0.5f, -0.5f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(0.5f, 0.5f, -0.5f); m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-0.5f, -0.5f, -0.5f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(0.5f, 0.5f, -0.5f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(0.5f, -0.5f, -0.5f); m_vecVertex.push_back(v);

	//v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	v.p = D3DXVECTOR3(-0.5f, -0.5f, 0.5f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(0.5f, 0.5f, 0.5f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-0.5f, 0.5f, 0.5f); m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-0.5f, -0.5f, 0.5f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(0.5f, -0.5f, 0.5f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(0.5f, 0.5f, 0.5f); m_vecVertex.push_back(v);

	//v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	v.p = D3DXVECTOR3(-0.5f, -0.5f, 0.5f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-0.5f, 0.5f, 0.5f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-0.5f, 0.5f, -0.5f); m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-0.5f, -0.5f, 0.5f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-0.5f, 0.5f, -0.5f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-0.5f, -0.5f, -0.5f); m_vecVertex.push_back(v);

	//v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	v.p = D3DXVECTOR3(0.5f, -0.5f, -0.5f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(0.5f, 0.5f, -0.5f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(0.5f, 0.5f, 0.5f); m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(0.5f, -0.5f, -0.5f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(0.5f, 0.5f, 0.5f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(0.5f, -0.5f, 0.5f); m_vecVertex.push_back(v);

	//v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	v.p = D3DXVECTOR3(-0.5f, 0.5f, -0.5f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-0.5f, 0.5f, 0.5f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(0.5f, 0.5f, 0.5f); m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-0.5f, 0.5f, -0.5f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(0.5f, 0.5f, 0.5f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(0.5f, 0.5f, -0.5f); m_vecVertex.push_back(v);

	//v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	v.p = D3DXVECTOR3(-0.5f, -0.5f, 0.5f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-0.5f, -0.5f, -0.5f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(0.5f, -0.5f, -0.5f); m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-0.5f, -0.5f, 0.5f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(0.5f, -0.5f, -0.5f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(0.5f, -0.5f, 0.5f); m_vecVertex.push_back(v);
}

void cCube::Update()
{
}

void cCube::Render()
{
	//g_pD3DDevice->SetTexture(0, NULL);
	g_pD3DDevice->SetFVF(ST_PT_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		m_vecVertex.size() / 3,
		&m_vecVertex[0],
		sizeof(ST_PT_VERTEX));
}
