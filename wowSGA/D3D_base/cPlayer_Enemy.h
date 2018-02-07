#pragma once
class cPlayer;
class cEnemyControl;
class cStage1;
class cFrustum;
class iMap;
class cPlayer_Enemy
{
	cPlayer*		m_Player;
	cEnemyControl*	m_EnemyControl;
	cStage1*		m_Stage1;
	cFrustum*		m_Frustum;
public:
	cPlayer_Enemy();
	~cPlayer_Enemy();

	void Setup();
	void Update(iMap* pMap);
	void Render();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

};

