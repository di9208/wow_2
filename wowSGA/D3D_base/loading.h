#pragma once
//#include "GameNode.h"

enum LOAD_KIND
{
	LOAD_KIND_IMAGE,
	LOAD_KIND_SKINNDEDMESH,
	LOAD_KIND_SOUND,
	LOAD_KIND_END
};
struct tagresource
{
	std::string keyname;
	char* folder;
	char* filename;
};

class loaditem
{
private:
	LOAD_KIND _kind;
	tagresource _resource;
public:
	loaditem();
	~loaditem();

	void initforSkinnedMesh(std::string  Name, IN char * szFolder, IN char * szFile);
	LOAD_KIND getloadkind() { return _kind; }

	tagresource getimageresource() { return _resource; }


};
class loading
{
private:
	typedef std ::vector<loaditem*> arrloaditem;

	arrloaditem _vloaditem;

	//image* _backGround;
	int _currentgauge;

public:
	loading():_currentgauge(0){};
	~loading() {};

	void Setup();
	void update();
	void render();
	void Destroy();
	
	void loadingSkinnedMesh(std::string  Name, IN char * szFolder, IN char * szFile);
	bool loadingdone();

	std ::vector<loaditem*> getloaditem() { return _vloaditem; }

	int getloaditemSize() { return _currentgauge; }
};

