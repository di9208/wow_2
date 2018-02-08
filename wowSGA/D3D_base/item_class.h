#pragma once
//#include "cUIObject.h"
//#include "cUIImage.h"
//#include "cUIButton.h"
//#include "cUIText.h"

class item_class
{
	enum item_where
	{
		EQUIT_item,
		inventory_item,
		inventory_collect,
		inventory_map
	};

	enum item_type
	{
		weapon,		//公扁
		Armor,		//规绢备
		special_item,	//
		Interaction_item,
		using_item	//器记
	};


	struct item_option
	{
		int ATK;
		int DEF;
		float ATK_SPEED;
		int Price;
		int Upgrade;
	};

private:
	//item main info
	SYNTHESIZE(item_option, ItemOption, _Ioption);
	SYNTHESIZE(item_where, ItemWhere, _Iwhere);
	SYNTHESIZE(item_type, ItemType, _Itype);
	SYNTHESIZE(std::string, ItemName, _Iname);
	SYNTHESIZE(std::string, ItemSub, _ISub);
	SYNTHESIZE(int, ItemNumber, _Inum);
	SYNTHESIZE(int, ItemVolume, _Ivolume);
	SYNTHESIZE(bool, ItemEquit, _Iequit);
	SYNTHESIZE(std::string, ItemImage, _Iimage);

	//item sub info - 1 (UI interface Part)
	SYNTHESIZE(RECT, Rc, I_Rect);
	SYNTHESIZE(float, Ix, I_x);
	SYNTHESIZE(float, Iy, I_y);
	SYNTHESIZE(float, IW, I_width);
	SYNTHESIZE(float, IH, I_height);
	SYNTHESIZE(bool, Ipicking, I_PICK);

	//cUIObject * m_item;
public:
	item_class();
	~item_class();

	void setting_option(int _atk, int _def, float _atk_speed, int _price, int _upgrade)
	{
		ItemOption.ATK = _atk;
		ItemOption.DEF = _def;
		ItemOption.ATK_SPEED = _atk_speed;
		ItemOption.Price = _price;
		ItemOption.Upgrade = _upgrade;
	}

	void setting_type(int num)
	{
		switch (num)
		{
		case 0:
			ItemType = weapon;
			break;
		case 1:
			ItemType = Armor;
			break;
		case 2:
			ItemType = special_item;
			break;
		case 3:
			ItemType = Interaction_item;
			break;
		case 4:
			ItemType = using_item;
			break;
		}
	}

	void setting_where(int num)
	{
		switch (num)
		{
		case 0:
			ItemWhere = EQUIT_item;
			break;
		case 1:
			ItemWhere = inventory_item;
			break;
		case 2:
			ItemWhere = inventory_collect;
			break;
		case 3:
			ItemWhere = inventory_map;
			break;
		}
	}

	//void Setting_cUIButton(D3DXVECTOR3 POS, char * image_up, char * image_over, char * image_down);
	//void Setting_cUIImage(D3DXVECTOR3 POS, char * image_text, D3DXVECTOR3 scal);
	//void Setting_cUIText(D3DXVECTOR3 POS, char * write_text, ST_SIZE Textsize, cFontManager::eFontType fonttype, D3DXCOLOR color);
};