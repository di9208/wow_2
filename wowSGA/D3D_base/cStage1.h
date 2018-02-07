#pragma once
#include "iMap.h"
class cQuadTree;
class cFrustum;


class cStage1:public iMap
{

private:
	ST_PTN_VERTEX* MapVertex;
	LPDIRECT3DVERTEXBUFFER9 m_vb;
	LPDIRECT3DINDEXBUFFER9 m_ib;

	int m_col;
	int m_row;
	int m_Polygon;

	std::vector<int> m_vecindex;
	

private:
	cQuadTree * m_QuadTree;
	LPDIRECT3DTEXTURE9			m_pTexture;
public:
	cStage1();
	~cStage1();

	void Setup();
	void SetMap();
	void SetQuad();
	void SetMaterial();
	void Draw(cFrustum* f);
	void Render();

	bool GetHeight(IN float x, OUT float& y, IN float z);
};

