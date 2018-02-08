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
{
}


inventory::~inventory()
{
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
	loader.items_loader(V_INVEN, "shop_data/invenFILE.txt");

	Setting_invenUI();

	for (int i = 0; i < 3; i++)
	{
		money_image[i] = new cUIImage;
		money_text[i] = new cUIText;
	}

	for (int i = 0; i < 16; i++)
	{
		item_slot[i].item_slot = new cUIImage;
		item_slot[i].item_num = -1;
	}
}

void inventory::Update()
{
	GetCursorPos(&MOUSE);
	ScreenToClient(g_hWnd, &MOUSE);

	inven_UI->Update();
	setting_moneyFram(inven_UI->GetPos().x, inven_UI->GetPos().y);
	Setting_items();
}

void inventory::Render(LPD3DXSPRITE in_Sprite)
{
	inven_UI->Render(in_Sprite);

	for (int i = 0; i < 16; i++)
	{
		item_slot[i].item_slot->Render(in_Sprite);
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
	UI_BUTTON01->SetTexture("inven_close", "shop_data/UI-Panel-MinimizeButton-Up.PNG", "shop_data/UI-Panel-MinimizeButton-Disabled.PNG", "shop_data/UI-Panel-MinimizeButton-Down.PNG");
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

		sprintf(chartext, "shop_data/%s", V_INVEN[i]->GetI_image().c_str());

		item_slot[i].item_num = V_INVEN[i]->GetI_num();

		item_slot[i].item_slot->SetTexture(chartext);
		item_slot[i].item_slot->SetPos(D3DXVECTOR3(inven_UI->GetPos().x + 18 + (i % 4) * 42, inven_UI->GetPos().y + 66 + (i / 4) * 42, 0));
		item_slot[i].item_slot->Sethidden(inven_UI->Gethidden());
		item_slot[i].item_slot->SetScal(D3DXVECTOR3(0.55, 0.55, 0));
		item_slot[i].item_slot->Update();
	}
}


void inventory::setting_moneyFram(float x, float y)
{
	char chartext[1024];

	float finx, finy;

	finx = x + 50;
	finy = y + 230;

	if (Money / 100 >= 1)
	{
		money_image[0]->SetTexture("shop_data/UI-GoldIcon.PNG");
		money_image[0]->SetPos(D3DXVECTOR3(finx, finy, 0));
		money_image[0]->Sethidden(inven_UI->Gethidden());
		money_image[0]->Update();

		sprintf(chartext, "%d", Money / 100);

		finx += 20;

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

		finx += 20;

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

		finx += 20;

		money_text[2]->SetupText(chartext, ST_SIZE(150, 25), cFontManager::FT_STORE, D3DXCOLOR(255, 255, 0, 255));
		money_text[2]->SetPos(D3DXVECTOR3(finx, finy, 0));
		money_text[2]->Sethidden(inven_UI->Gethidden());
		money_text[2]->Update();

		finx += 20;
	}
}

void inventory::Add_inven(item_class * temp)
{
	V_INVEN.push_back(temp);
}

void inventory::delete_inven(int arry)
{
	for (int j = 0; j < 16; j++)
	{
		item_slot[j].item_slot->Destroy();
		item_slot[j].item_slot = new cUIImage;
		item_slot[j].item_num = -1;
	}

	if (V_INVEN.size() == 1)
	{
		V_INVEN.clear();
	}
	else
	{
		V_INVEN.erase(V_INVEN.begin() + arry);

		Setting_items();
	}
}

bool inventory::ischeck(OUT int & nums)
{
	RECT rc;

	for (int i = 0; i < 16; i++)
	{
		SetRect(&rc, item_slot[i].item_slot->GetPos().x,
			item_slot[i].item_slot->GetPos().y,
			item_slot[i].item_slot->GetPos().x + 30,
			item_slot[i].item_slot->GetPos().y + 32);

		if (PtInRect(&rc, MOUSE))
		{
			nums = i;
			return true;
		}
	}

	return false;
}
