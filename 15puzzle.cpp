#include <iostream>
#include <stdlib.h> 
#include <time.h>
#include <conio.h>
#include <windows.h>

using namespace std;

void set(int*);//퍼즐 만드는 함수
bool inversion(int*);//퍼즐 해결가능여부 함수
void print(int*);//퍼즐 출력함수
void swap(int*, int*);//스왑
void move(int, int*, int*);//이동
bool cmp(int*, int*);//결과물과 비교함수.
void Rank(int);//등급 출력 함수
void gotoxy(int x, int y);//xy좌표
void setcolor(int color, int bgcolor);//색상지정
int wherex(); ﻿
int wherey();
void sub(int *);

int i;//반복문용
int count;// 이동 횟수 측정

void main()
{
	setcolor(15, 6);
	system("cls");
	int arr[16] = {};
	int end[16] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0 };//arr의 최종 결과물
	int a, zero = 15;//a는 방향키 입력 , zero는 zero의 위치
	int tim; // 걸린시간 측정

	clock_t bT, eT;//시작시간 끝시간 비교용

	srand(time(NULL));



	sub(end);// 완성 모양 출력
	getch();//키입력 받으면 시작
	system("cls");

	bT = clock();

	set(arr);//퍼즐조합
	print(arr);//퍼즐 출력
	for (;;)
	{

		a = getch();//조작입력받기
		fflush(stdin);
		move(a, &zero, arr);//이동함수
		system("cls");//화면지우고
		print(arr);//다시출력


		if (cmp(arr, end))//현재 출력되어있는 배열과
			break;//최종 배열을 비교
	}

	eT = clock();

	tim = (eT - bT) / CLOCKS_PER_SEC;

	cout << "\n\n\n";
	gotoxy(30, wherey());
	cout << "축하합니다. 성공입니다.\n";
	gotoxy(30, wherey());
	cout << "총 이동횟수 : " << count << "회\n";
	gotoxy(30, wherey());
	cout << "걸린시간 : " << tim << "초\n";
	gotoxy(30, wherey());
	cout << "등급 : ";
	Rank(tim);
	getch();

}

void set(int *arr)
{
	int a;

	for (;;) {
		for (i = 1; i<16; i++)
		{
			a = rand() % 15;
			if (!*(arr + a))//3행3열을 제외한 칸에 1~15를 랜덤으로 대입
				*(arr + a) = i;
			else
				i--;
		}
		if (inversion(arr))//조합된 퍼즐이 해결가능한 가능한지 확인
			break;
		else {
			for (i = 0; i<15; i++)//해결 불가능한 퍼즐일시 전부 0을 대입하고 퍼즐 재조합
				*(arr + i) = 0;
		}
	}
}

bool inversion(int *arr) //퍼즐 해결 가능여부 확인 함수
{
	int t, j, count = 0;

	for (i = 0; i<15; i++)//n보다 후에 있는 작은 수의 갯수의 합을 모두 더해
	{
		t = arr[i];
		for (j = i + 1; 15 - j; j++)
			if (t>arr[j])
				count++;
	}

	if (count % 2)//홀수일 경우 풀이가 불가능하고
		return 0;
	else//짝수일 경우 퍼즐 풀이가 가능하다는 점을 이용하였다.
		return 1;
}

void print(int *arr)
{
	int j;
	unsigned char a = 0xa6, b[11];

	for (i = 0; i<11; i++)
		b[i] = 0xa0 + i + 1;
	gotoxy(30, 5);
	printf("%c%c", a, b[2]);
	for (i = 0; i<3; i++)
	{
		printf("%c%c", a, b[0]);
		printf("%c%c", a, b[7]);
	}
	printf("%c%c", a, b[0]);
	printf("%c%c\n", a, b[3]);
	gotoxy(30, wherey());
	for (i = 0; i<3; i++)
	{
		for (j = 0; j<4; j++)
		{
			printf("%c%c", a, b[1]);
			printf("%2d", *arr++);
		}
		printf("%c%c\n", a, b[1]);
		gotoxy(30, wherey());
		printf("%c%c", a, b[6]);
		for (j = 0; j<3; j++)
		{
			printf("%c%c", a, b[0]);
			printf("%c%c", a, b[10]);
		}
		printf("%c%c", a, b[0]);
		printf("%c%c\n", a, b[8]);
		gotoxy(30, wherey());
	}

	for (j = 0; j<4; j++)
	{
		printf("%c%c", a, b[1]);
		printf("%2d", *arr++);
	}
	printf("%c%c\n", a, b[1]);
	gotoxy(30, wherey());
	printf("%c%c", a, b[5]);
	for (i = 0; i<3; i++)
	{
		printf("%c%c", a, b[0]);
		printf("%c%c", a, b[9]);
	}
	printf("%c%c", a, b[0]);
	printf("%c%c\n", a, b[4]);
}


void swap(int&a, int&b)
{
	int t;
	t = a;
	a = b;
	b = t;
}

void move(int a, int *z, int *arr) //getch로 방향키를 입력받는 함수
{
	switch (a)
	{
	case 75: //방향키 왼쪽
		if (*z % 4 == 0)
			break;
		swap(arr[*z], arr[*z - 1]);
		*z -= 1;
		count++;
		break;
	case 72: //방향키 위쪽
		if (*z<4)
			break;
		swap(arr[*z], arr[*z - 4]);
		*z -= 4;
		count++;
		break;
	case 77: //방향키 오른쪽
		if (*z % 4 == 3)
			break;
		swap(arr[*z], arr[*z + 1]);
		*z += 1;
		count++;
		break;
	case 80: //방향키 아래쪽
		if (*z>11)
			break;
		swap(arr[*z], arr[*z + 4]);
		*z += 4;
		count++;
		break;
	}
}

bool cmp(int *arr, int *end)
{
	for (; *arr || *end; arr++, end++)
		if (*arr != *end)
			return false;
	return true;
}

void Rank(int t)
{
	if (t <= 30)
		cout << "★★★★★" << endl;
	else if (t <= 60)
		cout << "★★★★☆" << endl;
	else if (t <= 180)
		cout << "★★★☆☆" << endl;
	else if (t <= 300)
		cout << "★★☆☆☆" << endl;
	else if (t <= 600)
		cout << "★☆☆☆☆" << endl;
	else
		cout << "☆☆☆☆☆" << endl;

}

void gotoxy(int x, int y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void setcolor(int color, int bgcolor)
{
	color &= 0xf;
	bgcolor &= 0xf;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (bgcolor << 4) | color);
}

int wherex()
{
	CONSOLE_SCREEN_BUFFER_INFO csb;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csb);
	return (csb.dwCursorPosition.X);
}

int wherey()
{
	CONSOLE_SCREEN_BUFFER_INFO csb;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csb);
	return (csb.dwCursorPosition.Y);
}

void sub(int *end)
{
	gotoxy(30, wherey());
	cout << "15 PUZZLE\n";
	gotoxy(30, wherey());
	cout << "0을 이동시켜 아래 모양으로\n";
	gotoxy(30, wherey());
	cout << "맞추시면 됩니다.\n";
	gotoxy(30, wherey());
	cout << "조작 : 방향키로 0 을 이동시킵니다.\n";

	print(end);

}