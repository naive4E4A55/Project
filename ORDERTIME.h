#pragma once
#include <string>
#include <fstream>
using namespace std;
class OrderTime
{
private:
	int year;
	int month;
	int day;
	int hour;
	int min;
	int analys(string& str);
	static int monthDays[12];
	//static int timeStandard[3];
	
public:
	OrderTime();
	~OrderTime();
	void clear() { year = month = day = hour = min = 0; }
	void set_time(string time);
	bool time_right();
	void standard_time() { year = 1970; month = day = hour = min = 0; };
	void operator=(OrderTime& nOrderTime) { year = nOrderTime.year; month = nOrderTime.month; day = nOrderTime.day; hour = nOrderTime.hour; min = nOrderTime.min; }
	void operator<<(string time) { set_time(time); }
	friend fstream& operator<<(fstream& outFile, OrderTime& orderTime);
	friend ostream& operator<<(ostream& outFile, OrderTime& orderTime);
	int near_time(OrderTime &nOrderTime)const;
	int get_year()const { return year; }
	int get_month()const { return month; }
	int get_day()const { return day; }
	int get_hour()const { return hour; }
	int get_min()const{ return min; }
};
static enum { Jan, Feb, Mar, Apr, May, Jun, Jul, Aug, Sept, Oct, Nov, Dec }mon;

//int OrderTime::timeStandard[3] = { 23,59,59 };
static fstream& operator<<(fstream& outFile, OrderTime& orderTime)
{
	outFile << orderTime.year << "/" << orderTime.month << "/" << orderTime.day << "\t" << orderTime.hour << ":" << orderTime.min;
	return outFile;
}

static ostream& operator<<(ostream& outFile, OrderTime& orderTime)
{
	outFile << orderTime.year << "/" << orderTime.month << "/" << orderTime.day << "\t" << orderTime.hour << ":" << orderTime.min;
	return outFile;
}
;
