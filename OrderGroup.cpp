#include "OrderGroup.h"
#include <fstream>
#include <string>
#include <streambuf>
//只是为了测试用
#include <ctime>
#include <iostream>
using namespace std;

OrderGroup::OrderGroup()
{
}


OrderGroup::~OrderGroup()
{
	clear();
}

bool OrderGroup::order_right(const Order& nOrder)
{
#ifdef filtration
	if (nOrder.get_userName() == "未找到用户名" || nOrder.get_userName() == "不需要收货人")
		return 0;
#endif // filtration
	return 1;
}

void OrderGroup::clear()
{
	/*vector<Order> orderGroup;//订单集合 感觉这个用deque好像也可以,但是没什么必要,deque能做到快速在首尾增删元素
	list<Order>orderList;//orderList,用于初始化队列
	//反了,反了,反了!但是没出错... 应该是map<string ,Order>
	map<Order, string>orderMap;//用order.ID作为特征值orderMap*/
	for (unsigned int i = 0; i < orderGroup.size(); i++)
		orderGroup[i].clear();
	list<Order>::iterator it = orderList.begin();
	for (; it != orderList.end(); )
	{
		list<Order>::iterator nIt = it;
		it++;
		nIt->clear();
	}
	//for(unsigned int i=0;i<orderMap.size();i++)orderMap[i].cl
	map<string, Order>::iterator Mit = orderMap.begin();
	for (; Mit != orderMap.end();)
	{
		map<string, Order>::iterator nMit = Mit;
		Mit++;
		nMit->second.clear();
		//nMit->first().clear();
		//(nMit->first).clear();
	}
	orderGroup.swap(vector<Order>()); orderList.swap(list<Order>()); orderMap.swap(map<string,Order>());
}

//去除所有指定字符Redundancy
string OrderGroup::delete_char(string sNewTag, char cRddcy)
{
	unsigned int begin = 0;
	begin = (unsigned int)sNewTag.find(cRddcy, begin);  //查找空格在str中第一次出现的位置
	while (begin != -1)  //表示字符串中存在空格
	{
		sNewTag.replace(begin, 1, "");  // 用空串替换str中从begin开始的1个字符
		begin = (unsigned int)sNewTag.find(cRddcy, begin);  //查找空格在替换后的str中第一次出现的位置
	}
	return sNewTag;
}

//获取从p0到end的字符串
//好像有string::substring(start,end)的功能和这个一样
string OrderGroup::get_string(string::iterator p, string::iterator end)const
{
	string s;
	for (; p != end; p++)
	{
		s += *p;
	}
	return s;
}

//去除掉第一个c之前的字符
void OrderGroup::delete_child_string(string& str, char c)
{
	string::iterator p = str.begin();
	while (*p != c&&p!=str.end())
	{
		p++;
	}
	if (p == str.end())
		return;
	p++;
	str = get_string(p, str.end());
}

//判断一个Order是否已经存在于这个OrderGroup中
bool OrderGroup::exist_group(Order& order)const
{
	for (unsigned int i = 0; i < orderGroup.size(); i++)
	{
		if (order == orderGroup[i])
			return 1;
	}
	return 0;
}


//获取用字符'c'分隔的内容
string OrderGroup::get_child(string& str, char c)
{
	string s;
	string::iterator p = str.begin();
	int number = 0;
	//获取从*p到第一个","的内容
	for (; *p != c || number % 2 == 1; p++)
	{
		s += *p;
		if (*p == '\"')number++;
	}
	p++;
	str = get_string(p, str.end());
	return s;
}



//核心函数,读取文件
int OrderGroup::set_group(string fileName)
{
	ifstream inFile;
	inFile.open(fileName,ios::in);
	if (!inFile) { throw(1); return -1; }
	//按行读取信息,并进行初始化
	//log.csv的格式是第一行是"ID WP_ID"这些,从第二行开始每个的第一个格子都是"第几个订单",没什么信息
	string s;	//读取的string
	Order nOrder;//子订单
	//std::ifstream t("file.txt");
	//std::string str((std::istreambuf_iterator<char>(inFile)),std::istreambuf_iterator<char>());
	//s = get_child(str, '\n');
	//inFile>>s;
	//cout << str << endl; exit(-1);
	//if (!inFile)cout << "victory" << endl; exit(-1);

	getline(inFile, s);
	//cout << s << endl; inFile.close(); return 0;
	//s.clear();//去除第一行,因为没用...
	//由于不知道文件末尾会不会有换行,所以用最稳妥的方式,这个方法看上去很难理解但是能保证无论在最后一个数据后有没有换行符都能读取正确,当然log.csv文件确实是没有这个奇葩的所以这个仅仅当作是科普就可以,也可以进行修改
	
	//s = get_child(str, '\n'); 
	getline(inFile, s);
	int number = 0;
	time_t in_time, out_time; time(&in_time);
	//"cannot dereference string iterator because it is out of range (e.g. an end iterator)"
	while (!inFile.fail()&&number<=1000000)
	{
		//cout << number << endl;
		delete_child_string(s, ',');//cout << s << endl;
		try
		{
			nOrder << s;//把解析出来的子字符串输入到一个新订单里
		}
		catch (char)
		{
			nOrder.clear();//s.clear();
			getline(inFile, s);//s = get_child(str, '\n');
			continue;
		}
		catch (char*)
		{
			nOrder.clear();//s.clear();
			getline(inFile, s);//s = get_child(str, '\n');
			continue;
		}
		catch (int)
		{
			cout << "错误数据:" << number << endl;
			nOrder.clear();//s.clear();
			getline(inFile, s);//s = get_child(str, '\n');
			continue;
		}
		//catch
		//catch("")
		/*if (!exist_group(nOrder))	//防止重复订单被加入//这行代码是vector慢的元凶!!!检测重复订单会造成巨大的时间浪费
		{
			//万恶之源
			//这就是速度慢的原因...把nOrder加入到orderGroup的时候,会把原有内容全部复制到一个更大的地方里...
			//其实这里我挺想用一个list来进行存储的,全存储完了再根据list的大小开辟相应的vector数组(vector好像可以用变量进行规定初始大小,比如vector<Order> ordegGroup[100];或者vector<Order> ordegGroup[count];count是个变量)
			orderGroup.push_back(nOrder);
			number++;
		}*/
		if (!exist_list(nOrder.get_ID()))//如果订单没有重复那么就把它加入到里面
		{
			//orderMap.insert(map<string, Order>::value_type(nOrder.get_ID()),nOrder);
			orderMap.insert(map<string,Order>::value_type(nOrder.get_ID(),nOrder));
			orderList.push_back(nOrder); number++;
		}
		if (number % 1000== 0&&number!=0) { time(&out_time); cout << "已经读取" << number << "行" << "\t用时" << out_time - in_time << "s" << endl;time(&in_time); }
		nOrder.clear();//s.clear();//s = get_child(str, '\n');
		getline(inFile, s);
	}
	list_to_vector();
	//进行排序,使用lamda表达式
	inFile.close();
	return 0;
}

//把List转移到vector
void OrderGroup::list_to_vector()
{
	//有直接的函数
	//其实应该判断一下是否有重复订单...但是我懒得写...
	//vector<Order>nOrderGroup(orderList.size());
	orderGroup.insert(orderGroup.end(),orderList.begin(),orderList.end());
	orderList.swap(list<Order>());//清空
}

//获取某个order
Order OrderGroup::get_order(int i)
{
	if ((unsigned)i >= orderGroup.size())
		throw("i is so large");
	return orderGroup[i];
}

//根据用户姓名获取某群order
vector<Order> OrderGroup::get_order_by_userName(string userName)
{
	vector<Order> cOrderGroup;
	for (unsigned int i = 0; i < orderGroup.size(); i++)
	{
		if (orderGroup[i].get_userName() == userName)
		{
			Order nOrder = orderGroup[i];
			cOrderGroup.push_back(nOrder);//如果今后申请了新的资源,直接用cOrderGroup.push_back(orderGroup[i])里申请的资源(比如new的东西)被两份指针指到,不安全,所以多用了一步赋值(如果我申请了资源,一定会重载"="操作符(大概会吧...))
		}
	}
	return cOrderGroup;
}

//存在于List里
bool OrderGroup::exist_list(string& str)const
{
	/*list<Order>::const_iterator pOrder;
	//_List_const_iterator<Order> pOrder;
	for (pOrder = orderList.begin(); pOrder != orderList.end(); pOrder++)
		if (order==*pOrder)return 1;
	return 0;*/
	//以上是错误的方法,用这个方法做的绝对是很慢的...
	//应该用map(map的实现就是树)
	//int i = orderMap.find(order.get_ID());
	return orderMap.count(str);
}


bool OrderGroup::exist_string(const string& str1, const string& str2)
{
	if (str2.size() > str1.size())return 0;
	for (unsigned int i = 0; i <= str1.size() - str2.size(); i++)
	{
		string s;
		for (unsigned int j = 0; j < str2.size(); j++)
		{
			s += str1[i + j];
		}
		if (s == str2)return 1;
		s = "";
	}
	return 0;
}