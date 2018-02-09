#pragma once
#include "cUIObject.h"
#include "cUIButton.h"
class cMapTool_UI :public iButtonDelegate
{
private:
	cUIObject * Root;		//Tab1
	cUIObject * Root2;		//Tab2
	cUIObject * Root3;		//Tab3
	std::string strings;
	
private:

	bool m_tab1;
	bool m_tab2;
	bool m_tab3;

	SYNTHESIZE(bool, m_save, save);
	SYNTHESIZE(bool, m_load, load);

	SYNTHESIZE(bool, m_upthow, upthow);
	SYNTHESIZE(bool, m_downthow, downthow);
	SYNTHESIZE(bool, m_flat, flat);
	SYNTHESIZE(bool, m_skybox, skybox);
	SYNTHESIZE(bool, m_terrain, terrain);
	SYNTHESIZE(bool, m_object, object);
	SYNTHESIZE(bool, m_player, player);
	///
	SYNTHESIZE(bool, m_spider, spider);
	SYNTHESIZE(bool, m_druid, druid);
	SYNTHESIZE(bool, m_worg, worg);
	SYNTHESIZE(bool, m_lichking, lichking);
	SYNTHESIZE(bool, m_rag, rag);
	SYNTHESIZE(bool, m_tau, tau);
	SYNTHESIZE(bool, m_tree, tree);
public:
	cMapTool_UI();
	~cMapTool_UI();

	void Setup();
	void SetupRoot();
	void SetupUI();
	void SetupImage();
	void SetupFont();

	void SetupTab1();
	void SetupTab2();
	void SetupTab3();

	void Update();
	void Render(LPD3DXSPRITE pSprite);
	void OnClick(cUIButton* pSender);

	void TabShowHide(cUIButton * pSender);
	void Save(cUIButton * pSender);
	void Load(cUIButton * pSender);
	void Landscape(cUIButton * pSender);
	void SkyBoxT(cUIButton * pSender);
	void Terrain(cUIButton * pSender);
	void Object(cUIButton* pSender);
	void Unit(cUIButton* pSender);


	void Setbool(bool& bf);

};

