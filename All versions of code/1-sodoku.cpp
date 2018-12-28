// sodoku.cpp : Defines the entry point for the console application.
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
class sodoku
{
public:
	char cs[2];
	char st[50];
	void createsodoku(int n);
	void solvesodoku(int i, int j);
	int choosecors(char a[], char b[]);
	int testtest1(char a[], char b[]);
	void setsodoku(char a[], char b[])
	{
		strcpy(this->cs, a);
		strcpy(this->st, b);
	}
};
int sodoku::testtest1(char a[],char b[])
{
	choosecors(a, b);
	char aaa[300] = { "6 1 2 3 4 5 7 9 8\n"
		"3 4 5 9 7 8 6 1 2\n"
		"9 7 8 6 1 2 3 4 5\n"
		"1 8 3 4 2 9 5 7 6\n"
		"4 5 9 7 8 6 1 2 3\n"
		"7 2 6 1 5 3 4 8 9\n"
		"2 3 4 5 9 7 8 6 1\n"
		"5 9 7 8 6 1 2 3 4\n"
		"8 6 1 2 3 4 9 5 7\n\n"
	};
	printf("%s", aaa);
	if (strcmp(aaa, print) == 0)
		return 1;
	
}
void sodoku::createsodoku(int n)

{
	FILE* create_outputfile;
	create_outputfile = fopen("sodoku.txt", "w");
	if (!create_outputfile)
	{
		printf("CANNOT open the sodoku.txt!\n");
		
		exit(1);
	}
	int shift[9] = { 0,3,6,1,4,7,2,5,8 };
	char num[10] = "612345789";
	for(int i = 0; i < 2 && n; i++) 
	{
		
		if (i)
			next_permutation(shift + 1, shift + 3);
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
	}

	fputs(print, create_outputfile);
	fclose(create_outputfile);
}


void sodoku::solvesodoku(int i, int j)
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
		if (i == 8 && j==16) {
			findans = 1;
			
		}

	}	

	if (save[i][j] == '0') 
	{//解
		bool flag = 0;
		for (int k = 1; k <= 9; k++)
		{
	
			
			if (visit[0][i / 3 * 3 + j / 6][k] == 0 && visit[1][i][k] == 0 && visit[2][j / 2][k] == 0) 
			{
				save[i][j] = k+'0';//整型变成char 不知道会不会有问题

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

int sodoku::choosecors(char a[], char b[])
{

	if (strcmp(a, "-c") == 0)
	{
		/*int n = atoi(argv[2]);*/
		int n = atoi(b);
		if (n<=1000000 && n>0)
		createsodoku(n);
		else {
			printf("-c后面的参数必须是1到1000000的整数");
			return 1;
		}

		printf("\n%d\n", sum);
		return 6;

	}
	else if (strcmp(a, "-s") == 0)
	{

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
				
				/*for (int i=0; i<9 ;i++)
				printf("%s", save[i]);*/
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

				/*if (firstsodoku == 0) 
				{
					char tempp[] = { "\n" };
					strcat(print, tempp);
				}
				
				if (firstsodoku == 1)
					firstsodoku = 0;*/

				//char aaa[300] = { "6 1 2 3 4 5 7 9 8\n"
				//	"3 4 5 9 7 8 6 1 2\n"
				//	"9 7 8 6 1 2 3 4 5\n"
				//	"1 8 3 4 2 9 5 7 6\n"
				//	"4 5 9 7 8 6 1 2 3\n"
				//	"7 2 6 1 5 3 4 8 9\n"
				//	"2 3 4 5 9 7 8 6 1\n"
				//	"5 9 7 8 6 1 2 3 4\n"
				//	"8 6 1 2 3 4 9 5 7\n\n"
				//};

				//strcat(aa, aaa);
				//printf("%s", aa);
				//
				save[9][0] = '\n';
				save[9][1] = '\0';
				for (int i = 0; i<10; i++)
					strcat(print, save[i]);
				printf("%s", print);

			/*if (strcmp(aaa, print) == 0)
			   printf("heliangli");*/

			/*	for (int i = 0; i<9; i++)
				printf("%s", save[i]);*/
				
				/*printf("\n");*/
				memset(save, 0, sizeof(save));
				memset(visit, 0, sizeof(visit));
			}

			
		}

		/*printf("%s", print);*/
		FILE* solve_outputfile;
		solve_outputfile = fopen("sodoku.txt", "w");
		if (!solve_outputfile)
		{
			printf("CANNOT open the sodoku.txt!\n");
			exit(1);
		}
		fputs(print, solve_outputfile);
		fclose(solve_outputfile);
		return 6;
	}
	else {
		return 3;
		printf("第二个参数必须是-s或者-c");
	}



	

}
int main(int argc,char*argv[])
{
	sodoku s1;
	//s1.setsodoku(argv[1], argv[2]);
	s1.choosecors(argv[1], argv[2]);

//
//	if (strcmp(s1.cs, "-c") == 0) 
//	{
//		/*int n = atoi(argv[2]);*/
//		s1.createsodoku(atoi(s1.st));		
//		printf("\n%d\n", sum);
//		
//	}
//	else if (strcmp(s1.cs, "-s") == 0)
//	{
//		
//		FILE *fp2 = fopen(s1.st, "r");
//		memset(save, 0, sizeof(save));
//			
//		char temp[25];
//		
//		int num = 0;
//		//int i = 0;
//		while (!feof(fp2)) {
//		fgets(temp, 22, fp2);
//		if (strcmp(temp, "\n") == 0)
//			continue;
//		strcat(save[num], temp);
//		num++;
//		if (num == 9) {
//			num = 0;
//			
//			/*for (int i=0; i<9 ;i++)
//			printf("%s", save[i]);*/
//			//save数组已经装下一个数独，开始求解
//			
//			/*printf("\n");*/
//			memset(visit, 0, sizeof(visit));
//			/*初始化visit
//			行列宫都从[109]*/
//			//注意 每一行一个数字过后紧跟着空格 换算至没有空格时候的visit数组
//			findans = 0;
//			for (int i = 0; i < 9; i++)
//				for(int j = 0; j < 17; j++)
//			{
//					if (save[i][j] != '0'&& save[i][j]!=' ') 
//					{
//						visit[0][i / 3 * 3 + j / 6][save[i][j]-'0'] = 1;
//						visit[1][i][save[i][j] - '0'] = 1;
//						visit[2][j / 2][save[i][j] - '0'] = 1;
//					}
//			}
//
//			s1.solvesodoku(0, 0);
//
//			save[9][0]= '\n';
//			save[9][1] = '\0';
//			for (int i = 0; i<10; i++)
//			strcat(print,save[i]);
//
//			/*for (int i = 0; i<9; i++)
//				printf("%s", save[i]);
//*/
//			/*printf("\n");*/
//			memset(save, 0, sizeof(save));
//			memset(visit, 0, sizeof(visit));
//		}
//		
//
//		}
//
//		FILE* solve_outputfile;
//		solve_outputfile = fopen("sudoku.txt", "w");
//		fputs(print, solve_outputfile);
//		fclose(solve_outputfile);
//		
//	}

	//printf("\n");
	/*printf("%f\n", time);*/
	system("pause");
	return 0;

}
