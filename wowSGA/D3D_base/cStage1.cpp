#include "stdafx.h"
#include "cStage1.h"
#include "cQuadTree.h"

cStage1::cStage1()
	: m_pTexture(NULL)
{
}


cStage1::~cStage1()
{
	SAFE_RELEASE(m_vb);
	SAFE_RELEASE(m_ib);
	SAFE_DELETE(m_QuadTree);
	SAFE_RELEASE(m_pTexture);
}

void cStage1::Setup()
{
	SetMap();
	m_QuadTree = new cQuadTree(m_col, m_row);
	SetQuad();
}

void cStage1::SetMap()
{
	int size;
	FILE * fp;
	fp = fopen("Stage1.txt", "r");
	m_pTexture = g_pTextureManager->GetTexture("HeightMapData/selectblend.png");

	fscanf(fp, "%d", &size);

	m_col = (int)sqrtf(size);
	m_row = (int)sqrtf(size);

	MapVertex = new ST_PTN_VERTEX[size];
	for (int i = 0; i < size; i++)
	{
		D3DXVECTOR3 v;
		fscanf(fp, "%f %f %f\n", &v.x, &v.y, &v.z);
		MapVertex[i].p = v;
	}
	for (int i = 0; i < size; i++)
	{
		D3DXVECTOR3 v;
		fscanf(fp, "%f %f %f\n", &v.x, &v.y, &v.z);
		MapVertex[i].n = v;
	}
	for (int i = 0; i < size; i++)
	{
		D3DXVECTOR2 v;
		fscanf(fp, "%f %f\n", &v.x, &v.y);
		MapVertex[i].t = v;
	}
	fclose(fp);

	
	g_pD3DDevice->CreateVertexBuffer(size * sizeof(ST_PTN_VERTEX), 0, ST_PTN_VERTEX::FVF, D3DPOOL_DEFAULT, &m_vb, nullptr);
	g_pD3DDevice->CreateIndexBuffer((m_col - 1)* (m_row - 1) * 2 * sizeof(ST_INDEX), 0, D3DFMT_INDEX32, D3DPOOL_DEFAULT, &m_ib, 0);

	void* vp;
	m_vb->Lock(0, size * sizeof(ST_PTN_VERTEX), &vp, 0);
	memcpy(vp, MapVertex, size * sizeof(ST_PTN_VERTEX));
	m_vb->Unlock();

}

void cStage1::SetQuad()
{
	m_QuadTree->Add(MapVertex);
}

void cStage1::SetMaterial()
{
	D3DMATERIAL9 mt;
	ZeroMemory(&mt, sizeof(D3DMATERIAL9));
	mt.Ambient = mt.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_pD3DDevice->SetMaterial(&mt);

}

void cStage1::Draw(cFrustum * f)
{
	LPDWORD pi;

	m_ib->Lock(0, (m_col - 1)* (m_row - 1) * 2 * sizeof(ST_INDEX), (void**)&pi, 0);
	m_Polygon = m_QuadTree->GenerateIndex(pi, MapVertex, f);
	m_vecindex.resize(m_Polygon * 3);
	for (int i = 0; i < m_Polygon * 3; i++)
	{
		m_vecindex[i] = pi[i];
	}
	m_ib->Unlock();

	Render();
}

void cStage1::Render()
{
	D3DXMATRIXA16 WOLRD;
	SetMaterial();
	D3DXMatrixIdentity(&WOLRD);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &WOLRD);
	g_pD3DDevice->SetFVF(ST_PTN_VERTEX::FVF);
	g_pD3DDevice->SetStreamSource(0, m_vb, 0, sizeof(ST_PTN_VERTEX));
	g_pD3DDevice->SetIndices(m_ib);
	g_pD3DDevice->SetTexture(0, m_pTexture);
	g_pD3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, (m_col*m_row), 0, m_Polygon);

}

bool cStage1::GetHeight(IN float x, OUT float& y, IN float z)
{
	if (x < -(m_col - 1) / 2 || z < -(m_col - 1) / 2
		|| x >= (m_col - 1) / 2 || z >= (m_col - 1) / 2)
	{
		return false;
	}
	int a = (m_col - 1) / 2;

	int nX = x;
	int nZ = z;
	if (x < 0)
		nX = x - 1.0f;
	if (z < 0)
		nZ = z - 1.0f;

	float fDeltaX = x - nX;
	float fDeltaZ = z - nZ;



	int _0 = (nZ + a + 0) * (m_col)+(nX + a + 0);
	int _1 = (nZ + a + 1) * (m_col)+(nX + a + 0);
	int _2 = (nZ + a + 1) * (m_col)+(nX + a + 1);
	int _3 = (nZ + a + 0) * (m_col)+(nX + a + 1);

	//_1.._3
	//.
	//.
	//_0.._2

	// ¾Æ·¡ »ï°¢Çü
	if (fDeltaX> fDeltaZ)
	{
		fDeltaX = 1.0f - fDeltaX;
		D3DXVECTOR3 v01 = MapVertex[_2].p - MapVertex[_3].p;
		D3DXVECTOR3 v02 = MapVertex[_0].p - MapVertex[_3].p;
		y = (v01 * fDeltaZ + v02 * fDeltaX).y + MapVertex[_3].p.y;
		return true;
	}
	// À§ »ï°¢Çü
	else
	{
		fDeltaZ = 1.0f - fDeltaZ;
		D3DXVECTOR3 v31 = MapVertex[_2].p - MapVertex[_1].p;
		D3DXVECTOR3 v32 = MapVertex[_0].p - MapVertex[_1].p;
		y = (v31 * fDeltaX + v32 * fDeltaZ).y + MapVertex[_1].p.y;
		return true;
	}

	return false;
}
