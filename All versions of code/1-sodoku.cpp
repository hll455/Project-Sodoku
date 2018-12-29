// sudoku.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cstdlib>
#include <algorithm>
#include <ctime>
//#include <fstream>
#include <string.h>
using namespace std;

//int sum = 0;
int findans = 0;//是否找到最终解
//ofstream create_outputfile("sudoku.txt");
char print[300000000];//存入写入文件的数独，一起写入
int p=0;//类似于指针
char save[12][25];
int visit[3][10][10] = { 0 };//记录是否填写
//int judge[3][10][10] = { 0 };
//char aa[300000000];
class sudoku
{
public:
	char cs[2];
	char st[50];
	void createsodoku(int n);
	void solvesodoku(int i, int j);
	int  choosecors(char a[], char b[]);
	void preprocess();
	/*void setsodoku(char a[], char b[])
	{
		strcpy(this->cs, a);
		strcpy(this->st, b);
	}*/
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
	//char shift[] = "036147258" ;
	//int shift[9] = { 0,3,6,1,4,7,2,5,8 };
	char num[10] = "612345789";
	

	char change[72][10] = {
		{ "036147258" },{ "036174258" },{ "036417258" },{ "036471258" },{ "036741258" },{ "036714258" },
		{ "036147285" },{ "036174285" },{ "036417285" },{ "036471285" },{ "036741285" },{ "036714285" },
		{ "036147825" },{ "036174825" },{ "036417825" },{ "036471825" },{ "036741825" },{ "036714825" },
		{ "036147852" },{ "036174852" },{ "036417852" },{ "036471852" },{ "036741852" },{ "036714852" },
		{ "036147528" },{ "036174528" },{ "036417528" },{ "036471528" },{ "036741528" },{ "036714528" },
		{ "036147582" },{ "036174582" },{ "036417582" },{ "036471582" },{ "036741582" },{ "036714582" },

		{ "063147258" },{ "063174258" },{ "063417258" },{ "063471258" },{ "063741258" },{ "063714258" },
		{ "063147285" },{ "063174285" },{ "063417285" },{ "063471285" },{ "063741285" },{ "063714285" },
		{ "063147825" },{ "063174825" },{ "063417825" },{ "063471825" },{ "063741825" },{ "063714825" },
		{ "063147852" },{ "063174852" },{ "063417852" },{ "063471852" },{ "063741852" },{ "063714852" },
		{ "063147528" },{ "063174528" },{ "063417528" },{ "063471528" },{ "063741528" },{ "063714528" },
		{ "063147582" },{ "063174582" },{ "063417582" },{ "063471582" },{ "063741582" },{ "063714582" }

	};


	for (int j = 0; j < 40320 && n; j++) {
			if (j)
		 next_permutation(num + 1, num + 9);
		for (int i = 0; i < 72 && n; i++) {	

			for (int m = 0; m < 9; m++)
			{
				for (int h = 0; h < 9; h++)
				{
					print[p++] = num[(h + (change[i][m]-'0')) % 9];
					if (h != 8)
				    print[p++] = ' ';
				}
				    print[p++] = '\n';

			}
					n--;
					if (n!=0)
					print[p++] = '\n';
					//sum++;
		}
	}
	print[p] = '\0';

	//create_outputfile << print;
	
	fputs(print, create_outputfile);
	fclose(create_outputfile);
	//printf("%d", sum);
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
void sudoku::preprocess()
{
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

		//printf("\n%d\n", sum);
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

				preprocess();


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
				//memset(visit, 0, sizeof(visit));
			}

			
		}

		fclose(fp2);
		
	/*	printf("%s", print);*/
		
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
	/*clock_t starttime, endtime;
	starttime = clock();*/
	if (argc!=3)
	printf("please input 3 arguments\n");
	else {
		s1.choosecors(argv[1], argv[2]);
		
	}
	/*endtime = clock();
	printf("程序运行的时间为%f\n", (double)(endtime - starttime)/CLOCKS_PER_SEC);*/
	system("pause");
	return 0;

}
