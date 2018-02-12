#pragma once


#define g_pSkinnedMeshManager cSkinnedMeshManager::GetInstance()

#include "cSkinnedMesh.h"
class cSkinnedMeshManager
{
private:
	SINGLETONE(cSkinnedMeshManager);
private:
	std::map<std::string, cSkinnedMesh*> m_mapSkinnedMesh;
public:
	/*cSkinnedMeshManager();
	~cSkinnedMeshManager();*/

	void Setup(std::string  Name, IN char* szFolder, IN char* szFile);
	cSkinnedMesh* Find(std::string Name);

	void Destroy();
};

