#pragma once
class textparsing_class
{
private:
	SYNTHESIZE(char, m_szToken[1024], Sztoken);
public:
	textparsing_class();
	~textparsing_class();

	char * GetToken(FILE* fp);
	bool Iswhile(char c);
	float Getfloat(FILE* fp);
	int GetInt(FILE* fp);
	bool IsEqual(char* str1, char* str2);
};

