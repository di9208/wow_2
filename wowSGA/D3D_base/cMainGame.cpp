#include "stdafx.h"
#include "cMainGame.h"
#include "cCamera.h"
#include "cGrid.h"
#include "cRay.h"
//#include "cPlayer.h"
//#include "cEnemyControl.h"
#include "cPlayer_Enemy.h"
#include "shop_TEST_CLASS.h"

cMainGame::cMainGame() :
	 m_pCamera(NULL)
	, m_pGrid(NULL)
	, m_pSprite(NULL)
	//, m_pPlayer(NULL)
	//, m_pMonster(NULL)
	, m_Player_Enemy(NULL)
	, m_shop_TEST_CLASS(NULL)
{
}


cMainGame::~cMainGame()
{
	SAFE_DELETE(m_pCamera);
	SAFE_DELETE(m_pGrid);
	//SAFE_DELETE(m_pPlayer);
	//SAFE_DELETE(m_pMonster);
	SAFE_DELETE(m_Player_Enemy);
	SAFE_DELETE(m_shop_TEST_CLASS);

	SAFE_RELEASE(m_pSprite);

	
	g_pFontManager->Destroy();
	g_pTextureManager->Destroy();
	//g_pSkinnedMeshManager->Destroy();

	g_pDeviceManager->Destroy();
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
	// light
	SetLight();

	m_pGrid = new cGrid;
	m_pGrid->Setup();

	m_pCamera = new cCamera;
	m_pCamera->Setup(NULL);

	//m_pPlayer = new cPlayer;
	//m_pPlayer->Setup();

	//m_pMonster = new cEnemyControl;
	//m_pMonster->SetUp();
	m_Player_Enemy = new cPlayer_Enemy();
	m_Player_Enemy->Setup();

	m_shop_TEST_CLASS = new shop_TEST_CLASS;
	m_shop_TEST_CLASS->Setup();

}

void cMainGame::Update()
{
	//--------------------------------------
	g_pTimeManager->Update();

	if (m_pCamera)
		m_pCamera->Update();
	//if (m_pPlayer)
	//	m_pPlayer->Update();
	//if (m_pMonster)
	//m_pMonster->Update();
	if (m_Player_Enemy)
		m_Player_Enemy->Update();
	if (m_shop_TEST_CLASS)
		m_shop_TEST_CLASS->Update();
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
	if (m_pGrid)
		m_pGrid->Render(); 
	//if (m_pPlayer)
	//	m_pPlayer->Render();
	//if (m_pMonster)
	//	m_pMonster->Render();
	if (m_Player_Enemy)
		m_Player_Enemy->Render();
	if (m_shop_TEST_CLASS)
		m_shop_TEST_CLASS->Render();


	///////////////////////////////////////////

	g_pD3DDevice->EndScene();

	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void cMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_pCamera)
		m_pCamera->WndProc(hWnd, message, wParam, lParam);
	if (m_shop_TEST_CLASS)
		m_shop_TEST_CLASS->WndProc(hWnd, message, wParam, lParam);
}