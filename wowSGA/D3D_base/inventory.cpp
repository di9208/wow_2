#include "stdafx.h"
#include "inventory.h"
#include "item_class.h"
#include "cUIImage.h"
#include "cUIButton.h"
#include "cUIText.h"
#include "cUIObject.h"
#include "DragAndDrob.h"
#include "Button_delegate.h"
#include "item_loader.h"

inventory::inventory()
	: inven_UI(NULL)
	, drage(NULL)
{
}


inventory::~inventory()
{
	SAFE_DELETE(drage);
	inven_UI->Destroy();
	for (int i = 0; i < 3; i++)
	{
		money_image[i]->Destroy();
		money_text[i]->Destroy();
	}
	V_INVEN.clear();
}

void inventory::Setup()
{
	Money = 1000;

	item_loader loader;
	loader.items_loader(V_INVEN,"shop_data/invenFILE.txt");

	Setting_invenUI();

	drage = new DragAndDrob;
	drage->reset();

	for (int i = 0; i < 3; i++)
	{
		money_image[i] = new cUIImage;
		money_text[i] = new cUIText;
	}

	for (int i = 0; i < 16; i++)
	{
		item_slot[i] = new cUIImage;
	}
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
	setting_moneyFram(inven_UI->GetPos().x, inven_UI->GetPos().y);
	Setting_items();

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

	for (int i = 0; i < 16; i++)
	{
		item_slot[i]->Render(in_Sprite);
	}

	for (int i = 0; i < 3; i++)
	{
		money_image[i]->Render(in_Sprite);
		money_text[i]->Render(in_Sprite);
	}
}

void inventory::Setting_invenUI()
{
	inven_UI = new cUIObject;
	inven_UI->Sethidden(true);
	inven_UI->SetPos(D3DXVECTOR3(1390, 450, 0));
	
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

void inventory::Setting_items()
{
	for (int i = 0; i < 16; i++)
	{
		if (V_INVEN.size() <= i) break;

		char chartext[1024];

		sprintf(chartext, "%s", V_INVEN[i]->GetI_image().c_str());

		item_slot[i]->SetTexture(chartext);
		item_slot[i]->SetPos(D3DXVECTOR3(inven_UI->GetPos().x + 18 + (i%4) * 42, inven_UI->GetPos().y + 66 + (i / 4) * 20,0));
		item_slot[i]->Sethidden(inven_UI->Gethidden());
		item_slot[i]->SetScal(D3DXVECTOR3(0.55, 0.55, 0));
		item_slot[i]->Update();
	}
}


void inventory::setting_moneyFram(float x, float y)
{
	char chartext[1024];

	float finx, finy;

	finx = x + 100;
	finy = y + 230;

	if (Money / 100 >= 1)
	{
		money_image[0]->SetTexture("shop_data/UI-GoldIcon.PNG");
		money_image[0]->SetPos(D3DXVECTOR3(finx, finy, 0));
		money_image[0]->Sethidden(inven_UI->Gethidden());
		money_image[0]->Update();

		sprintf(chartext, "%d", Money / 100);

		finx += 15;

		money_text[0]->SetupText(chartext, ST_SIZE(150, 25), cFontManager::FT_STORE, D3DXCOLOR(255, 255, 0, 255));
		money_text[0]->SetPos(D3DXVECTOR3(finx, finy, 0));
		money_text[0]->Sethidden(inven_UI->Gethidden());
		money_text[0]->Update();

		finx += 20;
	}

	if ((Money % 100) / 10 >= 1)
	{
		money_image[1]->SetTexture("shop_data/UI-SilverIcon.PNG");
		money_image[1]->SetPos(D3DXVECTOR3(finx, finy, 0));
		money_image[1]->Sethidden(inven_UI->Gethidden());
		money_image[1]->Update();

		sprintf(chartext, "%d", (Money % 100) / 10);

		finx += 15;

		money_text[1]->SetupText(chartext, ST_SIZE(150, 25), cFontManager::FT_STORE, D3DXCOLOR(255, 255, 0, 255));
		money_text[1]->SetPos(D3DXVECTOR3(finx, finy, 0));
		money_text[1]->Sethidden(inven_UI->Gethidden());
		money_text[1]->Update();

		finx += 20;
	}
	if ((Money % 100) % 10 >= 1)
	{
		money_image[2]->SetTexture("shop_data/UI-CopperIcon.PNG");
		money_image[2]->SetPos(D3DXVECTOR3(finx, finy, 0));
		money_image[2]->Sethidden(inven_UI->Gethidden());
		money_image[2]->Update();

		sprintf(chartext, "%d", (Money % 100) % 10);

		finx += 15;

		money_text[2]->SetupText(chartext, ST_SIZE(150, 25), cFontManager::FT_STORE, D3DXCOLOR(255, 255, 0, 255));
		money_text[2]->SetPos(D3DXVECTOR3(finx, finy, 0));
		money_text[2]->Sethidden(inven_UI->Gethidden());
		money_text[2]->Update();

		finx += 20;
	}
}