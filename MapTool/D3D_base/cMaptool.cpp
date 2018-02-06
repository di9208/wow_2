#include "stdafx.h"
#include "cMaptool.h"
#include "cUIButton.h"
#include "cQuadTree.h"
#include "cMapTool_UI.h"

cMaptool::cMaptool()
	:Heightmap(nullptr)
	, m_radius(1.0f)
	, m_QuadTree(nullptr)
	,_col(129)
	,_row(129)
{
}


cMaptool::~cMaptool()
{
	
	Heightmap->Destroy();
	SAFE_DELETE(m_QuadTree);
	SAFE_RELEASE(m_tex);
	SAFE_RELEASE(m_vb);
	SAFE_RELEASE(m_ib);
	SAFE_DELETE(m_UI);
}

void cMaptool::Setup()
{
	
	cUIButton* b = new cUIButton;
	b->SetTexture("UI/grid.png", "UI/grid.png", "UI/grid.png");
	b->SetTag(1);
	Heightmap = b;
	m_QuadTree = new cQuadTree(_col, _row);
	m_UI = new cMapTool_UI;
	m_UI->Setup();
	Setupmap();
	SetupQuad();
	SetupCircle();
	SetupControl();
	SetMaterial();
}

void cMaptool::Setupmap()
{

	ST_PTN_VERTEX v;
	Mapvertex = new ST_PTN_VERTEX[_col*_row];
	
	for (int i = 0; i < _col*_row; i++)
		{
			v.p = D3DXVECTOR3(-(_col-1)/2.0f + i % _col, 0, -(_col-1)/2.0f + i / _col);
			v.n = D3DXVECTOR3(0, 1, 0);
			v.t = D3DXVECTOR2((i%_col)/(float)_col, (i / _row) / (float)_row);
			Mapvertex[i] = v;
		}
	
	m_tex = g_pTextureManager->GetTexture("Map/selectblend.png");

	g_pD3DDevice->CreateVertexBuffer(_col*_row * sizeof(ST_PTN_VERTEX), 0, ST_PTN_VERTEX::FVF, D3DPOOL_DEFAULT, &m_vb, 0);
	
	void* vp;
	m_vb->Lock(0, _col*_row*sizeof(ST_PTN_VERTEX), (void**)&vp, 0);
	memcpy(vp, Mapvertex,
		_col*_row * sizeof(ST_PTN_VERTEX));
	m_vb->Unlock();
	
	g_pD3DDevice->CreateIndexBuffer((_col - 1)* (_row - 1) * 2 * sizeof(ST_INDEX), 0, D3DFMT_INDEX32, D3DPOOL_DEFAULT, &m_ib, 0);


}

void cMaptool::SetupQuad()
{
	m_QuadTree->Add(Mapvertex);
}

void cMaptool::SetupCircle()
{
	ST_PC_VERTEX pc;
	pc.c = D3DCOLOR_XRGB(192, 0, 0);
	for (int i = 0; i < 60; i++)
	{
		pc.p = D3DXVECTOR3(cos((D3DX_PI / 30.0f)*i)*1.0f, 0, sin((D3DX_PI / 30.0f)*i)*1.0f);
		vecCircle.push_back(pc);
	}
	vecCircle.push_back(vecCircle.front());
	ve.resize(vecCircle.size());
	for (int i = 0; i < ve.size(); i++)
	{
		ve[i].c = D3DCOLOR_XRGB(192, 0, 0);
	}
}

void cMaptool::SetupControl()
{
	
}

bool cMaptool::GetCircleHeight(float x, float &y, float z)
{
	if (x < -(_col - 1) / 2 || z < -(_col - 1) / 2
		|| x >= (_col - 1) / 2 || z >= (_col - 1) / 2)
	{
		return false;
	}
	int a = (_col - 1) / 2;
	
	int nX = x;
	int nZ = z;
	if (x < 0)
		nX = x - 1.0f;
	if (z < 0)
		nZ = z - 1.0f;

	float fDeltaX = x - nX;
	float fDeltaZ = z - nZ;

	

	int _0 = (nZ+a + 0) * (_col) + (nX+a + 0);
	int _1 = (nZ+a + 1) * (_col) + (nX+a + 0);
	int _2 = (nZ+a + 1) * (_col) + (nX+a + 1);
	int _3 = (nZ+a + 0) * (_col) + (nX+a + 1);

	//_1.._3
	//.
	//.
	//_0.._2

	// ¾Æ·¡ »ï°¢Çü
	if (fDeltaX> fDeltaZ)
	{
		fDeltaX = 1.0f - fDeltaX;
		D3DXVECTOR3 v01 = Mapvertex[_2].p - Mapvertex[_3].p;
		D3DXVECTOR3 v02 = Mapvertex[_0].p - Mapvertex[_3].p;
		y = (v01 * fDeltaZ + v02 * fDeltaX).y + Mapvertex[_3].p.y;
		return true;
	}
	// À§ »ï°¢Çü
	else
	{
		fDeltaZ = 1.0f - fDeltaZ;
		D3DXVECTOR3 v31 = Mapvertex[_2].p - Mapvertex[_1].p;
		D3DXVECTOR3 v32 = Mapvertex[_0].p - Mapvertex[_1].p;
		y = (v31 * fDeltaX + v32 * fDeltaZ).y + Mapvertex[_1].p.y;
		return true;
	}

	return false;
}

void cMaptool::SetNormal()
{
	// normal vector
	for (int z = 1; z < _row-1; z++)
	{
		for (int x = 1; x < _col-1; x++)
		{
			int left = (z + 0) * _row + (x - 1);
			int right = (z + 0) * _row + (x + 1);
			int up = (z + 1) * _row + (x + 0);
			int down = (z - 1) * _row + (x + 0);

			D3DXVECTOR3 vLeftToRight = Mapvertex[right].p - Mapvertex[left].p;
			D3DXVECTOR3 vDownToUp = Mapvertex[up].p - Mapvertex[down].p;
			D3DXVECTOR3 vNormal;
			D3DXVec3Cross(&vNormal, &vDownToUp, &vLeftToRight);
			D3DXVec3Normalize(&vNormal, &vNormal);

			int nIndex = z * _row + x;
			Mapvertex[nIndex].n = vNormal;
		}
	}
}

void cMaptool::SetMaterial()
{
	ZeroMemory(&m_mt, sizeof(D3DMATERIAL9));
	m_mt.Ambient.r = m_mt.Diffuse.r = 1.0f;
	m_mt.Ambient.g = m_mt.Diffuse.g = 1.0f;
	m_mt.Ambient.b = m_mt.Diffuse.b = 1.0f;
	m_mt.Ambient.a = m_mt.Diffuse.a = 1.0f;
	//m_mt.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
}


void cMaptool::Update()
{
	POINT p;
	GetCursorPos(&p);
	ScreenToClient(g_hWnd, &p);
	
	r = cRay::RayAtWorldSpace(p.x, p.y);
	
		for (int i = 0; i < vecindex.size(); i += 3)
		{
			
			if (r.IsPicked(Mapvertex[vecindex[i]].p, Mapvertex[vecindex[i + 1]].p, Mapvertex[vecindex[i + 2]].p, d1))
			{
				if (g_pKeyManager->isStayKeyDown(VK_RBUTTON))
				{
			
				for (int j = 0; j < vecindex.size(); j++)
				{
					D3DXVECTOR3 v1 = Mapvertex[vecindex[j]].p;
					D3DXVECTOR3 v2 = d1;
					//v1.y = 0;
					//v2.y = 0;
					float a = D3DXVec3Length(&(v1 - v2));

					if (a <= m_radius)
					{
						Mapvertex[vecindex[j]].p.y += 0.05f;
					}
				}
				SetNormal();
				void* vp;
				m_vb->Lock(0, _col*_row * sizeof(ST_PTN_VERTEX), (void**)&vp, 0);
				memcpy(vp, Mapvertex,
					_col*_row * sizeof(ST_PTN_VERTEX));
				m_vb->Unlock();

				break;
			}
		}
	}

	if (g_pKeyManager->isOnceKeyDown(VK_ADD))
	{
		m_radius += 0.1f;
	}
	if (g_pKeyManager->isOnceKeyDown(VK_SUBTRACT))
	{
		m_radius -= 0.1f;
	}

	UpdateCircle();
	m_UI->Update();
	SAVE();
	LOAD();
}

void cMaptool::UpdateCircle()
{

	D3DXMATRIXA16 matTT, matS2;
	D3DXMatrixTranslation(&matTT, d1.x, 0, d1.z);
	D3DXMatrixScaling(&matS2, m_radius, 0, m_radius);
	for (int i = 0; i < vecCircle.size(); i++)
	{
		D3DXVec3TransformCoord(&ve[i].p, &vecCircle[i].p, &(matS2*matTT));
	}
	for (int i = 0; i < ve.size(); i++)
	{
		if (GetCircleHeight(ve[i].p.x, ve[i].p.y, ve[i].p.z))
		{
		}
	}
}

void cMaptool::RenderMap()
{
	//g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	//g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->SetMaterial(&m_mt);
	g_pD3DDevice->SetFVF(ST_PTN_VERTEX::FVF);
	g_pD3DDevice->SetStreamSource(0, m_vb, 0, sizeof(ST_PTN_VERTEX));
	g_pD3DDevice->SetIndices(m_ib);
	g_pD3DDevice->SetTexture(0, m_tex);
	g_pD3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, (_col*_row), 0, m_polygon);

}
void cMaptool::RenderCircle()
{
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_LINESTRIP,
		ve.size() - 1,
		&ve[0],
		sizeof(ST_PC_VERTEX));
}
void cMaptool::Render(LPD3DXSPRITE pSprite)
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	RenderMap();
	RenderCircle();
	m_UI->Render(pSprite);
}


void cMaptool::CheckVertex(tagpoint p)
{
	int _0 = p.p0;
	int _1 = p.p1;
	int _2 = p.p2;
	int _3 = p.p3;
	vecCulIndex.clear();
	//left
	if (_0%_col == 0)
	{
		if (_0 == 0)
		{
			int i = _0;
			vecCulIndex.push_back(i);
			i = _3;
			vecCulIndex.push_back(i);
			i = _3 + 1;
			vecCulIndex.push_back(i);
			i = _1;
			vecCulIndex.push_back(i);
			i = _2;
			vecCulIndex.push_back(i);
			i = _2 + 1;
			vecCulIndex.push_back(i);
			i = _1 + _col;
			vecCulIndex.push_back(i);
			i = _2 + _col;
			vecCulIndex.push_back(i);
			i = _2 + _col + 1;
			vecCulIndex.push_back(i);

			return;
		}
		if (_0 == (_col) * (_row-2) )
		{
			int i = _0 - _col;
			vecCulIndex.push_back(i);
			i = _3 - _col;
			vecCulIndex.push_back(i);
			i = _3 - _col+1;
			vecCulIndex.push_back(i);
			i = _0;
			vecCulIndex.push_back(i);
			i = _3 ;
			vecCulIndex.push_back(i);
			i = _3 + 1;
			vecCulIndex.push_back(i);
			i = _1;
			vecCulIndex.push_back(i);
			i = _2;
			vecCulIndex.push_back(i);
			i = _2+1;
			vecCulIndex.push_back(i);

			return;
		}
		else
		{
			int i = _0 - _col;
			vecCulIndex.push_back(i);
			i = _3 - _col;
			vecCulIndex.push_back(i);
			i = _3 - _col + 1;
			vecCulIndex.push_back(i);
			i = _0;
			vecCulIndex.push_back(i);
			i = _3;
			vecCulIndex.push_back(i);
			i = _3 + 1;
			vecCulIndex.push_back(i);
			i = _1;
			vecCulIndex.push_back(i);
			i = _2;
			vecCulIndex.push_back(i);
			i = _2 + 1;
			vecCulIndex.push_back(i);
			i = _1 + _col;
			vecCulIndex.push_back(i);
			i = _2 + _col;
			vecCulIndex.push_back(i);
			i = _2 + _col + 1;
			vecCulIndex.push_back(i);

			return; 
		}
	}
	//bottom
	else if (_0>0 && _0 < _col-2)
	{
		int i = _0 - 1;
		vecCulIndex.push_back(i);
		i = _0;
		vecCulIndex.push_back(i);
		i = _3;
		vecCulIndex.push_back(i);
		i = _3 + 1;
		vecCulIndex.push_back(i);

		i = _1 - 1;
		vecCulIndex.push_back(i);
		i = _1;
		vecCulIndex.push_back(i);
		i = _2;
		vecCulIndex.push_back(i);
		i = _2 + 1;
		vecCulIndex.push_back(i);
		i = _1 + _col -1;
		vecCulIndex.push_back(i);
		i = _1 + _col;
		vecCulIndex.push_back(i);
		i = _2 + _col;
		vecCulIndex.push_back(i);
		i = _2 + _col+1;
		vecCulIndex.push_back(i);

	}
	//top
	else if (_0< (_col-1)*_row -2 && _0 > _col*(_row - 2))
	{
		int i = _0 - _col -1;
		vecCulIndex.push_back(i);
		i = _0 - _col;
		vecCulIndex.push_back(i);
		i = _3 - _col;
		vecCulIndex.push_back(i);
		i = _3 - _col+1;
		vecCulIndex.push_back(i);
		i = _0 - 1;
		vecCulIndex.push_back(i);
		i = _0;
		vecCulIndex.push_back(i);
		i = _3;
		vecCulIndex.push_back(i);
		i = _3 + 1;
		vecCulIndex.push_back(i);
		i = _1 - 1;
		vecCulIndex.push_back(i);
		i = _1;
		vecCulIndex.push_back(i);
		i = _2 ;
		vecCulIndex.push_back(i);
		i = _2 + 1;
		vecCulIndex.push_back(i);

		return;
	}
	//right
	else if (_0 % _col == _col-2)
	{
		if (_0 == _col - 2)
		{
			int i = _0 - 1;
			vecCulIndex.push_back(i);
			i = _0;
			vecCulIndex.push_back(i);
			i = _3;
			vecCulIndex.push_back(i);
			i = _1 - 1;
			vecCulIndex.push_back(i);
			i = _1;
			vecCulIndex.push_back(i);
			i = _2;
			vecCulIndex.push_back(i);
			i = _1 + _col - 1;
			vecCulIndex.push_back(i);
			i = _1 + _col;
			vecCulIndex.push_back(i);
			i = _2 + _col;
			vecCulIndex.push_back(i);
		}
		else if (_0 == (_col - 1)*_row - 2)
		{
			int i = _0 - _col - 1;
			vecCulIndex.push_back(i);
			i = _0 - _col;
			vecCulIndex.push_back(i);
			i = _3 - _col;
			vecCulIndex.push_back(i);
			i = _0 - 1;
			vecCulIndex.push_back(i);
			i = _0;
			vecCulIndex.push_back(i);
			i = _3;
			vecCulIndex.push_back(i);
			i = _1 - 1;
			vecCulIndex.push_back(i);
			i = _1;
			vecCulIndex.push_back(i);
			i = _2;
			vecCulIndex.push_back(i);
		}
		else
		{
			int i = _0 - _col - 1;
			vecCulIndex.push_back(i);
			i = _0 - _col;
			vecCulIndex.push_back(i);
			i = _3 - _col;
			vecCulIndex.push_back(i);
			i = _0 - 1;
			vecCulIndex.push_back(i);
			i = _0;
			vecCulIndex.push_back(i);
			i = _3;
			vecCulIndex.push_back(i);
			i = _1 - 1;
			vecCulIndex.push_back(i);
			i = _1;
			vecCulIndex.push_back(i);
			i = _2;
			vecCulIndex.push_back(i);
			i = _1 + _col - 1;
			vecCulIndex.push_back(i);
			i = _1 + _col;
			vecCulIndex.push_back(i);
			i = _2 + _col;
			vecCulIndex.push_back(i);
		}
	}
	//rest
	else
	{
		int i = _0 - _col - 1;
		vecCulIndex.push_back(i);
		i = _0 - _col;
		vecCulIndex.push_back(i);
		i = _3 - _col;
		vecCulIndex.push_back(i);
		i = _3 - _col + 1;
		vecCulIndex.push_back(i);
		i = _0 - 1;
		vecCulIndex.push_back(i);
		i = _0;
		vecCulIndex.push_back(i);
		i = _3;
		vecCulIndex.push_back(i);
		i = _3 + 1;
		vecCulIndex.push_back(i);
		i = _1 - 1;
		vecCulIndex.push_back(i);
		i = _1;
		vecCulIndex.push_back(i);
		i = _2;
		vecCulIndex.push_back(i);
		i = _2 + 1;
		vecCulIndex.push_back(i);
		i = _1 + _col - 1;
		vecCulIndex.push_back(i);
		i = _1 + _col;
		vecCulIndex.push_back(i);
		i = _2 + _col;
		vecCulIndex.push_back(i);
		i = _2 + _col + 1;
		vecCulIndex.push_back(i);
	}

}

void cMaptool::Draw(cFrustum *f)
{
	LPDWORD pi;
	
	m_ib->Lock(0, (_col - 1)* (_row - 1) *2* sizeof(ST_INDEX), (void**)&pi, 0);
	m_polygon = m_QuadTree->GenerateIndex(pi, Mapvertex, f);
	vecindex.resize(m_polygon * 3);
	for (int i = 0; i < m_polygon*3; i++)
	{
		vecindex[i] = pi[i];
	}
	m_ib->Unlock();

}

void cMaptool::SAVE()
{
	if (m_UI->Getsave())
	{
		TCHAR str[1024] = TEXT("");
		OPENFILENAME ope;
		memset(&ope, 0, sizeof(OPENFILENAME));
		ope.lStructSize = sizeof(OPENFILENAME);
		ope.hwndOwner = GetConsoleWindow();
		ope.lpstrFilter = TEXT("All Files(*.*)\0*.*\0");
		ope.lpstrFile = str;
		ope.nMaxFile = 1024;
		//ope.lpstrDefExt = TEXT("txt");
		GetSaveFileName(&ope);
		std::string strings = std::string(ope.lpstrFile);
		if (strings == "")
		{
			m_UI->Setsave(false);
			return;
		}
		FILE* fp;
		fp = fopen(strings.c_str(), "w");

		fprintf(fp, "%d\n", _col*_row);
		//fprintf(fp, "%s \n", "p");
		for (int i = 0; i < _col*_row; i++)
		{
			fprintf(fp, "%f %f %f\n", Mapvertex[i].p.x, Mapvertex[i].p.y, Mapvertex[i].p.z);
		}
		//fprintf(fp, "%s \n", "n");
		for (int i = 0; i < _col*_row; i++)
		fprintf(fp, "%f %f %f\n", Mapvertex[i].n.x, Mapvertex[i].n.y, Mapvertex[i].n.z);
		//fprintf(fp, "%s \n", "t");
		for (int i = 0; i < _col*_row; i++)
		fprintf(fp, "%f %f\n", Mapvertex[i].t.x, Mapvertex[i].t.y);
		fclose(fp);
		m_UI->Setsave(false);
	}
}

void cMaptool::LOAD()
{
	if (m_UI->Getload())
	{
		TCHAR str[1024] = TEXT("");
		OPENFILENAME ope;
		memset(&ope, 0, sizeof(OPENFILENAME));
		ope.lStructSize = sizeof(OPENFILENAME);
		ope.hwndOwner = GetConsoleWindow();
		ope.lpstrFilter = TEXT("All Files(*.*)\0*.*\0");
		ope.lpstrFile = str;
		ope.nMaxFile = 1024;
		//ope.lpstrDefExt = TEXT("txt");
		GetOpenFileName(&ope);
		std::string strings = std::string(ope.lpstrFile);
		if (strings == "")
		{
			m_UI->Setload(false);
			return;
		}
		FILE* fp;
		fp = fopen(strings.c_str(), "r");

		int size=0;
		fscanf(fp,"%d\n",&size);
		
		for (int i = 0; i < size; i++)
		{
			fscanf(fp, "%f %f %f\n", &Mapvertex[i].p.x, &Mapvertex[i].p.y, &Mapvertex[i].p.z);
		}
		for (int i = 0; i < size; i++)
		{
			fscanf(fp, "%f %f %f\n", &Mapvertex[i].n.x, &Mapvertex[i].n.y, &Mapvertex[i].n.z);
		}
		for (int i = 0; i < size; i++)
		{
			fscanf(fp, "%f %f\n", &Mapvertex[i].t.x, &Mapvertex[i].t.y);
		}

		fclose(fp);

		void* vp;
		m_vb->Lock(0, _col*_row * sizeof(ST_PTN_VERTEX), (void**)&vp, 0);
		memcpy(vp, Mapvertex,
			_col*_row * sizeof(ST_PTN_VERTEX));
		m_vb->Unlock();
		m_UI->Setload(false);
	}
}

