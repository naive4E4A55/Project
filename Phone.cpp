#include "Phone.h"



Phone::Phone()
{
}


Phone::~Phone()
{
	clear();
}


// 获取手机号
void Phone::set_number(string number)
{
	if (number == "未找到用户名")
		return;
	/*string::iterator p;
	for (p = number.begin();*p='-'&&p!=number.end();p++);
	if (p == number.end())
		phoneNumber = number;
	else phoneNumber = *p;*/
	const char* p = number.c_str();
	for (; p != (number.c_str() + (int)number.size()); p++)
		if (*p == '-') break;
	if (p == (number.c_str() + (int)number.size()))	phoneNumber = number;
	else phoneNumber = p + 1;

}
