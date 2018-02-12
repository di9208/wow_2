#pragma once
#include "iMap.h"
#include "cUnit.h"
#include "cSkyBox.h"

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
	
	cSkyBox * m_skybox;
	SYNTHESIZE(D3DXVECTOR3, Playerpos, playerpos);
	SYNTHESIZE(D3DXVECTOR3, NPCpos, npcpos);
	SYNTHESIZE_REF(std::vector<tagMon>, m_vecMonster, Monster);
	SYNTHESIZE_REF(std::vector<tagobject>, m_vecObjec, Object);
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
	void SkyRender(D3DXVECTOR3 camera);

	bool GetHeight(IN float x, OUT float& y, IN float z);
};

