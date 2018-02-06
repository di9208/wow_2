#include "stdafx.h"
#include "cMapTool_UI.h"
#include "cUIObject.h"
#include "cUIImage.h"
#include "cUIText.h"
//
// 0 Tab button0
//
// 10 Save
// 11 Load
//

//OPENFILENAME 
//GetOpenFileName
//GetSaveFileName
//L"All Files(*.*)\0*.*\0"

cMapTool_UI::cMapTool_UI()
	:m_save(false),
	m_load(false)
{
}


cMapTool_UI::~cMapTool_UI()
{
	Root->Destroy();
}

void cMapTool_UI::Setup()
{
	SetupRoot();
	SetupUI();
}

void cMapTool_UI::SetupRoot()
{
	cUIButton* tabbutton = new cUIButton;
	tabbutton->SetTexture("MapTool_UI/Tab_Button.png", "MapTool_UI/Tab_Button.png", "MapTool_UI/Tab_Button.png");
	tabbutton->SetTag(TAG_TAB);
	tabbutton->SetPos(tabbutton->GetPos() + D3DXVECTOR3(1500, 0, 0));
	tabbutton->SetDelegate(this);
	
	Root = tabbutton;
}

void cMapTool_UI::SetupUI()
{
	cUIImage * tab = new cUIImage;
	tab->SetTexture("MapTool_UI/Tab_Table.png");
	//tab->SetPos(tab->GetPos() + D3DXVECTOR3(1500, 0, 0));
	Root->AddChild(tab);

	cUIButton* save = new cUIButton;
	save->SetTexture("MapTool_UI/Save_Up.png", "MapTool_UI/Save_Over.png", "MapTool_UI/Save_Down.png");
	save->SetTag(TAG_SAVE);
	save->SetDelegate(this);
	save->SetPos(save->GetPos() + D3DXVECTOR3(120, 30, 0));
	Root->AddChild(save);

	cUIButton* load = new cUIButton;
	load->SetTexture("MapTool_UI/Load_Up.png", "MapTool_UI/Load_Over.png", "MapTool_UI/Load_Down.png");
	load->SetTag(TAG_LOAD);
	load->SetDelegate(this);
	load->SetPos(load->GetPos() + D3DXVECTOR3(120, 80, 0));
	Root->AddChild(load);

}

void cMapTool_UI::SetupImage()
{
	
}

void cMapTool_UI::SetupFont()
{
}

void cMapTool_UI::Update()
{
	Root->Update();
}

void cMapTool_UI::Render(LPD3DXSPRITE pSprite)
{
	D3DXMATRIXA16 matW;
	D3DXMatrixTranslation(&matW, 400, 100, 0);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matW);
	Root->Render(pSprite);
}

void cMapTool_UI::OnClick(cUIButton * pSender)
{
	TabShowHide(pSender);
	Save(pSender);
	Load(pSender); 
}

void cMapTool_UI::TabShowHide(cUIButton * pSender)
{
	if (pSender->GetTag() == TAG_TAB)
	{
		D3DXMATRIXA16 mat;
		if (pSender->GetPos() == D3DXVECTOR3(1500, 0, 0))
		{
			pSender->SetPos(pSender->GetPos() + D3DXVECTOR3(-150, 0, 0));
			return;
		}
		if (pSender->GetPos() == D3DXVECTOR3(1350, 0, 0))
		{
			pSender->SetPos(pSender->GetPos() + D3DXVECTOR3(150, 0, 0));
			return;
		}
	}
}

void cMapTool_UI::Save(cUIButton * pSender)
{
	if (pSender->GetTag() == TAG_SAVE)
	{
		m_save = true;
		
	}
}

void cMapTool_UI::Load(cUIButton * pSender)
{
	if (pSender->GetTag() == TAG_LOAD)
	{
		m_load = true;

	}
}

