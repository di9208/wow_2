#include "stdafx.h"
#include "Button_delegate.h"

void Button_delegate::OnClick(cUIButton * pSender)
{
	if (pSender->GetTag() == 0)
	{
		::MessageBox(0, "�׽�Ʈ", "�׽�Ʈ", 0);
	}
	else if (pSender->GetTag() == 1)
	{
		pSender->GetParent()->Sethidden(true);
	}
}
