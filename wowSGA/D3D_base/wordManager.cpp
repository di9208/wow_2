#include "stdafx.h"
#include "wordManager.h"


wordManager::wordManager()
	: m_pFont(NULL)
{
}


wordManager::~wordManager()
{
	SAFE_RELEASE(m_pFont);
}

void wordManager::SetFont()
{
	D3DXFONT_DESC stFD;
	ZeroMemory(&stFD, sizeof(D3DXFONT_DESC));
	stFD.Height = 25;
	stFD.Width = 10;
	stFD.Weight = FW_MEDIUM;
	stFD.Italic = false;
	stFD.CharSet = DEFAULT_CHARSET;
	stFD.OutputPrecision = OUT_DEFAULT_PRECIS;
	stFD.PitchAndFamily = FF_DONTCARE;

	strcpy_s(stFD.FaceName, "±¼¸²Ã¼");

	//AddFontResource("font/umberto.ttf");
	//strcpy_s(stFD.FaceName, "umberto");

	D3DXCreateFontIndirect(g_pD3DDevice, &stFD, &m_pFont);

}

void wordManager::Render(char * write_text,int x,int y,int weigth,int height)
{
	if (m_pFont)
	{
		std::string sText(write_text);
		RECT rc;
		SetRect(&rc, x, y, x + weigth, y + height);

		m_pFont->DrawText(NULL,
			sText.c_str(),
			sText.length(),
			&rc,
			DT_LEFT | DT_TOP | DT_NOCLIP,
			D3DCOLOR_XRGB(255, 255, 0));
	}
}