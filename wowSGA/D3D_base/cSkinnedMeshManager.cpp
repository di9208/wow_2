#include "stdafx.h"
#include "cSkinnedMeshManager.h"


cSkinnedMeshManager::cSkinnedMeshManager()
{
}


cSkinnedMeshManager::~cSkinnedMeshManager()
{

}

void cSkinnedMeshManager::Setup(std::string  Name, IN char * szFolder, IN char * szFile)
{
	if (m_mapSkinnedMesh.find(Name) == m_mapSkinnedMesh.end())
	{
		m_mapSkinnedMesh[Name] = new cSkinnedMesh();
		m_mapSkinnedMesh[Name]->Setup(szFolder, szFile);

	}
}

cSkinnedMesh* cSkinnedMeshManager::Find(std::string Name)
{
	if (m_mapSkinnedMesh.find(Name) != m_mapSkinnedMesh.end())
	{
		return m_mapSkinnedMesh[Name];
	}
	else
		return nullptr;
}

void cSkinnedMeshManager::Destroy()
{
	for each(auto p in m_mapSkinnedMesh)
	{
		SAFE_DELETE(p.second);
	}
	m_mapSkinnedMesh.clear();
}
