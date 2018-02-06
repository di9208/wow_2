#include "stdafx.h"
#include "cSceneManager.h"
#include "cGameManager.h"

cSceneManager::cSceneManager()
{
}

cGameManager* cSceneManager::_currentscene = nullptr;

cSceneManager::~cSceneManager()
{
}

void cSceneManager::Setup()
{
}

void cSceneManager::Destroy()
{
	iscenelist iter = _scenelist.begin();
	for (iter; iter != _scenelist.end();)
	{
		if (iter->second != NULL)
		{
			if (iter->second == _currentscene) iter->second->Destroy();
			SAFE_DELETE(iter->second);
			iter = _scenelist.erase(iter);
		}
		else
		{
			iter++;
		}
	}
	_scenelist.clear();
}

void cSceneManager::Update()
{
	if (_currentscene) _currentscene->Update();
}

void cSceneManager::Render()
{
	if (_currentscene) _currentscene->Render();
}

void cSceneManager::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (_currentscene) _currentscene->WndProc(hWnd, message, wParam, lParam);
}

cGameManager * cSceneManager::addscene(std::string sceneName, cGameManager * scene)
{
	if (!scene) return nullptr;
	_scenelist.insert(make_pair(sceneName, scene));
	return nullptr;
}

bool cSceneManager::changescene(std::string sceneName)
{
	iscenelist find = _scenelist.find(sceneName);

	if (find == _scenelist.end()) return false;

	if (find->second == _currentscene) return false;

	find->second->Setup();
	{
		if (_currentscene) _currentscene->Destroy();
		_currentscene = find->second;
		return true;
	}
	return false;
}
