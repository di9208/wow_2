#pragma once
#include "cObjLoader.h"
#include "cGroup.h"
#include "cSkinnedMesh.h"
class cMapToolObject
{
private:
	typedef std::vector<cGroup*> vecGroup;
	vecGroup m_vecGroup;
	std::vector<vecGroup> m_vecGroups;

	cSkinnedMesh* m_mesh;
	cObjLoader* m_obj;
	
	SYNTHESIZE_REF(D3DXMATRIXA16, T, tt);
	SYNTHESIZE_REF(D3DXMATRIXA16, m, mm);
	SYNTHESIZE_REF(D3DXMATRIXA16, s, ss);
public:
	cMapToolObject();
	~cMapToolObject();

	void Setup(std::string keyname);
	void SetObject(char * folder, char* file);
	void Update();
	void Render();
};

