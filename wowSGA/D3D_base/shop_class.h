#pragma once
class item_class;
class cUIObject;
class cUIText;
class cUIImage;
class Button_delegate;

class shop_class
{
	struct tag_slot
	{
		cUIImage* item_slot;
		cUIText* item_Main_name;
		cUIImage* item_money[3];
		cUIText* item_moeny_text[3];
		int item_num;
	};


private:
	POINT MOUSE;
	tag_slot item_slot[10];

	tag_slot buyback_item_slot;

	cUIText* Page_TEXT_UI;
	int Now_page_num;
	int Page_num;

	SYNTHESIZE(cUIObject*, Shop_UI, SHOP);
	SYNTHESIZE(cUIObject*, buybackShop_UI, buybackSHOP);

	SYNTHESIZE(RECT, Shop_UI_RECT, SHOP_Rect);

	std::vector<item_class*> v_shop_sell_Things;
	std::vector<item_class*> before_selling_Things;
public:
	shop_class();
	~shop_class();

	void Setup();
	void update();
	void render(LPD3DXSPRITE in_subsprite);

	void buy(IN int nums, OUT int & money, OUT item_class* buyitem);
	void sell(IN int nums, OUT int & money);
	void rebuy(IN int nums, OUT int & money, OUT item_class* buyitem);

	void setting_UI_frame();
	void setting_show_item_UI();
	void setting_buyback_UI_frame();

	void setting_moneyFram(float x, float y, int headnum, int money);

	bool ischeck(OUT int & nums);

	tag_slot Get_item_slot(int i) { return item_slot[i]; }
};

