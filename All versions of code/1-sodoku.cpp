// sudoku.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cstdlib>
//#include <iostream>
#include <algorithm>
//#include <fstream> 
#include <ctime>
#include <string.h>


using namespace std;
int sum = 0;
int findans = 0;//是否找到最终解

char print[300000000];//存入写入文件的数独，一起写入
int p=0;//类似于指针
char save[12][25];
int visit[3][10][10] = { 0 };//记录是否填写
int judge[3][10][10] = { 0 };
char aa[300000000];
class sudoku
{
public:
	char cs[2];
	char st[50];
	void createsodoku(int n);
	void solvesodoku(int i, int j);
	int choosecors(char a[], char b[]);
	/*int testtest1(char a[], char b[]);
	int testtest2(char a[], char b[]);*/
	void setsodoku(char a[], char b[])
	{
		strcpy(this->cs, a);
		strcpy(this->st, b);
	}
};


void sudoku::createsodoku(int n)

{
	FILE* create_outputfile;
	create_outputfile = fopen("sudoku.txt", "w");
	if (!create_outputfile)
	{
		printf("CANNOT open the sudoku.txt!\n");
		
		exit(1);
	}
	int shift[9] = { 0,3,6,1,4,7,2,5,8 };
	char num[10] = "612345789";
	/*for(int i = 0; i < 2 && n; i++) 
	{
		
		if (i)
			next_permutation(shift + 1, shift + 3);*/
		for (int j = 0; j < 6 && n; j++) 
		{
			if (j)
				next_permutation(shift + 3, shift + 6);
			for (int k = 0; k < 6 && n; k++)
			{
				if (k)
					next_permutation(shift + 6, shift + 9);
				for (int l = 0; l < 40320 && n; l++)
				{
					
					if (l)
						next_permutation(num + 1, num + 9);
					for (int m = 0; m < 9; m++)
					{
						for (int h = 0; h < 9; h++)
						{
							print[p++] = num[(h + shift[m]) % 9];
							if (h != 8)
								print[p++] = ' ';
							//fputc(num[(h + shift[m]) % 9], create_outputfile);
							
							/*if (h!=8)
							fputc(' ', create_outputfile);*/
						}
						print[p++] = '\n';
						//fputc('\n', create_outputfile);
						
					}
					n--;
					if (n!=0)
					print[p++] = '\n';
					//fputc('\n', create_outputfile);
				
					sum++;

				}

			}
		}
	//}

	fputs(print, create_outputfile);
	fclose(create_outputfile);
}


void sudoku::solvesodoku(int i, int j)
{
	if (findans == 1)
		return;
	while (save[i][j] != '0') 
	{
		j++;
		if (j == 17) {
			i++;
			j = 0;
		}
		if (i == 9) {
			findans = 1;	
			return;
		}

	}	

	if (save[i][j] == '0') 
	{//解
		bool flag = 0;
		for (int k = 1; k <= 9; k++)
		{
				
			if (visit[0][i / 3 * 3 + j / 6][k] == 0 && visit[1][i][k] == 0 && visit[2][j / 2][k] == 0) 
			{
				save[i][j] = k+'0';

				visit[0][i / 3 * 3 + j / 6][k] = 1;
				visit[1][i][k] = 1;
				visit[2][j / 2][k] = 1;

				flag = 1;

				solvesodoku(i, j);
			}
			if (flag)
			{
				flag = 0;
				if (findans)
					return;
				else
				{
					save[i][j] = '0';
					
					visit[0][i / 3 * 3 + j / 6][k] = 0;
					visit[1][i][k] = 0;
					visit[2][j / 2][k] = 0;
				}
			}

				
		}
	

	}
	//else solvesodoku(i, j);

}

int sudoku::choosecors(char a[], char b[])
{

	if (strcmp(a, "-c") == 0)
	{
		/*int n = atoi(argv[2]);*/
		int n = atoi(b);
		if (n<=1000000 && n>0)
		createsodoku(n);
		else {
			printf("-c后面的参数必须是1到1000000的整数\n");
			return 1;
		}

		printf("\n%d\n", sum);
		return 6;

	}
	else if (strcmp(a, "-s") == 0)
	{
		memset(print, 0, sizeof(print));
		FILE *fp2 = fopen(b, "r");
		memset(save, 0, sizeof(save));
		if (!fp2)
		{
			printf("CANNOT open the file that you input!\n");
			return 2;
			exit(1);

		}
		char temp[25];

		int num = 0;
		//int i = 0;
		int firstsodoku = 1;
		while (!feof(fp2)) {
			fgets(temp, 22, fp2);
			if (strcmp(temp, "\n") == 0)
				continue;
			strcat(save[num], temp);
			num++;
			if (num == 9) {
				num = 0;

				//save数组已经装下一个数独，开始求解

				/*printf("\n");*/
				memset(visit, 0, sizeof(visit));
				/*初始化visit
				行列宫都从[109]*/
				//注意 每一行一个数字过后紧跟着空格 换算至没有空格时候的visit数组
				findans = 0;
				for (int i = 0; i < 9; i++)
					for (int j = 0; j < 17; j++)
					{
						if (save[i][j] != '0'&& save[i][j] != ' ')
						{
							visit[0][i / 3 * 3 + j / 6][save[i][j] - '0'] = 1;
							visit[1][i][save[i][j] - '0'] = 1;
							visit[2][j / 2][save[i][j] - '0'] = 1;
						}
					}

				solvesodoku(0, 0);

				if (firstsodoku == 0) {
					char temm[] = "\n";
					strcat(print, temm);
				}

				if (firstsodoku == 1) {
					firstsodoku = 0;
				}
	

				for (int i = 0; i<9; i++)
					strcat(print, save[i]);
			
				memset(save, 0, sizeof(save));
				memset(visit, 0, sizeof(visit));
			}

			
		}

		fclose(fp2);
		
		printf("%s", print);
		
		FILE* solve_outputfile;
		solve_outputfile = fopen("sudoku.txt", "w");
		if (!solve_outputfile)
		{
			printf("CANNOT open the sudoku.txt!\n");
			exit(1);
		}
		fputs(print, solve_outputfile);
		fclose(solve_outputfile);
		//printf("6");
		return 6;
		
		
	}
	else {
		
		printf("第二个参数必须是-s或者-c\n");
		return 3;
	}
	memset(print, 0, strlen(print));
}
int main(int argc,char*argv[])
{
	sudoku s1;

	if (argc!=3)
	printf("please input 3 arguments\n");
	else 
	s1.choosecors(argv[1], argv[2]);
		
	
	system("pause");
	return 0;

}
