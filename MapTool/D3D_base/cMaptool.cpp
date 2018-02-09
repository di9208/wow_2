#include "stdafx.h"
#include "cMaptool.h"
#include "cUIButton.h"
#include "cQuadTree.h"
#include "cMapTool_UI.h"
#include "cSkyBox.h"


cMaptool::cMaptool()
	:Heightmap(nullptr)
	, m_radius(1.0f)
	, m_QuadTree(nullptr)
	, _col(129)
	, _row(129)
	, m_LandControl(0.05f)
	, m_UpDown(0.05f)
	, m_tex1(nullptr)
	, m_playerTranslation(false)
	, m_isPlayerExist(false)
	, m_isMonsterExist(false)
	, m_monsterTranslation(false)
	, m_NPCTranslation(false)
	, m_isNPCExist(false)
{
	
}


cMaptool::~cMaptool()
{
	
	Heightmap->Destroy();
	SAFE_DELETE(m_QuadTree);
	SAFE_RELEASE(m_tex1);
	SAFE_RELEASE(m_vb);
	SAFE_RELEASE(m_ib);
	SAFE_DELETE(m_UI);
	SAFE_DELETE(m_player);
	for (int i = 0; i < m_vecMonster.size(); i++)
	{
		SAFE_DELETE(m_vecMonster[i].monster);
	}
	m_vecMonster.clear();

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
	m_SkyBox = new cSkyBox;
	m_SkyBox->Setup();
	
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

void cMaptool::SetTexture(std::string t)
{
	if (t == "")
	{
		m_tex1 = NULL;
		return;
	}
	m_tex1 = g_pTextureManager->GetTexture(t);
	return;
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
	
	GetCursorPos(&p);
	ScreenToClient(g_hWnd, &p);
	
	r = cRay::RayAtWorldSpace(p.x, p.y);
	
	if (m_UI->Getupthow() || m_UI->Getdownthow() || m_UI->Getflat() || m_playerTranslation || m_monsterTranslation || m_NPCTranslation)
	{
		for (int i = 0; i < vecindex.size(); i += 3)
		{

			if (r.IsPicked(Mapvertex[vecindex[i]].p, Mapvertex[vecindex[i + 1]].p, Mapvertex[vecindex[i + 2]].p, d1))
			{
				if (!m_playerTranslation &&!m_monsterTranslation&&!m_NPCTranslation)
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
								if (m_UI->Getflat())
								{
									Mapvertex[vecindex[j]].p.y = 0;
								}
								else
									Mapvertex[vecindex[j]].p.y += m_LandControl;
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
		}

		UpdateCircle();
	}



	
	m_UI->Update();
	SAVE();
	LOAD();
	LandScaping();
	SkyBoxT();
	Terrain();
	Object();
	Unit();
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
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->SetMaterial(&m_mt);
	g_pD3DDevice->SetFVF(ST_PTN_VERTEX::FVF);
	g_pD3DDevice->SetStreamSource(0, m_vb, 0, sizeof(ST_PTN_VERTEX));
	g_pD3DDevice->SetIndices(m_ib);
	g_pD3DDevice->SetTexture(0, m_tex1);
	g_pD3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, (_col*_row), 0, m_polygon);
	
	
	PlayerRender();
	NPCRender();
	MonsterRender();
	
}
void cMaptool::RenderCircle()
{
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_LINESTRIP,
		ve.size() - 1,
		&ve[0],
		sizeof(ST_PC_VERTEX));
}
void cMaptool::Render(LPD3DXSPRITE pSprite,D3DXVECTOR3 camera)
{
	m_SkyBox->Render(camera);

	float strat = 90.0f;
	float end = 150.0f;
	float den = 0.07f;
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	
	g_pD3DDevice->SetRenderState(D3DRS_FOGVERTEXMODE, D3DFOG_LINEAR);

	//g_pD3DDevice->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_LINEAR);

	g_pD3DDevice->SetRenderState(D3DRS_FOGSTART, *(DWORD*)(&strat));

	g_pD3DDevice->SetRenderState(D3DRS_FOGEND, *(DWORD*)(&end));
	
	//g_pD3DDevice->SetRenderState(D3DRS_FOGDENSITY, *(DWORD*)(&den));
	g_pD3DDevice->SetRenderState(D3DRS_FOGCOLOR, 0x00CCCCCC);
	g_pD3DDevice->SetRenderState(D3DRS_FOGENABLE, true);
	g_pD3DDevice->SetRenderState(D3DRS_RANGEFOGENABLE, true);
	
	D3DXMATRIXA16	matWorld;
	D3DXMatrixIdentity(&matWorld);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	RenderMap();
	//g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	if (m_UI->Getupthow() || m_UI->Getdownthow() || m_UI->Getflat())
		RenderCircle();
	m_UI->Render(pSprite);
	
	D3DXMATRIXA16 matS, matT;
	D3DXMatrixTranslation(&matT, -20, 0, 0);
	D3DXMatrixScaling(&matS, 0.3f, 0.3f, 0.3f);
	matWorld = matS * matT;
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);

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
		ope.lpstrFilter = TEXT("TEXT Files(*.txt)\0*.txt\0");
		ope.lpstrFile = str;
		ope.nMaxFile = 1024;
		ope.lpstrDefExt = TEXT("txt");
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

		///char str[1024];
		//std::string asd = std::string("asaa");
		fprintf(fp, "%s\n", m_SkyBox->Get8Way().front.c_str());
		fprintf(fp, "%s\n", m_SkyBox->Get8Way().back.c_str());
		fprintf(fp, "%s\n", m_SkyBox->Get8Way().left.c_str());
		fprintf(fp, "%s\n", m_SkyBox->Get8Way().right.c_str());
		fprintf(fp, "%s\n", m_SkyBox->Get8Way().top.c_str());
		fprintf(fp, "%s\n", m_SkyBox->Get8Way().bottom.c_str());
		fprintf(fp, "%s\n", m_stex.c_str());
		if (m_isPlayerExist)
		{
			fprintf(fp, "%s\n", "P");
			fprintf(fp, "%f %f %f\n", Playerpos.x, Playerpos.y, Playerpos.z);
		}
		if (m_isNPCExist)
		{
			fprintf(fp, "%s\n", "N");
			fprintf(fp, "%f %f %f\n", NPCpos.x, NPCpos.y, NPCpos.z);
		}
		if (m_vecMonster.size() != 0)
		{
			fprintf(fp, "%s\n", "M");
			fprintf(fp, "%d\n", BONESPIDER);
			for (int i = 0; i < m_vecMonster.size(); i++)
			{
				if (m_vecMonster[i].kind == BONESPIDER)
				{
					fprintf(fp, "%s\n", m_vecMonster[i].name.c_str());
					fprintf(fp, "%f %f %f\n", m_vecMonster[i].sphere.vCenter.x, m_vecMonster[i].sphere.vCenter.y, m_vecMonster[i].sphere.vCenter.z);
				}
			}

			fprintf(fp, "%d\n", DRUID);
			for (int i = 0; i < m_vecMonster.size(); i++)
			{
				if (m_vecMonster[i].kind == DRUID)
				{
					fprintf(fp, "%s\n", m_vecMonster[i].name.c_str());
					fprintf(fp, "%f %f %f\n", m_vecMonster[i].sphere.vCenter.x, m_vecMonster[i].sphere.vCenter.y, m_vecMonster[i].sphere.vCenter.z);
				}
			}


			fprintf(fp, "%d\n", WORG);
			for (int i = 0; i < m_vecMonster.size(); i++)
			{
				if (m_vecMonster[i].kind == WORG)
				{
					fprintf(fp, "%s\n", m_vecMonster[i].name.c_str());
					fprintf(fp, "%f %f %f\n", m_vecMonster[i].sphere.vCenter.x, m_vecMonster[i].sphere.vCenter.y, m_vecMonster[i].sphere.vCenter.z);
				}
			}

			fprintf(fp, "%d\n", LICHKING);
			for (int i = 0; i < m_vecMonster.size(); i++)
			{
				if (m_vecMonster[i].kind == LICHKING)
				{
					fprintf(fp, "%s\n", m_vecMonster[i].name.c_str());
					fprintf(fp, "%f %f %f\n", m_vecMonster[i].sphere.vCenter.x, m_vecMonster[i].sphere.vCenter.y, m_vecMonster[i].sphere.vCenter.z);
				}
			}

			fprintf(fp, "%d\n", RAGNAROS);
			for (int i = 0; i < m_vecMonster.size(); i++)
			{
				if (m_vecMonster[i].kind == RAGNAROS)
				{
					fprintf(fp, "%s\n", m_vecMonster[i].name.c_str());
					fprintf(fp, "%f %f %f\n", m_vecMonster[i].sphere.vCenter.x, m_vecMonster[i].sphere.vCenter.y, m_vecMonster[i].sphere.vCenter.z);
				}
			}

		}
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
		std::string tex;

		char astr[1024];
		fscanf(fp, "%s\n", astr);
		tex = std::string(astr);
		m_SkyBox->setTex(g_pTextureManager->GetTexture(tex), 0);
		fscanf(fp, "%s\n", astr);
		tex = std::string(astr);
		m_SkyBox->setTex(g_pTextureManager->GetTexture(tex), 1);
		fscanf(fp, "%s\n", astr);
		tex = std::string(astr);
		m_SkyBox->setTex(g_pTextureManager->GetTexture(tex), 2);
		fscanf(fp, "%s\n", astr);
		tex = std::string(astr);
		m_SkyBox->setTex(g_pTextureManager->GetTexture(tex), 3);
		fscanf(fp, "%s\n", astr);
		tex = std::string(astr);
		m_SkyBox->setTex(g_pTextureManager->GetTexture(tex), 4);
		fscanf(fp, "%s\n", astr);
		tex = std::string(astr);
		m_SkyBox->setTex(g_pTextureManager->GetTexture(tex), 5);
		fscanf(fp, "%s\n", astr);
		tex = std::string(astr);
		SetTexture(tex);

		char strr[1024];
		int number = 0;
		ENUMMONSTER em;
		
			
			fscanf(fp, "%s\n", strr);
			if (strr[0] == 'P')
			{
				fscanf(fp, "%f %f %f\n", &Playerpos.x, &Playerpos.y, &Playerpos.z);
			}
			fscanf(fp, "%s\n", strr);
			if (strr[0] == 'N')
			{
				fscanf(fp, "%f %f %f\n", &NPCpos.x, &NPCpos.y, &NPCpos.z);
			}
			fscanf(fp, "%s\n", strr);
			if (strr[0] == 'M')
			{
				while (true)
				{
					//fscanf(fp, "%s\n", strr);
					tagMonster tm;
					fscanf(fp, "%d\n", &em);
					if (feof(fp))
						break;
					tm.kind = em;
					fscanf(fp, "%s\n", strr);
					std::string s = std::string(strr);

					tm.name = strr;
					tm.number = number;
					tm.sphere.fRadius = 2.0f;
					tm.Translation = false;
					tm.monster = new cMapToolObject;
					tm.monster->Setup(strr);
					D3DXVECTOR3 vc;
					fscanf(fp, "%f %f %f\n", &vc.x, &vc.y, &vc.z);
					tm.sphere.vCenter = vc;
					D3DXMATRIXA16 matT, matS, matR, matW, matTT;
					D3DXMatrixRotationX(&matR, D3DX_PI / -2.0f);
					D3DXMatrixScaling(&matS, 0.01f, 0.01f, 0.01f);
					D3DXMatrixTranslation(&matT, 0, 0, 0);
					D3DXMatrixTranslation(&matTT, vc.x, vc.y, vc.z);
					matW = matS * matR* matT;
					tm.monster->Getmm() = matW;
					tm.monster->Gettt() = matTT;
					m_vecMonster.push_back(tm);
				}
			}
		
		fclose(fp);
		m_player = new cMapToolObject;
		m_isPlayerExist = true;
		m_playerTranslation = false;
		m_player->Setup("player");
		D3DXMATRIXA16 matT, matS, matR, matW, matTT;
		D3DXMatrixRotationX(&matR, D3DX_PI / -2.0f);
		D3DXMatrixScaling(&matS, 0.01f, 0.01f, 0.01f);
		D3DXMatrixTranslation(&matT, Playerpos.x, Playerpos.y, Playerpos.z);
		D3DXMatrixTranslation(&matTT, 0, 0, 0);
		matW = matS * matR*matTT;
		m_player->Getmm() = matW;
		m_player->Gettt() = matT;

		m_NPC = new cMapToolObject;
		m_isNPCExist = true;
		m_NPCTranslation = false;
		m_NPC->Setup("NPC");
	
		
		D3DXMatrixRotationX(&matR, D3DX_PI / -2.0f);
		D3DXMatrixScaling(&matS, 0.01f, 0.01f, 0.01f);
		D3DXMatrixTranslation(&matT, NPCpos.x, NPCpos.y, NPCpos.z);
		D3DXMatrixTranslation(&matTT, 0, 0, 0);
		matW = matS * matR* matTT;
		m_NPC->Getmm() = matW;
		m_NPC->Gettt() = matT;

		void* vp;
		m_vb->Lock(0, _col*_row * sizeof(ST_PTN_VERTEX), (void**)&vp, 0);
		memcpy(vp, Mapvertex,
			_col*_row * sizeof(ST_PTN_VERTEX));
		m_vb->Unlock();
		m_UI->Setload(false);
	}
}

void cMaptool::LandScaping()
{
	if (m_UI->Getdownthow())
	{
		m_LandControl = -m_UpDown;
	}
	if (m_UI->Getupthow())
	{
		m_LandControl = m_UpDown;
	}
	if (m_UI->Getflat())
	{
		m_LandControl = 0;
	}
	if (g_pKeyManager->isOnceKeyDown(VK_NUMPAD8))
	{
		m_UpDown += 0.05f;
	}
	if (g_pKeyManager->isOnceKeyDown(VK_NUMPAD2))
	{
		m_UpDown -= 0.05f;
	}
	if (g_pKeyManager->isStayKeyDown(VK_ADD))
	{
		m_radius += 0.1f;
	}
	if (g_pKeyManager->isStayKeyDown(VK_SUBTRACT))
	{
		m_radius -= 0.1f;
	}
}

void cMaptool::SkyBoxT()
{
	if (m_UI->Getskybox())
	{
		TCHAR str[1024] = TEXT("");
		OPENFILENAME ope;
		memset(&ope, 0, sizeof(OPENFILENAME));
		ope.lStructSize = sizeof(OPENFILENAME);
		ope.hwndOwner = g_hWnd;
		ope.lpstrFilter = TEXT("All Files(*.*)\0*.*\0");
		ope.lpstrFile = str;
		ope.nMaxFile = 1024;
		//ope.lpstrDefExt = TEXT("txt");
		GetOpenFileName(&ope);
	
		std::string strings = std::string(ope.lpstrFile);

		m_SkyBox->SetTexture(strings);

		//delete str;
		m_UI->Setskybox(false);
	}
}

void cMaptool::Terrain()
{
	if (m_UI->Getterrain())
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
		m_stex = std::string(str);

		this->SetTexture(m_stex);

		m_UI->Setterrain(false);
	}
}

void cMaptool::Object()
{
	if (m_UI->Gettree())
	{
		


		m_UI->Settree(false);
	}

}

void cMaptool::Unit()
{
	if (m_UI->Getplayer())
	{
		if (!m_isPlayerExist)
			m_player = new cMapToolObject;

		m_isPlayerExist = true;
		m_playerTranslation = true;
		m_player->Setup("player");
		D3DXMATRIXA16 matT, matS, matR, matW;
		D3DXMatrixRotationX(&matR, D3DX_PI / -2.0f);
		D3DXMatrixScaling(&matS, 0.01f, 0.01f, 0.01f);
		D3DXMatrixTranslation(&matT, 0, 0, 0);
		matW = matS * matR*matT;
		m_player->Getmm() = matW;

		m_UI->Setplayer(false);
	}
	if (m_UI->Gettau())
	{
		if (!m_isNPCExist)
				m_NPC = new cMapToolObject;

		m_isNPCExist = true;
		m_NPCTranslation = true;
		m_NPC->Setup("NPC");
	
		D3DXMATRIXA16 matT, matS, matR, matW;
		D3DXMatrixRotationX(&matR, D3DX_PI / -2.0f);
		D3DXMatrixScaling(&matS, 0.005f, 0.005f, 0.005f);
		D3DXMatrixTranslation(&matT, 0, 0, 0);
		matW = matS * matR* matT;
		
		m_NPC->Getmm() = matW;
		

		m_UI->Settau(false);
	}
	if (m_UI->Getspider())
	{
		int size = 1;
		for each(auto p in m_vecMonster)
		{
			if (p.kind == BONESPIDER)
				size++;
		}
		m_monsterTranslation = true;
		std::string m = "bonespider";
		tagMonster t;
		t.kind = BONESPIDER;
		t.monster = new cMapToolObject;
		t.number = size;
		t.Translation = true;
		char st[512];
		itoa(size,st,10);
		std::string m2 = m + std::string(st);
		t.name = m2;
		t.monster->Setup(m2);
		D3DXMATRIXA16 matT, matS, matR, matW;
		D3DXMatrixRotationX(&matR, D3DX_PI / -2.0f);
		D3DXMatrixScaling(&matS, 0.003f, 0.003f, 0.003f);
		D3DXMatrixTranslation(&matT, 0, 0, 0);
		matW = matS * matR* matT;
		t.monster->Getmm() = matW;
		t.sphere.fRadius = 0.8f;
		t.sphere.vCenter = D3DXVECTOR3(0, 0, 0);
		m_vecMonster.push_back(t);
		m_UI->Setspider(false);
	}

	if (m_UI->Getworg())
	{
		int size = 1;

		for each(auto p in m_vecMonster)
		{
			if (p.kind == WORG)
				size++;
		}

		m_monsterTranslation = true;
		std::string m = "worg";
		tagMonster t;
		t.kind = WORG;
		t.monster = new cMapToolObject;
		t.number = size;
		t.Translation = true;
		char st[512];
		itoa(size, st, 10);
		std::string m2 = m + std::string(st);
		t.name = m2;
		t.monster->Setup(m2);
		D3DXMATRIXA16 matT, matS, matR, matW;
		D3DXMatrixRotationX(&matR, D3DX_PI / -2.0f);
		D3DXMatrixScaling(&matS, 0.006f, 0.006f, 0.006f);
		D3DXMatrixTranslation(&matT, 0, 0, 0);
		matW = matS * matR* matT;
		t.monster->Getmm() = matW;
		t.sphere.fRadius = 0.35;
		t.sphere.vCenter = D3DXVECTOR3(0, 0, 0);
		m_vecMonster.push_back(t);
		
		m_UI->Setworg(false);
	}

	if (m_UI->Getlichking())
	{
		
		m_monsterTranslation = true;
		std::string m = "lichking";
		tagMonster t;
		t.kind = LICHKING;
		t.monster = new cMapToolObject;
		t.Translation = true;
		t.name = m;
		char st[512];
		t.monster->Setup(m);
		D3DXMATRIXA16 matT, matS, matR, matW;
		D3DXMatrixRotationX(&matR, D3DX_PI / -2.0f);
		D3DXMatrixScaling(&matS, 0.015f, 0.015f, 0.015f);
		D3DXMatrixTranslation(&matT, 0, 0, 0);
		matW = matS * matR* matT;
		t.monster->Getmm() = matW;
		t.sphere.fRadius = 0.5;
		t.sphere.vCenter = D3DXVECTOR3(0, 0, 0);
		m_vecMonster.push_back(t);

		m_UI->Setlichking(false);
	}

	if (m_UI->Getdruid())
	{
		int size = 1;

		for each(auto p in m_vecMonster)
		{
			if (p.kind == DRUID)
				size++;
		}

		m_monsterTranslation = true;
		std::string m = "druid";
		tagMonster t;
		t.kind = DRUID;
		t.monster = new cMapToolObject;
		t.number = size;
		t.Translation = true;
		char st[512];
		itoa(size, st, 10);
		std::string m2 = m + std::string(st);
		t.name = m2;
		t.monster->Setup(m2);
		D3DXMATRIXA16 matT, matS, matR, matW;
		D3DXMatrixRotationX(&matR, D3DX_PI / -2.0f);
		D3DXMatrixScaling(&matS, 0.003f, 0.003f, 0.003f);
		D3DXMatrixTranslation(&matT, 0, 0, 0);
		matW = matS * matR* matT;
		t.monster->Getmm() = matW;
		t.sphere.fRadius = 0.35;
		t.sphere.vCenter = D3DXVECTOR3(0, 0, 0);
		m_vecMonster.push_back(t);

		m_UI->Setdruid(false);
	}

	if (m_UI->Getrag())
	{

		m_monsterTranslation = true;
		std::string m = "rag";
		tagMonster t;
		t.kind = RAGNAROS;
		t.monster = new cMapToolObject;
		t.Translation = true;
		char st[512];
		t.name = m;
		t.monster->Setup(m);
		D3DXMATRIXA16 matT, matS, matR, matW;
		D3DXMatrixRotationX(&matR, D3DX_PI / -2.0f);
		D3DXMatrixScaling(&matS, 0.002f, 0.002f, 0.002f);
		D3DXMatrixTranslation(&matT, 0, 0, 0);
		matW = matS * matR* matT;
		t.monster->Getmm() = matW;
		t.sphere.fRadius = 0.5;
		t.sphere.vCenter = D3DXVECTOR3(0, 0, 0);
		m_vecMonster.push_back(t);

		m_UI->Setrag(false);
	}

	
}

void cMaptool::loadMonster()
{

}

void cMaptool::PlayerRender()
{
	if (g_pKeyManager->isOnceKeyDown('M') && m_isPlayerExist)
	{
		if (!m_playerTranslation)
		{
			m_playerTranslation = true;
			return;
		}
		if (m_playerTranslation)
		{
			m_playerTranslation = false;
			Playerpos = D3DXVECTOR3(d1.x, d1.y, d1.z);
			return;
		}
	}
	if (m_playerTranslation && m_isPlayerExist)
	{

		D3DXMATRIXA16 matT;
		D3DXMatrixTranslation(&matT, d1.x, d1.y, d1.z);
		m_player->Gettt() = matT;
	}

	if (!m_playerTranslation && m_isPlayerExist)
	{

		D3DXMATRIXA16 matT;
		D3DXMatrixTranslation(&matT, Playerpos.x, Playerpos.y, Playerpos.z);
		m_player->Gettt() = matT;
	}
	if (m_isPlayerExist)
	{
		m_player->Render();
	}
}

void cMaptool::NPCRender()
{
	if (g_pKeyManager->isOnceKeyDown('N') && m_isNPCExist)
	{
		if (!m_NPCTranslation)
		{
			m_NPCTranslation = true;
			return;
		}
		if (m_NPCTranslation)
		{
			m_NPCTranslation = false;
			NPCpos = D3DXVECTOR3(d1.x, d1.y, d1.z);
			return;
		}
	}
	if (m_NPCTranslation && m_isNPCExist)
	{

		D3DXMATRIXA16 matT;
		D3DXMatrixTranslation(&matT, d1.x, d1.y, d1.z);
		m_NPC->Gettt() = matT;
	}

	if (!m_NPCTranslation && m_isNPCExist)
	{

		D3DXMATRIXA16 matT;
		D3DXMatrixTranslation(&matT, NPCpos.x, NPCpos.y, NPCpos.z);
		m_NPC->Gettt() = matT;
	}
	if (m_isNPCExist)
	{
		m_NPC->Render();
	}
}

void cMaptool::MonsterRender()
{
	if (m_vecMonster.size() != 0)
	{
		for (int i = 0; i < m_vecMonster.size(); i++)
		{
			if (m_vecMonster[i].Translation)
			{

				D3DXMATRIXA16 matT;
				D3DXMatrixTranslation(&matT, d1.x, d1.y, d1.z);
				m_vecMonster[i].monster->Gettt() = matT;
				m_vecMonster[i].sphere.vCenter = D3DXVECTOR3(d1.x, d1.y, d1.z);

			}
			if (!m_vecMonster[i].Translation)
			{
				D3DXMATRIXA16 matT;
				D3DXMatrixTranslation(&matT, m_vecMonster[i].sphere.vCenter.x, m_vecMonster[i].sphere.vCenter.y, m_vecMonster[i].sphere.vCenter.z);
				m_vecMonster[i].monster->Gettt() = matT;
			}
		}
		if (g_pKeyManager->isOnceKeyDown(VK_RBUTTON))
		{
			for (int i = 0; i < m_vecMonster.size(); i++)
			{
				cRay ra = cRay::RayAtWorldSpace(p.x, p.y);

				if (ra.IsPicked(&m_vecMonster[i].sphere))
				{
					if (!m_vecMonster[i].Translation)
					{
						m_monsterTranslation = true;
						m_vecMonster[i].Translation = true;
						break;
					}
					if (m_vecMonster[i].Translation)
					{
						m_monsterTranslation = false;
						m_vecMonster[i].Translation = false;
						break;
					}
				}
			}
		}

		for (int i = 0; i < m_vecMonster.size(); i++)
		{
			m_vecMonster[i].monster->Render();
		}
	}
}

void cMaptool::ObjectRender()
{


}

