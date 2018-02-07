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
	SYNTHESIZE(item_option, Io, I_option);
	SYNTHESIZE(item_where, Iw, I_where);
	SYNTHESIZE(item_type, It, I_type);
	SYNTHESIZE(std::string, In, I_name);
	SYNTHESIZE(std::string, Ist, I_sub_text);
	SYNTHESIZE(int, Inum, I_num);
	SYNTHESIZE(int, Iv, I_volume);
	SYNTHESIZE(bool, Ie, I_equit);
	SYNTHESIZE(std::string, Ii, I_image);

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
		Io.ATK = _atk;
		Io.DEF = _def;
		Io.ATK_SPEED = _atk_speed;
		Io.Price = _price;
		Io.Upgrade = _upgrade;
	}

	void setting_type(int num)
	{
		switch (num)
		{
		case 0:
			It = weapon;
			break;
		case 1:
			It = Armor;
			break;
		case 2:
			It = special_item;
			break;
		case 3:
			It = Interaction_item;
			break;
		case 4:
			It = using_item;
			break;
		}
	}

	void setting_where(int num)
	{
		switch (num)
		{
		case 0:
			Iw = EQUIT_item;
			break;
		case 1:
			Iw = inventory_item;
			break;
		case 2:
			Iw = inventory_collect;
			break;
		case 3:
			Iw = inventory_map;
			break;
		}
	}

	//void Setting_cUIButton(D3DXVECTOR3 POS, char * image_up, char * image_over, char * image_down);
	//void Setting_cUIImage(D3DXVECTOR3 POS, char * image_text, D3DXVECTOR3 scal);
	//void Setting_cUIText(D3DXVECTOR3 POS, char * write_text, ST_SIZE Textsize, cFontManager::eFontType fonttype, D3DXCOLOR color);
};