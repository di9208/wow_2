#include "stdafx.h"
#include "cMainGame.h"
#include "cCamera.h"
#include "cGrid.h"
#include "cRay.h"
#include "cMaptool.h"
#include "cFrustum.h"
#include "cCube.h"
#include "cSkinnedMesh.h"
#include "cTesting.h"


cMainGame::cMainGame() 
	/* m_pCamera(NULL)
	, m_pGrid(NULL)
	, m_pSprite(NULL)*/
{
}


cMainGame::~cMainGame()
{
	/*SAFE_DELETE(m_pCamera);
	SAFE_DELETE(m_pGrid);
	SAFE_DELETE(m_maptool);
	SAFE_RELEASE(m_pSprite);*/

	/*g_pSceneManager->Destroy();
	g_pSkinnedMeshManager->Destroy();
	g_pFontManager->Destroy();
	g_pTextureManager->Destroy();
	g_pDeviceManager->Destroy();*/
}

void cMainGame::SetLight()
{
	D3DLIGHT9	stLight;
	ZeroMemory(&stLight, sizeof(D3DLIGHT9));
	stLight.Type = D3DLIGHT_DIRECTIONAL;
	stLight.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	stLight.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	stLight.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	D3DXVECTOR3		vDir(1.0f, -1.0f, 1.0f);
	D3DXVec3Normalize(&vDir, &vDir);
	stLight.Direction = vDir;
	g_pD3DDevice->SetLight(0, &stLight);
	g_pD3DDevice->LightEnable(0, true);
	//g_pD3DDevice->SetRenderState(D3DRS_SPECULARENABLE, true);

	//D3DLIGHT9	stLightPoint;
	//ZeroMemory(&stLightPoint, sizeof(D3DLIGHT9));
	//stLightPoint.Type = D3DLIGHT_POINT;
	//stLightPoint.Ambient = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
	//stLightPoint.Diffuse = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
	//stLightPoint.Specular = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);

	///*D3DXVECTOR3		vDir(1.0f, -1.0f, 1.0f);
	//D3DXVec3Normalize(&vDir, &vDir);
	//stLightPoint.Direction = vDir;*/

	//stLightPoint.Position = D3DXVECTOR3(0, 5, 0);
	//stLightPoint.Range = 8.0f;

	//g_pD3DDevice->SetLight(1, &stLightPoint);
	//g_pD3DDevice->LightEnable(1, true);
	//g_pD3DDevice->SetRenderState(D3DRS_SPECULARENABLE, true);
}

void cMainGame::Setup()
{

	g_pSceneManager->addscene("ss", new cMainLoading);
	g_pSceneManager->addscene("Testing", new cTesting);
	g_pSceneManager->changescene("ss");
	// light
	/*SetLight();
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
	
	g_pSkinnedMeshManager->Setup("z","Zealot", "zealot.X");*/
	
}

void cMainGame::Destroy()
{
}

void cMainGame::Update()
{
	g_pSceneManager->Update();
	//--------------------------------------
	/*g_pTimeManager->Update();

	if (m_pCamera)
		m_pCamera->Update();
	
	
	if (m_maptool)
		m_maptool->Update();
	
	if(frustum)
		frustum->SetupVertex();*/

}

void cMainGame::Render()
{
	g_pD3DDevice->Clear(NULL,
		NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(0, 0, 0),
		1.0f, 0);

	g_pD3DDevice->BeginScene();

	// TODO : ±×¸®±â
	/*if (m_pGrid)
		m_pGrid->Render();

	if (m_maptool)
	{
		m_maptool->Draw(frustum);
		m_maptool->Render(m_pSprite);
	}
	D3DXMATRIXA16 matW, matS;
	D3DXMatrixScaling(&matS, 10.0f, 10.0f, 10.0f);
	D3DXMatrixTranslation(&matW, 20, 0, 0);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &(matS*matW));
	if(frustum->isInside(&D3DXVECTOR3(20,0,0),5))
		m_cube->Render();*/

	g_pSceneManager->Render();

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////

	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void cMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	
	g_pSceneManager->WndProc(hWnd, message, wParam, lParam);
	/*std::string strings;
	TCHAR str[1024] = TEXT("");

	switch (message)
	{
		case WM_LBUTTONDOWN:
		
		
			OPENFILENAME ope;
			memset(&ope, 0, sizeof(OPENFILENAME));
			ope.lStructSize = sizeof(OPENFILENAME);
			ope.hwndOwner = GetConsoleWindow();
			ope.lpstrFilter = TEXT("All Files(*.*)\0*.*\0");
			ope.lpstrFile = str;
			ope.nMaxFile = 1024;
			ope.lpstrDefExt = TEXT("txt");
			GetSaveFileName(&ope);

			strings = std::string(ope.lpstrFile);
			break;
	}*/
	
}
