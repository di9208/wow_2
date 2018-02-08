#pragma once
class item_class;

class item_loader
{

private:
	FILE* fp;
	char  m_szToken[1024];
public:
	item_loader();
	~item_loader();

	void items_loader(OUT std::vector<item_class*> & result_vi, IN char * loadertext);
	void store_loader(OUT std::vector<item_class*> & result_vi, IN char * loadertext);

	void Item_setting(std::vector<item_class*> & result_vi);
	void Item_main_setting(std::vector<item_class*> & result_vi);
	void Item_sub_setting(item_class* temp);
	void Item_store_setting();


	char * GetToken();
	bool Iswhile(char c);
	float Getfloat();
	int GetInt();
	bool IsEqual(char* str1, char* str2);
};

