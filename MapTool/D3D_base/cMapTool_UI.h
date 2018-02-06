#pragma once
#include "cUIObject.h"
#include "cUIButton.h"
class cMapTool_UI :public iButtonDelegate
{
private:
	cUIObject * Root;
	std::string strings;
	
private:

	SYNTHESIZE(bool, m_save, save);
	SYNTHESIZE(bool, m_load, load);
public:
	cMapTool_UI();
	~cMapTool_UI();

	void Setup();
	void SetupRoot();
	void SetupUI();
	void SetupImage();
	void SetupFont();

	void Update();
	void Render(LPD3DXSPRITE pSprite);
	void OnClick(cUIButton* pSender);

	void TabShowHide(cUIButton * pSender);
	void Save(cUIButton * pSender);
	void Load(cUIButton * pSender);
};

