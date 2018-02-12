#include "stdafx.h"
#include "loading.h"



void loading::Setup()
{
}

void loading::update()
{
}

void loading::render()
{

}

void loading::Destroy()
{
}

void loading::loadingSkinnedMesh(char * Name, IN char * szFolder, IN char * szFile)
{
	loaditem* item = new loaditem;
	item->initforSkinnedMesh(Name, szFolder, szFile);
	_vloaditem.push_back(item);
}

bool loading::loadingdone()
{
	if (_currentgauge >= _vloaditem.size())
	{
		return true;
	}
	loaditem* item = _vloaditem[_currentgauge];

	tagresource img = item->getimageresource();

	switch (item->getloadkind())
	{
	case LOAD_KIND_SKINNDEDMESH:
	{
		std::string key = std::string(img.keyname);
		g_pSkinnedMeshManager->Setup(key, img.folder, img.filename);
		
	}
	break;
	}
	_currentgauge++;
	return false;
}

loaditem::loaditem()
{
}

loaditem::~loaditem()
{
}

void loaditem::initforSkinnedMesh(IN char * Name, IN char * szFolder, IN char * szFile)
{
	_kind = LOAD_KIND_SKINNDEDMESH;
	ZeroMemory(&_resource, sizeof(tagresource));

	_resource.keyname = Name;
	_resource.folder = szFolder;
	_resource.filename = szFile;
}
