#pragma once
#include "cUIButton.h"
#include "cUIText.h"
#include "cRay.h"
#include "cSkinnedMesh.h"
#include "cObjLoader.h"
#include "cGroup.h"
#include "cMapToolObject.h"
#include "cUnit.h"

class cFrustum;
class cUIObject;
class cQuadTree;
class cMapTool_UI;
class cSkyBox;

class cMaptool
{
private:
	cUIObject * Heightmap;
	cQuadTree * m_QuadTree;
	cSkyBox* m_SkyBox;
	std::vector<cMapToolObject*> m_vecOB;
	cMapToolObject* m_player;
	bool m_isPlayerExist;
	bool m_playerTranslation;
	bool m_monsterTranslation;
	bool m_objectTranslation;

	cMapToolObject* m_NPC;
	bool m_isNPCExist;
	bool m_NPCTranslation;
	///bool m_monsterTranslation;

	D3DXVECTOR3 Playerpos;
	D3DXVECTOR3 NPCpos;
	POINT p;
	struct tagMonster
	{
		std::string name;
		
		int number;
		bool Translation;
		cMapToolObject* monster;
		ST_SPHERE sphere;
		ENUMMONSTER kind;
		tagMonster()
			: number(0)
			,Translation(false)
			, monster(nullptr)
		{
		}
	};
	struct tagObject
	{
		std::string name;

		int number;
		bool Translation;
		cMapToolObject* object;
		ST_SPHERE sphere;
		tagObject()
			: number(0)
			, Translation(false)
			, object(nullptr)
		{
		}
	};
	bool m_isMonsterExist;
	std::vector<tagMonster> m_vecMonster;
	std::vector<tagObject> m_vecObject;
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

	LPDIRECT3DTEXTURE9 m_tex1;
	std::string m_stex;
	D3DMATERIAL9 m_mt;
	

	float m_LandControl;
	float m_UpDown;
private:
	std::vector<int> vecCulIndex;			//No More using This Vector

private:
	cMapTool_UI * m_UI;

private:
	std::vector<cGroup*> vecGroup;
	cObjLoader* Tree;
public:
	cMaptool();
	~cMaptool();

	void Setup(); 
	void Setupmap(); //Setup Tilemap
	void SetupQuad(); //Setup QuadTree
	void SetupCircle(); 
	void SetupControl();
	void SetTexture(std::string t);

	void Update();
	void UpdateCircle(); //Update Circle Height
	
	void Render(LPD3DXSPRITE pSprite, D3DXVECTOR3 camera);
	void RenderMap(); //Tilemap Render
	void RenderCircle(); 

	void CheckVertex(tagpoint p); //No More Using This Function
	void Draw(cFrustum *f); // Draw All



	bool GetCircleHeight(float x, float &y, float z); 
	void SetNormal();
	void SetMaterial();
	void SAVE();
	void LOAD();
	void LandScaping();
	void SkyBoxT();
	void Terrain();
	void Object();
	void Unit();

	void loadMonster();

	void PlayerRender();
	void NPCRender();
	void MonsterRender();
	void ObjectRender();
};

