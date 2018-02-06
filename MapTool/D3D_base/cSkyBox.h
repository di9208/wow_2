#pragma once
#include "cCubePTN.h"

class cSkyBox:public cCubePTN
{
private:
	std::vector<ST_PTN_VERTEX> vecSky;

	LPDIRECT3DVERTEXBUFFER9 m_vb;

	LPDIRECT3DTEXTURE9 m_skytex[6];

	struct Tag8Way
	{
		std::string front;
		std::string back; 
		std::string left; 
		std::string right;
		std::string top; 
		std::string bottom;
	};

	SYNTHESIZE(Tag8Way, m_8Way, 8Way);
public:
	cSkyBox();
	~cSkyBox();

	void Setup();
	void Update();
	void SetUV();
	void SetTexture(std::string t);
	void Render(D3DXVECTOR3 camera);

	void setTex(LPDIRECT3DTEXTURE9 te, int i) { m_skytex[i] = te; }
};

