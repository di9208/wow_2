#include "stdafx.h"
#include "cObjLoader.h"
#include "cMtlTex.h"
#include "cGroup.h"


cObjLoader::cObjLoader()
{
}


cObjLoader::~cObjLoader()
{
}

void cObjLoader::Load(OUT std::vector<cGroup*>& vecGroup,
	IN char * szFolder, IN char * szFile)
{
	bool isTex = false;
	std::vector<ST_PTN_VERTEX> vecVertex;
	std::vector<D3DXVECTOR3> vecV;
	std::vector<D3DXVECTOR2> vecVT;
	std::vector<D3DXVECTOR3> vecVN;

	std::string sFullPath(szFolder);
	sFullPath += (std::string("/") + std::string(szFile));

	std::string sMtlName;

	FILE* fp;
	fopen_s(&fp, sFullPath.c_str(), "r");

	char szTemp[1024];
	while (true)
	{
		if (feof(fp))
			break;

		fgets(szTemp, 1024, fp);
		if (szTemp[0] == '#')
		{
			continue;
		}
		else if (szTemp[0] == 'm')
		{
			// 메터리얼 파일 로드
			char szMtlFile[1024];
			sscanf_s(szTemp, "%*s %s", szMtlFile, 1024);
			LoadMtlLib(szFolder, szMtlFile);
		}
		else if (szTemp[0] == 'g')
		{
			if (!vecVertex.empty())
			{
				cGroup* pGroup = new cGroup;
				pGroup->SetVertex(vecVertex);
				pGroup->SetMtlTex(m_mapMtlTex[sMtlName]);
				vecGroup.push_back(pGroup);
				vecVertex.clear();
			}
		}
		else if (szTemp[0] == 'v')
		{
			if (szTemp[1] == ' ')
			{
				//v - 5.000000 - 5.000000 0.000000
				float x, y, z;
				sscanf_s(szTemp, "%*s %f %f %f", &x, &y, &z);
				vecV.push_back(D3DXVECTOR3(x, y, z));
			}
			else if (szTemp[1] == 't')
			{
				isTex = true;
				float u, v;
				sscanf_s(szTemp, "%*s %f %f %*f", &u, &v);
				vecVT.push_back(D3DXVECTOR2(u, 1.0f-v));
			}
			else if (szTemp[1] == 'n')
			{
				float x, y, z;
				sscanf_s(szTemp, "%*s %f %f %f", &x, &y, &z);
				vecVN.push_back(D3DXVECTOR3(x, y, z));
			}
		}
		else if (szTemp[0] == 'u')
		{
			// 사용할 메테리얼 이름 저장
			char szMtlName[1024];
			sscanf_s(szTemp, "%*s %s", szMtlName, 1024);
			sMtlName = std::string(szMtlName);
		}
		else if (szTemp[0] == 'f')
		{
			if (isTex)
			{
				int nIndex[3][3];
				sscanf_s(szTemp, "%*s %d/%d/%d %d/%d/%d %d/%d/%d",
					&nIndex[0][0], &nIndex[0][1], &nIndex[0][2],
					&nIndex[1][0], &nIndex[1][1], &nIndex[1][2],
					&nIndex[2][0], &nIndex[2][1], &nIndex[2][2]);

				for (int i = 0; i < 3; i++)
				{
					ST_PTN_VERTEX v;
					v.p = vecV[nIndex[i][0] - 1];	// 정점
					v.t = vecVT[nIndex[i][1] - 1];	// 텍스처
					v.n = vecVN[nIndex[i][2] - 1];	// 노말

					vecVertex.push_back(v);
				}
			}
			else
			{
				int nIndex[3][2];
				sscanf_s(szTemp, "%*s %d//%d %d//%d %d//%d",
					&nIndex[0][0], &nIndex[0][1],
					&nIndex[1][0], &nIndex[1][1],
					&nIndex[2][0], &nIndex[2][1]);

				for (int i = 0; i < 3; i++)
				{
					ST_PTN_VERTEX v;
					v.p = vecV[nIndex[i][0] - 1];	// 정점
					v.n = vecVN[nIndex[i][1] - 1];	// 노말

					vecVertex.push_back(v);
				}
			}
		}
	}

	fclose(fp);

	for each(auto p in m_mapMtlTex)
	{
		SAFE_RELEASE(p.second);
	}
	m_mapMtlTex.clear();
}

LPD3DXMESH cObjLoader::LoadMesh(OUT std::vector<cMtlTex*>& vecMtlTex,
	IN char * szFolder, IN char * szFile)
{
	std::vector<DWORD> vecAttrBuf;
	std::vector<ST_PTN_VERTEX> vecVertex;
	std::vector<D3DXVECTOR3> vecV;
	std::vector<D3DXVECTOR2> vecVT;
	std::vector<D3DXVECTOR3> vecVN;

	std::string sFullPath(szFolder);
	sFullPath += (std::string("/") + std::string(szFile));

	std::string sMtlName;

	FILE* fp;
	fopen_s(&fp, sFullPath.c_str(), "r");

	char szTemp[1024];
	while (true)
	{
		if (feof(fp))
			break;

		fgets(szTemp, 1024, fp);
		if (szTemp[0] == '#')
		{
			continue;
		}
		else if (szTemp[0] == 'm')
		{
			// 메터리얼 파일 로드
			char szMtlFile[1024];
			sscanf_s(szTemp, "%*s %s", szMtlFile, 1024);
			LoadMtlLib(szFolder, szMtlFile);
		}
		else if (szTemp[0] == 'g')
		{
			//if (!vecVertex.empty())
			//{
			//	cGroup* pGroup = new cGroup;
			//	pGroup->SetVertex(vecVertex);
			//	pGroup->SetMtlTex(m_mapMtlTex[sMtlName]);
			//	vecGroup.push_back(pGroup);
			//	vecVertex.clear();
			//}
		}
		else if (szTemp[0] == 'v')
		{
			if (szTemp[1] == ' ')
			{
				//v - 5.000000 - 5.000000 0.000000
				float x, y, z;
				sscanf_s(szTemp, "%*s %f %f %f", &x, &y, &z);
				vecV.push_back(D3DXVECTOR3(x, y, z));
			}
			else if (szTemp[1] == 't')
			{
				float u, v;
				sscanf_s(szTemp, "%*s %f %f %*f", &u, &v);
				vecVT.push_back(D3DXVECTOR2(u, v));
			}
			else if (szTemp[1] == 'n')
			{
				float x, y, z;
				sscanf_s(szTemp, "%*s %f %f %f", &x, &y, &z);
				vecVN.push_back(D3DXVECTOR3(x, y, z));
			}
		}
		else if (szTemp[0] == 'u')
		{
			// 사용할 메테리얼 이름 저장
			char szMtlName[1024];
			sscanf_s(szTemp, "%*s %s", szMtlName, 1024);
			sMtlName = std::string(szMtlName);
		}
		else if (szTemp[0] == 'f')
		{
			int nIndex[3][3];
			sscanf_s(szTemp, "%*s %d/%d/%d %d/%d/%d %d/%d/%d",
				&nIndex[0][0], &nIndex[0][1], &nIndex[0][2],
				&nIndex[1][0], &nIndex[1][1], &nIndex[1][2],
				&nIndex[2][0], &nIndex[2][1], &nIndex[2][2]);

			for (int i = 0; i < 3; i++)
			{
				ST_PTN_VERTEX v;
				v.p = vecV[nIndex[i][0] - 1];	// 정점
				v.t = vecVT[nIndex[i][1] - 1];	// 텍스처
				v.n = vecVN[nIndex[i][2] - 1];	// 노말

				vecVertex.push_back(v);
			}

			vecAttrBuf.push_back(m_mapMtlTex[sMtlName]->GetAttrID());
		}
	}

	fclose(fp);

	vecMtlTex.resize(m_mapMtlTex.size());
	for each(auto p in m_mapMtlTex)
	{
		vecMtlTex[p.second->GetAttrID()] = p.second;
	}

	// Mesh
	LPD3DXMESH pMesh = NULL;
	D3DXCreateMeshFVF(vecVertex.size() / 3,
		vecVertex.size(),
		D3DXMESH_MANAGED | D3DXMESH_32BIT,
		ST_PTN_VERTEX::FVF,
		g_pD3DDevice,
		&pMesh);

	ST_PTN_VERTEX* pV = NULL;
	pMesh->LockVertexBuffer(0, (void**)&pV);
	memcpy(pV, &vecVertex[0], vecVertex.size() * sizeof(ST_PTN_VERTEX));
	pMesh->UnlockVertexBuffer();

	DWORD* pI = NULL;
	pMesh->LockIndexBuffer(0, (void**)&pI);
	for (size_t i = 0; i < vecVertex.size(); i++)
	{
		pI[i] = i;
	}
	pMesh->UnlockIndexBuffer();

	DWORD* pA = NULL;
	pMesh->LockAttributeBuffer(0, &pA);
	memcpy(pA, &vecAttrBuf[0], vecAttrBuf.size() * sizeof(DWORD));
	pMesh->UnlockAttributeBuffer();

	std::vector<DWORD> vecAdj(vecVertex.size());
	pMesh->GenerateAdjacency(0.0f, &vecAdj[0]);

	pMesh->OptimizeInplace(
		D3DXMESHOPT_ATTRSORT |
		D3DXMESHOPT_COMPACT |
		D3DXMESHOPT_VERTEXCACHE,
		&vecAdj[0],
		0, 0, 0);

	//for each(auto p in m_mapMtlTex)
	//{
	//	SAFE_RELEASE(p.second);
	//}
	//m_mapMtlTex.clear();

	return pMesh;
}

void cObjLoader::LoadMtlLib(IN char * szFolder, IN char * szFile)
{
	std::string sFullPath(szFolder);
	sFullPath += (std::string("/") + std::string(szFile));

	FILE* fp;
	fopen_s(&fp, sFullPath.c_str(), "r");

	std::string sMtlName;
	char szTemp[1024];
	int nCount = 0;
	while (true)
	{
		if (feof(fp))
			break;

		fgets(szTemp, 1024, fp);
		if (szTemp[0] == '#')
		{
			continue;
		}
		else if (szTemp[0] == 'n')
		{
			char szMtlName[1024];
			sscanf_s(szTemp, "%*s %s", szMtlName, 1024);
			sMtlName = std::string(szMtlName);
			if (m_mapMtlTex.find(sMtlName) == m_mapMtlTex.end())
			{
				m_mapMtlTex[sMtlName] = new cMtlTex;
				m_mapMtlTex[sMtlName]->SetAttrID(nCount);
				nCount++;
			}
		}
		else if (szTemp[0] == 'K')
		{
			if (szTemp[1] == 'a')
			{
				float r, g, b;
				sscanf_s(szTemp, "%*s %f %f %f", &r, &g, &b);
				m_mapMtlTex[sMtlName]->GetMaterial().Ambient.r = r;
				m_mapMtlTex[sMtlName]->GetMaterial().Ambient.g = g;
				m_mapMtlTex[sMtlName]->GetMaterial().Ambient.b = b;
				m_mapMtlTex[sMtlName]->GetMaterial().Ambient.a = 1.0f;
			}
			else if (szTemp[1] == 'd')
			{
				float r, g, b;
				sscanf_s(szTemp, "%*s %f %f %f", &r, &g, &b);
				m_mapMtlTex[sMtlName]->GetMaterial().Diffuse.r = r;
				m_mapMtlTex[sMtlName]->GetMaterial().Diffuse.g = g;
				m_mapMtlTex[sMtlName]->GetMaterial().Diffuse.b = b;
				m_mapMtlTex[sMtlName]->GetMaterial().Diffuse.a = 1.0f;
			}
			else if (szTemp[1] == 's')
			{
				float r, g, b;
				sscanf_s(szTemp, "%*s %f %f %f", &r, &g, &b);
				m_mapMtlTex[sMtlName]->GetMaterial().Specular.r = r;
				m_mapMtlTex[sMtlName]->GetMaterial().Specular.g = g;
				m_mapMtlTex[sMtlName]->GetMaterial().Specular.b = b;
				m_mapMtlTex[sMtlName]->GetMaterial().Specular.a = 1.0f;
			}
		}
		else if (szTemp[0] == 'N')
		{
			float fPower;
			sscanf_s(szTemp, "%*s %f", &fPower);
			m_mapMtlTex[sMtlName]->GetMaterial().Power = fPower;
		}
		else if (szTemp[0] == 'm')
		{
			char szTextFile[1024];
			sscanf_s(szTemp, "%*s %s", &szTextFile, 1024);
			sFullPath = std::string(szFolder);
			sFullPath += (std::string("/") + std::string(szTextFile));

			LPDIRECT3DTEXTURE9 pTexture = g_pTextureManager->GetTexture(sFullPath);
			m_mapMtlTex[sMtlName]->SetTexture(pTexture);
		}
	}

	fclose(fp);

}

void cObjLoader::LoadSurface(OUT std::vector<D3DXVECTOR3>& vecSurface, IN char * szFolder, IN char * szFile, IN D3DXMATRIXA16* pMat)
{
	std::vector<D3DXVECTOR3> vecV;

	std::string sFullPath(szFolder);
	sFullPath += (std::string("/") + std::string(szFile));

	FILE* fp;
	fopen_s(&fp, sFullPath.c_str(), "r");

	char szTemp[1024];
	while (true)
	{
		if (feof(fp))
			break;

		fgets(szTemp, 1024, fp);
		if (szTemp[0] == '#')
		{
			continue;
		}
		else if (szTemp[0] == 'm')
		{
		}
		else if (szTemp[0] == 'g')
		{
		}
		else if (szTemp[0] == 'v')
		{
			if (szTemp[1] == ' ')
			{
				float x, y, z;
				sscanf_s(szTemp, "%*s %f %f %f", &x, &y, &z);
				vecV.push_back(D3DXVECTOR3(x, y, z));
			}
			else if (szTemp[1] == 't')
			{
			}
			else if (szTemp[1] == 'n')
			{
			}
		}
		else if (szTemp[0] == 'u')
		{
		}
		else if (szTemp[0] == 'f')
		{
			int nIndex[3];
			sscanf_s(szTemp, "%*s %d/%*d/%*d %d/%*d/%*d %d/%*d/%*d",
				&nIndex[0], &nIndex[1], &nIndex[2]);

			for (int i = 0; i < 3; i++)
			{
				vecSurface.push_back(vecV[nIndex[i] - 1]);
			}
		}
	}

	fclose(fp);

	if (pMat)
	{
		for (size_t i = 0; i < vecSurface.size(); i++)
		{
			D3DXVec3TransformCoord(&vecSurface[i],
				&vecSurface[i],
				pMat);
		}
	}
}
