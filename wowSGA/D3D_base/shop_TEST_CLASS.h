#pragma once
class shop_class;
class item_class;
class cUIObject;
class cUIImage;
class wordManager;
class cNpc;
class inventory;

class shop_TEST_CLASS
{
	struct tag_shop_sub_room
	{
		float x;
		float y;
		int item_num;
	};

	struct Tag_picking_mouse
	{
		cUIImage* mouse_pick;
		bool pick_now;
		item_class* item_data;
	};

private:
	shop_class* _shops;
	inventory* _invens;

	cUIObject* _UIob;
	cUIObject* _mouse;

	cNpc* _npc;

	std::vector<tag_shop_sub_room> shop_inven_UI;
	LPD3DXSPRITE UI_sprite;

	int shop_inven_calling_now_num;

	wordManager* WM_MANAGER;
	POINT Pt;
	RECT rc;

	bool cursor_text;

	LPDIRECT3DTEXTURE9 mouse_cursorImage;

	SYNTHESIZE(Tag_picking_mouse, sender, picking_data);

	SYNTHESIZE(bool, is_interface, isinterface);
public:
	shop_TEST_CLASS();
	~shop_TEST_CLASS();

	void Setup();
	void Update();
	void Render();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

