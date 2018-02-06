#include "stdafx.h"
#include "item_loader.h"
#include "item_class.h"
#include "textparsing_class.h"

item_loader::item_loader()
	: tp(NULL)
{

}


item_loader::~item_loader()
{
	SAFE_DELETE(tp);
}

void item_loader::items_loader(OUT std::vector<item_class*> & result_vi, IN char * loadertext)
{
	tp = new textparsing_class;

	fopen_s(&fp,loadertext,"r");
	 
	while (char* szToken = tp->GetToken(fp))
	{
		if (tp->IsEqual(szToken, "*ITEM_LIST"))
		{
			Item_setting(result_vi);
		}
	}
}

void item_loader::store_loader(OUT std::vector<item_class*> & result_vi, IN char * loadertext)
{

}

void item_loader::Item_setting(std::vector<item_class*> & result_vi)
{
	int nLevel = 0;
	do
	{
		char* szToken = tp->GetToken(fp);
		if (tp->IsEqual(szToken, "{"))
		{
			nLevel++;
		}
		else if (tp->IsEqual(szToken, "}"))
		{
			nLevel--;
		}
		else if (tp->IsEqual(szToken, "*ITEM"))
		{
			Item_main_setting(result_vi);
		}
	} while (nLevel > 0);
}

void item_loader::Item_main_setting(std::vector<item_class*> & result_vi)
{
	item_class* temp;
	temp = new item_class;

	int nLevel = 0;
	do
	{
		char* szToken = tp->GetToken(fp);
		if (tp->IsEqual(szToken, "{"))
		{
			nLevel++;
		}
		else if (tp->IsEqual(szToken, "}"))
		{
			nLevel--;
		}

		else if (tp->IsEqual(szToken, "*ITEM_NAME"))
		{
			temp->SetI_name(tp->GetToken(fp));
		}
		else if (tp->IsEqual(szToken, "*ITEM_NUMBER"))
		{
			temp->SetI_num(tp->GetInt(fp));
		}
		else if (tp->IsEqual(szToken, "*ITEM_WHERE"))
		{
			char* tempToken = tp->GetToken(fp);
			if (strcmp(tempToken, "EQUIT") == 0)	temp->setting_where(0);
			else if (strcmp(tempToken, "ITEM") == 0)	temp->setting_where(1);
			else if (strcmp(tempToken, "Collect") == 0)	temp->setting_where(2);
			else if (strcmp(tempToken, "Map") == 0)	temp->setting_where(3);
		}
		else if (tp->IsEqual(szToken, "*ITEM_TYPE"))
		{
			char* tempToken = tp->GetToken(fp);
			if (strcmp(tempToken, "WEAPON") == 0)	temp->setting_where(0);
			else if (strcmp(tempToken, "ARMOR") == 0)	temp->setting_where(1);
			else if (strcmp(tempToken, "SPECIAL") == 0)	temp->setting_where(2);
			else if (strcmp(tempToken, "INTERACTION") == 0)	temp->setting_where(3);
			else if (strcmp(tempToken, "USING") == 0)	temp->setting_where(4);
		}
		else if (tp->IsEqual(szToken, "*ITEM_SUBTEXT"))
		{
			temp->SetI_sub_text(tp->GetToken(fp));
		}
		else if (tp->IsEqual(szToken, "*ITEM_IMAGE"))
		{
			temp->SetI_image(std::string(tp->GetToken(fp)));
		}

		else if (tp->IsEqual(szToken, "*ITEM_OPTION"))
		{
			Item_sub_setting(temp);
		}
		else if (tp->IsEqual(szToken, "*STORE_OPTION"))
		{
			//Item_store_setting(temp);
		}
	} while (nLevel > 0);

	result_vi.push_back(temp);
}

void item_loader::Item_sub_setting(item_class* temp)
{
	int n1, n2, n3, n4;
	n1 = n2 = n3 = n4 = 0;
	float f1 = 0.0f;

	int nLevel = 0;
	do
	{
		char* szToken = tp->GetToken(fp);
		if (tp->IsEqual(szToken, "{"))
		{
			nLevel++;
		}
		else if (tp->IsEqual(szToken, "}"))
		{
			nLevel--;
		}
		else if (tp->IsEqual(szToken, "*ATK"))
		{
			n1 = tp->GetInt(fp);
		}
		else if (tp->IsEqual(szToken, "*DEF"))
		{
			n2 = tp->GetInt(fp);
		}
		else if (tp->IsEqual(szToken, "*ATK_SPEED"))
		{
			f1 = tp->Getfloat(fp);
		}
		else if (tp->IsEqual(szToken, "*PRICE"))
		{
			n3 = tp->GetInt(fp);
		}
		else if (tp->IsEqual(szToken, "*UPGRADE"))
		{
			n4 = tp->GetInt(fp);
		}

	} while (nLevel > 0);

	temp->setting_option(n1,n2,f1,n3,n4);
}

void item_loader::Item_store_setting()
{
}