#include "OrderTime.h"



int OrderTime::monthDays[12] = { 31,29,31,30,31,30,31,31,30,31,30,31 };
OrderTime::OrderTime()
{
	year = month = day = hour = min = 0; 
}


OrderTime::~OrderTime()
{
	clear();
}




int OrderTime:: analys(string& str)
{
	int i= stoi(str);
	const char* p = str.c_str();
	for (; *p != '/' && *p != ' '&&*p!=':'; p++);
	p++;
	string s = p;
	str = s;
	return i;
}
void OrderTime::set_time(string str)
{
	year = analys(str);
	month = analys(str);
	day = analys(str);
	hour = analys(str);
	min = analys(str);
	//if (!time_right())
		//standard_time();
}

int OrderTime::near_time(OrderTime &nOrderTime)const
{
	return 0;
}


bool OrderTime::time_right()
{
	if (month < 1 || month>13)
		return 0;
	if (day<1 || day>monthDays[month - 1])
		return 0;
	if (hour<0 || hour>23)
		return 0;
	if (min<0 || min>59)
		return 0;
	return 1;
}