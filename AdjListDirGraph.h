#include <iostream>
#include <list>
#include <queue>
using namespace std;


//�ڽӾ�������ͼ��C++����
const int DEFAULT_SIZE = 20;
enum StatusCode { SUCCESS, FAIL, UNDER_FLOW, OVER_FLOW, RANGE_ERROR, DUPLICATE_ERROR, NOT_PRESENT, ENTRY_INSERTED, ENTRY_FOUND, VISITED, UNVISITED };

// �ڽӱ�ͼ������ģ��
template <class ElemType>
class AdjListGraphVexNode
{
protected:
	ElemType data;//��������    
	list<int> adjList;

public:
	AdjListGraphVexNode(ElemType e, list<int> adj);
	AdjListGraphVexNode();

	ElemType GetData()const;
	void SetData(ElemType e);

	list<int> GetAdjList()const;
	void SetAdjList(list<int> l);
};

// ����ͼ���ڽӱ���ģ��
template <class ElemType>
class AdjListDirGraph
{
protected:
	int vexNum, edgeNum;                        // ��������ͱ���
	AdjListGraphVexNode<ElemType>* vexTable;    // �����
	mutable StatusCode* tags;                    // ָ���־�����ָ��                

	void DestroyHelp();                            // ��������ͼ,�ͷ�����ͼ���õĿռ�

public:
	AdjListDirGraph(ElemType es[], int vertexNum = DEFAULT_SIZE);// ���춥������Ϊes[],�������ΪvertexNum,����Ϊ0������ͼ
	AdjListDirGraph(int vertexNum = DEFAULT_SIZE);// ���춥�����ΪvertexNum,����Ϊ0������ͼ
	~AdjListDirGraph();                            // ��������ģ��
	AdjListDirGraph(const AdjListDirGraph<ElemType> &copy);    // ���ƹ��캯��ģ��
	AdjListDirGraph<ElemType>& operator=(const AdjListDirGraph<ElemType> &copy);// ���ظ�ֵ�����

	StatusCode GetElem(int v, ElemType &e) const;// �󶥵��Ԫ��    
	StatusCode SetElem(int v, const ElemType &e);// ���ö����Ԫ��ֵ
	int GetVexNum() const;                        // ���ض������             
	int GetedgeNum() const;                        // ���ر�������             
	int FirstAdjVex(int v) const;                // ���ض���v�ĵ�һ���ڽӵ�             
	int NextAdjVex(int v1, int v2) const;        // ���ض���v1�������v2����һ���ڽӵ�             
	void InsertEdge(int v1, int v2);            // ���붥��Ϊv1��v2�ı�             
	void DeleteEdge(int v1, int v2);            // ɾ������Ϊv1��v2�ı�             
	StatusCode GetTag(int v) const;            // ���ض���v�ı�־         
	void SetTag(int v, StatusCode val) const;    // ���ö���v�ı�־Ϊval         
	void Display(bool showVexElem = true) const;
	void BFSTraverse(void(*visit)(const ElemType &))const;
};


// �����������������Ϊitem,ָ���ڽ�����Ϊadj�Ķ���
template <class ElemType>
AdjListGraphVexNode<ElemType>::AdjListGraphVexNode(ElemType e, list<int> adj) {
	data = e;
	adjList = adj;
}

// Ĭ�ϵĹ��캯��
template <class ElemType>
AdjListGraphVexNode<ElemType>::AdjListGraphVexNode() {
}

template <class ElemType>
ElemType AdjListGraphVexNode<ElemType>::GetData() const {
	return data;
}

template <class ElemType>
void AdjListGraphVexNode<ElemType>::SetData(ElemType e) {
	data = e;
}


template <class ElemType>
list<int> AdjListGraphVexNode<ElemType>::GetAdjList() const {
	return adjList;
}

template <class ElemType>
void AdjListGraphVexNode<ElemType>::SetAdjList(list<int> l) {
	adjList = l;
}

// ������������춥����ΪnumVex,��������Ϊes[],����Ϊ0������ͼ
template <class ElemType>
AdjListDirGraph<ElemType>::AdjListDirGraph(ElemType es[], int vertexNum = DEFAULT_SIZE) {
	if (vertexNum < 0) throw "�����������Ϊ����";

	vexNum = vertexNum;
	edgeNum = 0;

	vexTable = new AdjListGraphVexNode<ElemType>[vertexNum];
	for (int i = 0; i < vertexNum; i++)
		vexTable[i].SetData(es[i]);

	tags = new StatusCode[vertexNum];
	for (int i = 0; i < vertexNum; i++)
		tags[i] = UNVISITED;
}

// ������������춥����ΪnumVex,����Ϊ0������ͼ
template <class ElemType>
AdjListDirGraph<ElemType>::AdjListDirGraph(int vertexNum = DEFAULT_SIZE) {
	if (vertexNum < 0) throw "�����������Ϊ����";

	vexNum = vertexNum;
	edgeNum = 0;

	vexTable = new AdjListGraphVexNode<ElemType>[vertexNum];

	tags = new StatusCode[vertexNum];
	for (int i = 0; i < vertexNum; i++)
		tags[i] = UNVISITED;
}

// �����������������ͼ,�ͷ�����ͼ���õĿռ�
template <class ElemType>
void AdjListDirGraph<ElemType>::DestroyHelp() {
	delete[] vexTable;
	delete[] tags;
}

template <class ElemType>
AdjListDirGraph<ElemType>::~AdjListDirGraph() {
	DestroyHelp();
}

//�������캯��
template <class ElemType>
AdjListDirGraph<ElemType>::AdjListDirGraph(const AdjListDirGraph<ElemType> &copy) {
	vexNum = copy.vexNum;
	edgeNum = copy.edgeNum;

	vexTable = new AdjListGraphVexNode<ElemType>[vexNum];
	for (int i = 0; i< vexNum; i++) {
		vexTable[i].SetData(copy.vexTable[i].GetData());
		vexTable[i].SetAdjList(copy.vexTable[i].GetAdjList());
	}

	tags = new StatusCode[vexNum];
	for (int i = 0; i < vexNum; i++) {
		tags[i] = copy.tags[i];
	}
}

template <class ElemType>
AdjListDirGraph<ElemType>& AdjListDirGraph<ElemType>::operator=(const AdjListDirGraph<ElemType> &copy) {
	if (this == &copy)
		return *this;

	DestroyHelp();

	vexNum = copy.vexNum;
	edgeNum = copy.edgeNum;

	vexTable = new AdjListGraphVexNode<ElemType>[vexNum];
	for (int i = 0; i< vexNum; i++) {
		vexTable[i].SetData(copy.vexTable[i].GetData());
		vexTable[i].SetAdjList(copy.vexTable[i].GetAdjList());
	}

	tags = new StatusCode[vexNum];
	for (int i = 0; i < vexNum; i++) {
		tags[i] = copy.tags[i];
	}

	return *this;
}

// ����������󶥵�v��Ԫ��, v��ȡֵ��ΧΪ0 �� v �� vexNum, v�Ϸ�ʱ����SUCCESS, ���򷵻�RANGE_ERROR
template <class ElemType>
StatusCode AdjListDirGraph<ElemType>::GetElem(int v, ElemType &e) const {
	if (v < 0 || v >= vexNum) {
		return NOT_PRESENT;
	}
	else {
		e = vexTable[v].GetData();
		return ENTRY_FOUND;
	}
}

// ������������ö����Ԫ��ֵv��ȡֵ��ΧΪ0 �� v �� vexNum, v�Ϸ�ʱ����SUCCESS, ���򷵻�RANGE_ERROR
template <class ElemType>
StatusCode AdjListDirGraph<ElemType>::SetElem(int v, const ElemType &e) {
	if (v < 0 || v >= vexNum) {
		return RANGE_ERROR;
	}
	else {
		vexTable[v].SetData(e);
		return SUCCESS;
	}
}

template <class ElemType>
int AdjListDirGraph<ElemType>::GetVexNum() const {
	return vexNum;
}

template <class ElemType>
int AdjListDirGraph<ElemType>::GetedgeNum() const {
	return edgeNum;
}

// ������������ض���v�ĵ�һ���ڽӵ�    
template <class ElemType>
int AdjListDirGraph<ElemType>::FirstAdjVex(int v) const {
	if (v < 0 || v >= vexNum) throw "v���Ϸ�!";

	list<int> list_v = vexTable[v].GetAdjList();

	if (list_v.empty()) {//���ڽ��������ڽӵ�
		return -1;
	}
	else {
		list<int>::iterator it = list_v.begin();
		return *it;
	}
}

// ������������ض���v1�������v2����һ���ڽӵ�        
template <class ElemType>
int AdjListDirGraph<ElemType>::NextAdjVex(int v1, int v2) const {
	if (v1 < 0 || v1 >= vexNum) throw "v1���Ϸ���";
	if (v2 < 0 || v2 >= vexNum) throw "v2���Ϸ�!";
	if (v1 == v2) throw "v1���ܵ���v2!";

	list<int> list_v1 = vexTable[v1].GetAdjList();

	if (list_v1.empty())// ���ڽ��������ڽӵ�
		return -1;
	else {
		list<int>::iterator it = list_v1.begin();
		for (; it != list_v1.end() && *it != v2; it++);//����list_v1
		if (*it == v2) {//�ҵ��ڽӵ�v2
			it++;
			if (it != list_v1.end())
				return *it;
			else
				return -1;
		}
		else {//δ�ҵ��ڽӵ�v2
			return -1;
		}
	}
}

// ������������붥��Ϊv1��v2�ı�        
template <class ElemType>
void AdjListDirGraph<ElemType>::InsertEdge(int v1, int v2) {
	if (v1 < 0 || v1 >= vexNum) throw "v1���Ϸ���";
	if (v2 < 0 || v2 >= vexNum) throw "v2���Ϸ�!";
	if (v1 == v2) throw "v1���ܵ���v2!";

	list<int> list_v1 = vexTable[v1].GetAdjList();

	if (list_v1.empty()) {// ���ڽ��������ڽӵ�
		list_v1.push_back(v2);
		vexTable[v1].SetAdjList(list_v1);
		edgeNum++;
	}
	else {//�����Ӧv1�����ڽӱ�Ϊ��
		list<int>::iterator it = list_v1.begin();
		for (; it != list_v1.end() && *it != v2; it++);//����list_v1
		if (it == list_v1.end()) {//�����ڱ�v1-v2
			list_v1.push_back(v2);
			vexTable[v1].SetAdjList(list_v1);
			edgeNum++;
		}
	}
}

// ���������ɾ������Ϊv1��v2�ı�             
template <class ElemType>
void AdjListDirGraph<ElemType>::DeleteEdge(int v1, int v2) {
	if (v1 < 0 || v1 >= vexNum) throw "v1���Ϸ���";
	if (v2 < 0 || v2 >= vexNum) throw "v2���Ϸ�!";
	if (v1 == v2) throw "v1���ܵ���v2!";

	list<int> list_v1 = vexTable[v1].GetAdjList();

	if (!list_v1.empty()) {//�����Ӧv1�����ڽӱ�Ϊ��
		list<int>::iterator it = list_v1.begin();
		for (; it != list_v1.end() && *it != v2; it++);//����list_v1
		if (*it == v2) {//�ҵ��ڽӵ�v2
			list_v1.erase(it);
			vexTable[v1].SetAdjList(list_v1);
			edgeNum--;
		}
	}
}

template <class ElemType>
StatusCode AdjListDirGraph<ElemType>::GetTag(int v) const {
	if (v < 0 || v >= vexNum) throw "v���Ϸ�!";
	return tags[v];
}

template <class ElemType>
void AdjListDirGraph<ElemType>::SetTag(int v, StatusCode val) const {
	if (v < 0 || v >= vexNum) throw "v���Ϸ�!";
	tags[v] = val;
}

// �������: ��ʾ�ڽӾ�������ͼ
template <class ElemType>
void AdjListDirGraph<ElemType>::Display(bool showVexElem = true) const {
	for (int i = 0; i < vexNum; i++) {//����ÿһ������
		if (showVexElem)
			cout << vexTable[i].GetData();

		list<int> list_v1 = vexTable[i].GetAdjList();
		if (!list_v1.empty()) {
			list<int>::iterator it = list_v1.begin();
			for (; it != list_v1.end(); it++)
				cout << " -> " << *it;
		}
		cout << endl;
	}
}

// �����������ͼg���й�����ȱ���
template <class ElemType>
void AdjListDirGraph<ElemType>::BFSTraverse(void(*visit)(const ElemType &))const {
	for (int i = 0; i < vexNum; i++) {
		tags[i] = UNVISITED;
	}

	for (int i = 0; i < vexNum; i++) {
		if (tags[i] == UNVISITED) {
			tags[i] = VISITED;
			visit(vexTable[i].GetData());
			queue<int> q;
			q.push(i);
			while (!q.empty()) {
				int v = q.front();
				q.pop();
				for (int u = FirstAdjVex(v); u != -1; u = NextAdjVex(v, u)) {
					if (tags[u] == UNVISITED) {
						visit(vexTable[u].GetData());
						tags[u] = VISITED;
						q.push(u);
					}
				}
			}
		}
	}
}
