#include "stdafx.h"
#include "cMainLoading.h"
#include "cUIObject.h"
#include "cUIImage.h"
#include "loading.h"


cMainLoading::cMainLoading()
{
}

cMainLoading::~cMainLoading()
{
	Destroy();
}

void cMainLoading::Setup()
{
	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);

	m_loading = new loading;

	cUIImage * main = new cUIImage;
	main->SetTexture("UI/LOADSCREENNORTHREND.png");
	main->SetPos(D3DXVECTOR3(0, 0, 1));
	Root = main;

	cUIImage * loadingbar = new cUIImage;
	loadingbar->SetTexture("UI/Loading-BarFill.png");
	loadingbar->SetPos(D3DXVECTOR3(352, 735, 0));
	Root->AddChild(loadingbar);

	cUIImage * loading = new cUIImage;
	loading->SetTexture("UI/Loading-BarBorder.png");
	loading->SetPos(D3DXVECTOR3(300, 720, 0));
	Root->AddChild(loading);

	
	
	this->Loading();
}

void cMainLoading::Destroy()
{
	SAFE_DELETE(m_loading);
	SAFE_RELEASE(m_pSprite);
	Root->Destroy();
}

void cMainLoading::Update()
{
	g_pTimeManager->Update();
	Root->Update();
	static float j = 0.0f;
	 j += g_pTimeManager->GetEllapsedTime()*4.5f;
	Root->GetChild()[0]->SetScale(D3DXVECTOR3(j,1,0));
	
	m_loading->update();
	if (m_loading->loadingdone())
	{
		if(j>=1)
		g_pSceneManager->changescene("Testing");
	}
}

void cMainLoading::Render()
{
	Root->Render(m_pSprite);
}

void cMainLoading::Loading()
{

}

void cMainLoading::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

}



