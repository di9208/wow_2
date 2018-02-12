#pragma once
#include "cUIObject.h"

class cUIImage : public cUIObject
{
protected:
	LPDIRECT3DTEXTURE9	m_pTexture;
public:
	cUIImage();
	virtual ~cUIImage();

	void SetTexture(IN char* szFullPath);
	void SetTexture(IN std::string keyname, IN char * szFullPath);
	virtual void Render(LPD3DXSPRITE pSprite);
};

