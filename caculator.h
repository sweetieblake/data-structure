#include<iostream>
#include<deque>         //Ĭ�ϻ���������
#include<stack>
#include<ctype.h>
#include<stdlib.h>

using namespace std;

template<class ElemType>
class Caculator
{
private:
	stack<ElemType> opnd;
	stack<char> optr;

	bool IsOperator(char op);
	int OperPrior(char op);
	void GetTwoOperand(ElemType &a, ElemType &b);
	ElemType Operate(ElemType &a, char op,ElemType &b);         //����ʹ�ùؼ��� operator��Ϊ����������

public:

	Caculator() {};
	~Caculator() {};
	void Run();
};

template<class ElemType>
bool Caculator<ElemType>::IsOperator(char op)
{
	if (op == '=' || op == '(' || op == ')' || op == '+' || op == '-' || op == '*' || op == '/')
	{
		return true;
	}
	else
	{
		return false;
	}
}

template<class ElemType>
int Caculator<ElemType>::OperPrior(char op)
{
	switch (op)
	{
	case '=':
		return 1;
	case '(':
		return 2;
	case ')':
		return 2;
	case '+':
		return 3;
	case '-':
		return 3;
	case '*':
		return 4;
	case '/':
		return 4;
	}
}

template<class ElemType>
void Caculator<ElemType>::GetTwoOperand(ElemType &a, ElemType &b)  //�˴���ջ˳���ܸ㷴������������������
{
	b = opnd.top();                
	opnd.pop();
	a = opnd.top();
	opnd.pop();
}

template<class ElemType>
ElemType Caculator<ElemType>::Operate(ElemType &a, char op, ElemType &b)
{
	switch (op)
	{
	case '+':
		return a + b;
	case '-':
		return a - b;
	case '*':
		return a * b;
	case '/':
		return a / b;
	}
}

template<class ElemType>
void Caculator<ElemType>::Run()
{
	char usercommand = 'y';
	do
	{
		while (!optr.empty())              //stack���в��Դ�clear(������
		{
			optr.pop();
		}
		while (!opnd.empty())
		{
			opnd.pop();
		}

		optr.push('=');

		char ch;
		char optrTop;
		char preChar;
		ElemType operand;
		char op;

		cin >> ch;

		optrTop = optr.top();
		preChar = '=';

		while (optrTop != '=' || ch != '=')
		{
			if (isdigit(ch))
			{
				cin.putback(ch);
				cin >> operand;           //��ʱ����������ȡ�������᲻ֹ1λ��
				opnd.push(operand);
				preChar = '0';
				cin >> ch;
			}
			else if (!IsOperator(ch))
			{
				cout << "���ʽ����" << endl;
				system("PAUSE");
				exit(1);
			}
			else
			{
				if ((preChar == '=' || preChar == '(') && (ch == '+' || ch == '-'))
				{
					opnd.push(0);
					preChar = '0';
				}
				if (optrTop == ')' && ch == '(' || optrTop == '(' && ch == '=' || optrTop == '=' && ch == ')')
				{
					cout << "���ʽ����" << endl;
					system("PAUSE");
					exit(1);
				}
				else if (optrTop == '(' && ch == ')')
				{
					optr.pop();
					cin >> ch;
				}
				else if (ch == '(' || OperPrior(ch) > OperPrior(optrTop))
				{
					optr.push(ch);
					preChar = ch;
					cin >> ch;
				}
				else
				{
					ElemType a, b;
					GetTwoOperand(a, b);
					optr.pop();
					opnd.push(Operate(a, optrTop, b));
				}
			}
			optrTop = optr.top();
		}
		cout << opnd.top() << endl;
		cout << "Ҫ��������������������Y/N" << endl;
		cin >> usercommand;
	} while (tolower(usercommand) == 'y');

}

