#pragma once

class wordManager
{
private:
	LPD3DXFONT	m_pFont;
public:
	wordManager();
	~wordManager();

	void SetFont();
	void Render(char * write_text, int x, int y, int weigth, int height);
};
