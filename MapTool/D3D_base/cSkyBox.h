#pragma once
#include "cCubePTN.h"

class cSkyBox:public cCubePTN
{
private:
	std::vector<ST_PTN_VERTEX> vecSky;

	LPDIRECT3DVERTEXBUFFER9 m_vb;

	LPDIRECT3DTEXTURE9 m_skytex[6];
public:
	cSkyBox();
	~cSkyBox();

	void Setup();
	void SetTexture();
	void Render(D3DXVECTOR3 camera);
};

