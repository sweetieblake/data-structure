#include"HuffmanCompress.h"

int main(void)
{
	HuffmanCompress demo;

	cout << "请选择你想要的操作：" << endl;
	cout << "a.压缩文件 b.解压文件 c.退出" << endl;
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
			cout << "请输入abc" << endl;
		}
		cin >> userCommand;
	}
	return 0;
}