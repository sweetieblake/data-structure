#include"HuffmanCompress.h"

int main(void)
{
	HuffmanCompress demo;

	cout << "��ѡ������Ҫ�Ĳ�����" << endl;
	cout << "a.ѹ���ļ� b.��ѹ�ļ� c.�˳�" << endl;
	char userCommand;
	cin >> userCommand;

	while (tolower(userCommand) != 'c')
	{
		if (tolower(userCommand) == 'a')
		{
			demo.Compress();
		}
		else if (tolower(userCommand) == 'b')
		{
			demo.DeCompress();
		}
		else
		{
			cout << "������abc" << endl;
		}
		cin >> userCommand;
	}
	return 0;
}