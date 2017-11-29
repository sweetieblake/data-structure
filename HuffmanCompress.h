#include"HuffmanTree.h"
#include<stdio.h>

struct  BufferType
{
	char ch;
	unsigned int bits;

};

class HuffmanCompress
{
protected:
	HuffmanTree<char, unsigned long>* pHuffmanTree;
	FILE *infile, *outfile;
	BufferType buf;

	void Write(unsigned int bit);
	void WriteComp();

public:
	HuffmanCompress() {};
	~HuffmanCompress() {};
	void Compress();
	void DeCompress();
};

void HuffmanCompress::Write(unsigned int bit)
{
	buf.bits++;
	buf.ch = (buf.ch << 1) | bit;
	if (buf.bits == 8)
	{
		fputc(buf.ch, outfile);
		buf.bits = 0;
		buf.ch = 0;
	}

}

void HuffmanCompress::WriteComp()
{
	unsigned int len = buf.bits;
	if (len > 0)
	{
		for (unsigned int i = 1; i <= 8 - len; i++)             //i �� len��������ƥ��
		{
			Write(0);
		}
	}
}

void HuffmanCompress::Compress()
{
	char infName[256], outfName[256];
	cout << "������Դ�ļ�����";
	cin >> infName;

	if ((infile = fopen(infName, "rb")) == NULL)
	{
		cout << "��Դ�ļ�ʧ�ܣ�" << endl;
		exit(1);
	}

	fgetc(infile);
	if (feof(infile))
	{
		cout << "��Դ�ļ���" << endl;
		exit(1);
	}

	cout << "������Ŀ���ļ���" << endl;
	cin >> outfName;

	if ((outfile = fopen(outfName, "wb")) == NULL)
	{
		cout << "��Ŀ���ļ�ʧ�ܣ�" << endl;
		exit(1);
	}

	cout << "���ڴ������Ժ�......" << endl;

	const int n = 256;
	char ch[n];
	unsigned long w[n];
	unsigned long i, size = 0;
	char getc;

	for (i = 0; i < n; i++)
	{
		ch[i] = (char)i;
		w[i] = 0;
	}

	rewind(infile);
	getc = fgetc(infile);
	while (!feof(infile))
	{
		size++;
		w[(int)getc]++;
		getc = fgetc(infile);
	}

	if (pHuffmanTree != NULL) delete []pHuffmanTree;
	pHuffmanTree = new HuffmanTree<char, unsigned long>(ch, w, n);

	rewind(outfile);
	fwrite(&size, sizeof(unsigned long), 1, outfile);
	for (i = 0; i < n; i++)
	{
		fwrite(&w[i], sizeof(unsigned long), 1, outfile);
	}

	buf.bits = 0;            //��ʼ���ַ�������
	buf.ch = 0;
	rewind(infile);
	getc = fgetc(infile);
	while (!feof(infile))
	{
		string strTemp;
		strTemp = pHuffmanTree->EnCode(getc);
		for (i = 0; i < strTemp.length(); i++)
		{
			if (strTemp[i] == '0') Write(0);
			else Write(1);
		}
		getc = fgetc(infile);
	}
	WriteComp();                  //ǿ��д��һ���ַ���β

	fclose(infile);
	fclose(outfile);

	cout << "�������" << endl;
}

void HuffmanCompress::DeCompress()
{
	char infName[256], outfName[256];
	cout << "������ѹ���ļ�����" << endl;
	cin >> infName;

	if ((infile = fopen(infName, "rb")) == NULL)
	{
		cout << "�����ļ���ʧ�ܣ�" << endl;
		exit(1);
	}

	fgetc(infile);
	if (feof(infile))
	{
		cout << "�����ļ�Ϊ�գ�" << endl;
		exit(1);
	}

	cout << "������Ŀ���ļ�����" << endl;
	cin >> outfName;

	if ((outfile = fopen(outfName, "wb")) == NULL)
	{
		cout << "��Ŀ���ļ�ʧ�ܣ�" << endl;
		exit(1);
	}

	cout << "���ڴ������Ժ�......" << endl;

	const int n = 256;
	char ch[n];
	unsigned long w[n];
	unsigned long i, size = 0;
	char getc;

	rewind(infile);
	fread(&size, sizeof(unsigned long), 1, infile);

	for (i = 0; i < n; i++)
	{
		ch[i] = (char)i;
		fread(&w[i], sizeof(unsigned long), 1, infile);
	}

	if (pHuffmanTree != NULL) delete[]pHuffmanTree;
	pHuffmanTree = new HuffmanTree<char, unsigned long>(ch, w, n);

	unsigned long len = 0;
	getc = fgetc(infile);

	while (!feof(infile))
	{
		string strTemp="";
		unsigned char c = (unsigned char)getc;
		for (i = 0; i < 8; i++)
		{
			if (c < 128) strTemp += '0';
			else strTemp += '1';
			c = c << 1;
		}

		list<char> charlist = pHuffmanTree->DeCode(strTemp);
		int n = charlist.size();
		for (i = 1; i <= n; i++)
		{
			len++;
			fputc(charlist.front(), outfile);

			charlist.pop_front();
			if (len == size) break;
		}

		if (len == size) break;
		getc = fgetc(infile);


	}

	fclose(infile);
	fclose(outfile);

	cout << "������ϣ�" << endl;
}
