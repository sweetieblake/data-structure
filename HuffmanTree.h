#include<iostream>
#include<string>
#include<list>

using namespace std;


template<class WeightType>
struct HuffmanTreeNode
{
	WeightType weight;
	unsigned int parent, leftChild, rightChild;

	HuffmanTreeNode();
	HuffmanTreeNode(WeightType w, int p, int l, int r);

};

template<class WeightType>
HuffmanTreeNode<WeightType>:: HuffmanTreeNode()                 //�轫��ĸ���ӳ�ʼ��Ϊ�㣬��������Ϊ�жϱ�׼
{
	parent = 0;
	leftChild = 0;
	rightChild = 0;
}

template<class WeightType>
HuffmanTreeNode<WeightType>::HuffmanTreeNode(WeightType w, int p, int l, int r)
{
	weight = w;
	parent = p;
	leftChild = l;
	rightChild = r;
}

template<class CharType,class WeightType>
class HuffmanTree
{
protected:
	HuffmanTreeNode<WeightType> *nodes;       
	CharType *leafChars;
	string *leafCharCodes;
	int curPos;        //�Ӹ��ڵ㵽Ҷ�ڵ��·���еĵ�ǰ���
	int num;       //Ҷ�ڵ���

	void Select(int cur, int &min1, int &min2);
	void CreateHuffmanTree(CharType ch[], WeightType w[], int n);

public:
	HuffmanTree(CharType ch[],WeightType w[],int n);
	virtual~HuffmanTree() {};
	string EnCode(CharType ch);
	list<CharType> DeCode(string strCode);
};

template<class CharType,class WeightType>
void HuffmanTree<CharType, WeightType>::CreateHuffmanTree(CharType ch[], WeightType w[], int n)
{
	num = n;
	int m = 2 * n - 1;
	curPos = m;

	nodes = new HuffmanTreeNode<WeightType>[m+1];
	leafChars = new CharType[n + 1];
	leafCharCodes = new string[n + 1];

	for (int cur = 1; cur <= n; cur++)
	{
		leafChars[cur] = ch[cur - 1];
		nodes[cur].weight = w[cur - 1];
	}

	for (int cur = n + 1; cur <= m; cur++)
	{
		int r1, r2;
		Select(cur - 1, r1, r2);
		nodes[cur].weight = nodes[r1].weight + nodes[r2].weight;
		nodes[cur].leftChild = r1;
		nodes[cur].rightChild = r2;
		nodes[r1].parent = nodes[r2].parent = cur;

	}

	for (int cur = 1; cur <= n; cur++)
	{


	
		for (int child = cur, parent = nodes[cur].parent; parent != 0; child = parent, parent = nodes[child].parent)
		{
			if (nodes[parent].leftChild == child)
			{
	
				leafCharCodes[cur].insert(string::size_type(0),1,'0');
			}
			else
			{
				leafCharCodes[cur].insert(string::size_type(0), 1, '1');
			}
		}
	
	}
	//for (int i = 1; i <= n; i++)              һ��ʼ���ڲ鿴�ڵ㸸�����Ƿ���ȷ
	//{
	//	cout << nodes[i].parent << nodes[i].leftChild << nodes[i].rightChild << endl;
	//}
}

template<class CharType,class WeightType>
void HuffmanTree<CharType, WeightType>::Select(int cur, int &min1, int &min2)
{
	int min;              
	WeightType minWeight = 999999;    //�˴�Ӧ������һ���ܴ��ֵ��������������һ������������ֵ�ͱ��滻������
	for (int i = 1; i <= cur; i++)
	{
		if (nodes[i].parent == 0)
		{
			if (nodes[i].weight < minWeight)
			{
				minWeight = nodes[i].weight;
				min = i;
			}
		}
	}
	min1 = min;
	minWeight = 999999;
	for (int i = 1; i <= cur; i++)
	{
		if (nodes[i].parent == 0 && i != min1)
		{
			if (nodes[i].weight < minWeight)
			{
				minWeight = nodes[i].weight;
				min = i;
			}
		}
	}
	min2 = min;
}

template<class CharType,class WeightType>
HuffmanTree<CharType, WeightType>::HuffmanTree(CharType ch[], WeightType w[], int n)
{
	CreateHuffmanTree(ch, w, n);
}

template<class CharType, class WeightType>
string HuffmanTree<CharType, WeightType>::EnCode(CharType ch)
{
	for (int i = 1; i <= num; i++)
	{
		if (leafChars[i] == ch)
		{
			return leafCharCodes[i];
		}
	}
}

template<class CharType, class WeightType>
list<CharType> HuffmanTree<CharType, WeightType>::DeCode(string strCode)
{
	list<CharType> result;
	for (int i = 0; i < strCode.length(); i++)        //��0��ʼ
	{
		if (strCode[i] == '0')
		{
			curPos = nodes[curPos].leftChild;
		}
		else
		{
			curPos = nodes[curPos].rightChild;
		}
		if (nodes[curPos].leftChild == 0 && nodes[curPos].rightChild == 0)
		{
			result.push_back(leafChars[curPos]);
			curPos = 2*num - 1;              //curPos �ع���ڵ��λ�� Ҳ����2*num - 1
		}
	}
	return result;
}
