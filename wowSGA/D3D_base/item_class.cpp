#include "stdafx.h"
#include "item_class.h"


item_class::item_class()
{
	ZeroMemory(&Io, sizeof(item_option));
	ZeroMemory(&Iw, sizeof(item_where));
	ZeroMemory(&It, sizeof(item_type));
	ZeroMemory(&In, sizeof(std::string));
	ZeroMemory(&Ist, sizeof(std::string));
	ZeroMemory(&Rc, sizeof(RECT));

	Inum = 0;
	Ix = 0;
	Iy = 0;
	IW = 0;
	IH = 0;
	Iv = 0;
	Ie = NULL;
	Ii = "";
	Ipicking = false;
}


item_class::~item_class()
{
	//m_item->Destroy();
}

//void item_class::Setting_cUIButton(D3DXVECTOR3 POS, char * image_up, char * image_over, char * image_down)
//{
//	cUIButton* _UIBUTTON;
//	_UIBUTTON = new cUIButton;
//	_UIBUTTON->SetTexture(image_up,
//		image_over,
//		image_down);
//	_UIBUTTON->SetPos(POS);
//
//	m_item = _UIBUTTON;
//	//this->AddChild(_UIBUTTON);
//}
//
//void item_class::Setting_cUIImage(D3DXVECTOR3 POS, char * image_text, D3DXVECTOR3 scal)
//{
//	cUIImage* _UIIMAGE;
//	_UIIMAGE = new cUIImage;
//	_UIIMAGE->SetTexture(image_text);
//	_UIIMAGE->SetPos(POS);
//	_UIIMAGE->SetScal(scal);
//	m_item->AddChild(_UIIMAGE);
//	//this->AddChild(_UIIMAGE);
//}
//
//void item_class::Setting_cUIText(D3DXVECTOR3 POS, char * write_text, ST_SIZE Textsize, cFontManager::eFontType fonttype, D3DXCOLOR color)
//{
//	cUIText* _cUIText;
//	_cUIText = new cUIText;
//	_cUIText->SetPos(POS);
//	_cUIText->SetupText(write_text, Textsize, fonttype, color);
//
//	m_item->AddChild(_cUIText);
//	//this->AddChild(_cUIText);
//}