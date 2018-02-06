#pragma once
#include "cUIButton.h"

class Button_delegate : public iButtonDelegate
{
public:
	void OnClick(cUIButton* pSender);
};

