#include "stdafx.h"
#include "cTesting.h"
#include "cCamera.h"
#include "cGrid.h"
#include "cRay.h"
#include "cMaptool.h"
#include "cFrustum.h"
#include "cCube.h"
#include "cSkinnedMesh.h"
#include "cSkyBox.h"
#include "cSkyBox1.h"


cTesting::cTesting()
	: m_pCamera(NULL)
	, m_pGrid(NULL)
	, m_pSprite(NULL)
{
}


cTesting::~cTesting()
{
	SAFE_DELETE(m_pCamera);
	SAFE_DELETE(m_pGrid);
	SAFE_DELETE(m_maptool);
	SAFE_RELEASE(m_pSprite);

}

void cTesting::SetLight()
{
	D3DLIGHT9	stLight;
	ZeroMemory(&stLight, sizeof(D3DLIGHT9));
	stLight.Type = D3DLIGHT_DIRECTIONAL;
	//stLight.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	stLight.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	stLight.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	D3DXVECTOR3		vDir(0.0f, -1.0f, 0.0f);
	D3DXVec3Normalize(&vDir, &vDir);
	stLight.Direction = vDir;
	g_pD3DDevice->SetLight(0, &stLight);
	g_pD3DDevice->LightEnable(0, true);
	//g_pD3DDevice->SetRenderState(D3DRS_AMBIENT, 0x00202020);
}

void cTesting::Setup()
{
	SetLight();

	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);
	m_pGrid = new cGrid;
	m_pGrid->Setup();


	m_maptool = new cMaptool;
	m_maptool->Setup();


	m_pCamera = new cCamera;
	m_pCamera->Setup(NULL);

	m_cube = new cCube;
	m_cube->Setup();

	frustum = new cFrustum;


	m_sky = new cSkyBox;
	m_sky->Setup();

}

void cTesting::Destroy()
{
}

void cTesting::Update()
{
	g_pTimeManager->Update();

	if (m_pCamera)
		m_pCamera->Update();


	if (m_maptool)
		m_maptool->Update();

	if (frustum)
		frustum->SetupVertex();

}

void cTesting::Render()
{
	g_pD3DDevice->Clear(NULL,
		NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(0, 0, 0),
		1.0f, 0);

	g_pD3DDevice->BeginScene();


	//g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);

	/*if (g_pKeyManager->isToggleKey('Q'))
		m_sky->Render(m_pCamera->GetEye());*/


	/*if (m_pGrid)
		m_pGrid->Render();*/
	
	if (m_maptool)
	{
		m_maptool->Draw(frustum);
		m_maptool->Render(m_pSprite, m_pCamera->GetEye());
	}
	
	
	//D3DXMATRIXA16 matW, matS;
	//D3DXMatrixScaling(&matS, 10.0f, 10.0f, 10.0f);
	//D3DXMatrixTranslation(&matW, 20, 0, 0);
	//g_pD3DDevice->SetTransform(D3DTS_WORLD, &(matS*matW));
	
	/*if(frustum->isInside(&D3DXVECTOR3(20,0,0),5))
	m_cube->Render();*/

	
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////
	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void cTesting::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_pCamera)
		m_pCamera->WndProc(hWnd, message, wParam, lParam);
}
