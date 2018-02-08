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

	SYNTHESIZE(int, picking_nums, pick_number);
	SYNTHESIZE(bool, picking_isit, pick_Truefalse);

	LPDIRECT3DTEXTURE9 mouse_cursorImage;

	SYNTHESIZE(bool, is_interface, isinterface);
public:
	shop_TEST_CLASS();
	~shop_TEST_CLASS();

	void Setup();
	void Update();
	void Render();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	inventory* get_inven() { return _invens; }
	//void resetting_inven() 
	//{
	//	//_invens->Setting_items();
	//}
};

