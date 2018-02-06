#include "stdafx.h"
#include "cTextureManager.h"


cTextureManager::cTextureManager()
{
}


cTextureManager::~cTextureManager()
{
}

LPDIRECT3DTEXTURE9 cTextureManager::GetTexture(std::string sFullPath)
{
	if (m_mapTexture.find(sFullPath) == m_mapTexture.end())
	{
		D3DXCreateTextureFromFile(g_pD3DDevice, sFullPath.c_str(),
			&m_mapTexture[sFullPath]);
	}

	return m_mapTexture[sFullPath];
}

LPDIRECT3DTEXTURE9 cTextureManager::GetTexture(std::string sFullPath, D3DXIMAGE_INFO * pImageInfo)
{
	if (m_mapTexture.find(sFullPath) == m_mapTexture.end())
	{
		D3DXCreateTextureFromFileEx(
			g_pD3DDevice,
			sFullPath.c_str(),
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT,
			0,
			D3DFMT_UNKNOWN,
			D3DPOOL_MANAGED,
			D3DX_FILTER_NONE,
			D3DX_DEFAULT,
			0,
			pImageInfo,
			NULL,
			&m_mapTexture[sFullPath]);
	}

	return m_mapTexture[sFullPath];
}

LPDIRECT3DTEXTURE9 cTextureManager::GetTexture(std::string KeyName, std::string sFullPath, D3DXIMAGE_INFO * pImageInfo)
{
	if (m_mapTexture.find(KeyName) == m_mapTexture.end())
	{
		D3DXCreateTextureFromFileEx(
			g_pD3DDevice,
			sFullPath.c_str(),
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT,
			0,
			D3DFMT_UNKNOWN,
			D3DPOOL_MANAGED,
			D3DX_FILTER_NONE,
			D3DX_DEFAULT,
			0,
			pImageInfo,
			NULL,
			&m_mapTexture[KeyName]);
	}

	return m_mapTexture[KeyName];
}

void cTextureManager::Destroy()
{
	for each(auto p in m_mapTexture)
	{
		SAFE_RELEASE(p.second);
	}
	m_mapTexture.clear();
}
