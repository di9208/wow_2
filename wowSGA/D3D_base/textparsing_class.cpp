#include "stdafx.h"
#include "textparsing_class.h"

textparsing_class::textparsing_class()
{
}


textparsing_class::~textparsing_class()
{
}


// text passing advice functions
char * textparsing_class::GetToken(FILE* fp)
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
bool textparsing_class::Iswhile(char c)
{
	return c < 33;
}
float textparsing_class::Getfloat(FILE* fp)
{
	return (float)atof(GetToken(fp));
}
int textparsing_class::GetInt(FILE* fp)
{
	return atof(GetToken(fp));
}
bool textparsing_class::IsEqual(char* str1, char* str2)
{
	return strcmp(str1, str2) == 0;
}