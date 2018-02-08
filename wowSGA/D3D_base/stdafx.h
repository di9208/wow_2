// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

#define WIDTH 1600
#define HEIGHT 900

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>

// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
#include <assert.h>
#include <d3dx9.h>
#include <vector>
#include <list>
#include <map>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#define DRAW_GRID

extern HWND g_hWnd;

#define SAFE_ADD(p) { if(p) p->AddRef(); }
#define SAFE_DELETE(p) { if(p) { delete p; p = NULL; } }
#define SAFE_DELETE_ARRAY(p) { if(p) { delete [] p; p = NULL; } }
#define SAFE_RELEASE(p) { if(p) { p->Release(); p = NULL; } }

#define SYNTHESIZE(varType, varName, funName) \
protected: varType varName;\
public: inline varType Get##funName(void) const { return varName; }\
public: inline void Set##funName(varType var) { varName = var; }

#define SYNTHESIZE_REF(varType, varName, funName) \
protected: varType varName;\
public: inline varType& Get##funName(void) { return varName; }\
public: inline void Set##funName(varType& var) { varName = var; }


#define SYNTHESIZE_ADD_REF(varType, varName, funName) \
protected: varType varName;\
public: virtual varType Get##funName(void) const { return varName; }\
public: virtual void Set##funName(varType var)\
{\
	if (varName != var)\
	{\
		SAFE_ADD(var);\
		SAFE_RELEASE(varName);\
		varName = var;\
	}\
}

#define SINGLETONE(class_name) \
	private: \
		class_name(void); \
		~class_name(void); \
	public: \
		static class_name* GetInstance() \
		{ \
			static class_name instance; \
			return &instance; \
		}

struct ST_PC_VERTEX
{
	D3DXVECTOR3 p;
	D3DCOLOR	c;
	enum { FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE };
};

struct ST_PT_VERTEX
{
	D3DXVECTOR3 p;
	D3DXVECTOR2	t;
	enum { FVF = D3DFVF_XYZ | D3DFVF_TEX1 };
};

struct ST_PN_VERTEX
{
	D3DXVECTOR3 p;
	D3DXVECTOR3 n;
	enum { FVF = D3DFVF_XYZ | D3DFVF_NORMAL };
};

struct ST_PTN_VERTEX
{
	D3DXVECTOR3 p;
	D3DXVECTOR3 n;
	D3DXVECTOR2	t;
	enum { FVF = D3DFVF_XYZ | D3DFVF_TEX1 | D3DFVF_NORMAL };
};

struct ST_POS_SAMPLE
{
	int			frame;
	D3DXVECTOR3 v;

	ST_POS_SAMPLE() : frame(0), v(0, 0, 0) {}
};

struct ST_ROT_SAMPLE
{
	int				frame;
	D3DXQUATERNION	q;

	ST_ROT_SAMPLE() : frame(0)
	{
		D3DXQuaternionIdentity(&q);
	}
};

struct ST_SPHERE
{
	D3DXVECTOR3 vCenter;
	float		fRadius;
	bool		bIsPicked;

	ST_SPHERE() : vCenter(0, 0, 0)
		, fRadius(0.0f), bIsPicked(false) {}
};

struct ST_SIZE
{
	int nWidth;
	int nHeight;
	ST_SIZE() : nWidth(0), nHeight(0) {}
	ST_SIZE(int _nWidth, int _nHeight)
		: nWidth(_nWidth), nHeight(_nHeight) {}
};

struct ST_MONSTER_ITEM{
	LPDIRECT3DTEXTURE9			m_pTexture;
	D3DXIMAGE_INFO				m_stImageInfo;
	RECT						rc;
};


struct ST_BONE : public D3DXFRAME
{
	D3DXMATRIXA16	matCombinedTransformMatrix;
};
#include "cDeviceManager.h"
#include "cTimeManager.h"
#include "cTextureManager.h"
#include "cFontManager.h"
#include "keyManager.h"
#include "cSkinnedMeshManager.h"
#include "cSceneManager.h"
#include "soundManager.h"