#pragma once
#include "cUIButton.h"
#include "cUIText.h"
#include "cRay.h"
#include "ZQuadTree.h"

class cFrustum;
class cUIObject;
class cQuadTree;
class cMapTool_UI;

class cMaptool
{
private:
	cUIObject * Heightmap;
	cQuadTree * m_QuadTree;

private:
	int _col ; //Column
	int _row ; //Row
	
private:
	cRay r; //Ray
	D3DXVECTOR3 d1;							//Mouse Position

private:
	std::vector<ST_PC_VERTEX> vecCircle;	//Circle Vertex
	float m_radius;							//Circle Radius
	std::vector<ST_PC_VERTEX> ve;			//Clone Circle Vertex 

private:
	LPDIRECT3DVERTEXBUFFER9 m_vb;			//Vertex Buffer
	LPDIRECT3DINDEXBUFFER9 m_ib;			//Index Buffer
	ST_PTN_VERTEX * Mapvertex;				//Tile Vectex
	std::vector<int> vecindex;				//Clone Index 
	int m_polygon;							//Current Culled Polygon

	LPDIRECT3DTEXTURE9 m_tex;
	D3DMATERIAL9 m_mt;
private:
	std::vector<int> vecCulIndex;			//No More using This Vector

private:
	cMapTool_UI * m_UI;

public:
	cMaptool();
	~cMaptool();

	void Setup(); 
	void Setupmap(); //Setup Tilemap
	void SetupQuad(); //Setup QuadTree
	void SetupCircle(); 
	void SetupControl();

	void Update();
	void UpdateCircle(); //Update Circle Height
	
	void Render(LPD3DXSPRITE pSprite);
	void RenderMap(); //Tilemap Render
	void RenderCircle(); 

	void CheckVertex(tagpoint p); //No More Using This Function
	void Draw(cFrustum *f); // Draw All



	bool GetCircleHeight(float x, float &y, float z); 
	void SetNormal();
	void SetMaterial();
	void SAVE();
	void LOAD();

};

