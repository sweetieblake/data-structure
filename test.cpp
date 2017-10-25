#include"TextEditor.h"
#include<process.h>

int main(void)
{
	TextEditor demo("demo.txt");
	demo.Run();

	system("PAUSE");
	return 0;
}