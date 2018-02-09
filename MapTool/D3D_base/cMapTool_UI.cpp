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
	m_object(false),
	m_player(false),
	m_spider(false),
	m_lichking(false),
	m_druid(false),
	m_worg(false),
	m_rag(false),
	m_tau(false),
	m_tree(false)

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

}

void cMapTool_UI::SetupUI()
{
	SetupTab1();
	SetupTab2();
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

	cUIButton* temp4 = new cUIButton;
	temp4->SetTexture("t1", "MapTool_UI/Flattening_Up.png", "MapTool_UI/Flattening_Over.png", "MapTool_UI/Flattening_Down.png");
	temp4->SetTag(TAG_FLATTENING);
	temp4->SetDelegate(this);
	temp4->SetPos(temp4->GetPos() + D3DXVECTOR3(220, 30, 0));
	Root->AddChild(temp4);

	cUIButton* temp5 = new cUIButton;
	temp5->SetTexture("t2", "MapTool_UI/UpThrow_Up.png", "MapTool_UI/UpThrow_Over.png", "MapTool_UI/UpThrow_Down.png");
	temp5->SetTag(TAG_UPTHROW);
	temp5->SetDelegate(this);
	temp5->SetPos(temp5->GetPos() + D3DXVECTOR3(220, 80, 0));
	Root->AddChild(temp5);

	cUIButton* temp3 = new cUIButton;
	temp3->SetTexture("t3", "MapTool_UI/DownThow_Up.png", "MapTool_UI/DownThow_Over.png", "MapTool_UI/DownThow_Down.png");
	temp3->SetTag(TAG_DOWNTHROW);
	temp3->SetDelegate(this);
	temp3->SetPos(temp3->GetPos() + D3DXVECTOR3(220, 130, 0));
	Root->AddChild(temp3);

	cUIButton* temp7 = new cUIButton;
	temp7->SetTexture("MapTool_UI/Delete_Up.png", "MapTool_UI/Delete_Over.png", "MapTool_UI/Delete_Down.png");
	temp7->SetTag(TAG_DELETE);
	temp7->SetDelegate(this);
	temp7->SetPos(temp7->GetPos() + D3DXVECTOR3(220, 180, 0));
	Root->AddChild(temp7);
}

void cMapTool_UI::SetupTab2()
{
	cUIImage* tab2 = new cUIImage;
	tab2->SetTexture("MapTool_UI/Tab_Table2.png");
	tab2->SetTag(TAG_IMAGE);
	tab2->SetPos(tab2->GetPos() + D3DXVECTOR3(0, -220, 0));
	Root2->AddChild(tab2);

	cUIButton* temp1 = new cUIButton;
	temp1->SetTexture("MapTool_UI/Player_Up.png", "MapTool_UI/Player_Over.png", "MapTool_UI/Player_Down.png");
	temp1->SetTag(TAG_PLAYER);
	temp1->SetDelegate(this);
	temp1->SetPos(temp1->GetPos() + D3DXVECTOR3(100, -180, 0));
	Root2->AddChild(temp1);

	cUIButton* temp2 = new cUIButton;
	temp2->SetTexture("MapTool_UI/LichKing_Up.png", "MapTool_UI/LichKing_Over.png", "MapTool_UI/LichKing_Down.png");
	temp2->SetTag(TAG_LICHKING);
	temp2->SetDelegate(this);
	temp2->SetPos(temp2->GetPos() + D3DXVECTOR3(200, -180, 0));
	Root2->AddChild(temp2);

	cUIButton* temp3 = new cUIButton;
	temp3->SetTexture("MapTool_UI/Ragnaros_Up.png", "MapTool_UI/Ragnaros_Over.png", "MapTool_UI/Ragnaros_Down.png");
	temp3->SetTag(TAG_RAG);
	temp3->SetDelegate(this);
	temp3->SetPos(temp3->GetPos() + D3DXVECTOR3(100, -60, 0));
	Root2->AddChild(temp3);

	cUIButton* temp4 = new cUIButton;
	temp4->SetTexture("MapTool_UI/Spider_Up.png", "MapTool_UI/Spider_Over.png", "MapTool_UI/Spider_Down.png");
	temp4->SetTag(TAG_BONESPIDER);
	temp4->SetDelegate(this);
	temp4->SetPos(temp4->GetPos() + D3DXVECTOR3(200, -60, 0));
	Root2->AddChild(temp4);

	cUIButton* temp5 = new cUIButton;
	temp5->SetTexture("MapTool_UI/Druid_Up.png", "MapTool_UI/Druid_Over.png", "MapTool_UI/Druid_Down.png");
	temp5->SetTag(TAG_DRUID);
	temp5->SetDelegate(this);
	temp5->SetPos(temp5->GetPos() + D3DXVECTOR3(100, 60, 0));
	Root2->AddChild(temp5);

	cUIButton* temp6 = new cUIButton;
	temp6->SetTexture("MapTool_UI/Worg_Up.png", "MapTool_UI/Worg_Over.png", "MapTool_UI/Worg_Down.png");
	temp6->SetTag(TAG_WORG);
	temp6->SetDelegate(this);
	temp6->SetPos(temp6->GetPos() + D3DXVECTOR3(200, 60, 0));
	Root2->AddChild(temp6);

	cUIButton* temp7 = new cUIButton;
	temp7->SetTexture("MapTool_UI/Tauren_Up.png", "MapTool_UI/Tauren_Over.png", "MapTool_UI/Tauren_Down.png");
	temp7->SetTag(TAG_TAUREN);
	temp7->SetDelegate(this);
	temp7->SetPos(temp7->GetPos() + D3DXVECTOR3(100, 180, 0));
	Root2->AddChild(temp7);
	/*cUIButton* temp1 = new cUIButton;
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
	Root2->AddChild(temp3);*/
}

void cMapTool_UI::SetupTab3()
{
	
}


void cMapTool_UI::Update()
{
	Root2->Update();
	Root->Update();
}

void cMapTool_UI::Render(LPD3DXSPRITE pSprite)
{
	D3DXMATRIXA16 matW;
	D3DXMatrixTranslation(&matW, 400, 100, 0);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matW);
	Root->Render(pSprite);
	Root2->Render(pSprite);
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
	Unit(pSender);
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
			pSender->SetPos(pSender->GetPos() + D3DXVECTOR3(-300, 0, -0.5f));
			return;
		}
		if (pSender->GetPos().x == 1200)
		{
			if (pSender->GetTag() == TAG_TAB1)
				m_tab1 = false;
			if (pSender->GetTag() == TAG_TAB2)
				m_tab2 = false;
			if (pSender->GetTag() == TAG_TAB3)
				m_tab3 = false;
			pSender->SetPos(pSender->GetPos() + D3DXVECTOR3(300, 0, 0.5f));
			return;
		}
	}
}

void cMapTool_UI::Save(cUIButton * pSender)
{
	if (pSender->GetTag() == TAG_SAVE)
	{
		Setbool(m_save);
	}
}

void cMapTool_UI::Load(cUIButton * pSender)
{
	if (pSender->GetTag() == TAG_LOAD)
	{
		Setbool(m_load);
	}
}

void cMapTool_UI::Landscape(cUIButton * pSender)
{
	if (pSender->GetTag() == TAG_UPTHROW)
	{
		Setbool(m_upthow);
	}
	if (pSender->GetTag() == TAG_DOWNTHROW)
	{
		Setbool(m_downthow);
	}
	if (pSender->GetTag() == TAG_FLATTENING)
	{
		Setbool(m_flat);
	}

}

void cMapTool_UI::SkyBoxT(cUIButton * pSender)
{
	if (pSender->GetTag() == TAG_SKYBOX)
	{
		Setbool(m_skybox);
	}
}

void cMapTool_UI::Terrain(cUIButton * pSender)
{
	if (pSender->GetTag() == TAG_TERRAIN)
	{
		Setbool(m_terrain);
	}
}

void cMapTool_UI::Object(cUIButton * pSender)
{
	if (pSender->GetTag() == TAG_TREE)
	{
		Setbool(m_tree);
	}
}

void cMapTool_UI::Unit(cUIButton * pSender)
{
	if (pSender->GetTag() == TAG_PLAYER)
	{
		Setbool(m_player);
	}
	if (pSender->GetTag() == TAG_BONESPIDER)
	{
		Setbool(m_spider);
	}
	if (pSender->GetTag() == TAG_DRUID)
	{
		Setbool(m_druid);
	}
	if (pSender->GetTag() == TAG_LICHKING)
	{
		Setbool(m_lichking);
	}
	if (pSender->GetTag() == TAG_WORG)
	{
		Setbool(m_worg);
	}
	if (pSender->GetTag() == TAG_RAG)
	{
		Setbool(m_rag);
	}

	if (pSender->GetTag() == TAG_TAUREN)
	{
		Setbool(m_tau);
	}
}

void cMapTool_UI::Setbool(bool &bf)
{
	m_save = false;
	m_load = false;
	m_player = false;
	m_object = false;
	m_terrain = false;
	m_upthow = false;
	m_downthow = false;
	m_flat = false;
	m_spider = false;
	m_druid = false;
	m_lichking = false;
	m_worg = false;
	m_rag = false;
	m_tau = false;
	m_tree = false;
	bf = true;
}

