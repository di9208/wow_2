#include "stdafx.h"
#include "cScene2.h"
#include "cCamera.h"
#include "cPlayer_Enemy.h"
#include "cStage2.h"
#include "cFrustum.h"
#include "cSkyBox.h"

cScene2::cScene2()
	: m_pCamera(NULL)
	, m_Player_Enemy(NULL)
	, m_Stage2(NULL)
	, m_Frustum(NULL)
{
}


cScene2::~cScene2()
{
}

void cScene2::SetLight()
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

void cScene2::Setup()
{
	SetLight();

	

	m_pCamera = new cCamera;
	m_pCamera->Setup(NULL, 0);

	m_Stage2 = new cStage2;
	m_Stage2->Setup();

	m_Player_Enemy = new cPlayer_Enemy();
	m_Player_Enemy->Setup(m_Stage2->Getplayerpos().x, m_Stage2->Getplayerpos().y, m_Stage2->Getplayerpos().z, m_Stage2->GetMonster());
	m_Player_Enemy->setState(E_BOSS_DEATH);
	
	m_Frustum = new cFrustum();
}

void cScene2::Destroy()
{
	SAFE_DELETE(m_pCamera);
	SAFE_DELETE(m_Player_Enemy);
	SAFE_DELETE(m_Stage2);
	SAFE_DELETE(m_Frustum);
	g_pFontManager->Destroy();
	g_pTextureManager->Destroy();
}

void cScene2::Update()
{
	g_pTimeManager->Update();

	if (m_pCamera)
	{
		m_pCamera->Setup(&m_Player_Enemy->Getpos(), m_Player_Enemy->Getrot());
		m_pCamera->Update();
	}

	if (m_Player_Enemy)
		m_Player_Enemy->Update(m_Stage2, m_Stage2->GetMonster());
	
	m_Frustum->SetupVertex();
}

void cScene2::Render()
{
	if (m_Stage2)
		m_Stage2->SkyRender(m_pCamera->GetEye());

	if (m_Player_Enemy)
		m_Player_Enemy->Render();


	if (m_Stage2)
		m_Stage2->Draw(m_Frustum);
}

void cScene2::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_pCamera)
		m_pCamera->WndProc(hWnd, message, wParam, lParam);
	if (m_Player_Enemy)
		m_Player_Enemy->WndProc(hWnd, message, wParam, lParam);

}
