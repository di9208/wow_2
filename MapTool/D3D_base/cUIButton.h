#pragma once
#include "cUIObject.h"

class cUIButton;

class iButtonDelegate
{
public:
	virtual void OnClick(cUIButton* pSender) = 0;
};

class cUIButton : public cUIObject
{
protected:
	enum eButtonState
	{
		BTN_DOWN,
		BTN_OVER,
		BTN_UP,
		BTN_NUM
	};

	eButtonState		m_eButtonState;
	LPDIRECT3DTEXTURE9	m_pTextures[BTN_NUM];

	SYNTHESIZE(iButtonDelegate*, m_pDelegate, Delegate);
	SYNTHESIZE(bool, m_isclick, isClick);
public:
	cUIButton();
	virtual ~cUIButton();

	void SetTexture(IN char* szUp, IN char* szOver, IN char* szDown);
	void SetTexture(IN std::string keyname, IN char* szUp, IN char* szOver, IN char* szDown);

	virtual void Update();
	virtual void Render(LPD3DXSPRITE pSprite);
};

