#include "stdafx.h"
#include "cMapToolObject.h"


cMapToolObject::cMapToolObject()
{
	D3DXMatrixIdentity(&s);
}


cMapToolObject::~cMapToolObject()
{
	//SAFE_DELETE(m_obj);
	
}

void cMapToolObject::Setup(std::string keyname)
{
	m_mesh = g_pSkinnedMeshManager->Find(keyname);

}

void cMapToolObject::SetObject(char * folder, char* file)
{
	m_mesh->Setup(folder, file);
	/*m_obj->Load(m_vecGroup,folder,file);
	m_vecGroups.push_back(m_vecGroup);*/
}

void cMapToolObject::Update()
{
}

void cMapToolObject::Render()
{
	g_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHAREF, 0x00000088);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	/*for each(auto p in m_vecGroups)
	{
		for each(auto pp in p)
		{
			pp->Render();
		}
	}*/
	D3DXMATRIXA16 matW;
	matW = m * T;
	m_mesh->Render(NULL, &matW);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, 0);
}
