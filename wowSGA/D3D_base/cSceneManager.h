#pragma once
#define g_pSceneManager cSceneManager::GetInstance()
class cGameManager;

class cSceneManager
{
private:
	SINGLETONE(cSceneManager);

private:
	typedef std::map<std::string, cGameManager*> scenelist;
	typedef std::map<std::string, cGameManager*>::iterator iscenelist;

	static cGameManager* _currentscene;
	scenelist _scenelist;
public:
	virtual void Setup();
	virtual void Destroy();
	virtual void Update();
	virtual void Render();

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	cGameManager* addscene(std::string sceneName, cGameManager* scene);

	bool changescene(std::string sceneName);

};

