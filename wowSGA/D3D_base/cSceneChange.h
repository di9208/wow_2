#pragma once
#include "cGameManager.h"
#include "cUIObject.h"
class cSceneChange:public cGameManager
{
private:
	cUIObject * Root;
	LPD3DXSPRITE m_sprite;
	int count;
	int alpha;
public:
	cSceneChange();
	~cSceneChange();

	void Setup();
	void Destroy();
	void Update();
	void Render();

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

};

