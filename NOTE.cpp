#include "Note.h"
#include <iostream>
using namespace std;
#define Threshold 0.8;


Note::Note()
{
}


Note::~Note()
{
	clear();
}

string Note::get_string(string::iterator begin, string::iterator end)
{
	//string get_string(string::iterator begin, string::iterator end)
	string s;
	for (; begin != end; begin++)
		s += *begin;
	return s;
}

void Note::clear()
{
	for (unsigned int i = 0; i < note.size(); i++)
		note[i].clear();
	//note.clear();
	//Note note2;
	//vector<ChildNote> note2;
	note.swap(vector<ChildNote>());
	//note.shrink_to_fit();
}


void Note::set_note(string str)
{
	if (str == "[]"||str=="None")
		return;
	str = get_string(str.begin()+1, str.end());
	string::iterator it = str.begin();
	string s;
	int number = 1;
	while (number != 0)
	{
		for (; it!=str.end()&& *it != '{'; it++);
		if (it == str.end())throw 1;
		int count = 1;
		it++;
		for (;it!=str.end(); it++)
		{
			if (*it == '\0')throw 'a';
			if (*it == '{')count++;
			if (*it == '}')count--;
			if (count == 0)break;
			s += *it;
		}
		ChildNote newNote;
		newNote.set_note(s);
		//note.insert(map<ChildNote,string>::value_type(newNote,newNote.get_name()));
		note.push_back(newNote);
		s.shrink_to_fit();
		if (it != str.end())
		{
			it++;
			while (it!=str.end()&& *it == ' ')
				it++;
			if (it == str.end())throw 2;
			if (*it == '[')number++;
			if (*it == ']')number--;
		}
		else throw 3;
	}
	sort_note();

	//str = str.c_str() + 1;
	//const char* p = str.c_str();
	//string s;
	//int number = 1;
	//while (number!=0)
	//{
	//	for (; *p != '{'; p++);
	//	int count = 1;
	//	p++;
	//	for (;; p++)
	//	{ 
	//		if (*p == '\0')throw'a';
	//		if (*p == '{')count++;
	//		if (*p == '}')count--;
	//		if (count == 0)break; 
	//		s += *p;
	//	}
	//	ChildNote newNote;
	//	newNote.set_note(s);
	//	//note.insert(map<ChildNote,string>::value_type(newNote,newNote.get_name()));
	//	note.push_back(newNote);
	//	s.clear();
	//	p++;
	//	while (*p == ' ')
	//		p++;
	//	if (*p == '[')number++;
	//	if (*p == ']')number--;
	//}
	//sort_note();
}

//体现两个note相似度的函数,从0到1
double Note::sml_num(Note nNote)
{
	/*
	设计思路:两个note,每个note里有若干的childnote,首先把这些childnote合并,再根据相似度设计向量值
	*/
	/*本段作用:把输入的nNote里的子标签挨个与thisNote的子标签对比,建立特征向量*/
	vector<double>vecThis, vecNote;
	for (unsigned int i = 0; i < note.size(); i++)
	{
		ChildNote nChildNote;
		//cout << note[i].get_name();
		nChildNote = nNote.find_by_name(note[i].get_name());
		if (nChildNote.get_value() == nChildNote.get_name() && nChildNote.get_value() == "")//如果这个ChileNote只存在于thisNote里
		{
			vecThis.push_back(1); vecNote.push_back(-1);
		}
		else//如果这个ChileNote同时存在于thisNote和nNote里
		{
			string str = max_same_string(note[i].get_value(), nChildNote.get_value());//获取note[i]和nChildNote最大相同子串
			if (str.size() / note[i].get_value().size() > 0.7&&str.size() / nChildNote.get_value().size() > 0.7)
			{
				vecThis.push_back(1); vecNote.push_back(1);
			}
			//计算两者vaule的差异值
			//难度在于词法分析
			else
			{
				double thisDouble, nDouble;
				thisDouble = 1 - (double)str.size() / note[i].get_value().size();
				nDouble = -(1 - (double)str.size() / nChildNote.get_value().size());
				vecThis.push_back(thisDouble); vecNote.push_back(nDouble);
			}
			str.clear();
		}
		nChildNote.clear();
	}
	for (unsigned int i = 0; i < (unsigned int)nNote.size(); i++)
	{
		ChildNote nChildNote;
		if (exist_name(nNote.note[i].get_name()) == 0)//不存在于thisNote里,即只存在于nNote里
		{
			vecThis.push_back(-1); vecNote.push_back(1);
		}
	}
	/*已经完成了vecThis和vecNote的设置*/

	/*计算vecThis和vecNote的相似度*/
	double sml = degress(vecThis, vecNote);
	return sml;
}

void Note::sort_note()//把ChileMote按名字的升序排列
{
	sort(note.begin(),note.end());
}

string Note::max_same_string(const string& str1, const string& str2)//返回str1和str2的最大相同子串
{
	string str;
	for (unsigned int i = 0; i<str2.length(); i++)
	{
		for (unsigned int j = i + 1; j<str2.length(); j++)
		{
			if (str1.find(str2.substr(i, j - i + 1)) != -1)
			{
				if (str.length()<str2.substr(i, j - i + 1).length())
					str = str2.substr(i, j - i + 1);
			}
			else
				break;
		}
	}
	return str;
}

bool Note::exist_name(string& name)
{
	for (unsigned int i = 0; i < note.size(); i++)
		if (name == note[i].get_name())return 1;
	return 0;
}

inline ChildNote Note::find_by_name(string& name)
{
	ChildNote childNote;
	for (unsigned int i = 0; i < note.size(); i++)
	{
		if (name == note[i].get_name())return note[i];
		//if (name > note[i].get_name())return childNote;
	}
	return childNote;
}

double Note::inner_product(vector<double> vec1, vector<double>vec2)
{
	if (vec1.size() == 0 || vec2.size() == 0)//如果有一个向量为0,就返回为0
		return 0;
	if (vec1.size() != vec2.size())//如果两个向量大小不同,就抛出"size flase"
		throw("size false");
	double sum = 0;
	for (unsigned int i = 0; i < vec1.size(); i++)
		sum += vec1[i] * vec2[i];
	return sum;
}

double Note::model(vector<double> vec)
{
	double num = inner_product(vec, vec);
	return sqrt(num);
}

double Note::degress(vector<double> vec1, vector<double> vec2)
{
	double inner = inner_product(vec1, vec2);
	double mod1 = model(vec1);
	double mod2 = model(vec2);
	if (mod1 > 1e-6 || mod1 < -1e-6)
	{
		if (mod2 > 1e-6 || mod2 < -1e-6)
			return inner / (mod1*mod2);
		return 0;
	}
	else return smlAverage;
}
/*
/*Group<string, string, Order> orderGroupByUserName;
for (unsigned int i = 0; i < orderGroup.get_size(); i++)
nOrderSet.add_order(orderGroup.get_order(i).get_ID(), orderGroup.get_order(i));*/
//cout << "现在进入按数字搜索模式,请输入你想查询第几条订单,会自动打印出用户的信息" << endl; read = 1;
//while (read)
//{
//	cout << "请输入想搜索第几条订单" << endl;
//	unsigned int number; cin >> number;
//	if (number >= orderGroup.get_size())cout << "没有此订单(输入的数字太大)" << endl;
//	else
//	{
//		cout << "orderID\tname\tuserID\tphone\taddress" << endl;
//		cout << orderGroup.get_order(number) << endl;
//	}
//	cout << "是否要继续搜索?输入1继续读取,输入0停止搜索" << endl; cin >> read;
//}
//cout << "现在进入搜索模式,请输入你想查询的用户姓名,会自动打印出姓名为用户的信息" << endl; read = 1;
//while (read)
//{
//	cout << "请输入想搜索的用户的姓名" << endl;
//	string userName; cin >> userName;
//	vector<Order> nOrderGroup = orderGroup.get_order_by_userName(userName);
//	if (nOrderGroup.size() == 0) { cout << "不存在此用户ID" << endl; }
//	else
//	{
//		//out << order.get_orderID() << "  " << order.get_name() << "  " << order.get_userID() << "  " << order.get_phone().get_number() << "  " << order.get_address().get_all();
//		cout << "orderID\tname\tuserID\tphone\taddress" << endl;
//		for (unsigned int i = 0; i < nOrderGroup.size(); i++)
//			cout << nOrderGroup[i] << endl;
//	}
//	userName.clear();cout<<"是否要继续搜索?输入1继续读取,输入0停止搜索" << endl; cin >> read;
//}
/*Note note1, note2;
cout << "现在进入note比对模式,输入两个订单位置,输出相对应的相似度" << endl; read = 1;
double max = -1; double sml = 0;
while (read)
{

int i, j; cin >> i >> j;
note1 = orderGroup.get_order(i).get_note();
for (int k = 0; k < j; k++)
{
note2 = orderGroup.get_order(k).get_note();
sml = note1.sml_num(note2);
if (sml != smlAverage)
{
cout <<note1 << endl << note2<<"\t"<<k<< endl << "相似度为:";
cout << sml << endl;
}
note2.clear();
if (sml > max)max = sml;
}
note1.clear();
cout << "是否继续?" << endl; cin >> read;
}
cout << "最大相似度为" <<max<<endl;*/
//system("pause");
//cout << nOrder << endl;
/*OrderTime order;
order.set_time("2017 12 2 3:45");
cout << order.get_year() << endl;
cout << order.get_month() << endl << order.get_day() << endl << order.get_hour() << endl << order.get_min() << endl;*/
/*ChildNote child;*/
/*string str = "          'name' : '颜色', 'value' : '深蓝'";
for (const char* p = str.c_str(); *p != '\''; str=p)
p++;
cout << str;*/
//str.replace(" ", "", NULL);
//child.get_note("{ 'name' : '颜色', 'value' : '深蓝'}");// , { 'name': '尺码', 'value' : '185' }]");
//cout << child.get_name() << endl << child.get_value() << endl;
/*Note note;
note.set_note("[{'name': '颜色', 'value'    : '深蓝'},    {    'name'   : '尺码', 'value' : '185'  }   ]");
for (int i = 0; i < note.size(); i++)
{
ChildNote nNote = note.get_child_note(i);
cout << "Name:"<<nNote.get_name() << "\t" <<"Value"<< nNote.get_value() << endl;
}*/
/*Phone phoneTest;
phoneTest.set_number("86-123");
cout << phoneTest.get_number() << endl;*/
//string str = "淮安市";
/*const char* p = str.c_str();
string s;
for (; *p != ' '; p++)
s += *p;
cout << s;*/
/*char a[9] = {-50,-46,-80,-82,-60,-29,0};
cout << a;*/
//string s = "      涛野";//前面的都是空格，不是Tab
//const char* p = s.c_str();
//for (; *p == ' '; p++);//目的是去掉所有的非空格的字符
//s= p;//把p指向的字符串赋值给s
//cout << p << endl;
/*Address address;
address.set_address("江苏省 淮安市 清江浦区 长东街道 淮海东路淮海花园63-1门面房，缇拉米苏精致摄影馆 ");
address.set_address("025-232-4220037");
cout << address.get_province() << address.get_city() << address.get_county() << address.get_town() << address.get_other() << endl;*/
/*Order order;
string s = "C5AB15DEB54711E781AD00155D88D822,67774385564773200.00 ,江苏电信100元 自动充值话费 快充秒充到账,2017/10/13 22:07,龙新话费充值专营店,99.8,[],充值成功,张波,86-13921700873,江苏省 泰州市 海陵区 城西街道 北仓路招贤公寓3号301室 ,tzzbo52,2017/10/20 11:35,0,a316fcfbc7af618f389a2bbd828b701c,,,1";
order.set_order(s);
cout<<order.get_ID()<<endl;
cout << order.get_orderID() << endl;
cout << order.get_orderTime().get_day() << endl;
cout << order.get_seller() << endl;
cout << order.get_note() << endl;*/
//-50 -46 -80 -82 -60 -29

//读取文件测试 csv用","作为分隔,而非"，"
//可使用:getline(ifstream& inFile,string& s); ifstream::getline(char ch[],int maxCount);
/*ifstream inFile;
inFile.open("test.csv", ios::in);
if (!inFile) return -1;
string s1, s2, s3;
char s4[1000];
getline(inFile,s1);
cout << s1 << endl;
getline(inFile, s2);
cout << s2 << endl;
inFile.getline(s4,1000);
cout << s4 << endl;*/

//bool isPrime_3(int num)
//{
//	//两个较小数另外处理  
//	if (num == 2 || num == 3)
//		return 1;
//	//不在6的倍数两侧的一定不是质数  
//	if (num % 6 != 1 && num % 6 != 5)
//		return 0;
//	int tmp = sqrt(num);
//	//在6的倍数两侧的也可能不是质数  
//	for (int i = 5; i <= tmp; i += 6)
//		if (num %i == 0 || num % (i + 2) == 0)
//			return 0;
//	//排除所有，剩余的是质数  
//	return 1;
//}
//#include <stdio.h>  
//#include <stdlib.h>  
//#include <math.h>  
//
//#define QUEEN 6     //皇后的数目  
//#define INITIAL -10000   //棋盘的初始值  
//
//int a[QUEEN];    //一维数组表示棋盘  
//
//void init()  //对棋盘进行初始化  
//{
//	int *p;
//	for (p = a; p < a + QUEEN; ++p)
//	{
//		*p = INITIAL;
//	}
//}
//
//int valid(int row, int col)    //判断第row行第col列是否可以放置皇后  
//{
//	int i;
//	for (i = 0; i < QUEEN; ++i)   //对棋盘进行扫描  
//	{
//		if (a[i] == col || abs(i - row) == abs(a[i] - col))   //判断列冲突与斜线上的冲突  
//			return 0;
//	}
//	return 1;
//}
//
//void print()    //打印输出N皇后的一组解  
//{
//	int i, j;
//	for (i = 0; i < QUEEN; ++i)
//	{
//		for (j = 0; j < QUEEN; ++j)
//		{
//			if (a[i] != j)      //a[i]为初始值  
//				printf("%c ", '.');
//			else                //a[i]表示在第i行的第a[i]列可以放置皇后  
//				printf("%c ", '#');
//		}
//		printf("\n");
//	}
//	for (i = 0; i < QUEEN; ++i)
//		printf("%d ", a[i]);
//	printf("\n");
//	printf("--------------------------------\n");
//}
//

/*zhangmengyao woaini wojueode womenkeyizaiyiqi le wozhendeaide qingnijiugeiwo wozhendehenxihuani 
zhendezhende
ruguonikandaozhegezhushi 
qingni gaosuwo 
niaiwo
zhangmengyao woaini;
//void queen()      //N皇后程序
//{
//	int n = 0;
//	int i = 0, j = 0;
//	while (i < QUEEN)
//	{
//		while (j < QUEEN)        //对i行的每一列进行探测，看是否可以放置皇后
//		{
//			if (valid(i, j))      //该位置可以放置皇后
//			{
//				a[i] = j;        //第i行放置皇后
//				j = 0;           //第i行放置皇后以后，需要继续探测下一行的皇后位置，所以此处将j清零，从下一行的第0列开始逐列探测
//				break;
//			}
//			else
//			{
//				++j;             //继续探测下一列
//			}
//		}
//		if (a[i] == INITIAL)         //第i行没有找到可以放置皇后的位置
//		{
//			if (i == 0)             //回溯到第一行，仍然无法找到可以放置皇后的位置，则说明已经找到所有的解，程序终止
//				break;
//			else                    //没有找到可以放置皇后的列，此时就应该回溯
//			{
//				--i;
//				j = a[i] + 1;        //把上一行皇后的位置往后移一列
//				a[i] = INITIAL;      //把上一行皇后的位置清除，重新探测
//				continue;
//			}
//		}
//		if (i == QUEEN - 1)          //最后一行找到了一个皇后位置，说明找到一个结果，打印出来
//		{
//			printf("answer %d : \n", ++n);
//			print();
//			//不能在此处结束程序，因为我们要找的是N皇后问题的所有解，此时应该清除该行的皇后，从当前放置皇后列数的下一列继续探测。
//			//_sleep(600);
//			j = a[i] + 1;             //从最后一行放置皇后列数的下一列继续探测
//			a[i] = INITIAL;           //清除最后一行的皇后位置
//			continue;
//		}
//		++i;              //继续探测下一行的皇后位置
//	}
//}
//
//int main(void)
//{
//	init();
//	queen();
//	system("pause");
//	return 0;
//}
#define MaxNum 5
#define smlAverage 0.5;
//这段代码可以用于
double inner_product(double vec1[MaxNum],double vec2[MaxNum])	//计算两个向量的内积
{
	double sum = 0;
	for (int i = 0; i < MaxNum; i++)
		sum += vec1[i] * vec2[i];
	return sum;
}
double model(double vec[MaxNum])
{
	double num = inner_product(vec, vec);
	return sqrt(num);
}
double degress(double vec1[MaxNum], double vec2[MaxNum])
{
	double inner = inner_product(vec1, vec2);
	double mod1 = model(vec1);
	double mod2 = model(vec2);
	if (mod1 > 1e-6 || mod1 < -1e-6)
	{
		if (mod2 > 1e-6 || mod2 < -1e-6)
			return inner / (mod1*mod2);
	}
	else return smlAverage;	//如果有一个向量的模是0，那么他们的相似度是平均值（暂定为0.5）
	
}
*/