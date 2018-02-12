#include "stdafx.h"
#include "cUIImage.h"


cUIImage::cUIImage()
	: m_pTexture(NULL)
{
}


cUIImage::~cUIImage()
{
	//SAFE_RELEASE(m_pTexture);
}

void cUIImage::SetTexture(IN char * szFullPath)
{
	D3DXIMAGE_INFO stImageInfo;
	ZeroMemory(&stImageInfo, sizeof(D3DXIMAGE_INFO));
	std::string sFullPath = std::string(szFullPath);
	m_pTexture = g_pTextureManager->GetTexture(sFullPath, &stImageInfo);

	m_stSize.nWidth = stImageInfo.Width;
	m_stSize.nHeight = stImageInfo.Height;
}

void cUIImage::SetTexture(IN std ::string keyname, IN char * szFullPath)
{
	D3DXIMAGE_INFO stImageInfo;
	ZeroMemory(&stImageInfo, sizeof(D3DXIMAGE_INFO));
	std::string sFullPath = std::string(szFullPath);
	m_pTexture = g_pTextureManager->GetTexture(keyname, sFullPath, &stImageInfo);

	m_stSize.nWidth = stImageInfo.Width;
	m_stSize.nHeight = stImageInfo.Height;
}

void cUIImage::Render(LPD3DXSPRITE pSprite)
{
	if (m_isHidden) return;

	pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	pSprite->SetTransform(&m_matWorld);
	/*RECT rc;*/
	pSprite->Draw(m_pTexture,
		NULL, //&rc,
		&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(0, 0, 0),
		D3DCOLOR_ARGB(m_alpha, 255, 255, 255));

	pSprite->End();

	cUIObject::Render(pSprite);
}
