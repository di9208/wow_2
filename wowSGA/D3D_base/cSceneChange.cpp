#include "stdafx.h"
#include "cSceneChange.h"
#include "cUIImage.h"

cSceneChange::cSceneChange()
	:alpha(255)
	, count(0)
{
}


cSceneChange::~cSceneChange()
{
}

void cSceneChange::Setup()
{
	D3DXCreateSprite(g_pD3DDevice, &m_sprite);

	cUIImage* White = new cUIImage;
	White->SetTexture("UI/White.png");
	White->Setalpha(alpha);
	Root = White;

}

void cSceneChange::Destroy()
{
	Root->Destroy();
}

void cSceneChange::Update()
{
	count++;
	if (count >= 200)
	{
		alpha--;
	}
	Root->Update();
	Root->Setalpha(alpha);

	if (alpha == 0)
	{
		g_pSceneManager->changescene("Scene2");
	}
}

void cSceneChange::Render()
{
	Root->Render(m_sprite);
}

void cSceneChange::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
}
