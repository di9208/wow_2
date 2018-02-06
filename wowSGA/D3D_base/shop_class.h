#pragma once
class item_class;
class cUIObject;
class cUIText;
class cUIImage;
class Button_delegate;
class DragAndDrob;

class shop_class
{

private:
	POINT MOUSE;
	DragAndDrob* dragFution;

	cUIImage* item_slot[10];
	cUIText* item_Main_name[10];
	cUIText* item_Sub_name[10];

	cUIText* Page_TEXT_UI;
	int Now_page_num;
	int Page_num;

	SYNTHESIZE(cUIObject*, Shop_UI, SHOP);
	SYNTHESIZE(RECT, Shop_UI_RECT, SHOP_Rect);

	std::vector<item_class*> v_shop_sell_Things;
	std::vector<item_class*> before_selling_Things;
public:
	shop_class();
	~shop_class();

	void Setup();
	void update();
	void render(LPD3DXSPRITE in_subsprite);

	void buy(IN int nums, OUT float & money, OUT item_class* buyitem);
	void sell(IN int nums, OUT float & money);
	void rebuy(IN int nums, OUT float & money, OUT item_class* buyitem);

	void setting_UI_frame();
	void setting_show_item_UI();
	void reset_item_UI();
};

