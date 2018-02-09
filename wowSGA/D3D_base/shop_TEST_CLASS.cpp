#include "stdafx.h"
#include "shop_TEST_CLASS.h"
#include "shop_class.h"
#include "item_class.h"
#include "item_loader.h"
#include "cUIObject.h"
#include "cUIImage.h"
#include "cUIButton.h"
#include "cUIText.h"
#include "wordManager.h"
#include "cNpc.h"
#include "inventory.h"
#include "cPlayerInFo.h"

shop_TEST_CLASS::shop_TEST_CLASS()
	: _shops(NULL)
	, WM_MANAGER(NULL)
	, _npc(NULL)
	, _invens(NULL)
{
	Pt.x = Pt.y = 0;
	cursor_text = false;
	is_interface = false;
}


shop_TEST_CLASS::~shop_TEST_CLASS()
{
	SAFE_DELETE(_shops);
	SAFE_RELEASE(UI_sprite);
	shop_inven_UI.clear();
	SAFE_DELETE(WM_MANAGER);
	SAFE_DELETE(_npc);
	SAFE_DELETE(_invens);

	//_mouse->Destroy();
}

void shop_TEST_CLASS::Setup(D3DXVECTOR3 pos)
{
	D3DXCreateSprite(g_pD3DDevice, &UI_sprite);

	g_pSoundManager->Setup();
	g_pSoundManager->addSound("shopopend", "sound/shop&inven/상점열기.mp3", true, false);
	g_pSoundManager->addSound("golds", "sound/shop&inven/골드.mp3", true, false);
	g_pSoundManager->addSound("buythings", "sound/shop&inven/아이템사기나 줍기.mp3", true, false);

	_npc = new cNpc;
	_npc->Setup(pos);

	_shops = new shop_class;
	_shops->Setup();

	_invens = new inventory;
	_invens->Setup();

	WM_MANAGER = new wordManager;
	WM_MANAGER->SetFont();

	//cUIImage* _UImouse;
	//_UImouse = new cUIImage;
	//_UImouse->SetTexture("shop_data/cursor/Attack.PNG");
	//_mouse = _UImouse;
	//_mouse->Sethidden(true);

	shop_inven_calling_now_num = 0;

	shop_inven_UI.resize(28);
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			shop_inven_UI[i * 7 + j].x = 41 + 49 * j;
			shop_inven_UI[i * 7 + j].y = 74 + 43 * i;
		}
	}
	picking_isit = false;
}

void shop_TEST_CLASS::Update()
{
	if (_npc)
		_npc->update();

	if (_npc->GetRAYPICK())
	{
		g_pSoundManager->play("shopopend", 1.0f);
		_shops->GetSHOP()->Sethidden(false);
		_invens->GetINVEN()->Sethidden(false);
		player_info_page->GetEquite_window()->Sethidden(true);
		_npc->SetRAYPICK(false);
		is_interface = true;
	}


	if (_invens->GetINVEN()->Gethidden())
	{
		if (g_pKeyManager->isOnceKeyDown('B'))
		{
			g_pSoundManager->play("shopopend", 1.0f);
			_invens->GetINVEN()->Sethidden(false);
		}
	}
	else if (!_invens->GetINVEN()->Gethidden())
	{
		if (g_pKeyManager->isOnceKeyDown('B'))
		{
			_invens->GetINVEN()->Sethidden(true);
		}
	}

	//사고 팔기
	int item_nums = 0;
	if (!_shops->GetSHOP()->Gethidden())
	{
		if (_shops->ischeck(item_nums))
		{
			if (g_pKeyManager->isOnceKeyDown(VK_RBUTTON))
			{
				if (_invens->Getvector_inven().size() < 16)
				{
					item_class* temp;
					temp = new item_class;

					int money_temp = _invens->GetMONEY();

					int a = 0;
					_shops->buy(_shops->Get_item_slot(item_nums).item_num, money_temp, temp);

					_invens->SetMONEY(money_temp);
					_invens->Add_inven(temp);

					g_pSoundManager->play("buythings", 1.0f);
				}
			}
		}
		if (!_invens->GetINVEN()->Gethidden())
		{
			if (_invens->ischeck(item_nums) && !picking_isit)
			{
				if (g_pKeyManager->isOnceKeyDown(VK_RBUTTON))
				{
					item_class* temp;
					temp = new item_class;

					int money_temp = _invens->GetMONEY();

					_shops->sell(_invens->Get_item_slot(item_nums).item_num, money_temp);

					_invens->SetMONEY(money_temp);
					_invens->delete_inven(item_nums);
					g_pSoundManager->play("golds", 1.0f);
				}
			}
		}
	}
	//

	if (!_invens->GetINVEN()->Gethidden())
	{
		if (!picking_isit)
		{
			if (_invens->ischeck(item_nums))
			{
				if (g_pKeyManager->isOnceKeyDown(VK_RBUTTON))
				{
					picking_isit = true;
					picking_nums = item_nums;
				}
			}
		}
	}

	//if (!_invens->GetINVEN()->Gethidden())
	//{
	//	if (picking_isit)
	//	{
	//		_invens->Set_item_slot(picking_nums, D3DXVECTOR3(Pt.x, Pt.y, 0));
	//		_invens->Get_item_slot(picking_nums).item_slot->Update();
	//	}
	//}
	/*if (sender.pick_now)
	{
	sender.mouse_pick->SetPos(D3DXVECTOR3(Pt.x - 20, Pt.y - 20, 0));

	sender.mouse_pick->Update();

	if (GetKeyState(VK_LBUTTON) & 0x0001)
	{
	sender.mouse_pick->Destroy();

	sender.mouse_pick = new cUIImage;

	sender.pick_now = false;
	}

	}*/


	//if (is_interface)
	//{
	//	for (int i = 0; i < _invens->Getvector_inven().size(); i++)
	//	{
	//		RECT PINKING_R;
	//
	//		SetRect(&PINKING_R, _invens->Getslot()[i].GetPos().x,
	//			_invens->Getslot()[i].GetPos().y,
	//			_invens->Getslot()[i].GetPos().x + _invens->Getslot()[i].GetSize().nWidth,
	//			_invens->Getslot()[i].GetPos().y + _invens->Getslot()[i].GetSize().nHeight);
	//
	//		if (PtInRect(&PINKING_R, Pt))
	//		{
	//			if (g_pKeyManager->isOnceKeyDown(VK_LBUTTON))
	//			{
	//				//뭔가 트루
	//				sender.item_data = _invens->Getvector_inven()[i];
	//				sender.mouse_pick = &_invens->Getslot()[i];
	//				sender.pick_now = true;
	//			}
	//		}
	//
	//	  }
	//  }
	//
	//if (g_pKeyManager->isOnceKeyUp(VK_LBUTTON) && sender.pick_now)
	//{
	//	//뭔가 안트루
	//	sender.pick_now = false;
	//}
	//
	//if (g_pKeyManager->isOnceKeyDown('M'))
	//{
	//if (shop_inven_UI.size() > shop_inven_calling_now_num)
	//{
	//	item_class* temp;
	//	temp = new item_class;
	//	_shops->buy(0, Money, temp);
	//	
	//	char char_temp[1024];
	//	ZeroMemory(&char_temp, 1024);
	//	sprintf(char_temp, "shop_data/%s", temp->GetI_image().c_str());
	//	temp->Setting_cUIImage(D3DXVECTOR3(_UIob->GetPos().x + shop_inven_UI[shop_inven_calling_now_num].x,
	//		_UIob->GetPos().y + shop_inven_UI[shop_inven_calling_now_num].y, 0),
	//		char_temp, D3DXVECTOR3(0.6, 0.6, 0));
	//
	//	RECT RECTTEMP;
	//	SetRect(&RECTTEMP, _UIob->GetPos().x + shop_inven_UI[shop_inven_calling_now_num].x, 
	//		_UIob->GetPos().y + shop_inven_UI[shop_inven_calling_now_num].y,
	//		_UIob->GetPos().x + shop_inven_UI[shop_inven_calling_now_num].x + 38,
	//		_UIob->GetPos().x + shop_inven_UI[shop_inven_calling_now_num].y + 35);
	//	temp->SetI_Rect(RECTTEMP);
	//
	//	_vtestitem.push_back(temp);
	//
	//	shop_inven_calling_now_num++;
	//}
	//}
	//if (g_pKeyManager->isStayKeyDown(VK_LBUTTON))
	//{	
	//	for (int i = 0; i < _vtestitem.size(); i++)
	//	{
	//		if (PtInRect(&_vtestitem[i]->GetI_Rect(), Pt))
	//		{
	//			_vtestitem[i]->SetI_PICK(true);
	//		}
	//	}
	//}

	GetCursorPos(&Pt);
	ScreenToClient(g_hWnd, &Pt);

	//_mouse->SetPos(D3DXVECTOR3(Pt.x, Pt.y, 0));
	//_mouse->Update();

	_shops->update();
	_invens->Update();
}

void shop_TEST_CLASS::Render()
{

	if (_npc)
		_npc->render();


	UI_sprite->Begin(D3DXSPRITE_ALPHABLEND);

	_shops->render(UI_sprite);
	_invens->Render(UI_sprite);

	if (!cursor_text)
	{
		char ssssstemp[1024];
		sprintf_s(ssssstemp, 1024, "%d , %d", Pt.x, Pt.y);
		WM_MANAGER->Render(ssssstemp, Pt.x, Pt.y + 20, 100, 20);
	}

	//if (is_now_picking_item(UI_sprite))
	//{
	//	_mouse->Render(UI_sprite);
	//}

	UI_sprite->End();
}
void  shop_TEST_CLASS::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//switch (message)
	//{
	//case WM_SETCURSOR:
	//	SetCursor(NULL);
	//	ShowCursor(true);
	//	break;
	//}
}
