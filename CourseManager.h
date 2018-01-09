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
	while (ch != 'c')                       //��λ���γ���Ϣ��ʼ��λ��
	{
		if (ch != '\n') Readln();
		ch = infile.get();
	}

	while (ch == 'c')
	{
		string temp;            //��ʱ�ַ���
		int n;                  //��ʱ���ͱ���
		vector<string> cPre_Node;         //���п����нڵ�
		cPre_Node.clear();       //��սڵ�������
		infile.seekg(-1, ios::cur);       //��ǰһ���ַ�
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

		if (ch == '\n')              //û�����пε����
		{ 
			cPre.push_back(cPre_Node);
		}
		else                         //��һ�����������пε����
		{
			infile.seekg(-1, ios::cur);     //��ǰһ���ַ�
			infile >> temp;
			cPre_Node.push_back(temp);
			ch = infile.get();
			if (ch != '\n')
			{
				infile >> temp;
				cPre_Node.push_back(temp);
				ch = infile.get();                //�����˴���Ӧ��ִ��һ��ȡ�ַ���������ȷ������һ��
			}
			cPre.push_back(cPre_Node);

		}
		ch = infile.get();
	}                                                        //��ȡ�γ���Ϣ���

	int num = cNumber.size();                              //����cNumber�е����ݵ�string������
	string *es = new string[num];
	for (int i = 0; i < num; i++)
	{
		es[i] = cNumber[i];
	}

	cRelation = new AdjListDirGraph<string>(es, num);          //�Կγ̱��Ϊ�ڵ㽨���ڽӱ�����ͼ

	for (int i = 0; i < cPre.size(); i++)                   //��cPre�е���ϢΪ����ͼ��ӱ�
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

	num = 0;                                            //ͳ��û�б����ŵĿγ̵�����
	while (cSemester[num] == 0)
	{
		num++;
	}

	int completeNum = 0;
	while (completeNum != num)                       //�������򣬽�������cList��
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
		cout << "��"<<i<<"ѧ��:";
		while (num[i] != n[i])
		{
			cout << cList[mark]<<"  ";
			mark++;
			num[i]++;
		}
		cout << endl;

	}
}


