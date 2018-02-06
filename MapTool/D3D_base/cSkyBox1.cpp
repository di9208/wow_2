#include "stdafx.h"
#include "cSkyBox1.h"
#include "cSkinnedMesh.h"

cSkyBox1::cSkyBox1()
{
}


cSkyBox1::~cSkyBox1()
{
}

void cSkyBox1::Setup()
{
	g_pSkinnedMeshManager->Setup("sky1","SkyBox", "sky3.X");
	m_skybox = g_pSkinnedMeshManager->Find("sky1");
}

void cSkyBox1::Update()
{
	m_skybox->Update();
}

void cSkyBox1::Render(D3DXVECTOR3 camera)
{
	D3DXMATRIXA16 matW,matR,matS;
	D3DXMatrixTranslation(&matS, camera.x, camera.y, camera.z);
	D3DXMatrixRotationX(&matR, D3DX_PI / 2.0f);
	//g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
	g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, false);
	matW = matS;
	m_skybox->Render(NULL, &matW);

	//g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, true);

}
