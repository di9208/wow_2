#pragma once
#include "cScene1.h"
#include "cScene2.h"
#include "cSceneChange.h"
#include "cMainLoading.h"

class cMainGame
{
private:

public:
	cMainGame();
	~cMainGame();

	void Setup();
	void Destroy();
	void Update();
	void Render();

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

