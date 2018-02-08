#include "stdafx.h"
#include "shop_class.h"
#include "item_class.h"
#include "item_loader.h"
#include "cUIObject.h"
#include "cUIImage.h"
#include "cUIButton.h"
#include "cUIText.h"
#include "Button_delegate.h"
#include "DragAndDrob.h"

shop_class::shop_class()
{
}


shop_class::~shop_class()
{
	for each(auto p in v_shop_sell_Things)
	{
		SAFE_DELETE(p);
	}

	for each(auto p in before_selling_Things)
	{
		SAFE_DELETE(p);
	}
	for (int i = 0; i < 10; i++)
	{
		item_slot[i].item_slot->Destroy();
		item_slot[i].item_Main_name->Destroy();
		for (int j = 0; j < 3; j++)
		{
			item_slot[i].item_money[j]->Destroy();
			item_slot[i].item_moeny_text[j]->Destroy();
		}
	}

	Shop_UI->Destroy();
	buybackShop_UI->Destroy();

	Page_TEXT_UI->Destroy();
}

void shop_class::Setup()
{
	item_loader loader;
	loader.items_loader(v_shop_sell_Things, "shop_data/item_list.txt");

	Now_page_num = 1;
	Page_num = v_shop_sell_Things.size() / 10;
	if (Page_num == 0) Page_num = 1;
	if ((v_shop_sell_Things.size() - (Page_num * 10)) < 0) Page_num += 1;

	setting_UI_frame();
	setting_buyback_UI_frame();

	SetRect(&Shop_UI_RECT, Shop_UI->GetPos().x, Shop_UI->GetPos().y, Shop_UI->GetPos().x + 404, Shop_UI->GetPos().y + 420);

	Page_TEXT_UI = new cUIText;

	for (int i = 0; i < 10; i++)
	{
		item_slot[i].item_slot = new cUIImage;
		item_slot[i].item_Main_name = new cUIText;
		for (int j = 0; j < 3; j++)
		{
			item_slot[i].item_money[j] = new cUIImage;
			item_slot[i].item_moeny_text[j] = new cUIText;
		}
	}

	setting_show_item_UI();
}

void shop_class::update()
{



	SetRect(&Shop_UI_RECT, Shop_UI->GetPos().x, Shop_UI->GetPos().y, Shop_UI->GetPos().x + 404, Shop_UI->GetPos().y + 420);

	Shop_UI->Update();
	buybackShop_UI->Update();

	char Page_text_temp[1024];
	ZeroMemory(Page_text_temp, 1024);
	sprintf(Page_text_temp, " %d 쪽 중 %d ", Page_num, Now_page_num);

	Page_TEXT_UI->SetupText(Page_text_temp, ST_SIZE(80, 25), cFontManager::FT_wow, D3DXCOLOR(255, 255, 0, 255));
	Page_TEXT_UI->SetPos(D3DXVECTOR3(Shop_UI->GetPos().x + 140, Shop_UI->GetPos().y + 344, 0));
	Page_TEXT_UI->Sethidden(Shop_UI->Gethidden());

	Page_TEXT_UI->Update();

	for (int i = 0; i < 10; i++)
	{
		item_slot[i].item_slot->Update();
		item_slot[i].item_slot->Sethidden(Shop_UI->Gethidden());
		item_slot[i].item_Main_name->Update();
		item_slot[i].item_Main_name->Sethidden(Shop_UI->Gethidden());
		for (int j = 0; j < 3; j++)
		{
			item_slot[i].item_money[j]->Update();
			item_slot[i].item_money[j]->Sethidden(Shop_UI->Gethidden());
			item_slot[i].item_moeny_text[j]->Update();
			item_slot[i].item_moeny_text[j]->Sethidden(Shop_UI->Gethidden());
		}
	}

	GetCursorPos(&MOUSE);
	ScreenToClient(g_hWnd, &MOUSE);
}

void shop_class::render(LPD3DXSPRITE in_subsprite)
{
	Shop_UI->Render(in_subsprite);
	buybackShop_UI->Render(in_subsprite);

	for (int i = 0; i < 10; i++)
	{
		item_slot[i].item_slot->Render(in_subsprite);
		item_slot[i].item_Main_name->Render(in_subsprite);

		for (int j = 0; j < 3; j++)
		{
			item_slot[i].item_money[j]->Render(in_subsprite);
			item_slot[i].item_moeny_text[j]->Render(in_subsprite);
		}
	}

	Page_TEXT_UI->Render(in_subsprite);
}

void shop_class::buy(IN int nums, OUT int & money, OUT item_class* buyitem)
{
	for (int i = 0; i < v_shop_sell_Things.size(); i++)
	{
		if (v_shop_sell_Things[i]->GetI_num() == nums)
		{
			if (money - v_shop_sell_Things[i]->GetI_option().Price < 0)
			{
				break;
				//::MessageBox(0, "저런 돈이 없어요 ㅋ", "상점 왈", 0);
			}
			else
			{
				*buyitem = *v_shop_sell_Things[i];
				money -= v_shop_sell_Things[i]->GetI_option().Price;
			}
		}
	}
}

void shop_class::sell(IN int nums, OUT int & money)
{
	for (int i = 0; i < v_shop_sell_Things.size(); i++)
	{
		if (v_shop_sell_Things[i]->GetI_num() == nums)
		{
			before_selling_Things.push_back(v_shop_sell_Things[i]);
			money += v_shop_sell_Things[i]->GetI_option().Price;
		}
	}
}

void shop_class::rebuy(IN int nums, OUT int & money, OUT item_class* buyitem)
{
	for (int i = 0; i < v_shop_sell_Things.size(); i++)
	{
		if (v_shop_sell_Things[i]->GetI_num() == nums)
		{
			float seal = v_shop_sell_Things[i]->GetI_option().Price * 0.25;

			if (money - v_shop_sell_Things[i]->GetI_option().Price - seal < 0)
			{
				break;
				//::MessageBox(0, "저런 돈이 없어요 ㅋ", "상점 왈", 0);
			}
			else
			{
				*buyitem = *v_shop_sell_Things[i];
				money -= v_shop_sell_Things[i]->GetI_option().Price - seal;
			}
		}
	}
}

void shop_class::setting_UI_frame()
{
	Shop_UI = new cUIObject;
	Shop_UI->Sethidden(true);
	//image

	cUIImage* cui_I01;
	cui_I01 = new cUIImage;
	cui_I01->SetTexture("shop_data/SHOP_UI/UI-Merchant-TopLeft.PNG");
	cui_I01->SetPos(D3DXVECTOR3(0, 0, 0));

	cUIImage* cui_I02;
	cui_I02 = new cUIImage;
	cui_I02->SetTexture("shop_data/SHOP_UI/UI-Merchant-TopRight.PNG");
	cui_I02->SetPos(D3DXVECTOR3(256, 0, 0));

	cUIImage* cui_I03;
	cui_I03 = new cUIImage;
	cui_I03->SetTexture("shop_data/SHOP_UI/UI-Merchant-BotLeft.PNG");
	cui_I03->SetPos(D3DXVECTOR3(0, 256, 0));

	cUIImage* cui_I04;
	cui_I04 = new cUIImage;
	cui_I04->SetTexture("shop_data/SHOP_UI/UI-Merchant-BotRight.png");
	cui_I04->SetPos(D3DXVECTOR3(256, 256, 0));

	cUIImage* cui_I05;
	cui_I05 = new cUIImage;
	cui_I05->SetTexture("shop_data/SHOP_UI/sub.PNG");
	cui_I05->SetPos(D3DXVECTOR3(14, 365, 0));

	cUIImage* cui_I06;
	cui_I06 = new cUIImage;
	cui_I06->SetTexture("shop_data/SHOP_UI/sub2.PNG");
	cui_I06->SetPos(D3DXVECTOR3(270, 365, 0));

	//cUIImage* cui_I07;
	//cui_I07 = new cUIImage;
	//cui_I07->SetTexture("shop_data/SHOP_UI/UI-AuctionFrame-ItemSlot.PNG");
	//cui_I07->SetPos(D3DXVECTOR3(164, 310, 0));

	cUIImage* cui_I08;
	cui_I08 = new cUIImage;
	cui_I08->SetTexture("shop_data/TEMPORARYPORTRAIT-MALE-TAUREN.PNG");
	cui_I08->SetPos(D3DXVECTOR3(12, 15, 0));
	cui_I08->SetScal(D3DXVECTOR3(0.8, 0.8, 0));


	cUIImage* cui_Item_slot01;
	cui_Item_slot01 = new cUIImage;
	cui_Item_slot01->SetTexture("shop_data/SHOP_UI/UI-Merchant-LabelSlots.PNG");
	cui_Item_slot01->SetPos(D3DXVECTOR3(67, 75, 0));

	cUIImage* cui_Item_slot02;
	cui_Item_slot02 = new cUIImage;
	cui_Item_slot02->SetTexture("shop_data/SHOP_UI/UI-Merchant-LabelSlots.PNG");
	cui_Item_slot02->SetPos(D3DXVECTOR3(67 + 160, 75, 0));

	cUIImage* cui_Item_slot03;
	cui_Item_slot03 = new cUIImage;
	cui_Item_slot03->SetTexture("shop_data/SHOP_UI/UI-Merchant-LabelSlots.PNG");
	cui_Item_slot03->SetPos(D3DXVECTOR3(67, 75 + 48, 0));

	cUIImage* cui_Item_slot04;
	cui_Item_slot04 = new cUIImage;
	cui_Item_slot04->SetTexture("shop_data/SHOP_UI/UI-Merchant-LabelSlots.PNG");
	cui_Item_slot04->SetPos(D3DXVECTOR3(67 + 160, 75 + 48, 0));

	cUIImage* cui_Item_slot05;
	cui_Item_slot05 = new cUIImage;
	cui_Item_slot05->SetTexture("shop_data/SHOP_UI/UI-Merchant-LabelSlots.PNG");
	cui_Item_slot05->SetPos(D3DXVECTOR3(67, 75 + 96, 0));

	cUIImage* cui_Item_slot06;
	cui_Item_slot06 = new cUIImage;
	cui_Item_slot06->SetTexture("shop_data/SHOP_UI/UI-Merchant-LabelSlots.PNG");
	cui_Item_slot06->SetPos(D3DXVECTOR3(67 + 160, 75 + 96, 0));

	cUIImage* cui_Item_slot07;
	cui_Item_slot07 = new cUIImage;
	cui_Item_slot07->SetTexture("shop_data/SHOP_UI/UI-Merchant-LabelSlots.PNG");
	cui_Item_slot07->SetPos(D3DXVECTOR3(67, 75 + 144, 0));

	cUIImage* cui_Item_slot08;
	cui_Item_slot08 = new cUIImage;
	cui_Item_slot08->SetTexture("shop_data/SHOP_UI/UI-Merchant-LabelSlots.PNG");
	cui_Item_slot08->SetPos(D3DXVECTOR3(67 + 160, 75 + 144, 0));

	cUIImage* cui_Item_slot09;
	cui_Item_slot09 = new cUIImage;
	cui_Item_slot09->SetTexture("shop_data/SHOP_UI/UI-Merchant-LabelSlots.PNG");
	cui_Item_slot09->SetPos(D3DXVECTOR3(67, 75 + 192, 0));

	cUIImage* cui_Item_slot10;
	cui_Item_slot10 = new cUIImage;
	cui_Item_slot10->SetTexture("shop_data/SHOP_UI/UI-Merchant-LabelSlots.PNG");
	cui_Item_slot10->SetPos(D3DXVECTOR3(67 + 160, 75 + 192, 0));


	//text

	cUIText* cui_T01;
	cui_T01 = new cUIText;
	cui_T01->SetupText("타우렌 상점", ST_SIZE(150, 25), cFontManager::FT_STORE, D3DXCOLOR(255, 255, 0, 255));
	cui_T01->SetPos(D3DXVECTOR3(145, 17, 0));

	cUIText* cui_T02;
	cui_T02 = new cUIText;
	cui_T02->SetupText("상품 목록", ST_SIZE(80, 25), cFontManager::FT_STORE, D3DXCOLOR(255, 255, 0, 255));
	cui_T02->SetPos(D3DXVECTOR3(23, 455, 0));

	cUIText* cui_T03;
	cui_T03 = new cUIText;
	cui_T03->SetupText("재 매입", ST_SIZE(80, 25), cFontManager::FT_STORE, D3DXCOLOR(255, 255, 0, 255));
	cui_T03->SetPos(D3DXVECTOR3(135, 455, 0));

	cUIText* cui_T04;
	cui_T04 = new cUIText;
	cui_T04->SetupText("이전", ST_SIZE(80, 25), cFontManager::FT_STORE, D3DXCOLOR(255, 255, 0, 255));
	cui_T04->SetPos(D3DXVECTOR3(63, 344, 0));

	cUIText* cui_T05;
	cui_T05 = new cUIText;
	cui_T05->SetupText("다음", ST_SIZE(80, 25), cFontManager::FT_STORE, D3DXCOLOR(255, 255, 0, 255));
	cui_T05->SetPos(D3DXVECTOR3(265, 344, 0));

	//button

	Button_delegate* dele_close = new Button_delegate;

	cUIButton* cui_close;
	cui_close = new cUIButton;
	cui_close->SetTag(1);
	cui_close->SetTexture("shop_data/UI-Panel-MinimizeButton-Up.PNG", "shop_data/UI-Panel-MinimizeButton-Disabled.PNG", "shop_data/UI-Panel-MinimizeButton-Down.PNG");
	cui_close->SetPos(D3DXVECTOR3(322, 8, 0));
	cui_close->SetDeleGate(dele_close);

	cUIButton* cui_B01;
	cui_B01 = new cUIButton;
	cui_B01->SetTexture("slot1", "shop_data/UI-EmptySlot.PNG", "shop_data/UI-EmptySlot-Disabled.PNG", "shop_data/UI-EmptySlot-White.PNG");
	cui_B01->SetPos(D3DXVECTOR3(20, 75, 0));

	cUIButton* cui_B02;
	cui_B02 = new cUIButton;
	cui_B02->SetTexture("slot2", "shop_data/UI-EmptySlot.PNG", "shop_data/UI-EmptySlot-Disabled.PNG", "shop_data/UI-EmptySlot-White.PNG");
	cui_B02->SetPos(D3DXVECTOR3(20 + 160, 75, 0));

	cUIButton* cui_B03;
	cui_B03 = new cUIButton;
	cui_B03->SetTexture("slot3", "shop_data/UI-EmptySlot.PNG", "shop_data/UI-EmptySlot-Disabled.PNG", "shop_data/UI-EmptySlot-White.PNG");
	cui_B03->SetPos(D3DXVECTOR3(20, 75 + 48, 0));

	cUIButton* cui_B04;
	cui_B04 = new cUIButton;
	cui_B04->SetTexture("slot4", "shop_data/UI-EmptySlot.PNG", "shop_data/UI-EmptySlot-Disabled.PNG", "shop_data/UI-EmptySlot-White.PNG");
	cui_B04->SetPos(D3DXVECTOR3(20 + 160, 75 + 48, 0));

	cUIButton* cui_B05;
	cui_B05 = new cUIButton;
	cui_B05->SetTexture("slot5", "shop_data/UI-EmptySlot.PNG", "shop_data/UI-EmptySlot-Disabled.PNG", "shop_data/UI-EmptySlot-White.PNG");
	cui_B05->SetPos(D3DXVECTOR3(20, 75 + 96, 0));

	cUIButton* cui_B06;
	cui_B06 = new cUIButton;
	cui_B06->SetTexture("slot6", "shop_data/UI-EmptySlot.PNG", "shop_data/UI-EmptySlot-Disabled.PNG", "shop_data/UI-EmptySlot-White.PNG");
	cui_B06->SetPos(D3DXVECTOR3(20 + 160, 75 + 96, 0));

	cUIButton* cui_B07;
	cui_B07 = new cUIButton;
	cui_B07->SetTexture("slot7", "shop_data/UI-EmptySlot.PNG", "shop_data/UI-EmptySlot-Disabled.PNG", "shop_data/UI-EmptySlot-White.PNG");
	cui_B07->SetPos(D3DXVECTOR3(20, 75 + 144, 0));

	cUIButton* cui_B08;
	cui_B08 = new cUIButton;
	cui_B08->SetTexture("slot8", "shop_data/UI-EmptySlot.PNG", "shop_data/UI-EmptySlot-Disabled.PNG", "shop_data/UI-EmptySlot-White.PNG");
	cui_B08->SetPos(D3DXVECTOR3(20 + 160, 75 + 144, 0));

	cUIButton* cui_B09;
	cui_B09 = new cUIButton;
	cui_B09->SetTexture("slot9", "shop_data/UI-EmptySlot.PNG", "shop_data/UI-EmptySlot-Disabled.PNG", "shop_data/UI-EmptySlot-White.PNG");
	cui_B09->SetPos(D3DXVECTOR3(20, 75 + 192, 0));

	cUIButton* cui_B10;
	cui_B10 = new cUIButton;
	cui_B10->SetTexture("slot10", "shop_data/UI-EmptySlot.PNG", "shop_data/UI-EmptySlot-Disabled.PNG", "shop_data/UI-EmptySlot-White.PNG");
	cui_B10->SetPos(D3DXVECTOR3(20 + 160, 75 + 192, 0));

	cUIButton* cui_BLT;
	cui_BLT = new cUIButton;
	cui_BLT->SetTexture("push_left_Square", "shop_data/SHOP_UI/UI-SquareButton-LEFT-Up.PNG", "shop_data/SHOP_UI/UI-SquareButton-LEFT-Disabled.PNG", "shop_data/SHOP_UI/UI-SquareButton-LEFT-Down.PNG");
	cui_BLT->SetPos(D3DXVECTOR3(30, 335, 0));

	cUIButton* cui_BRT;
	cui_BRT = new cUIButton;
	cui_BRT->SetTexture("push_right_Square", "shop_data/SHOP_UI/UI-SquareButton-RIGHT-Up.PNG", "shop_data/SHOP_UI/UI-SquareButton-RIGHT-Disabled.PNG", "shop_data/SHOP_UI/UI-SquareButton-RIGHT-Down.PNG");
	cui_BRT->SetPos(D3DXVECTOR3(300, 335, 0));


	cUIButton* cui_BuyBack_EMPTY_ICON;
	cui_BuyBack_EMPTY_ICON = new cUIButton;
	cui_BuyBack_EMPTY_ICON->SetTexture("BuyBack_EMPTY_ICON", "shop_data/UI-EmptySlot.PNG", "shop_data/UI-EmptySlot-Disabled.PNG", "shop_data/UI-EmptySlot-White.PNG");
	cui_BuyBack_EMPTY_ICON->SetPos(D3DXVECTOR3(20 + 162, 75 + 296, 0));

	cUIButton* cui_BUY;
	cui_BUY = new cUIButton;
	cui_BUY->SetTexture("Buy", "shop_data/SHOP_UI/UI-Character-InActiveTab.PNG", "shop_data/SHOP_UI/UI-Character-ActiveTab.PNG", "shop_data/SHOP_UI/UI-Character-ActiveTab.PNG");
	cui_BUY->SetPos(D3DXVECTOR3(10, 450, 0));
	cui_BUY->SetScal(D3DXVECTOR3(0.8, 1, 0));

	cUIButton* cui_BUYBACK;
	cui_BUYBACK = new cUIButton;
	//cui_BUYBACK->SetTag(0);
	cui_BUYBACK->SetTexture("BuyBack", "shop_data/SHOP_UI/UI-Character-InActiveTab.PNG", "shop_data/SHOP_UI/UI-Character-ActiveTab.PNG", "shop_data/SHOP_UI/UI-Character-ActiveTab.PNG");
	cui_BUYBACK->SetPos(D3DXVECTOR3(120, 450, 0));
	cui_BUYBACK->SetScal(D3DXVECTOR3(0.8, 1, 0));
	//cui_BUYBACK->SetDelevery(dele_close);

	//add

	Shop_UI->AddChild(cui_I01);
	Shop_UI->AddChild(cui_I02);
	Shop_UI->AddChild(cui_I03);
	Shop_UI->AddChild(cui_I04);
	Shop_UI->AddChild(cui_I05);
	Shop_UI->AddChild(cui_I06);
	//Shop_UI->AddChild(cui_I07);
	Shop_UI->AddChild(cui_I08);

	Shop_UI->AddChild(cui_Item_slot01);
	Shop_UI->AddChild(cui_Item_slot02);
	Shop_UI->AddChild(cui_Item_slot03);
	Shop_UI->AddChild(cui_Item_slot04);
	Shop_UI->AddChild(cui_Item_slot05);
	Shop_UI->AddChild(cui_Item_slot06);
	Shop_UI->AddChild(cui_Item_slot07);
	Shop_UI->AddChild(cui_Item_slot08);
	Shop_UI->AddChild(cui_Item_slot09);
	Shop_UI->AddChild(cui_Item_slot10);

	Shop_UI->AddChild(cui_close);
	Shop_UI->AddChild(cui_BUY);
	Shop_UI->AddChild(cui_BUYBACK);

	Shop_UI->AddChild(cui_B01);
	Shop_UI->AddChild(cui_B02);
	Shop_UI->AddChild(cui_B03);
	Shop_UI->AddChild(cui_B04);
	Shop_UI->AddChild(cui_B05);
	Shop_UI->AddChild(cui_B06);
	Shop_UI->AddChild(cui_B07);
	Shop_UI->AddChild(cui_B08);
	Shop_UI->AddChild(cui_B09);
	Shop_UI->AddChild(cui_B10);
	Shop_UI->AddChild(cui_BLT);
	Shop_UI->AddChild(cui_BRT);
	Shop_UI->AddChild(cui_BuyBack_EMPTY_ICON);

	Shop_UI->AddChild(cui_T01);
	Shop_UI->AddChild(cui_T02);
	Shop_UI->AddChild(cui_T03);
	Shop_UI->AddChild(cui_T04);
	Shop_UI->AddChild(cui_T05);

}

void shop_class::setting_buyback_UI_frame()
{
	buybackShop_UI = new cUIObject;
	buybackShop_UI->Sethidden(true);
	//image

	cUIImage* cui_I01;
	cui_I01 = new cUIImage;
	cui_I01->SetTexture("shop_data/SHOP_UI/UI-Merchant-TopLeft.PNG");
	cui_I01->SetPos(D3DXVECTOR3(0, 0, 0));

	cUIImage* cui_I02;
	cui_I02 = new cUIImage;
	cui_I02->SetTexture("shop_data/SHOP_UI/UI-Merchant-TopRight.PNG");
	cui_I02->SetPos(D3DXVECTOR3(256, 0, 0));

	cUIImage* cui_I03;
	cui_I03 = new cUIImage;
	cui_I03->SetTexture("shop_data/SHOP_UI/UI-Merchant-BotLeft.PNG");
	cui_I03->SetPos(D3DXVECTOR3(0, 256, 0));

	cUIImage* cui_I04;
	cui_I04 = new cUIImage;
	cui_I04->SetTexture("shop_data/SHOP_UI/UI-Merchant-BotRight.png");
	cui_I04->SetPos(D3DXVECTOR3(256, 256, 0));

	cUIImage* cui_I08;
	cui_I08 = new cUIImage;
	cui_I08->SetTexture("shop_data/TEMPORARYPORTRAIT-MALE-TAUREN.PNG");
	cui_I08->SetPos(D3DXVECTOR3(12, 15, 0));
	cui_I08->SetScal(D3DXVECTOR3(0.8, 0.8, 0));


	cUIImage* cui_Item_slot01;
	cui_Item_slot01 = new cUIImage;
	cui_Item_slot01->SetTexture("shop_data/SHOP_UI/UI-Merchant-LabelSlots.PNG");
	cui_Item_slot01->SetPos(D3DXVECTOR3(67, 75, 0));

	cUIImage* cui_Item_slot02;
	cui_Item_slot02 = new cUIImage;
	cui_Item_slot02->SetTexture("shop_data/SHOP_UI/UI-Merchant-LabelSlots.PNG");
	cui_Item_slot02->SetPos(D3DXVECTOR3(67 + 160, 75, 0));

	cUIImage* cui_Item_slot03;
	cui_Item_slot03 = new cUIImage;
	cui_Item_slot03->SetTexture("shop_data/SHOP_UI/UI-Merchant-LabelSlots.PNG");
	cui_Item_slot03->SetPos(D3DXVECTOR3(67, 75 + 48, 0));

	cUIImage* cui_Item_slot04;
	cui_Item_slot04 = new cUIImage;
	cui_Item_slot04->SetTexture("shop_data/SHOP_UI/UI-Merchant-LabelSlots.PNG");
	cui_Item_slot04->SetPos(D3DXVECTOR3(67 + 160, 75 + 48, 0));

	cUIImage* cui_Item_slot05;
	cui_Item_slot05 = new cUIImage;
	cui_Item_slot05->SetTexture("shop_data/SHOP_UI/UI-Merchant-LabelSlots.PNG");
	cui_Item_slot05->SetPos(D3DXVECTOR3(67, 75 + 96, 0));

	cUIImage* cui_Item_slot06;
	cui_Item_slot06 = new cUIImage;
	cui_Item_slot06->SetTexture("shop_data/SHOP_UI/UI-Merchant-LabelSlots.PNG");
	cui_Item_slot06->SetPos(D3DXVECTOR3(67 + 160, 75 + 96, 0));

	cUIImage* cui_Item_slot07;
	cui_Item_slot07 = new cUIImage;
	cui_Item_slot07->SetTexture("shop_data/SHOP_UI/UI-Merchant-LabelSlots.PNG");
	cui_Item_slot07->SetPos(D3DXVECTOR3(67, 75 + 144, 0));

	cUIImage* cui_Item_slot08;
	cui_Item_slot08 = new cUIImage;
	cui_Item_slot08->SetTexture("shop_data/SHOP_UI/UI-Merchant-LabelSlots.PNG");
	cui_Item_slot08->SetPos(D3DXVECTOR3(67 + 160, 75 + 144, 0));

	cUIImage* cui_Item_slot09;
	cui_Item_slot09 = new cUIImage;
	cui_Item_slot09->SetTexture("shop_data/SHOP_UI/UI-Merchant-LabelSlots.PNG");
	cui_Item_slot09->SetPos(D3DXVECTOR3(67, 75 + 192, 0));

	cUIImage* cui_Item_slot10;
	cui_Item_slot10 = new cUIImage;
	cui_Item_slot10->SetTexture("shop_data/SHOP_UI/UI-Merchant-LabelSlots.PNG");
	cui_Item_slot10->SetPos(D3DXVECTOR3(67 + 160, 75 + 192, 0));

	cUIImage* cui_Item_slot11;
	cui_Item_slot11 = new cUIImage;
	cui_Item_slot11->SetTexture("shop_data/SHOP_UI/UI-Merchant-LabelSlots.PNG");
	cui_Item_slot11->SetPos(D3DXVECTOR3(67, 75 + 240, 0));

	cUIImage* cui_Item_slot12;
	cui_Item_slot12 = new cUIImage;
	cui_Item_slot12->SetTexture("shop_data/SHOP_UI/UI-Merchant-LabelSlots.PNG");
	cui_Item_slot12->SetPos(D3DXVECTOR3(67 + 160, 75 + 240, 0));

	cUIImage* cui_Item_slot13;
	cui_Item_slot13 = new cUIImage;
	cui_Item_slot13->SetTexture("shop_data/SHOP_UI/UI-Merchant-LabelSlots.PNG");
	cui_Item_slot13->SetPos(D3DXVECTOR3(67, 75 + 288, 0));

	cUIImage* cui_Item_slot14;
	cui_Item_slot14 = new cUIImage;
	cui_Item_slot14->SetTexture("shop_data/SHOP_UI/UI-Merchant-LabelSlots.PNG");
	cui_Item_slot14->SetPos(D3DXVECTOR3(67 + 160, 75 + 288, 0));

	//text

	cUIText* cui_T01;
	cui_T01 = new cUIText;
	cui_T01->SetupText("타우렌 상점", ST_SIZE(150, 25), cFontManager::FT_STORE, D3DXCOLOR(255, 255, 0, 255));
	cui_T01->SetPos(D3DXVECTOR3(145, 17, 0));

	cUIText* cui_T02;
	cui_T02 = new cUIText;
	cui_T02->SetupText("상품 목록", ST_SIZE(80, 25), cFontManager::FT_STORE, D3DXCOLOR(255, 255, 0, 255));
	cui_T02->SetPos(D3DXVECTOR3(23, 455, 0));

	cUIText* cui_T03;
	cui_T03 = new cUIText;
	cui_T03->SetupText("재 매입", ST_SIZE(80, 25), cFontManager::FT_STORE, D3DXCOLOR(255, 255, 0, 255));
	cui_T03->SetPos(D3DXVECTOR3(135, 455, 0));

	//button

	Button_delegate* dele_close = new Button_delegate;

	cUIButton* cui_close;
	cui_close = new cUIButton;
	cui_close->SetTag(1);
	cui_close->SetTexture("buybackclose", "shop_data/UI-Panel-MinimizeButton-Up.PNG", "shop_data/UI-Panel-MinimizeButton-Disabled.PNG", "shop_data/UI-Panel-MinimizeButton-Down.PNG");
	cui_close->SetPos(D3DXVECTOR3(322, 8, 0));
	cui_close->SetDeleGate(dele_close);

	cUIButton* cui_B01;
	cui_B01 = new cUIButton;
	cui_B01->SetTexture("BBslot1", "shop_data/UI-EmptySlot.PNG", "shop_data/UI-EmptySlot-Disabled.PNG", "shop_data/UI-EmptySlot-White.PNG");
	cui_B01->SetPos(D3DXVECTOR3(20, 75, 0));

	cUIButton* cui_B02;
	cui_B02 = new cUIButton;
	cui_B02->SetTexture("BBslot2", "shop_data/UI-EmptySlot.PNG", "shop_data/UI-EmptySlot-Disabled.PNG", "shop_data/UI-EmptySlot-White.PNG");
	cui_B02->SetPos(D3DXVECTOR3(20 + 160, 75, 0));

	cUIButton* cui_B03;
	cui_B03 = new cUIButton;
	cui_B03->SetTexture("BBslot3", "shop_data/UI-EmptySlot.PNG", "shop_data/UI-EmptySlot-Disabled.PNG", "shop_data/UI-EmptySlot-White.PNG");
	cui_B03->SetPos(D3DXVECTOR3(20, 75 + 48, 0));

	cUIButton* cui_B04;
	cui_B04 = new cUIButton;
	cui_B04->SetTexture("BBslot4", "shop_data/UI-EmptySlot.PNG", "shop_data/UI-EmptySlot-Disabled.PNG", "shop_data/UI-EmptySlot-White.PNG");
	cui_B04->SetPos(D3DXVECTOR3(20 + 160, 75 + 48, 0));

	cUIButton* cui_B05;
	cui_B05 = new cUIButton;
	cui_B05->SetTexture("BBslot5", "shop_data/UI-EmptySlot.PNG", "shop_data/UI-EmptySlot-Disabled.PNG", "shop_data/UI-EmptySlot-White.PNG");
	cui_B05->SetPos(D3DXVECTOR3(20, 75 + 96, 0));

	cUIButton* cui_B06;
	cui_B06 = new cUIButton;
	cui_B06->SetTexture("BBslot6", "shop_data/UI-EmptySlot.PNG", "shop_data/UI-EmptySlot-Disabled.PNG", "shop_data/UI-EmptySlot-White.PNG");
	cui_B06->SetPos(D3DXVECTOR3(20 + 160, 75 + 96, 0));

	cUIButton* cui_B07;
	cui_B07 = new cUIButton;
	cui_B07->SetTexture("BBslot7", "shop_data/UI-EmptySlot.PNG", "shop_data/UI-EmptySlot-Disabled.PNG", "shop_data/UI-EmptySlot-White.PNG");
	cui_B07->SetPos(D3DXVECTOR3(20, 75 + 144, 0));

	cUIButton* cui_B08;
	cui_B08 = new cUIButton;
	cui_B08->SetTexture("BBslot8", "shop_data/UI-EmptySlot.PNG", "shop_data/UI-EmptySlot-Disabled.PNG", "shop_data/UI-EmptySlot-White.PNG");
	cui_B08->SetPos(D3DXVECTOR3(20 + 160, 75 + 144, 0));

	cUIButton* cui_B09;
	cui_B09 = new cUIButton;
	cui_B09->SetTexture("BBslot9", "shop_data/UI-EmptySlot.PNG", "shop_data/UI-EmptySlot-Disabled.PNG", "shop_data/UI-EmptySlot-White.PNG");
	cui_B09->SetPos(D3DXVECTOR3(20, 75 + 192, 0));

	cUIButton* cui_B10;
	cui_B10 = new cUIButton;
	cui_B10->SetTexture("BBslot10", "shop_data/UI-EmptySlot.PNG", "shop_data/UI-EmptySlot-Disabled.PNG", "shop_data/UI-EmptySlot-White.PNG");
	cui_B10->SetPos(D3DXVECTOR3(20 + 160, 75 + 192, 0));

	cUIButton* cui_B11;
	cui_B11 = new cUIButton;
	cui_B11->SetTexture("BBslot11", "shop_data/UI-EmptySlot.PNG", "shop_data/UI-EmptySlot-Disabled.PNG", "shop_data/UI-EmptySlot-White.PNG");
	cui_B11->SetPos(D3DXVECTOR3(20, 75 + 240, 0));

	cUIButton* cui_B12;
	cui_B12 = new cUIButton;
	cui_B12->SetTexture("BBslot12", "shop_data/UI-EmptySlot.PNG", "shop_data/UI-EmptySlot-Disabled.PNG", "shop_data/UI-EmptySlot-White.PNG");
	cui_B12->SetPos(D3DXVECTOR3(20 + 160, 75 + 240, 0));

	cUIButton* cui_B13;
	cui_B13 = new cUIButton;
	cui_B13->SetTexture("BBslot13", "shop_data/UI-EmptySlot.PNG", "shop_data/UI-EmptySlot-Disabled.PNG", "shop_data/UI-EmptySlot-White.PNG");
	cui_B13->SetPos(D3DXVECTOR3(20, 75 + 288, 0));

	cUIButton* cui_B14;
	cui_B14 = new cUIButton;
	cui_B14->SetTexture("BBslot14", "shop_data/UI-EmptySlot.PNG", "shop_data/UI-EmptySlot-Disabled.PNG", "shop_data/UI-EmptySlot-White.PNG");
	cui_B14->SetPos(D3DXVECTOR3(20 + 160, 75 + 288, 0));

	cUIButton* cui_BUY;
	cui_BUY = new cUIButton;
	cui_BUY->SetTexture("BBBuy", "shop_data/SHOP_UI/UI-Character-InActiveTab.PNG", "shop_data/SHOP_UI/UI-Character-ActiveTab.PNG", "shop_data/SHOP_UI/UI-Character-ActiveTab.PNG");
	cui_BUY->SetPos(D3DXVECTOR3(10, 450, 0));
	cui_BUY->SetScal(D3DXVECTOR3(0.8, 1, 0));

	cUIButton* cui_BUYBACK;
	cui_BUYBACK = new cUIButton;
	cui_BUYBACK->SetTexture("BBBuyBack", "shop_data/SHOP_UI/UI-Character-InActiveTab.PNG", "shop_data/SHOP_UI/UI-Character-ActiveTab.PNG", "shop_data/SHOP_UI/UI-Character-ActiveTab.PNG");
	cui_BUYBACK->SetPos(D3DXVECTOR3(120, 450, 0));
	cui_BUYBACK->SetScal(D3DXVECTOR3(0.8, 1, 0));

	//add

	buybackShop_UI->AddChild(cui_I01);
	buybackShop_UI->AddChild(cui_I02);
	buybackShop_UI->AddChild(cui_I03);
	buybackShop_UI->AddChild(cui_I04);
	buybackShop_UI->AddChild(cui_I08);

	buybackShop_UI->AddChild(cui_Item_slot01);
	buybackShop_UI->AddChild(cui_Item_slot02);
	buybackShop_UI->AddChild(cui_Item_slot03);
	buybackShop_UI->AddChild(cui_Item_slot04);
	buybackShop_UI->AddChild(cui_Item_slot05);
	buybackShop_UI->AddChild(cui_Item_slot06);
	buybackShop_UI->AddChild(cui_Item_slot07);
	buybackShop_UI->AddChild(cui_Item_slot08);
	buybackShop_UI->AddChild(cui_Item_slot09);
	buybackShop_UI->AddChild(cui_Item_slot10);
	buybackShop_UI->AddChild(cui_Item_slot11);
	buybackShop_UI->AddChild(cui_Item_slot12);
	buybackShop_UI->AddChild(cui_Item_slot13);
	buybackShop_UI->AddChild(cui_Item_slot14);

	buybackShop_UI->AddChild(cui_close);
	buybackShop_UI->AddChild(cui_BUY);
	buybackShop_UI->AddChild(cui_BUYBACK);

	buybackShop_UI->AddChild(cui_B01);
	buybackShop_UI->AddChild(cui_B02);
	buybackShop_UI->AddChild(cui_B03);
	buybackShop_UI->AddChild(cui_B04);
	buybackShop_UI->AddChild(cui_B05);
	buybackShop_UI->AddChild(cui_B06);
	buybackShop_UI->AddChild(cui_B07);
	buybackShop_UI->AddChild(cui_B08);
	buybackShop_UI->AddChild(cui_B09);
	buybackShop_UI->AddChild(cui_B10);
	buybackShop_UI->AddChild(cui_B11);
	buybackShop_UI->AddChild(cui_B12);
	buybackShop_UI->AddChild(cui_B13);
	buybackShop_UI->AddChild(cui_B14);

	buybackShop_UI->AddChild(cui_T01);
	buybackShop_UI->AddChild(cui_T02);
	buybackShop_UI->AddChild(cui_T03);

}


void shop_class::setting_show_item_UI()
{
	for (int i = Now_page_num - 1; i < Now_page_num * 10 - 1; i++)
	{
		if (v_shop_sell_Things.size() <= i) break;

		item_slot[i % 10].item_num = v_shop_sell_Things[i]->GetI_num();

		char chartext[1024];
		sprintf(chartext, "shop_data/%s", v_shop_sell_Things[i]->GetI_image().c_str());

		item_slot[i % 10].item_slot->SetTexture(chartext);
		item_slot[i % 10].item_slot->SetScal(D3DXVECTOR3(0.58, 0.58, 0));
		item_slot[i % 10].item_slot->SetPos(D3DXVECTOR3(Shop_UI->GetPos().x + 24 + 160 * (i % 2), Shop_UI->GetPos().y + 80 + 48 * (i / 2), 0));

		sprintf(chartext, "%s", (v_shop_sell_Things[i]->GetI_name()));

		item_slot[i % 10].item_Main_name->SetupText(chartext, ST_SIZE(150, 25), cFontManager::FT_STORE, D3DXCOLOR(255, 255, 0, 255));
		item_slot[i % 10].item_Main_name->SetPos(D3DXVECTOR3(Shop_UI->GetPos().x + 70 + 160 * (i % 2), Shop_UI->GetPos().y + 80 + 48 * (i / 2), 0));

		setting_moneyFram(Shop_UI->GetPos().x + 70 + 160 * (i % 2),
			Shop_UI->GetPos().y + 80 + 48 * (i / 2),
			i,
			v_shop_sell_Things[i]->GetI_option().Price);
	}
}

void shop_class::setting_moneyFram(float x, float y, int headnum, int money)
{
	char chartext[1024];

	float finx, finy;

	finx = x;
	finy = y + 20;

	if (money / 100 >= 1)
	{
		item_slot[headnum].item_money[0]->SetTexture("shop_data/UI-GoldIcon.PNG");
		item_slot[headnum].item_money[0]->SetPos(D3DXVECTOR3(finx, finy, 0));

		sprintf(chartext, "%d", money / 100);

		finx += 15;

		item_slot[headnum].item_moeny_text[0]->SetupText(chartext, ST_SIZE(150, 25), cFontManager::FT_STORE, D3DXCOLOR(255, 255, 0, 255));
		item_slot[headnum].item_moeny_text[0]->SetPos(D3DXVECTOR3(finx, finy, 0));

		finx += 20;
	}

	if ((money % 100) / 10 >= 1)
	{
		item_slot[headnum].item_money[1]->SetTexture("shop_data/UI-SilverIcon.PNG");
		item_slot[headnum].item_money[1]->SetPos(D3DXVECTOR3(finx, finy, 0));

		sprintf(chartext, "%d", (money % 100) / 10);

		finx += 15;

		item_slot[headnum].item_moeny_text[1]->SetupText(chartext, ST_SIZE(150, 25), cFontManager::FT_STORE, D3DXCOLOR(255, 255, 0, 255));
		item_slot[headnum].item_moeny_text[1]->SetPos(D3DXVECTOR3(finx, finy, 0));

		finx += 20;
	}
	if ((money % 100) % 10 >= 1)
	{
		item_slot[headnum].item_money[2]->SetTexture("shop_data/UI-CopperIcon.PNG");
		item_slot[headnum].item_money[2]->SetPos(D3DXVECTOR3(finx, finy, 0));

		sprintf(chartext, "%d", (money % 100) % 10);

		finx += 15;

		item_slot[headnum].item_moeny_text[2]->SetupText(chartext, ST_SIZE(150, 25), cFontManager::FT_STORE, D3DXCOLOR(255, 255, 0, 255));
		item_slot[headnum].item_moeny_text[2]->SetPos(D3DXVECTOR3(finx, finy, 0));

		finx += 20;
	}
}

bool shop_class::ischeck(OUT int & nums)
{
	RECT rc;

	for (int i = 0; i < 10; i++)
	{
		SetRect(&rc, item_slot[i].item_slot->GetPos().x,
			item_slot[i].item_slot->GetPos().y,
			item_slot[i].item_slot->GetPos().x + 40,
			item_slot[i].item_slot->GetPos().y + 40);

		if (PtInRect(&rc, MOUSE))
		{
			nums = i;
			return true;
		}
	}

	return false;
}
