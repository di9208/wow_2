#pragma once
#include "cUIButton.h"

class Button_delegate : public iButtonDelegate
{
public:
	Button_delegate();
	~Button_delegate();
	void OnClick(cUIButton* pSender);
};

