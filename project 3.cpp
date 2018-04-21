//GBK汉字内码范围
//区码位码
//B0A1-F7FE  AA40-FEA0  8140-A0FE

#pragma warning(disable:4996)
#include<iostream>
#include<fstream>
#include<string>
#include<map>
#include<functional>//std::greater
#include<ctime>
using namespace std;
int judge(unsigned char a, unsigned char b){//判断a和b组成的是否是个汉字
	if ((a >= 176 && b >= 161 && a <= 247 && b <= 254) || (a >= 170 && b >= 64 && a <= 254 && b <= 160) || (a >= 129 && b >= 64 && a <= 160 && b <= 254))
		return 1;
	return 0;
}
int del(string s){//判断该字符串是否应该删去
	if (s.find("的") != -1 || s.find("是") != -1 || s.find("在") != -1 || s.find("了") != -1)//如果包含“的”“是”“在”“了”，return 1
		return 1;
	else if (((s.find("华") == 0||s.find("者")==0) && s.length() > 2)||(s.find("国")==0&&s.length()>4))//以“华”开头的基本都不成词,以“国”开头的三、四字基本不成词
		return 1;
	return 0;
}
int main()
{

	//定义一些数据
	typedef map<string, int> mymap;
	typedef multimap<int, string, greater<int>> mymap2;
	mymap::iterator it1;
	mymap2::iterator it2;
	mymap m1, m3, m5, m7, sum, sum2;
	mymap2 m2, m4, m6, m8;
	FILE* infile;
	ofstream outfile;//整个程序可以共用一个输出的类
	unsigned char t0, t1, t2, t3, t4, t5, t6, t7;//公用8个unsigned char变量
	int s1 = 0, s2 = 0, s3 = 0, s4 = 0;
	int x1, x2, x3, x4;
	//统计用时用到的变量
	cout << "**************************************" << endl;
	cout << "注：程序中时间单位均为ms" << endl;
	cout << "**************************************" << endl;
	clock_t f1, f2, begin, end;
	begin = clock();

	//读文件
	cout << "请输入要处理的文本文件的路径及文件名：" << endl;
	char txt[50];
	cin >> txt;
	infile = fopen(txt, "rb");
	while (!infile){
		cout << "无法打开文件！请检查输入是否正确并重新输入！" << endl;
		cout << "请重新输入：" << endl;
		cin >> txt;
		infile = fopen(txt, "rb");
	}
	f1 = clock();
	fseek(infile, 0, SEEK_END);
	int length = ftell(infile);
	cout << "文本文件总字节数：" << length << endl;
	rewind(infile);
	char* s = new char[length];
	fread(s, 1, length, infile);
	fclose(infile);
	f2 = clock();
	cout << "读文件用时：" << difftime(f2, f1) << endl;

	//统计一字串
	for (int i = 0; i < length - 1; i++){
		if (s[i] >= 0)continue;
		t0 = s[i], t1 = s[i + 1];
		//B0A1-F7FE  AA40-FEA0  8140-A0FE
		if (judge(t0, t1))
		{
			string t;
			t += t0;
			t += t1;
			m1[t]++;
		}
		i++;
	}
	f1 = clock();
	cout << "统计一字串用时：" << difftime(f1, f2) << endl;

	//排序输出一字串

	for (it1 = m1.begin(); it1 != m1.end(); it1++){
		m2.insert(pair<int, string>(it1->second, it1->first));
		s1 += it1->second;
	}
	outfile.open("d://一字串.txt", ios::out);
	outfile << "总次数：" << s1 << endl;
	for (it2 = m2.begin(); it2 != m2.end(); it2++){
		outfile << it2->second << " " << it2->first << endl;
	}
	outfile.close();
	f2 = clock();
	cout << "排序输出一字串用时：" << difftime(f2, f1) << endl;


	//统计二字串
	for (int i = 0; i < length - 3; i++){
		if (s[i]>0)continue;
		if (s[i + 2] > 0){
			i += 2; continue;
		}
		t0 = s[i], t1 = s[i + 1], t2 = s[i + 2], t3 = s[i + 3];
		if (judge(t0, t1) && judge(t2, t3)){
			string t;
			t += t0;
			t += t1;
			t += t2;
			t += t3;
			m3[t]++;
		}
		i++;
	}
	f1 = clock();
	cout << "统计二字串用时：" << difftime(f1, f2) << endl;

	//排序输出二字串
	for (it1 = m3.begin(); it1 != m3.end(); it1++){
		m4.insert(pair<int, string>(it1->second, it1->first));
		s2 += it1->second;
	}
	f2 = clock();
	cout << "排序二字串用时：" << difftime(f2, f1) << endl;
	outfile.open("d://二字串.txt", ios::out);
	outfile << "总次数：" << s2 << endl;
	for (it2 = m4.begin(); it2 != m4.end(); it2++){
		outfile << it2->second << " " << it2->first << endl;
	}
	outfile.close();
	f1 = clock();
	cout << "输出二字串用时：" << difftime(f1, f2) << endl;


	//统计三字串
	for (int i = 0; i < length - 5; i++){
		if (s[i]>0)continue;
		if (s[i + 2] > 0){
			i += 2; continue;
		}
		if (s[i + 4] > 0){
			i += 4; continue;
		}
		t0 = s[i], t1 = s[i + 1], t2 = s[i + 2], t3 = s[i + 3], t4 = s[i + 4], t5 = s[i + 5];
		if (judge(t0, t1) && judge(t2, t3) && judge(t4, t5)){
			string t;
			t += t0;
			t += t1;
			t += t2;
			t += t3;
			t += t4;
			t += t5;
			m5[t]++;
		}
		i++;
	}
	f2 = clock();
	cout << "统计三字串用时：" << difftime(f2, f1) << endl;

	//排序输出三字串
	for (it1 = m5.begin(); it1 != m5.end(); it1++){
		m6.insert(pair<int, string>(it1->second, it1->first));
		s3 += it1->second;
	}
	f1 = clock();
	cout << "排序三字串用时：" << difftime(f1, f2) << endl;
	outfile.open("d://三字串.txt", ios::out);
	outfile << "总次数：" << s3 << endl;
	for (it2 = m6.begin(); it2 != m6.end(); it2++){
		outfile << it2->second << " " << it2->first << endl;
	}
	outfile.close();
	f2 = clock();
	cout << "输出三字串用时：" << difftime(f2, f1) << endl;


	//统计四字串
	for (int i = 0; i < length - 5; i++){
		if (s[i]>0)continue;
		if (s[i + 2] > 0){
			i += 2; continue;
		}
		if (s[i + 4] > 0){
			i += 4; continue;
		}
		if (s[i + 6] > 0){
			i += 6; continue;
		}
		t0 = s[i], t1 = s[i + 1], t2 = s[i + 2], t3 = s[i + 3], t4 = s[i + 4], t5 = s[i + 5], t6 = s[i + 6], t7 = s[i + 7];
		if (judge(t0, t1) && judge(t2, t3) && judge(t4, t5) && judge(t6, t7)){
			string t;
			t += t0;
			t += t1;
			t += t2;
			t += t3;
			t += t4;
			t += t5;
			t += t6;
			t += t7;
			m7[t]++;
		}
		i++;
	}
	f1 = clock();


	//排序输出四字串
	for (it1 = m7.begin(); it1 != m7.end(); it1++){
		m8.insert(pair<int, string>(it1->second, it1->first));
		s4 += it1->second;
	}

	f2 = clock();
	cout << "排序四字串用时：" << difftime(f2, f1) << endl;
	outfile.open("d://四字串.txt", ios::out);
	outfile << "总次数：" << s4 << endl;
	for (it2 = m8.begin(); it2 != m8.end(); it2++){
		outfile << it2->second << " " << it2->first << endl;
	}
	outfile.close();
	f1 = clock();
	cout << "输出四字串用时：" << difftime(f1, f2) << endl;
	cout << "统计四字串用时：" << difftime(f1, f2) << endl;

	//按阈值初步生成词典map
	x1 = s1*0.00117;
	x2 = s2*0.000206;
	x3 = s3*0.0000603;
	x4 = s4*0.0000259;
	for (it2 = m2.begin(); it2->first > x1; it2++){
		sum.insert(pair<string, int>(it2->second, it2->first));
	}
	for (it2 = m4.begin(); it2->first > x2; it2++){
		sum.insert(pair<string, int>(it2->second, it2->first));
	}
	for (it2 = m6.begin(); it2->first > x3; it2++){
		sum.insert(pair<string, int>(it2->second, it2->first));
	}
	for (it2 = m8.begin(); it2->first > x4; it2++){
		sum.insert(pair<string, int>(it2->second, it2->first));
	}

	//根据判断函数进一步筛选词典文件
	outfile.open("d://词典.txt", ios::out);
	int i = 1;
	for (it1 = sum.begin();it1!= sum.end(); it1++){
		if (!del(it1->first)){//如果该string无须删去
			outfile << i << ". " << it1->first << endl;
			i++;
		}
	}
	outfile.close();
	f2 = clock();
	cout << "统计词典文件用时：" << difftime(f2, f1) << endl;
	end = clock();
	cout << "程序总用时：" << difftime(end, begin) << endl;

	
	return 0;
}