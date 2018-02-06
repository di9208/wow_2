#pragma once
#include "cGameManager.h"
#include "cUIObject.h"

class loading;

class cMainLoading:public cGameManager
{
private:
	cUIObject * Root;
	LPD3DXSPRITE m_pSprite;
	loading * m_loading;
public:
	cMainLoading();
	~cMainLoading();

	virtual void Setup();
	virtual void Destroy();
	virtual void Update();
	virtual void Render();

	void Loading();

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

