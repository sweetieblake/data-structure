#include <iostream>
#include <list>
#include <queue>
using namespace std;


//邻接矩阵有向图的C++描述
const int DEFAULT_SIZE = 20;
enum StatusCode { SUCCESS, FAIL, UNDER_FLOW, OVER_FLOW, RANGE_ERROR, DUPLICATE_ERROR, NOT_PRESENT, ENTRY_INSERTED, ENTRY_FOUND, VISITED, UNVISITED };

// 邻接表图顶点类模板
template <class ElemType>
class AdjListGraphVexNode
{
protected:
	ElemType data;//顶点数据    
	list<int> adjList;

public:
	AdjListGraphVexNode(ElemType e, list<int> adj);
	AdjListGraphVexNode();

	ElemType GetData()const;
	void SetData(ElemType e);

	list<int> GetAdjList()const;
	void SetAdjList(list<int> l);
};

// 有向图的邻接表类模板
template <class ElemType>
class AdjListDirGraph
{
protected:
	int vexNum, edgeNum;                        // 顶点个数和边数
	AdjListGraphVexNode<ElemType>* vexTable;    // 顶点表
	mutable StatusCode* tags;                    // 指向标志数组的指针                

	void DestroyHelp();                            // 销毁有向图,释放有向图点用的空间

public:
	AdjListDirGraph(ElemType es[], int vertexNum = DEFAULT_SIZE);// 构造顶点数据为es[],顶点个数为vertexNum,边数为0的有向图
	AdjListDirGraph(int vertexNum = DEFAULT_SIZE);// 构造顶点个数为vertexNum,边数为0的有向图
	~AdjListDirGraph();                            // 析构函数模板
	AdjListDirGraph(const AdjListDirGraph<ElemType> &copy);    // 复制构造函数模板
	AdjListDirGraph<ElemType>& operator=(const AdjListDirGraph<ElemType> &copy);// 重载赋值运算符

	StatusCode GetElem(int v, ElemType &e) const;// 求顶点的元素    
	StatusCode SetElem(int v, const ElemType &e);// 设置顶点的元素值
	int GetVexNum() const;                        // 返回顶点个数             
	int GetedgeNum() const;                        // 返回边数个数             
	int FirstAdjVex(int v) const;                // 返回顶点v的第一个邻接点             
	int NextAdjVex(int v1, int v2) const;        // 返回顶点v1的相对于v2的下一个邻接点             
	void InsertEdge(int v1, int v2);            // 插入顶点为v1和v2的边             
	void DeleteEdge(int v1, int v2);            // 删除顶点为v1和v2的边             
	StatusCode GetTag(int v) const;            // 返回顶点v的标志         
	void SetTag(int v, StatusCode val) const;    // 设置顶点v的标志为val         
	void Display(bool showVexElem = true) const;
	void BFSTraverse(void(*visit)(const ElemType &))const;
};


// 操作结果：构造数据为item,指向邻接链表为adj的顶点
template <class ElemType>
AdjListGraphVexNode<ElemType>::AdjListGraphVexNode(ElemType e, list<int> adj) {
	data = e;
	adjList = adj;
}

// 默认的构造函数
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

// 操作结果：构造顶点数为numVex,顶点数据为es[],边数为0的有向图
template <class ElemType>
AdjListDirGraph<ElemType>::AdjListDirGraph(ElemType es[], int vertexNum = DEFAULT_SIZE) {
	if (vertexNum < 0) throw "顶点个数不能为负！";

	vexNum = vertexNum;
	edgeNum = 0;

	vexTable = new AdjListGraphVexNode<ElemType>[vertexNum];
	for (int i = 0; i < vertexNum; i++)
		vexTable[i].SetData(es[i]);

	tags = new StatusCode[vertexNum];
	for (int i = 0; i < vertexNum; i++)
		tags[i] = UNVISITED;
}

// 操作结果：构造顶点数为numVex,边数为0的有向图
template <class ElemType>
AdjListDirGraph<ElemType>::AdjListDirGraph(int vertexNum = DEFAULT_SIZE) {
	if (vertexNum < 0) throw "顶点个数不能为负！";

	vexNum = vertexNum;
	edgeNum = 0;

	vexTable = new AdjListGraphVexNode<ElemType>[vertexNum];

	tags = new StatusCode[vertexNum];
	for (int i = 0; i < vertexNum; i++)
		tags[i] = UNVISITED;
}

// 操作结果：销毁有向图,释放有向图点用的空间
template <class ElemType>
void AdjListDirGraph<ElemType>::DestroyHelp() {
	delete[] vexTable;
	delete[] tags;
}

template <class ElemType>
AdjListDirGraph<ElemType>::~AdjListDirGraph() {
	DestroyHelp();
}

//拷贝构造函数
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

// 操作结果：求顶点v的元素, v的取值范围为0 ≤ v ＜ vexNum, v合法时返回SUCCESS, 否则返回RANGE_ERROR
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

// 操作结果：设置顶点的元素值v的取值范围为0 ≤ v ＜ vexNum, v合法时返回SUCCESS, 否则返回RANGE_ERROR
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

// 操作结果：返回顶点v的第一个邻接点    
template <class ElemType>
int AdjListDirGraph<ElemType>::FirstAdjVex(int v) const {
	if (v < 0 || v >= vexNum) throw "v不合法!";

	list<int> list_v = vexTable[v].GetAdjList();

	if (list_v.empty()) {//空邻接链表，无邻接点
		return -1;
	}
	else {
		list<int>::iterator it = list_v.begin();
		return *it;
	}
}

// 操作结果：返回顶点v1的相对于v2的下一个邻接点        
template <class ElemType>
int AdjListDirGraph<ElemType>::NextAdjVex(int v1, int v2) const {
	if (v1 < 0 || v1 >= vexNum) throw "v1不合法！";
	if (v2 < 0 || v2 >= vexNum) throw "v2不合法!";
	if (v1 == v2) throw "v1不能等于v2!";

	list<int> list_v1 = vexTable[v1].GetAdjList();

	if (list_v1.empty())// 空邻接链表，无邻接点
		return -1;
	else {
		list<int>::iterator it = list_v1.begin();
		for (; it != list_v1.end() && *it != v2; it++);//遍历list_v1
		if (*it == v2) {//找到邻接点v2
			it++;
			if (it != list_v1.end())
				return *it;
			else
				return -1;
		}
		else {//未找到邻接点v2
			return -1;
		}
	}
}

// 操作结果：插入顶点为v1和v2的边        
template <class ElemType>
void AdjListDirGraph<ElemType>::InsertEdge(int v1, int v2) {
	if (v1 < 0 || v1 >= vexNum) throw "v1不合法！";
	if (v2 < 0 || v2 >= vexNum) throw "v2不合法!";
	if (v1 == v2) throw "v1不能等于v2!";

	list<int> list_v1 = vexTable[v1].GetAdjList();

	if (list_v1.empty()) {// 空邻接链表，无邻接点
		list_v1.push_back(v2);
		vexTable[v1].SetAdjList(list_v1);
		edgeNum++;
	}
	else {//如果对应v1结点的邻接表不为空
		list<int>::iterator it = list_v1.begin();
		for (; it != list_v1.end() && *it != v2; it++);//遍历list_v1
		if (it == list_v1.end()) {//不存在边v1-v2
			list_v1.push_back(v2);
			vexTable[v1].SetAdjList(list_v1);
			edgeNum++;
		}
	}
}

// 操作结果：删除顶点为v1和v2的边             
template <class ElemType>
void AdjListDirGraph<ElemType>::DeleteEdge(int v1, int v2) {
	if (v1 < 0 || v1 >= vexNum) throw "v1不合法！";
	if (v2 < 0 || v2 >= vexNum) throw "v2不合法!";
	if (v1 == v2) throw "v1不能等于v2!";

	list<int> list_v1 = vexTable[v1].GetAdjList();

	if (!list_v1.empty()) {//如果对应v1结点的邻接表不为空
		list<int>::iterator it = list_v1.begin();
		for (; it != list_v1.end() && *it != v2; it++);//遍历list_v1
		if (*it == v2) {//找到邻接点v2
			list_v1.erase(it);
			vexTable[v1].SetAdjList(list_v1);
			edgeNum--;
		}
	}
}

template <class ElemType>
StatusCode AdjListDirGraph<ElemType>::GetTag(int v) const {
	if (v < 0 || v >= vexNum) throw "v不合法!";
	return tags[v];
}

template <class ElemType>
void AdjListDirGraph<ElemType>::SetTag(int v, StatusCode val) const {
	if (v < 0 || v >= vexNum) throw "v不合法!";
	tags[v] = val;
}

// 操作结果: 显示邻接矩阵有向图
template <class ElemType>
void AdjListDirGraph<ElemType>::Display(bool showVexElem = true) const {
	for (int i = 0; i < vexNum; i++) {//遍历每一个顶点
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

// 操作结果：对图g进行广度优先遍历
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
