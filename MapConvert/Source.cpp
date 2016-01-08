#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>

#include<windows.h>

#include<conio.h>
#include <string>

using namespace std;
void main()
{

	FILE * pFile;
	FILE * sFile;

	int m = 0;
	int i = 0, j = 0;

	pFile = fopen("MAP1.ptl", "r");
	sFile = fopen("MAP1.txt", "w");
	long a[200][1000];

	char ch;
	string s = "";
	if (pFile == NULL)
	{
		printf("File ko ton tai");
		return;
	}
	bool kt = true;
	while (EOF != (ch = getc(pFile)))

	{

		if (ch != ' ' && ch != '\n')
		{
			s = s + ch;
		}

		if (' ' == ch && s != "")
		{
			a[i][j] = atoi(s.c_str());
			j++;
			s = "";
			kt = true;
		}
		if ('\n' == ch)
		{
			if (s != ""){
				a[i][j] = atoi(s.c_str());
				j++;

			}
			m = j;
			j = 0;
			i++;
			s = "";
			kt = true;
		}

	}
	int n = i;

	for (int k = 0; k < n; k++)
	{
		for (int l = 0; l < m; l++)
		{
			if (a[k][l] == 0)
				continue;
			else
			{
				fprintf(sFile,"%d ", a[k][l]);
				fprintf(sFile,"%d ", l + 1);
				fprintf(sFile ,"%d ", k + 1);
				fprintf(sFile,"\n");
			}
			
		}
	}

	fclose(sFile);
	fclose(pFile);

	_getch();
}




