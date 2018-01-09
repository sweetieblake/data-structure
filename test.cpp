#include"CourseManager.h"

int main(void)
{
	char ch[318];
	cout << "请输入课程信息文件：" << endl;
	cin >> ch;

	CourseManager demo;

	demo.courseManage(ch);
	demo.show();
	system("PAUSE");

	return 0;

}

