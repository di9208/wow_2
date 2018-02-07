#pragma once

class cUIObject;
class DragAndDrob;
class item_class;
class cUIImage;
class cUIText;

class inventory
{
private:
	SYNTHESIZE(cUIObject*, inven_UI, INVEN);
	DragAndDrob* drage;

	std::vector<item_class*> V_INVEN;

	int Money;

	cUIImage* item_slot[16];

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
};

