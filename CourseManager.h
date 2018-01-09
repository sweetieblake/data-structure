#include"AdjListDirGraph.h"
#include<vector>
#include<string>
#include<fstream>
using namespace std;

class CourseManager
{
protected:
	AdjListDirGraph<string> *cRelation;
	vector<string> cNumber;
	vector<string> cName;
	vector<int> cHour;
	vector<int> cSemester;
	vector<vector<string>> cPre;
	vector<string> cList;
	ifstream infile;

	int LocateVex(const string &e);
	void Readln();
	
public:
	CourseManager() {};
	~CourseManager() {};
	void courseManage(char infileName[]);
	void show();

};
int CourseManager::LocateVex(const string &e)
{
	string temp;
	for (int i = 0; i < cRelation->GetVexNum(); i++)
	{
		cRelation->GetElem(i, temp);
		if (temp == e)
		{
			return i;
		}
	}
}

void CourseManager::Readln()
{
	char ch[318];
	infile.getline(ch, 318);
	return;
	
}

void CourseManager::courseManage(char infileName[])
{
	infile.open(infileName);
	char ch;

	infile.seekg(0);
	ch = infile.get();
	while (ch != 'c')                       //定位到课程信息开始的位置
	{
		if (ch != '\n') Readln();
		ch = infile.get();
	}

	while (ch == 'c')
	{
		string temp;            //临时字符串
		int n;                  //临时整型变量
		vector<string> cPre_Node;         //先行课序列节点
		cPre_Node.clear();       //清空节点内内容
		infile.seekg(-1, ios::cur);       //向前一个字符
		infile >> temp;
		cNumber.push_back(temp);
		infile >> temp;
		cName.push_back(temp);
		infile >> n;
		cHour.push_back(n);
		infile >> n;
		cSemester.push_back(n);

		ch = infile.get();
		while (ch == ' ' || ch == '\t')
		{
			ch = infile.get();
		}

		if (ch == '\n')              //没有先行课的情况
		{ 
			cPre.push_back(cPre_Node);
		}
		else                         //有一个或两个先行课的情况
		{
			infile.seekg(-1, ios::cur);     //向前一个字符
			infile >> temp;
			cPre_Node.push_back(temp);
			ch = infile.get();
			if (ch != '\n')
			{
				infile >> temp;
				cPre_Node.push_back(temp);
				ch = infile.get();                //！！此处还应当执行一次取字符操作以正确跳到下一行
			}
			cPre.push_back(cPre_Node);

		}
		ch = infile.get();
	}                                                        //读取课程信息完毕

	int num = cNumber.size();                              //复制cNumber中的内容到string数组中
	string *es = new string[num];
	for (int i = 0; i < num; i++)
	{
		es[i] = cNumber[i];
	}

	cRelation = new AdjListDirGraph<string>(es, num);          //以课程编号为节点建立邻接表有向图

	for (int i = 0; i < cPre.size(); i++)                   //用cPre中的信息为有向图添加边
	{
		if (!cPre[i].empty())
		{
			string e1, e2;
			int v1, v2;
			e1 = cNumber[i];
			e2 = cPre[i][0];
			v1 = LocateVex(e1);
			v2 = LocateVex(e2);
			cRelation->InsertEdge(v1, v2);

			if (cPre[i].size() == 2)
			{
				e2 = cPre[i][1];
				v2 = LocateVex(e2);
				cRelation->InsertEdge(v1, v2);
			}
		}
	}

	num = 0;                                            //统计没有被安排的课程的数量
	while (cSemester[num] == 0)
	{
		num++;
	}

	int completeNum = 0;
	while (completeNum != num)                       //拓扑排序，结果存放在cList中
	{
		string temp;
		for (int i = 0; i < num; i++)
		{
			if (cRelation->GetTag(i) == UNVISITED)
			{
				if (cRelation->FirstAdjVex(i) == -1)
				{
					cRelation->SetTag(i, VISITED);
					for (int j = 0; j < num; j++)
					{
						cRelation->DeleteEdge(j, i);
					}
					cRelation->GetElem(i, temp);
					cList.push_back(temp);
					completeNum++;
				}
			}
		}
	}

}

void CourseManager::show()
{
	infile.seekg(0);
	char ch;
	ch = infile.get();
	while (ch < 30 || ch > 39)
	{
		if (ch != '\n') Readln();
		ch = infile.get();
	}

	infile.seekg(-1, ios::cur);

	int n[9];
	for (int i = 1; i <= 8; i++)
	{
		infile >> n[i];
	}

	int num[9] = { 0 };
	for (int i = cList.size(); i<cSemester.size() ; i++)
	{
		int semester;
		semester = cSemester[i];
		num[semester]++;
	}

	int mark = 0;
	for (int i = 1; i <= 8; i++)
	{
		cout << "第"<<i<<"学期:";
		while (num[i] != n[i])
		{
			cout << cList[mark]<<"  ";
			mark++;
			num[i]++;
		}
		cout << endl;

	}
}


