#include "Address.h"
#include <iostream>
using namespace std;


Address::Address()
{
	type = 0;
}


Address::~Address()
{
	clear();
}

string Address::get_string(string::iterator begin, string::iterator end)
{
	//string get_string(string::iterator begin, string::iterator end)
	string s;
	for (; begin != end; begin++)
		s += *begin;
	//cout << s << endl;
	return s;
}

string Address::get_child_address(string& str)//获取第一个非空格信息
{
	string s;
	if (str.size() == 0)
		return s;
	/*string::iterator it = str.begin();
	for (; *it == ' '; it++);
	str = get_string(it, str.end());
	it = str.begin();
	if (str.size() == 0)return s;*/
	string::iterator np = str.begin();
	for (; np != str.end() && *np != ' '; np++)
		s += *np;
	if (np == str.end())return s;
	np++;
	str = get_string(np, str.end());
	//str = str.c_str() + (np - str.begin());
	return s;

	//const char* p = str.c_str();
	//for (; *p == ' '; p++);
	//str = p;//不要再用p指向的内容了，此时p指向的内容已经被改变了
	//if (str.size() == 0)	return s;
	//for (; *p != ' '; p++)	
	//	s += *p;
	//str = p;
}


string Address::get_child_number(string& str)
{
	string s;
	if (str.size() == 0)
		return s;
	/*string::iterator it = str.begin();
	for (; !(*it >= '0'&&*it <= '9'); it++);
	str = get_string(it, str.end());
	it = str.begin();
	for (; *it != '-'&&*it != '\0'; it++)s += *it;
	if (*it == '-')it++;
	str = get_string(it, str.end());
	it = str.begin();
	return s;*/

	const char* p = str.c_str();
	for (; !(*p>='0'&&*p<='9'); p++);
	str = p;
	for (; *p != '-'&&*p!='\0'; p++)s += *p;
	if (*p == '-')p++;
	str = p;
	return s;
}

//volatile int add_test_number = 0;
void Address::set_address(string str)
{
	if (str.size() == 0)	return;
	const char* p = str.c_str();
	if (*p >= '0'&&*p <= '9')
		type = 1;
	else type = 0;
	if (type == 0)//普通地区式寻址
	{
		string s;
		s= get_child_address(str);
		if (s != "未找到用户地址")
		{
			province = s;
			city = get_child_address(str);
			county = get_child_address(str);
			town = get_child_address(str);
			other = get_child_address(str);
		}
	}
	if (type == 1)//电话号式寻址
	{
		string s = get_child_number(str);
		if (s == "86")	s = get_child_number(str);
		if (s.size() >= 5)	other = s;
		else
		{
			province = s;
			s.clear();
			s = get_child_number(str);
			if (s.size() >= 5)
				other = s;
			else
			{
				city = s;
				s.clear();
				s = get_child_number(str);
				other = s;
			}
		}
	}
	//add_test_number++;
}