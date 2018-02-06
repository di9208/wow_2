#pragma once
class cGameManager
{
public:
	cGameManager();
	virtual ~cGameManager();
		    

	virtual void Setup();
	virtual void Destroy();
	virtual void Update();
	virtual void Render();

	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};	
