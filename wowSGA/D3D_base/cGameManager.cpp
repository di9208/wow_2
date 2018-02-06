#include "stdafx.h"
#include "cGameManager.h"


cGameManager::cGameManager()
{
}


cGameManager::~cGameManager()
{
}

void cGameManager::Setup()
{
}

void cGameManager::Destroy()
{
	g_pSkinnedMeshManager->Destroy();
	g_pFontManager->Destroy();
	g_pTextureManager->Destroy();
	g_pDeviceManager->Destroy();
}

void cGameManager::Update()
{
}

void cGameManager::Render()
{
}

void cGameManager::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
}
