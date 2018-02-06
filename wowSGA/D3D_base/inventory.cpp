#include "stdafx.h"
#include "inventory.h"
#include "item_class.h"
#include "cUIImage.h"
#include "cUIButton.h"
#include "cUIText.h"
#include "cUIObject.h"
#include "DragAndDrob.h"
#include "Button_delegate.h"

inventory::inventory()
	: inven_UI(NULL)
	, drage(NULL)
{
}


inventory::~inventory()
{
	SAFE_DELETE(drage);
	inven_UI->Destroy();
}

void inventory::Setup()
{
	Setting_invenUI();

	all_size.resize(16);
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			all_size[i * 4 + j].nWidth = inven_UI->GetPos().x + 20 + 20 * j;
			all_size[i * 4 + j].nHeight = inven_UI->GetPos().y + 20 + 20 * i;
		}
	}

	drage = new DragAndDrob;
	drage->reset();
}

void inventory::Update()
{
	POINT MOUSE;
	GetCursorPos(&MOUSE);
	ScreenToClient(g_hWnd, &MOUSE);
	RECT INVEN_UI_RECT;
	SetRect(&INVEN_UI_RECT, inven_UI->GetPos().x, inven_UI->GetPos().y, inven_UI->GetPos().x + 404, inven_UI->GetPos().y + 420);

	if (PtInRect(&INVEN_UI_RECT, MOUSE))
	{
		if (g_pKeyManager->isOnceKeyDown(VK_RBUTTON))
		{
			drage->Setting(MOUSE, INVEN_UI_RECT);
		}
		if (g_pKeyManager->isOnceKeyUp(VK_RBUTTON))
		{
			drage->reset();
		}
	}

	inven_UI->Update();

	RECT rc;
	drage->Update(MOUSE, rc);
	if (drage->Getkey())
	{
		inven_UI->SetPos(D3DXVECTOR3(rc.left, rc.top, 0));
	}
}

void inventory::Render(LPD3DXSPRITE in_Sprite)
{
	inven_UI->Render(in_Sprite);
}

void inventory::Setting_invenUI()
{
	inven_UI = new cUIObject;
	inven_UI->Sethidden(true);
	inven_UI->SetPos(D3DXVECTOR3(1000, 100, 0));
	
	cUIImage* UI_IMAGE01 = new cUIImage;
	UI_IMAGE01->SetTexture("shop_data/UI-BackpackBackground.PNG");

	Button_delegate* dele_temp = new Button_delegate;

	cUIButton* UI_BUTTON01 = new cUIButton;
	UI_BUTTON01->SetTexture("inven_close","shop_data/UI-Panel-MinimizeButton-Up.PNG","shop_data/UI-Panel-MinimizeButton-Disabled.PNG", "shop_data/UI-Panel-MinimizeButton-Down.PNG");
	UI_BUTTON01->SetPos(D3DXVECTOR3(160, 2, 0));
	UI_BUTTON01->SetTag(1);
	UI_BUTTON01->SetDeleGate(dele_temp);

	inven_UI->AddChild(UI_IMAGE01);
	inven_UI->AddChild(UI_BUTTON01);
}
