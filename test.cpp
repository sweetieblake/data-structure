#include"CourseManager.h"

int main(void)
{
	char ch[318];
	cout << "������γ���Ϣ�ļ���" << endl;
	cin >> ch;

	CourseManager demo;

	demo.courseManage(ch);
	demo.show();
	system("PAUSE");

	return 0;

}

