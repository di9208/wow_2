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
	for each(auto p in _vtestitem)
	{
		SAFE_DELETE(p);
	}

	SAFE_DELETE(_shops);
	SAFE_RELEASE(UI_sprite);
	shop_inven_UI.clear();
	SAFE_DELETE(WM_MANAGER);
	SAFE_DELETE(_npc);
	SAFE_DELETE(_invens);
}

void shop_TEST_CLASS::Setup()
{
	D3DXCreateSprite(g_pD3DDevice, &UI_sprite);

	_npc = new cNpc;
	_npc->Setup();

	_shops = new shop_class;
	_shops->Setup();

	_invens = new inventory;
	_invens->Setup();

	WM_MANAGER = new wordManager;
	WM_MANAGER->SetFont();

	cUIImage* _UImouse;
	_UImouse = new cUIImage;
	_UImouse->SetTexture("shop_data/cursor/Attack.PNG");
	_mouse = _UImouse;
	_mouse->Sethidden(true);

	shop_inven_calling_now_num = 0;
	Money = 1000;

	shop_inven_UI.resize(28);
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			shop_inven_UI[i * 7 + j].x = 41 + 49 * j;
			shop_inven_UI[i * 7 + j].y = 74 + 43 * i;
		}
	}
}

void shop_TEST_CLASS::Update()
{
	if (_npc)
		_npc->update();

	if (_npc->GetM_info().bIsPicked)
	{
		_shops->GetSHOP()->Sethidden(false);
		_invens->GetINVEN()->Sethidden(false);
	}

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

	_mouse->SetPos(D3DXVECTOR3(Pt.x, Pt.y, 0));

	_mouse->Update();
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

	if (is_now_picking_item(UI_sprite))
	{
		_mouse->Render(UI_sprite);
	}

	UI_sprite->End();
}
void  shop_TEST_CLASS::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_SETCURSOR:
		SetCursor(NULL);
		ShowCursor(true);
		break;
	}
}

bool shop_TEST_CLASS::is_now_picking_item(LPD3DXSPRITE sprite)
{
	for (int i = 0; i < _vtestitem.size(); i++)
	{
		if (_vtestitem[i]->GetI_PICK() == true)
		{
			return false;
		}
	}
	return true;
}