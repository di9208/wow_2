#include "stdafx.h"
#include "item_loader.h"
#include "item_class.h"


item_loader::item_loader()
{

}


item_loader::~item_loader()
{

}

void item_loader::items_loader(OUT std::vector<item_class*> & result_vi, IN char * loadertext)
{

	fopen_s(&fp, loadertext, "r");

	while (char* szToken = GetToken())
	{
		if (IsEqual(szToken, "*ITEM_LIST"))
		{
			Item_setting(result_vi);
		}
	}
}

void item_loader::inven_loader(OUT std::vector<item_class*> & result_vi, OUT int & sett_ing_money, IN char * loadertext)
{
	fopen_s(&fp, loadertext, "r");

	while (char* szToken = GetToken())
	{
		if (IsEqual(szToken, "*MONEY"))
		{
			sett_ing_money = GetInt();
		}

		else if (IsEqual(szToken, "*ITEM_LIST"))
		{
			Item_setting(result_vi);
		}
	}
}

void item_loader::Item_setting(std::vector<item_class*> & result_vi)
{
	int nLevel = 0;
	do
	{
		char* szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			nLevel++;
		}
		else if (IsEqual(szToken, "}"))
		{
			nLevel--;
		}
		else if (IsEqual(szToken, "*ITEM"))
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
		char* szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			nLevel++;
		}
		else if (IsEqual(szToken, "}"))
		{
			nLevel--;
		}

		else if (IsEqual(szToken, "*ITEM_NAME"))
		{
			temp->Set_Iname(std::string(GetToken()));
		}
		else if (IsEqual(szToken, "*ITEM_NUMBER"))
		{
			temp->Set_Inum(GetInt());
		}
		else if (IsEqual(szToken, "*ITEM_WHERE"))
		{
			char* tempToken = GetToken();
			if (strcmp(tempToken, "EQUIT") == 0)	temp->setting_where(0);
			else if (strcmp(tempToken, "ITEM") == 0)	temp->setting_where(1);
			else if (strcmp(tempToken, "Collect") == 0)	temp->setting_where(2);
			else if (strcmp(tempToken, "Map") == 0)	temp->setting_where(3);
		}
		else if (IsEqual(szToken, "*ITEM_TYPE"))
		{
			char* tempToken = GetToken();
			if (strcmp(tempToken, "WEAPON") == 0)	temp->setting_where(0);
			else if (strcmp(tempToken, "ARMOR") == 0)	temp->setting_where(1);
			else if (strcmp(tempToken, "SPECIAL") == 0)	temp->setting_where(2);
			else if (strcmp(tempToken, "INTERACTION") == 0)	temp->setting_where(3);
			else if (strcmp(tempToken, "USING") == 0)	temp->setting_where(4);
		}

		else if (IsEqual(szToken, "*ITEM_IMAGE"))
		{
			temp->Set_Iimage(std::string(GetToken()));
		}
		else if (IsEqual(szToken, "*ITEM_SUBTEXT"))
		{
			temp->Set_ISub(std::string(GetToken()));
		}
		else if (IsEqual(szToken, "*ITEM_OPTION"))
		{
			Item_sub_setting(temp);
		}
		else if (IsEqual(szToken, "*STORE_OPTION"))
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
		char* szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			nLevel++;
		}
		else if (IsEqual(szToken, "}"))
		{
			nLevel--;
		}
		else if (IsEqual(szToken, "*ATK"))
		{
			n1 = GetInt();
		}
		else if (IsEqual(szToken, "*DEF"))
		{
			n2 = GetInt();
		}
		else if (IsEqual(szToken, "*ATK_SPEED"))
		{
			f1 = Getfloat();
		}
		else if (IsEqual(szToken, "*PRICE"))
		{
			n3 = GetInt();
		}
		else if (IsEqual(szToken, "*UPGRADE"))
		{
			n4 = GetInt();
		}

	} while (nLevel > 0);

	temp->setting_option(n1, n2, f1, n3, n4);
}

void item_loader::Item_store_setting()
{
}

// text passing advice functions
char * item_loader::GetToken()
{
	int nReadCnt = 0;
	bool isQuote = false;

	while (true)
	{
		if (feof(fp))
			break;

		char c = fgetc(fp);

		if (c == '\"')
		{
			if (isQuote)
				break;

			isQuote = true;
			continue;
		}

		if (!isQuote && Iswhile(c))
		{
			if (nReadCnt == 0)
				continue;
			else
				break;
		}
		m_szToken[nReadCnt++] = c;
	}

	if (nReadCnt == 0)
		return NULL;

	m_szToken[nReadCnt] = '\0';

	return m_szToken;
}
bool item_loader::Iswhile(char c)
{
	return c < 33;
}
float item_loader::Getfloat()
{
	return (float)atof(GetToken());
}
int item_loader::GetInt()
{
	return atof(GetToken());
}
bool item_loader::IsEqual(char* str1, char* str2)
{
	return strcmp(str1, str2) == 0;
}