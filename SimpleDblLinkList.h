#include<iostream>

using namespace std;

enum StatusCode
{
	SUCCESS, FAIL, UNDER_FLOW, OVER_FLOW, RANGE_ERROR, DUPLICATE_ERROR, NOT_PRESENT, ENTRY_INSERTED, ENTRY_FOUND, VISITED, UNVISITED
};

template <class ElemType>
struct DblNode
{
	ElemType data;
	DblNode<ElemType> *back;
	DblNode<ElemType> *next;

	DblNode();
	DblNode(ElemType, DblNode<ElemType> *linkBack = NULL, DblNode<ElemType> *linkNext = NULL);
};

template<class ElemType>
class SimpleDblLinkList
{

protected:
	DblNode<ElemType> *head;
	DblNode<ElemType> *GetElemPtr(int position) const;
	void Init();

public:
	SimpleDblLinkList();
	virtual ~SimpleDblLinkList();
	int Length() const;
	bool Empty() const;
	void Clear();
	void Traverse(void(*visit)(const ElemType &)) const;
	StatusCode GetElem(int position, ElemType &e) const;
	StatusCode SetElem(int position, const ElemType &e);
	StatusCode Delete(int position, ElemType &e);
	StatusCode Insert(int position, const ElemType &e);
	SimpleDblLinkList<ElemType> &operator=(const SimpleDblLinkList<ElemType> &copy);
};


template<class ElemType>
DblNode<ElemType>::DblNode()
{
	next = NULL;
}

template<class ElemType>
DblNode<ElemType>::DblNode(ElemType item, DblNode<ElemType> *linkBack /* = NULL */, DblNode<ElemType> *linkNext /* = NULL */)
{
	data = item;
	back = linkBack;
	next = linkNext;
}

template<class ElemType>
DblNode<ElemType> *SimpleDblLinkList<ElemType>::GetElemPtr(int position) const
{
	if (position == 0)
	{
		return head;
	}

	DblNode<ElemType> *tmpPtr = head->next;
	int curPosition = 1;
	while (tmpPtr != head && curPosition < position)
	{
		tmpPtr = tmpPtr->next;
		curPosition++;
	}

	if (tmpPtr != head && curPosition == position)
	{
		return tmpPtr;
	}
	else
	{
		return NULL;
	}
}

template<class ElemType>
void SimpleDblLinkList<ElemType>::Init()
{
	head = new DblNode<ElemType>;
	head->next = head;
	head->back = head;
}

template<class ElemType>
SimpleDblLinkList<ElemType>::SimpleDblLinkList()
{
	Init();
}

template<class ElemType>
SimpleDblLinkList<ElemType>::~SimpleDblLinkList()
{
	Clear();
	delete head;
}

template<class ElemType>
int SimpleDblLinkList<ElemType>::Length() const
{
	int count = 0;
	for (DblNode<ElemType> *tmpPtr = head->next; tmpPtr != head; tmpPtr = tmpPtr->next)
	{
		count++;
	}
	return count;
}

template<class ElemType>
bool SimpleDblLinkList<ElemType>::Empty() const
{
	return head->next == head;
}

template<class ElemType>
void SimpleDblLinkList<ElemType>::Clear()
{
	ElemType temp;
	while (!Empty())
	{
		Delete(1, temp);
	}
}

template<class ElemType>
void SimpleDblLinkList<ElemType>::Traverse(void(*visit)(const ElemType &)) const
{
	for (DblNode<ElemType> * tmpPtr = head->next; tmpPtr != head; tmpPtr = tmpPtr->next)
	{
		(*visit)(tmpPtr->data);
	}
}

template<class ElemType>
StatusCode SimpleDblLinkList<ElemType>::GetElem(int position, ElemType &e) const
{
	if (position < 1 || position > Length())
	{
		return RANGE_ERROR;
	}
	else
	{
		DblNode<ElemType> * tmpPtr = GetElemPtr(position);
		e = tmpPtr->data;
		return ENTRY_FOUND;
	}
}

template<class ElemType>
StatusCode SimpleDblLinkList<ElemType>::SetElem(int position, const ElemType &e)
{
	if (position < 1 || position > Length())
	{
		return RANGE_ERROR;
	}
	else
	{
		DblNode<ElemType> *tmpPtr = GetElemPtr(position);
		tmpPtr->data = e;
		return SUCCESS;
	}
}

template<class ElemType>
StatusCode SimpleDblLinkList<ElemType>::Insert(int position, const ElemType &e)
{
	if (position < 1 || position > Length() + 1)
	{
		return RANGE_ERROR;
	}

	else
	{
		DblNode<ElemType> *tmpPtr, *nextPtr, *newPtr;
		tmpPtr = GetElemPtr(position - 1);
		nextPtr = tmpPtr->next;
		newPtr = new DblNode<ElemType>(e, tmpPtr, nextPtr);         //注意此处不要遗忘 给出模板参数列表
		tmpPtr->next = newPtr;
		nextPtr->back = newPtr;
		return SUCCESS;

	}
}

template<class ElemType>
StatusCode SimpleDblLinkList<ElemType>::Delete(int position, ElemType &e)
{
	if (position < 1 || position > Length())
	{
		return RANGE_ERROR;
	}
	else
	{
		DblNode<ElemType> *tmpPtr = GetElemPtr(position);
		tmpPtr->back->next = tmpPtr->next;
		tmpPtr->next->back = tmpPtr->back;
		e = tmpPtr->data;
		delete tmpPtr;
		return SUCCESS;
	}
}

template<class ElemType>
SimpleDblLinkList<ElemType> & SimpleDblLinkList<ElemType>::operator=(const SimpleDblLinkList<ElemType> &copy)
{
	if (&copy != this)
	{
		int copyLength = copy.Length();
		ElemType e;
		Clear();
		for (int curPosition = 1; curPosition <= copyLength; curPosition++)
		{
			copy.GetElem(curPosition, e);
			Insert(Length() + 1, e);

		}

	}
	return *this;

}
