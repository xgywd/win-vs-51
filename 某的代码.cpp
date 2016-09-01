#include<iostream>
#include<string>
#include<fstream>
#include<iomanip>
#include<vector>
using namespace std;

class info
{
public:
	string name;
	string number;            //学号唯一！
	string kecheng;           //info类的格式：姓名；学号；课程；学分；成绩；类型；判断是否挂科
	int xuefen;               //要实现一个学号对应一种姓名，一个姓名只能对应一个课程一次
	string chengji;           
	string leixing;
	int pdjg;
	void print();
	virtual void puanduan(){}//根据类型、成绩，给出是否及格（1、0）
};
void info::print()
{
	cout<<name
		<<","
		<<number
		<<","
		<<kecheng
		<<","
		<<xuefen
		<<","
		<<chengji
		<<endl;
}
void showgrade()
{
	fstream iofile;
	iofile.open("data.dat",ios::binary|ios::in|ios::out);
	try{
		if(!iofile) throw(0);
	}
	catch(int){
		cerr<<"OPEN ERROR!"<<endl;
		abort();
	}
	int cho;
	char outf[];
	
	info *oute = new info;
	//info oute;
	string name;
	string number;

	cout<<"请选择：1.输入姓名   2.输入学号"<<endl;
	cin>>cho;
	if(cho==1){
		cout<<"请输入姓名"<<endl;
		cin>>name;
	}else if (cho==2){
		cout<<"请输入学号"<<endl;
		cin>>number;
	}
	for(int i=0;;)
	{
		iofile.read(outf,sizeof(info));
		oute=(info)outf;
		if (iofile.eof()==1){
			if(i==0) cout<<"未找到"<<endl;
			cout<<"查找结束"<<endl;
			break;
		}
		if (cho==1){
			if (oute->name==name){
				oute->print();
				i++;
			}
		}
		else if (cho==2){
			if (oute->number==number){
				oute->print();
				i++;
			}
		}
	}
	iofile.close();
	delete oute;
}


int main()
{
	showgrade();
	return 0;
}