#include<iostream>
#include<deque>         //默认基本容器类
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
	ElemType Operate(ElemType &a, char op,ElemType &b);         //不能使用关键字 operator作为变量命名！

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
void Caculator<ElemType>::GetTwoOperand(ElemType &a, ElemType &b)  //此处出栈顺序不能搞反，否则减法除法会出错
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
		while (!optr.empty())              //stack类中不自带clear(）函数
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
				cin >> operand;           //此时从输入流中取的数将会不止1位数
				opnd.push(operand);
				preChar = '0';
				cin >> ch;
			}
			else if (!IsOperator(ch))
			{
				cout << "表达式有误！" << endl;
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
					cout << "表达式有误！" << endl;
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
		cout << "要继续进行运算吗？请输入Y/N" << endl;
		cin >> usercommand;
	} while (tolower(usercommand) == 'y');

}

