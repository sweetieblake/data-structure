#include"SimpleDblLinkList.h"
#include<string>
#include<fstream>
#include<process.h>

class TextEditor
{
private:
	SimpleDblLinkList<string> textBuffer;
	int curLineNo;
	SimpleDblLinkList<string> textUndoBuffer;
	int curUndoLineNo;
	ifstream inFile;
	ofstream outFile;

	//辅助函数
	bool NextLine();
	bool PreviousLine();
	bool GotoLine();
	bool InsertLine();
	void ChangeLine();
	void ReadFile();
	void WriteFile();
	void FindString();
	void View();
	void Statisticts();

public:
	TextEditor(char infileName[]);
	~TextEditor() {};
	void Run();

};
TextEditor::TextEditor(char infileName[])
{
	inFile.open(infileName, ios::in);
	if (inFile.fail())
	{
		cout << "can't open the file " << endl;
		system("PAUSE");
		exit(1);
	}
	string temp;
	char s[318];
	inFile.getline(s, 318);
	while (!inFile.eof())
	{
		temp = s;
		textBuffer.Insert(textBuffer.Length() + 1, temp);
		inFile.getline(s, 318);
	}
	inFile.close();

	curLineNo = 1;  //初始化当前行号为1
}

bool TextEditor::NextLine()
{
	if (curLineNo + 1 <= textBuffer.Length())
	{
		curLineNo++;
		return true;
	}
	else
	{
		return false;
	}
}

bool TextEditor::PreviousLine()
{
	if (curLineNo - 1 >= 1)
	{
		curLineNo--;
		return true;
	}
	else
	{
		return false;
	}
}

bool TextEditor::GotoLine()
{
	int num;
	cout << "Please input the linenumber you want to go to:" << endl;
	cin >> num;
	if (num >= 1 || num <= textBuffer.Length())
	{
		curLineNo = num;
		return true;
	}
	else
	{
		return false;
	}
}

bool TextEditor::InsertLine()
{
	int num;
	cout << "Please input the linenumber you want to insert" << endl;
	cin >> num;
	string strNew;
	cout << "Please input the string you want to insert" << endl;
	cin.clear();
	cin.ignore(100, '\n');
	getline(cin, strNew);
	if (textBuffer.Insert(num, strNew) == SUCCESS)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void TextEditor::ChangeLine()
{
	char answer;
	bool initialResponse = true;

	do
	{
		if (initialResponse == true)
		{
			cout << "替换当前行请输入c;替换所有行请输入a" << endl;

		}
		else
		{
			cout << "请用c或a回答" << endl;
		}
		cin >> answer;
		answer = tolower(answer);
		initialResponse = false;
	} while (answer != 'a' && answer != 'c');

	cout << "输入要被替换的指定文本串:" << endl;
	string strOld;
	cin >> strOld;
	cout << "输入新文本串" << endl;
	string strNew;
	cin >> strNew;

	for (int row = 1; row <= textBuffer.Length(); row++)
	{
		if (answer == 'c' && row != curLineNo)
		{
			continue;
		}
		string strRow;
		textBuffer.GetElem(row, strRow);
		int index = strRow.find(strOld);
		if (index != -1)
		{
			strRow = strRow.replace(index, strOld.length(), strNew);
			textBuffer.SetElem(row, strRow);
		}

	}
}

void TextEditor::FindString()
{
	char answer;
	bool initialResponce = true;

	do
	{
		if (initialResponce = true)
		{
			cout << "如果从第一行开始查找输入f；如果从当前行开始查找输入c" << endl;

		}
		else
		{
			cout << "请使用f或c回答" << endl;
		}
		cin >> answer;
		answer = tolower(answer);
		initialResponce = false;
	} while (answer != 'f' && answer != 'c');

	if (answer == 'f') curLineNo = 1;

	string strLine;
	textBuffer.GetElem(curLineNo, strLine);
	string strSearch;
	cout << "请输入你想要查找的字符串" << endl;
	cin >> strSearch;
	int index;
	while ((index = strLine.find(strSearch)) == -1)
	{
		if (curLineNo < textBuffer.Length())
		{
			curLineNo++;
			textBuffer.GetElem(curLineNo, strLine);
		}
		else
		{
			break;
		}
	}
	if (index == -1)
	{
		cout << "查找失败" << endl;

	}
	else
	{
		cout << strLine << endl;
		for (int i = 0; i < index; i++)
		{
			cout << " ";
		
		}
		for (int j = 0; j < (int)strlen(strSearch.c_str()); j++)
		{
			cout << "^";
		}
		cout << endl;

	}

}

void TextEditor::View()
{
	string GetLine;
	for (int i = 1; i <= textBuffer.Length(); i++)
	{
		textBuffer.GetElem(i, GetLine);
		cout << GetLine <<endl;
	}

}

void TextEditor::ReadFile()
{
	char s[318],infileName[20];
	cout << "请输入文件名" << endl;
	cin >> infileName;
	inFile.open(infileName);
	if (inFile.fail())
	{
		cout << "打开文件失败！" << endl;
		exit(1);
	}
	inFile.getline(s, 318);
	string temp;
	textBuffer.Clear();
	while (!inFile.eof())
	{
		temp = s;
		textBuffer.Insert(textBuffer.Length() + 1, temp);
		inFile.getline(s, 318);

	}
	inFile.close();
}

void TextEditor::WriteFile()
{
	char outfileName[20];
	cout << "请输入文件名" << endl;
	cin >> outfileName;
	outFile.open(outfileName);
	if (outFile.fail())
	{
		cout << "打开文件失败!" << endl;
		exit(1);
	}
	string strLine;
	for (int i = 1; i <= textBuffer.Length(); i++)
	{
		textBuffer.GetElem(i, strLine);
		outFile << strLine <<endl;
	}
	outFile.close();
}

void TextEditor::Statisticts()
{
	int sumOfChar = 0;
	string tempStr;
	for(int i = 1; i <= textBuffer.Length(); i++)
	{
		textBuffer.GetElem(i, tempStr);
		sumOfChar += tempStr.length();
	}
	cout << "行数：" << textBuffer.Length() << "  " << "字符数：" << sumOfChar << endl;

}

void TextEditor::Run()
{
	char userCommand;

	do
	{
		string tempString;
		string curLine;

		if (curLineNo != 0)
		{
			textBuffer.GetElem(curLineNo, curLine);
			cout << curLineNo << ":" << curLine << endl;
			cout << "请输入你的命令：";
		}
		else
		{
			cout << "文件缓存为空" << endl;

		}

		cin >> userCommand;
		userCommand = tolower(userCommand);

		if (userCommand != 'u' && userCommand != 'h' && userCommand != '?' && userCommand != 'v')
		{
			textUndoBuffer = textBuffer;
			curUndoLineNo = curLineNo;
		}

		switch (userCommand)
		{
		case 'b':
			if (textBuffer.Empty())
			{
				cout << "警告：文本缓存空" << endl;
			}
			else
			{
				curLineNo = 1;
			}
			break;
		case 'c':
			if (textBuffer.Empty())
			{
				cout << "警告：文本缓存空" << endl;

			}
			else
			{
				ChangeLine();
			}
			break;
		case 'd':
			if (textBuffer.Delete(curLineNo, tempString) == RANGE_ERROR)
			{
				cout << "删除失败" << endl;

			}
			break;
		case 'e':
			if (textBuffer.Empty())
			{
				cout << "警告：文本缓存空" << endl;
			}
			else
			{
				curLineNo = textBuffer.Length();
			}
			break;
		case 'f':
			if (textBuffer.Empty())
			{
				cout << "警告：文本缓存空" << endl;
			}
			else
			{
				FindString();
			}
			break;
		case 'g':
			if (GotoLine() != true)
			{
				cout << "那行不存在" << endl;
			}
			break;
		case 'h':
			cout << "可用命令：b(egin) c(hange) d(elete) e(nd)" << endl
				<< "f(ind) g(o) h(elp) i(nsert) n(ext) p(rior)" << endl
				<< "q(uit) r(ead) s(tatistics) u(ndo) v(iew) w(rite)" << endl;
			break;
		case 'i':
			if (!InsertLine())
			{
				cout << "插入行有误" << endl;
			
			}
			break;
		case 'n':
			if (!NextLine())
			{
				cout << "无下一行" << endl;
			}
			break;
		case 'p':
			if (!PreviousLine())
			{
				cout << "无上一行" << endl;
			}
			break;
		case 'q':
			break;
		case 'r':
			ReadFile();
			break;
		case 's':
			Statisticts();
			break;
		case 'u':
			textBuffer = textUndoBuffer;
			swap(curUndoLineNo, curLineNo);
			break;
		case 'v':
			View();
			break;
		case 'w':
			if (textBuffer.Empty())
			{
				cout << "文本缓存为空" << endl;
			}
			else
			{
				WriteFile();
			}
			break;
		default:
			cout << "请输入有效命令，如需帮助查看命令请输入h" << endl;

		}

		
	}while (userCommand != 'q');
	
	cout << "你想要保存编辑结果吗？请输入Y/N" << endl;
	cin >> userCommand;
	if (tolower(userCommand) == 'y')
	{
		WriteFile();
	}

}
