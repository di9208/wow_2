#include "stdafx.h"
#include "Button_delegate.h"

Button_delegate::Button_delegate()
{
}

Button_delegate::~Button_delegate()
{
}

void Button_delegate::OnClick(cUIButton * pSender)
{
	if (pSender->GetTag() == TAG_SHOP)
	{
		if (pSender->GetParent()->GetPos().z == 0.5);
		{
			pSender->GetParent()->SetPos(D3DXVECTOR3(0, 0, 0.0));
			return;
		}
		if (pSender->GetParent()->GetPos().z == 0.0);
		{
			pSender->GetParent()->SetPos(D3DXVECTOR3(0, 0, 0.5));
			return;
		}
	}
	if (pSender->GetTag() == TAG_CLOSE)
	{
		pSender->GetParent()->Sethidden(true);
	}
}
