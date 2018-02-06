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
	m_load(false),
	m_upthow(false),
	m_downthow(false),
	m_flat(false),
	m_skybox(false),
	m_terrain(false),
	m_tab1(false),
	m_tab2(false),
	m_tab3(false),
	m_object(false)

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
	//Tab1
	cUIButton* tabbutton = new cUIButton;
	tabbutton->SetTexture("MapTool_UI/Tab_Button.png", "MapTool_UI/Tab_Button.png", "MapTool_UI/Tab_Button.png");
	tabbutton->SetTag(TAG_TAB1);
	tabbutton->SetPos(tabbutton->GetPos() + D3DXVECTOR3(1500, 0, 0.5f));
	tabbutton->SetDelegate(this);
	
	Root = tabbutton;

	//Tab2
	cUIButton* tabbutton2 = new cUIButton;
	tabbutton2->SetTexture("tab2", "MapTool_UI/Tab_Button.png", "MapTool_UI/Tab_Button.png", "MapTool_UI/Tab_Button.png");
	tabbutton2->SetTag(TAG_TAB2);
	tabbutton2->SetPos(tabbutton2->GetPos() + D3DXVECTOR3(1500, 220, 0.5f));
	tabbutton2->SetDelegate(this);

	Root2 = tabbutton2;

	//Tab3
	cUIButton* tabbutton3 = new cUIButton;
	tabbutton3->SetTexture("tab3", "MapTool_UI/Tab_Button.png", "MapTool_UI/Tab_Button.png", "MapTool_UI/Tab_Button.png");
	tabbutton3->SetTag(TAG_TAB3);
	tabbutton3->SetPos(tabbutton3->GetPos() + D3DXVECTOR3(1500, 445, 0.5f));
	tabbutton3->SetDelegate(this);

	Root3 = tabbutton3;
}

void cMapTool_UI::SetupUI()
{
	SetupTab1();
	SetupTab2();
	SetupTab3();
}

void cMapTool_UI::SetupImage()
{
	
}

void cMapTool_UI::SetupFont()
{
}

void cMapTool_UI::SetupTab1()
{
	cUIImage * tab = new cUIImage;
	tab->SetTexture("MapTool_UI/Tab_Table1.png");
	//tab->SetPos(tab->GetPos() + D3DXVECTOR3(1500, 0, 0));
	tab->SetTag(TAG_IMAGE);
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

	cUIButton* temp1 = new cUIButton;
	temp1->SetTexture("MapTool_UI/SkyBox_Up.png", "MapTool_UI/SkyBox_Over.png", "MapTool_UI/SkyBox_Down.png");
	temp1->SetTag(TAG_SKYBOX);
	temp1->SetDelegate(this);
	temp1->SetPos(temp1->GetPos() + D3DXVECTOR3(120, 130, 0));
	Root->AddChild(temp1);

	cUIButton* temp2 = new cUIButton;
	temp2->SetTexture("MapTool_UI/Terrain_Up.png", "MapTool_UI/Terrain_Over.png", "MapTool_UI/Terrain_Down.png");
	temp2->SetTag(TAG_TERRAIN);
	temp2->SetDelegate(this);
	temp2->SetPos(temp2->GetPos() + D3DXVECTOR3(120, 180, 0));
	Root->AddChild(temp2);
}

void cMapTool_UI::SetupTab2()
{
	cUIImage* tab2 = new cUIImage;
	tab2->SetTexture("MapTool_UI/Tab_Table2.png");
	tab2->SetTag(TAG_IMAGE);
	tab2->SetPos(tab2->GetPos() + D3DXVECTOR3(0, -220, 0));
	Root2->AddChild(tab2);

	cUIButton* temp1 = new cUIButton;
	temp1->SetTexture("t1", "MapTool_UI/Flattening_Up.png", "MapTool_UI/Flattening_Over.png", "MapTool_UI/Flattening_Down.png");
	temp1->SetTag(TAG_FLATTENING);
	temp1->SetDelegate(this);
	temp1->SetPos(temp1->GetPos() + D3DXVECTOR3(120, -190, 0));
	Root2->AddChild(temp1);

	cUIButton* temp2 = new cUIButton;
	temp2->SetTexture("t2", "MapTool_UI/UpThrow_Up.png", "MapTool_UI/UpThrow_Over.png", "MapTool_UI/UpThrow_Down.png");
	temp2->SetTag(TAG_UPTHROW);
	temp2->SetDelegate(this);
	temp2->SetPos(temp2->GetPos() + D3DXVECTOR3(120, -140, 0));
	Root2->AddChild(temp2);

	cUIButton* temp3 = new cUIButton;
	temp3->SetTexture("t3", "MapTool_UI/DownThow_Up.png", "MapTool_UI/DownThow_Over.png", "MapTool_UI/DownThow_Down.png");
	temp3->SetTag(TAG_DOWNTHROW);
	temp3->SetDelegate(this);
	temp3->SetPos(temp3->GetPos() + D3DXVECTOR3(120, -90, 0));
	Root2->AddChild(temp3);
}

void cMapTool_UI::SetupTab3()
{
	cUIImage * tab3 = new cUIImage;
	tab3->SetTexture("MapTool_UI/Tab_Table3.png");
	tab3->SetTag(TAG_IMAGE);
	tab3->SetPos(tab3->GetPos() + D3DXVECTOR3(0, -385, 0));
	Root3->AddChild(tab3);

	cUIButton* temp = new cUIButton;
	temp->SetTexture("t77", "MapTool_UI/DownThow_Up.png", "MapTool_UI/DownThow_Over.png", "MapTool_UI/DownThow_Down.png");
	temp->SetTag(TAG_OB);
	temp->SetDelegate(this);
	temp->SetPos(temp->GetPos() + D3DXVECTOR3(120, -320, 0));
	Root3->AddChild(temp);
}


void cMapTool_UI::Update()
{
	Root2->Update();
	Root->Update();
	Root3->Update();
}

void cMapTool_UI::Render(LPD3DXSPRITE pSprite)
{
	D3DXMATRIXA16 matW;
	D3DXMatrixTranslation(&matW, 400, 100, 0);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matW);
	Root->Render(pSprite);
	Root2->Render(pSprite);
	Root3->Render(pSprite);
}

void cMapTool_UI::OnClick(cUIButton * pSender)
{
	TabShowHide(pSender);
	Save(pSender);
	Load(pSender); 
	Landscape(pSender);
	SkyBoxT(pSender);
	Terrain(pSender);
	Object(pSender);
}

void cMapTool_UI::TabShowHide(cUIButton * pSender)
{
	if (pSender->GetTag() == TAG_TAB1|| pSender->GetTag() == TAG_TAB2 || pSender->GetTag() == TAG_TAB3)
	{	
		

		if (pSender->GetPos().x == 1500)
		{
			if (pSender->GetTag() == TAG_TAB1)
			{
				if (m_tab2 || m_tab3)
					return;
				m_tab1 = true;
			}
			if (pSender->GetTag() == TAG_TAB2)
			{
				if (m_tab1 || m_tab3)
					return;
				m_tab2 = true;
			}
			if (pSender->GetTag() == TAG_TAB3)
			{
				if (m_tab1 || m_tab2)
					return;
				m_tab3 = true;
			}
			pSender->SetPos(pSender->GetPos() + D3DXVECTOR3(-150, 0, -0.5f));
			return;
		}
		if (pSender->GetPos().x == 1350)
		{
			if (pSender->GetTag() == TAG_TAB1)
				m_tab1 = false;
			if (pSender->GetTag() == TAG_TAB2)
				m_tab2 = false;
			if (pSender->GetTag() == TAG_TAB3)
				m_tab3 = false;
			pSender->SetPos(pSender->GetPos() + D3DXVECTOR3(150, 0, 0.5f));
			return;
		}
	}
}

void cMapTool_UI::Save(cUIButton * pSender)
{
	if (pSender->GetTag() == TAG_SAVE)
	{
		m_save = true;
		m_upthow = false;
		m_downthow = false;
		m_flat = false;
		m_object = false;
	}
}

void cMapTool_UI::Load(cUIButton * pSender)
{
	if (pSender->GetTag() == TAG_LOAD)
	{
		m_load = true;
		m_upthow = false;
		m_downthow = false;
		m_flat = false;
		m_object = false;
	}
}

void cMapTool_UI::Landscape(cUIButton * pSender)
{
	if (pSender->GetTag() == TAG_UPTHROW)
	{
		m_upthow = true;
		m_downthow = false;
		m_flat = false;
		m_object = false;
	}
	if (pSender->GetTag() == TAG_DOWNTHROW)
	{
		m_downthow = true;
		m_upthow = false;
		m_flat = false;
		m_object = false;
	}
	if (pSender->GetTag() == TAG_FLATTENING)
	{
		m_flat = true;
		m_upthow = false;
		m_downthow = false;
		m_object = false;
	}

}

void cMapTool_UI::SkyBoxT(cUIButton * pSender)
{
	if (pSender->GetTag() == TAG_SKYBOX)
	{
		m_skybox = true;
		m_upthow = false;
		m_downthow = false;
		m_flat = false;
		m_object = false;
	}
}

void cMapTool_UI::Terrain(cUIButton * pSender)
{
	if (pSender->GetTag() == TAG_TERRAIN)
	{
		m_terrain = true;
		m_upthow = false;
		m_downthow = false;
		m_flat = false;
		m_object = false;
	}
}

void cMapTool_UI::Object(cUIButton * pSender)
{
	if (pSender->GetTag() == TAG_OB)
	{
		m_object = true;
		m_terrain = false;
		m_upthow = false;
		m_downthow = false;
		m_flat = false;
	}
}

