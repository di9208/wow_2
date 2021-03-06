#pragma once
#include "cUnit.h"
class cPlayer;
class cEnemyControl;
class cStage1;
class cFrustum;
class iMap;
class shop_TEST_CLASS;

class cPlayer_Enemy
{
	cPlayer*		m_Player;
	cEnemyControl*	m_EnemyControl;
	cStage1*		m_Stage1;
	cFrustum*		m_Frustum;

	//===================================
	bool			RichKing;
	bool			RichKingCheck;
	float			RichKingTime;
	//-------------------------
	bool			Player_Attack;
	//===================================================
	int				Enemy_NUM;

	//=-==============================
	bool			Rag;
	bool			RagCheck;
	float			RagTime;
public:
	cPlayer_Enemy();
	~cPlayer_Enemy();

	void Setup(float x, float y, float z, std::vector<tagMon> Monster);
	void Update(iMap* pMap, std::vector<tagMon> Monster);
	void Render();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void connet_shop(shop_TEST_CLASS * _connectSHOP);

	D3DXVECTOR3 Getpos();
	float Getrot();

	bool isChange();
	void setState(E_BOSS_STATE s);

};

