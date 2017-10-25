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

	//��������
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

	curLineNo = 1;  //��ʼ����ǰ�к�Ϊ1
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
			cout << "�滻��ǰ��������c;�滻������������a" << endl;

		}
		else
		{
			cout << "����c��a�ش�" << endl;
		}
		cin >> answer;
		answer = tolower(answer);
		initialResponse = false;
	} while (answer != 'a' && answer != 'c');

	cout << "����Ҫ���滻��ָ���ı���:" << endl;
	string strOld;
	cin >> strOld;
	cout << "�������ı���" << endl;
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
			cout << "����ӵ�һ�п�ʼ��������f������ӵ�ǰ�п�ʼ��������c" << endl;

		}
		else
		{
			cout << "��ʹ��f��c�ش�" << endl;
		}
		cin >> answer;
		answer = tolower(answer);
		initialResponce = false;
	} while (answer != 'f' && answer != 'c');

	if (answer == 'f') curLineNo = 1;

	string strLine;
	textBuffer.GetElem(curLineNo, strLine);
	string strSearch;
	cout << "����������Ҫ���ҵ��ַ���" << endl;
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
		cout << "����ʧ��" << endl;

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
	cout << "�������ļ���" << endl;
	cin >> infileName;
	inFile.open(infileName);
	if (inFile.fail())
	{
		cout << "���ļ�ʧ�ܣ�" << endl;
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
	cout << "�������ļ���" << endl;
	cin >> outfileName;
	outFile.open(outfileName);
	if (outFile.fail())
	{
		cout << "���ļ�ʧ��!" << endl;
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
	cout << "������" << textBuffer.Length() << "  " << "�ַ�����" << sumOfChar << endl;

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
			cout << "������������";
		}
		else
		{
			cout << "�ļ�����Ϊ��" << endl;

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
				cout << "���棺�ı������" << endl;
			}
			else
			{
				curLineNo = 1;
			}
			break;
		case 'c':
			if (textBuffer.Empty())
			{
				cout << "���棺�ı������" << endl;

			}
			else
			{
				ChangeLine();
			}
			break;
		case 'd':
			if (textBuffer.Delete(curLineNo, tempString) == RANGE_ERROR)
			{
				cout << "ɾ��ʧ��" << endl;

			}
			break;
		case 'e':
			if (textBuffer.Empty())
			{
				cout << "���棺�ı������" << endl;
			}
			else
			{
				curLineNo = textBuffer.Length();
			}
			break;
		case 'f':
			if (textBuffer.Empty())
			{
				cout << "���棺�ı������" << endl;
			}
			else
			{
				FindString();
			}
			break;
		case 'g':
			if (GotoLine() != true)
			{
				cout << "���в�����" << endl;
			}
			break;
		case 'h':
			cout << "�������b(egin) c(hange) d(elete) e(nd)" << endl
				<< "f(ind) g(o) h(elp) i(nsert) n(ext) p(rior)" << endl
				<< "q(uit) r(ead) s(tatistics) u(ndo) v(iew) w(rite)" << endl;
			break;
		case 'i':
			if (!InsertLine())
			{
				cout << "����������" << endl;
			
			}
			break;
		case 'n':
			if (!NextLine())
			{
				cout << "����һ��" << endl;
			}
			break;
		case 'p':
			if (!PreviousLine())
			{
				cout << "����һ��" << endl;
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
				cout << "�ı�����Ϊ��" << endl;
			}
			else
			{
				WriteFile();
			}
			break;
		default:
			cout << "��������Ч�����������鿴����������h" << endl;

		}

		
	}while (userCommand != 'q');

}