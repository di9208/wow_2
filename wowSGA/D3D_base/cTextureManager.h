#pragma once
#define g_pTextureManager cTextureManager::GetInstance()

class cTextureManager
{
private:
	SINGLETONE(cTextureManager);

	std::map<std::string, LPDIRECT3DTEXTURE9>	m_mapTexture;

public:
	LPDIRECT3DTEXTURE9 GetTexture(std::string sFullPath);
	LPDIRECT3DTEXTURE9 GetTexture(std::string sFullPath, D3DXIMAGE_INFO* pImageInfo);
	LPDIRECT3DTEXTURE9 GetTexture(std::string KeyName, std::string sFullPath, D3DXIMAGE_INFO* pImageInfo);

	void Destroy();
};

