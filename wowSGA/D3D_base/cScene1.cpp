#include "stdafx.h"
#include "cScene1.h"
#include "cCamera.h"
#include "cGrid.h"
#include "cPlayer_Enemy.h"
#include "shop_TEST_CLASS.h"
#include "cStage1.h"
#include "cFrustum.h"

cScene1::cScene1()
	: m_pCamera(NULL)
	, m_pGrid(NULL)
	, m_Player_Enemy(NULL)
	, m_shop_TEST_CLASS(NULL)
	, m_Stage1(NULL)
	, m_Frustum(NULL)
{
}


cScene1::~cScene1()
{
}

void cScene1::SetLight()
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
}

void cScene1::Setup()
{
	SetLight();

	m_pGrid = new cGrid;
	m_pGrid->Setup();

	m_pCamera = new cCamera;
	m_pCamera->Setup(NULL);

	m_Player_Enemy = new cPlayer_Enemy();
	m_Player_Enemy->Setup();

	m_shop_TEST_CLASS = new shop_TEST_CLASS;
	m_shop_TEST_CLASS->Setup();

	m_Stage1 = new cStage1();
	m_Stage1->Setup();

	m_Frustum = new cFrustum();
}

void cScene1::Destroy()
{
	SAFE_DELETE(m_pCamera);
	SAFE_DELETE(m_pGrid);
	SAFE_DELETE(m_Player_Enemy);
	SAFE_DELETE(m_shop_TEST_CLASS);
	SAFE_DELETE(m_Stage1);
	SAFE_DELETE(m_Frustum);
	g_pFontManager->Destroy();
	g_pTextureManager->Destroy();
	g_pDeviceManager->Destroy();
}

void cScene1::Update()
{
	g_pTimeManager->Update();

	if (m_pCamera)
		m_pCamera->Update();

	if (m_Player_Enemy)
		m_Player_Enemy->Update(m_Stage1);
		m_Player_Enemy->connet_shop(m_shop_TEST_CLASS);

	if (m_shop_TEST_CLASS)
		m_shop_TEST_CLASS->Update();

	m_Frustum->SetupVertex();
}

void cScene1::Render()
{
	// TODO : ±×¸®±â
	if (m_pGrid)
		m_pGrid->Render();

	if (m_Player_Enemy)
		m_Player_Enemy->Render();


	if (m_shop_TEST_CLASS)
		m_shop_TEST_CLASS->Render();

	if (m_Stage1)
		m_Stage1->Draw(m_Frustum);

	///////////////////////////////////////////
}

void cScene1::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_pCamera)
		m_pCamera->WndProc(hWnd, message, wParam, lParam);
	if (m_shop_TEST_CLASS)
		m_shop_TEST_CLASS->WndProc(hWnd, message, wParam, lParam);
	if (m_Player_Enemy)
		m_Player_Enemy->WndProc(hWnd, message, wParam, lParam);

}
