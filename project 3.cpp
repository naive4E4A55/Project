//GBK�������뷶Χ
//����λ��
//B0A1-F7FE  AA40-FEA0  8140-A0FE

#pragma warning(disable:4996)
#include<iostream>
#include<fstream>
#include<string>
#include<map>
#include<functional>//std::greater
#include<ctime>
using namespace std;
int judge(unsigned char a, unsigned char b){//�ж�a��b��ɵ��Ƿ��Ǹ�����
	if ((a >= 176 && b >= 161 && a <= 247 && b <= 254) || (a >= 170 && b >= 64 && a <= 254 && b <= 160) || (a >= 129 && b >= 64 && a <= 160 && b <= 254))
		return 1;
	return 0;
}
int del(string s){//�жϸ��ַ����Ƿ�Ӧ��ɾȥ
	if (s.find("��") != -1 || s.find("��") != -1 || s.find("��") != -1 || s.find("��") != -1)//����������ġ����ǡ����ڡ����ˡ���return 1
		return 1;
	else if (((s.find("��") == 0||s.find("��")==0) && s.length() > 2)||(s.find("��")==0&&s.length()>4))//�ԡ�������ͷ�Ļ��������ɴ�,�ԡ�������ͷ���������ֻ������ɴ�
		return 1;
	return 0;
}
int main()
{

	//����һЩ����
	typedef map<string, int> mymap;
	typedef multimap<int, string, greater<int>> mymap2;
	mymap::iterator it1;
	mymap2::iterator it2;
	mymap m1, m3, m5, m7, sum, sum2;
	mymap2 m2, m4, m6, m8;
	FILE* infile;
	ofstream outfile;//����������Թ���һ���������
	unsigned char t0, t1, t2, t3, t4, t5, t6, t7;//����8��unsigned char����
	int s1 = 0, s2 = 0, s3 = 0, s4 = 0;
	int x1, x2, x3, x4;
	//ͳ����ʱ�õ��ı���
	cout << "**************************************" << endl;
	cout << "ע��������ʱ�䵥λ��Ϊms" << endl;
	cout << "**************************************" << endl;
	clock_t f1, f2, begin, end;
	begin = clock();

	//���ļ�
	cout << "������Ҫ������ı��ļ���·�����ļ�����" << endl;
	char txt[50];
	cin >> txt;
	infile = fopen(txt, "rb");
	while (!infile){
		cout << "�޷����ļ������������Ƿ���ȷ���������룡" << endl;
		cout << "���������룺" << endl;
		cin >> txt;
		infile = fopen(txt, "rb");
	}
	f1 = clock();
	fseek(infile, 0, SEEK_END);
	int length = ftell(infile);
	cout << "�ı��ļ����ֽ�����" << length << endl;
	rewind(infile);
	char* s = new char[length];
	fread(s, 1, length, infile);
	fclose(infile);
	f2 = clock();
	cout << "���ļ���ʱ��" << difftime(f2, f1) << endl;

	//ͳ��һ�ִ�
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
	cout << "ͳ��һ�ִ���ʱ��" << difftime(f1, f2) << endl;

	//�������һ�ִ�

	for (it1 = m1.begin(); it1 != m1.end(); it1++){
		m2.insert(pair<int, string>(it1->second, it1->first));
		s1 += it1->second;
	}
	outfile.open("d://һ�ִ�.txt", ios::out);
	outfile << "�ܴ�����" << s1 << endl;
	for (it2 = m2.begin(); it2 != m2.end(); it2++){
		outfile << it2->second << " " << it2->first << endl;
	}
	outfile.close();
	f2 = clock();
	cout << "�������һ�ִ���ʱ��" << difftime(f2, f1) << endl;


	//ͳ�ƶ��ִ�
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
	cout << "ͳ�ƶ��ִ���ʱ��" << difftime(f1, f2) << endl;

	//����������ִ�
	for (it1 = m3.begin(); it1 != m3.end(); it1++){
		m4.insert(pair<int, string>(it1->second, it1->first));
		s2 += it1->second;
	}
	f2 = clock();
	cout << "������ִ���ʱ��" << difftime(f2, f1) << endl;
	outfile.open("d://���ִ�.txt", ios::out);
	outfile << "�ܴ�����" << s2 << endl;
	for (it2 = m4.begin(); it2 != m4.end(); it2++){
		outfile << it2->second << " " << it2->first << endl;
	}
	outfile.close();
	f1 = clock();
	cout << "������ִ���ʱ��" << difftime(f1, f2) << endl;


	//ͳ�����ִ�
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
	cout << "ͳ�����ִ���ʱ��" << difftime(f2, f1) << endl;

	//����������ִ�
	for (it1 = m5.begin(); it1 != m5.end(); it1++){
		m6.insert(pair<int, string>(it1->second, it1->first));
		s3 += it1->second;
	}
	f1 = clock();
	cout << "�������ִ���ʱ��" << difftime(f1, f2) << endl;
	outfile.open("d://���ִ�.txt", ios::out);
	outfile << "�ܴ�����" << s3 << endl;
	for (it2 = m6.begin(); it2 != m6.end(); it2++){
		outfile << it2->second << " " << it2->first << endl;
	}
	outfile.close();
	f2 = clock();
	cout << "������ִ���ʱ��" << difftime(f2, f1) << endl;


	//ͳ�����ִ�
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


	//����������ִ�
	for (it1 = m7.begin(); it1 != m7.end(); it1++){
		m8.insert(pair<int, string>(it1->second, it1->first));
		s4 += it1->second;
	}

	f2 = clock();
	cout << "�������ִ���ʱ��" << difftime(f2, f1) << endl;
	outfile.open("d://���ִ�.txt", ios::out);
	outfile << "�ܴ�����" << s4 << endl;
	for (it2 = m8.begin(); it2 != m8.end(); it2++){
		outfile << it2->second << " " << it2->first << endl;
	}
	outfile.close();
	f1 = clock();
	cout << "������ִ���ʱ��" << difftime(f1, f2) << endl;
	cout << "ͳ�����ִ���ʱ��" << difftime(f1, f2) << endl;

	//����ֵ�������ɴʵ�map
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

	//�����жϺ�����һ��ɸѡ�ʵ��ļ�
	outfile.open("d://�ʵ�.txt", ios::out);
	int i = 1;
	for (it1 = sum.begin();it1!= sum.end(); it1++){
		if (!del(it1->first)){//�����string����ɾȥ
			outfile << i << ". " << it1->first << endl;
			i++;
		}
	}
	outfile.close();
	f2 = clock();
	cout << "ͳ�ƴʵ��ļ���ʱ��" << difftime(f2, f1) << endl;
	end = clock();
	cout << "��������ʱ��" << difftime(end, begin) << endl;

	
	return 0;
}