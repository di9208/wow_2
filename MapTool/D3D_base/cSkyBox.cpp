#include "stdafx.h"
#include "cSkyBox.h"


cSkyBox::cSkyBox()
{
}


cSkyBox::~cSkyBox()
{
	for(int i=0; i<6; i++)
	SAFE_RELEASE(m_skytex[i])
}

void cSkyBox::Setup()
{
	cCubePTN::Setup();

	m_skytex[0] = g_pTextureManager->GetTexture("Map/front.png");
	m_skytex[1] = g_pTextureManager->GetTexture("Map/back.png");
	m_skytex[2] = g_pTextureManager->GetTexture("Map/left.png");
	m_skytex[3] = g_pTextureManager->GetTexture("Map/right.png");
	m_skytex[4] = g_pTextureManager->GetTexture("Map/top.png");
	m_skytex[5] = g_pTextureManager->GetTexture("Map/bottom.png");

	SetTexture();

	g_pD3DDevice->CreateVertexBuffer(m_vecVertex.size() * sizeof(ST_PTN_VERTEX), 0, ST_PTN_VERTEX::FVF, D3DPOOL_MANAGED, &m_vb, nullptr);

	void * v;
	m_vb->Lock(0, 0, (void**)&v, 0);

	memcpy(v, &m_vecVertex[0],
		m_vecVertex.size() * sizeof(ST_PTN_VERTEX));
	m_vb->Unlock();
}

void cSkyBox::SetTexture()
{
	//front
	m_vecVertex[0].t = D3DXVECTOR2(1, 1);
	m_vecVertex[1].t = D3DXVECTOR2(1, 0);
	m_vecVertex[2].t = D3DXVECTOR2(0, 0);
	m_vecVertex[3].t = D3DXVECTOR2(1, 1);
	m_vecVertex[4].t = D3DXVECTOR2(0, 0);
	m_vecVertex[5].t = D3DXVECTOR2(0, 1);

	//back
	m_vecVertex[6].t = D3DXVECTOR2(0, 1);
	m_vecVertex[7].t = D3DXVECTOR2(1, 0);
	m_vecVertex[8].t = D3DXVECTOR2(0, 0);
	m_vecVertex[9].t = D3DXVECTOR2(0, 1);
	m_vecVertex[10].t = D3DXVECTOR2(1, 1);
	m_vecVertex[11].t = D3DXVECTOR2(1, 0);

	//left
	m_vecVertex[12].t = D3DXVECTOR2(1, 1);
	m_vecVertex[13].t = D3DXVECTOR2(1, 0);
	m_vecVertex[14].t = D3DXVECTOR2(0, 0);
	m_vecVertex[15].t = D3DXVECTOR2(1, 1);
	m_vecVertex[16].t = D3DXVECTOR2(0, 0);
	m_vecVertex[17].t = D3DXVECTOR2(0, 1);

	//right
	m_vecVertex[18].t = D3DXVECTOR2(1, 1);
	m_vecVertex[19].t = D3DXVECTOR2(1, 0);
	m_vecVertex[20].t = D3DXVECTOR2(0, 0);
	m_vecVertex[21].t = D3DXVECTOR2(1, 1);
	m_vecVertex[22].t = D3DXVECTOR2(0, 0);
	m_vecVertex[23].t = D3DXVECTOR2(0, 1);

	//top
	m_vecVertex[24].t = D3DXVECTOR2(0, 0);
	m_vecVertex[25].t = D3DXVECTOR2(0, 1);
	m_vecVertex[26].t = D3DXVECTOR2(1, 1);
	m_vecVertex[27].t = D3DXVECTOR2(0, 0);
	m_vecVertex[28].t = D3DXVECTOR2(1, 1);
	m_vecVertex[29].t = D3DXVECTOR2(1, 0);

	//bottom
	m_vecVertex[30].t = D3DXVECTOR2(0, 0);
	m_vecVertex[31].t = D3DXVECTOR2(0, 1);
	m_vecVertex[32].t = D3DXVECTOR2(1, 1);
	m_vecVertex[33].t = D3DXVECTOR2(0, 0);
	m_vecVertex[34].t = D3DXVECTOR2(1, 1);
	m_vecVertex[35].t = D3DXVECTOR2(1, 0);

}

void cSkyBox::Render(D3DXVECTOR3 camera)
{

	D3DXMATRIXA16 matW, matS;
	D3DXVECTOR3 a;

	D3DXMatrixTranslation(&matW, camera.x, camera.y, camera.z);
	D3DXMatrixScaling(&matS, 200, 200, 200);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &(matS*matW));
	g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, false);
	g_pD3DDevice->SetFVF(ST_PTN_VERTEX::FVF);
	g_pD3DDevice->SetStreamSource(0, m_vb, 0, sizeof(ST_PTN_VERTEX));
	
	for (int i = 0; i < m_vecVertex.size() / 6; i++)
	{
		g_pD3DDevice->SetTexture(0, m_skytex[i]);
		g_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, i * 6, 2);
	}
	//cCubePTN::Render();
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, true);

}
