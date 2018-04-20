#include "ChildNote.h"
//#include <iostream>
//using namespace std;


ChildNote::ChildNote()
{
	Name.clear();
	Value.clear();
}


ChildNote::~ChildNote()
{
	clear();
}

string ChildNote::get_string(string::iterator begin, string::iterator end)
{
	//string get_string(string::iterator begin, string::iterator end)
	string s="";
	for (; begin != end; begin++)
		s += *begin;
	//cout << s << endl;
	return s;
}

string ChildNote::get_child_note(string& str) //获取 ' '里的内容
{
	string::iterator p = str.begin();
	for (; p!=str.end()&&*p != '\''; p++);
	str = get_string(p, str.end());
	if (str == "")return "";

	string::iterator p0 = str.begin();
	string::iterator p1 = p0 + 1;
	while (p1!=str.end()&&*p1 != '\'') p1 = p1 + 1;
	if (p1 == str.end())throw 1;//如果只有一个',就抛出异常

	string s;
	for (string::iterator p = p0 + 1; p != p1; p++) s += *p;
	str = get_string(p1 + 1,str.end());
	return s;


	/*const char* p = str.c_str();
	for (; *p != '\''; p++);
	str = p;
	const char* p0 = str.c_str();
	const char* p1 = p0 + 1;
	while (*p1 != '\'') p1 = p1 + 1;
	string s;
	for (const char* p = p0 + 1; p != p1; p++) s += *p;
	str = (p1 + 1);
	return s;*/
}


void ChildNote::set_note(string str)
{
	if (Name.size() == 0 && Value.size() == 0)
	{
		for (int i = 0; i < 2; i++)
		{
			string note = get_child_note(str);
			if (note == "name")
			{
				const char* Pstr = str.c_str();
				for (; *Pstr != '\''; Pstr++);
				str = Pstr;
				Name = get_child_note(str);
			}
			if (note == "value")
			{
				const char* Pstr = str.c_str();
				for (; *Pstr != '\''; Pstr++);
				str = Pstr;
				Value = get_child_note(str);
			}
			note.clear();
			const char* Pstr = str.c_str();
			for (; *Pstr != '\''; Pstr++);
			str = Pstr;
		}
	}
}

bool ChildNote::same_name(const ChildNote& nChildNote)const
{
	return nChildNote.Name == Name;
}
