#pragma once

class cUIObject;
class item_class;
class cUIImage;
class cUIText;

class inventory
{
	struct tag_slot
	{
		cUIImage* item_slot;
		int item_num;
	};

private:
	POINT MOUSE;

	SYNTHESIZE(cUIObject*, inven_UI, INVEN);

	SYNTHESIZE(std::vector<item_class*>, V_INVEN, vector_inven);

	SYNTHESIZE(int, Money, MONEY);

	tag_slot item_slot[16];

	cUIImage* money_image[3];
	cUIText* money_text[3];

public:
	inventory();
	~inventory();

	void Setup();
	void Update();
	void Render(LPD3DXSPRITE in_Sprite);

	void Setting_invenUI();
	void Setting_items();
	void setting_moneyFram(float x, float y);
	void Add_inven(item_class* temp);
	void delete_inven(int arry);
	bool ischeck(OUT int & nums);

	tag_slot Get_item_slot(int i) { return item_slot[i]; }

	void Set_item_slot(int i, D3DXVECTOR3 pt);


};

