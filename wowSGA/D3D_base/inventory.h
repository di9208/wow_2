#pragma once

class cUIObject;
class DragAndDrob;
class item_class;

class inventory
{
private:
	SYNTHESIZE(cUIObject*, inven_UI, INVEN);
	DragAndDrob* drage;

	std::vector<item_class*> V_INVEN;
	std::vector<ST_SIZE> all_size;

	int Money;
public:
	inventory();
	~inventory();

	void Setup();
	void Update();
	void Render(LPD3DXSPRITE in_Sprite);

	void Setting_invenUI();

};

