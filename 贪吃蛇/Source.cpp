#include <windows.h>
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include <time.h>
constexpr int LEN = 4;
// ��������, ������ƶ���ָ������
void gotoXY(int x, int y)
{
	COORD c;
	c.X = x - 1;
	c.Y = y - 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}


//ʹ�ð���
//����ָ����������(��(x,y)��(x+w,y+h)�ľ���
void clear(int x, int y, int w, int h)
{
	for (int i = 0; i < h; i++) {
		gotoXY(x, y + i);
		for (int j = 0; j < w; j++) putchar(' ');
	}
}



/*
���ô�ӡ�������ɫ
0x24: ��λ4��ʾ�����ɫ ��λ2��ʾ������ɫ

0: ��
1: ��
2: ��
3: ����
4: ��
5: ��
6: ��
7: ��
+8��ʾ����
*/
void setPrintColor(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}




/*
�˵�:
չʾѡ��
��ʼ��Ϸ: ������Ϸ����
����: �������ý���
���а�: �������а����
�˳�: �˳���Ϸ

ѡ��:
�û���������w/s����ѡ��: �ƶ����
ȷ��:
�û�����س�����ȷ��: ִ�ж�Ӧ�Ĳ���


��Ϸ����:
չʾ:
����, �е�ͼ(ʳ��, �յ�,ǽ)
�в�����ʾ
�����������Բ�����
�����ײǽ ��Ϸ����  ����߳Ե�ʳ��xxxxxxx

��������:
������뷽��� ��������������޸��ߵķ���
��������ǺϷ����� �޸�
����ǲ��Ϸ� ʲô��û�з���
esc: �˳���Ϸ
�ո�: ��ͣ��Ϸ

��ʱִ��:
���ƶ�һ��
�յ�xxxxxxxx
ʳ��xxxxxxxx
ǽxxxxxxxx
*/

// �ߵĳ���
int len = 0;

//1ǽ, 2ʳ��, 0�յ�
int map[20][20] = {
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }

};

/*
��һά�ȱ�ʾ�ߵĵ�n������
�ڶ�ά�ȱ�ʾ�ߵĵ�n�������x���y��

s[0][0] ��ʾ��ͷ��x����
s[3][1] ��ʾ��4�������y����

#define X 0
#define Y 0
*/
int s[20 * 20][2] = { 0 };

//���� wasd
char dir = 'wsw';



//------------------service------------------------


/*
����: ��, ��ͼ, ʳ��, ����, ����
1. ��ʼ����ͼ
һȦ1���м�0

2. ��
����: 3
����: d
����: ͷ��λ�� ����, ����, ��߾������

3. ʳ��
�������ʳ��  ע��: �������ɵ��ߵ�������
*/
void init();


/*
������: ����
����:
�ж� �û����������ԭ���ķ��� �Ƿ��г�ͻ
����г�ͻ ���޸� ����0
���û�� �޸ĳ��û�����ķ���  ����1

����:
input: �û�������
����ֵ:
0: ��ʾ�����޸�ʧ��
1: ��ʾ�����޸ĳɹ�
*/
int updateDir(char input);

/*
* ��Ϸ����
*/
void over();


/*
������: ����
����:
���ƶ�һ��

�ж�: �ж��ߵ���һ�� ��ʲô����
�����ǽ/�ߵ�����: return 2;
�����ʳ��:
����+1
��������µ�ʳ��
����ǿյ�:
void

�����޸�: ��������� ��ǰŲһ��

����гԵ�ʳ��: return 1;
���û�гԵ�: return 0;


����: void
����ֵ:
����: 2
�Ե�ʳ��: ����1
�յ�: 0

*/
int moveToNext(void);

//-------------view-----------------------------

/*
*	������: ����
����:
1. ��ʼ������       service        ��ʼ�����ݺ���
2. ��ӡ����: ��, ��ͼ, ʳ��, ��ʾ��Ϣ�ȵ�     view
while(1){
3. �ж���������       view
������:
���ղ��ж���������:   view
����:
�޸ķ���() service      �޸ķ�����
��ͣ: getch();   view
�˳�: return;	view
�Ƿ�����: ����
û������:
4. ��ͣ500�����result = �ƶ�()  service   �ƶ�����
5. �ж��ƶ���Ľ��      view
ǽ/ҧ��β��:
��ӡ��Ϸ����	view
return;
ʳ��:
������Ч		view

����+1			service
�������ʳ��	service

�յ�:
ʲô��û�з���.

6. ��ӡ����				view
}
����: void
����ֵ: void
*/
void gameView();

/*
������: ����
����:
�˵�:
while(1){
��ӡѡ��
��ʼ��Ϸ
����
���а�
�˳�
�û�����:
ѡ��:
�û���������w/s����ѡ��: �ƶ����
ȷ��:
�����Ӧ�Ľ���
��ʼ��Ϸ: gameView();
����: �������ý���
���а�: �������а����
�˳�: �˳���Ϸ
}
����: void
����ֵ: void
*/
void menu();



int main() {
	srand((unsigned)time(NULL));
	menu();
	return 0;
}
// ���ӵ�λ��
static void randFruitLocation(int *x, int *y)
{
	while (true)
	{
		*x = rand() % 20;
		*y = rand() % 20;
		// λ�ú���
		if (*x > 0 && *x < 19 && *y > 0 && *y < 19)
		{
			if (map[*x][*y] == 0)
			{
				map[*x][*y] = 2;
			}
			return;
		}
	}
}

// ���ӡ��ߡ��յء��߽����ɫ����
static void printColor(int x)
{
	// �յ�
	if (x == 0)
	{
		setPrintColor(0x00);
	}
	// �߽�
	else if (x == 1)
	{
		setPrintColor(0x6f);
	}
	// ��ʵ
	else if (x == 2)
	{
		setPrintColor(0x4f);
	}
	// ��
	else
	{
		setPrintColor(0x2f);
	}
	printf("%d", x);
}
// �ߵ�λ�ø�ֵ
static void changeSnakePos(int len)
{
	// �ߵ�������������Ϊ8
	for (int i = 0; i < len; i++)
	{
		map[s[i][0]][s[i][1]] = 8;
	}
}
// ��ʼ����,�ʼ��3������+1���Դ�
static void randSnakeLocation(int a, int b)//�����ǹ�ʵ��λ��
{
	len = 4;
	// �������λ��, 19��0��λ�ò���ռ
	int x = 1, y = 1;
	while (true)
	{
		x = rand() % 20;
		y = rand() % 20;
		// ͷλ�ú���
		if (x > 0 && x < 19 && y > 0 && y < 19 && x != a && y != b)
		{
			// δ�����߽�
			if (x + LEN < 19 && y + LEN < 19)
			{
				break;
			}
		}
	}
	s[0][0] = x; s[0][1] = y;
	// ���Ż�������
	if (rand() % 2)
	{
		// ����
		for (int i = 0; i <= 3; i++)
		{
			s[i][0] = x + i; s[i][1] = y;
		}
	}
	else
	{
		// ����
		for (int i = 0; i <= 3; i++)
		{
			s[i][0] = x; s[i][1] = y + i;
		}
	}
	changeSnakePos(len);
}
void init()
{
	int x, y;
	randFruitLocation(&x, &y);
	randSnakeLocation(x, y);
	const int size = sizeof(map) / sizeof(map[0]);
	// ��ʼ����ͼ
	gotoXY(50, 3);
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			printColor(map[i][j]);
		}
		gotoXY(50, 3 + i + 1);
	}
	setPrintColor(0x0f);
}

// �ж��û������Ƿ��ͻ
int updateDir(char input)
{
	int headX = s[0][0];
	int headY = s[0][1];
	// ͷ����һ��λ��
	switch (dir)
	{
	case 'w':
		headX -= 1;
		break;
	case 's':
		headX += 1;
		break;
	case 'a':
		headY -= 1;
		break;
	case 'd':
		headY += 1;
		break;
	default:
		break;
	}
	if (headX == s[1][0] && headY == s[1][1])
		return 0;
	return 1;
}

void over()
{
	exit(1);
}
static void runNoAdd()
{
	changeSnakePos(len);	// �ı��ߵ�λ��
	int size = sizeof(map) / sizeof(map[0]);
	// ��ʼ����ͼ
	gotoXY(50, 3);
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			printColor(map[i][j]);
		}
		gotoXY(50, 3 + i + 1);
	}
	setPrintColor(0x0f);
}
static void runLenAdd()
{
	int x, y;
	changeSnakePos(len);	// �ı��ߵ�λ��
	randFruitLocation(&x, &y);
	map[x][y] = 2;
	int size = sizeof(map) / sizeof(map[0]);
	// ��ʼ����ͼ
	gotoXY(50, 3);
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			printColor(map[i][j]);
		}
		gotoXY(50, 3 + i + 1);
	}
	setPrintColor(0x0f);
}
// �ж���һ��
int moveToNext(void)
{
	int headX = s[0][0];
	int headY = s[0][1];
	// ͷ����һ��λ��
	switch (dir)
	{
	case 'w':
		headX -= 1;
		break;
	case 's':
		headX += 1;
		break;
	case 'a':
		headY -= 1;
		break;
	case 'd':
		headY += 1;
		break;
	default:
		break;
	}
	switch (map[headX][headY])
	{
	case 1:		// ǽ
	case 8:		// ҧ���Լ�
		over();
		break;
	case 2:		// �Ե��˹�ʵ
		len++;	// ���ȱ䳤
		// �ı�����λ��
		for (int i = len - 1; i >= 0; --i)
		{
			s[i + 1][0] = s[i][0], s[i + 1][1] = s[i][1]; // �����ƶ�
		}
		s[0][0] = headX, s[0][1] = headY;	// �ı�ͷλ��
		runLenAdd();
		break;
	default:
		for (int i = len - 1; i > 0; --i)
		{
			map[s[i][0]][s[i][1]] = 0;
			s[i][0] = s[i - 1][0],s[i][1] = s[i - 1][1]; // �����ƶ�
		}
		s[0][0] = headX, s[0][1] = headY;	// �ı�ͷλ��
		runNoAdd();
		break;
	}
	return 0;
}
static void move()
{
	moveToNext();
}
void gameView()
{
	// ��ʼ��
	init();
	/*
	* 		while(1){
	3. �ж���������       view
	������:
	���ղ��ж���������:   view
	����:
	�޸ķ���() service      �޸ķ�����
	��ͣ: getch();   view
	�˳�: return;	view
	�Ƿ�����: ����
	û������:
	4. ��ͣ500�����result = �ƶ�()  service   �ƶ�����
	5. �ж��ƶ���Ľ��      view
	ǽ/ҧ��β��:
	��ӡ��Ϸ����	view
	return;
	ʳ��:
	������Ч		view

	����+1			service
	�������ʳ��	service

	�յ�:
	ʲô��û�з���.

	6. ��ӡ����				view
	}
	*/
	while (1)
	{
		while (!_kbhit())
		{
			move();
			Sleep(200);
		}
		char input = _getch();
		switch (input)
		{
		case 'w':
		case 's':
		case 'a':
		case 'd':
			if (updateDir(input))	// �ƶ�����
			{
				dir = input; // �ı䷽��
			}
		default:
			// ����֮ǰ�ķ�������ƶ�
			move();
		}
	}
}

void menu() {
	int userChoose = 0;
	while (1) {
		gotoXY(60, 3);
		printf("̰     ��     ��");
		if (userChoose == 0) setPrintColor(0x6f);
		gotoXY(64, 6);
		printf("��ʼ��Ϸ");
		if (userChoose == 0) setPrintColor(0x0f);

		if (userChoose == 1) setPrintColor(0x6f);
		gotoXY(65, 9);
		printf("���а�");
		if (userChoose == 1) setPrintColor(0x0f);

		if (userChoose == 2) setPrintColor(0x6f);
		gotoXY(64, 12);
		printf("��Ϸ����");
		if (userChoose == 2) setPrintColor(0x0f);

		if (userChoose == 3) setPrintColor(0x6f);
		gotoXY(64, 15);
		printf("�˳���Ϸ");
		if (userChoose == 3) setPrintColor(0x0f);


		char input = _getch();
		switch (input) {
		case 'w':
			userChoose -= 1;
			if (userChoose == -1) userChoose = 3;
			break;
		case 's':
			userChoose = (userChoose + 1) % 4;
			break;
		case '\r':
			clear(3, 2, 80, 20);
			switch (userChoose) {
			case 0:
				gameView();
				exit(0);
				break;
			case 1:
				exit(0);
				break;
			case 2:
				//settingView();
				exit(0);

				break;
			case 3:
				exit(0);
				break;
			}
			clear(3, 2, 36, 20);
			break;
		}
	}
}








