#include <windows.h>
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include <time.h>
constexpr int LEN = 4;
// 传入坐标, 将光标移动到指定坐标
void gotoXY(int x, int y)
{
	COORD c;
	c.X = x - 1;
	c.Y = y - 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}


//使用案例
//清理指定矩形区域(从(x,y)到(x+w,y+h)的矩形
void clear(int x, int y, int w, int h)
{
	for (int i = 0; i < h; i++) {
		gotoXY(x, y + i);
		for (int j = 0; j < w; j++) putchar(' ');
	}
}



/*
设置打印字体的颜色
0x24: 低位4表示字体红色 高位2表示背景绿色

0: 黑
1: 蓝
2: 绿
3: 蓝绿
4: 红
5: 紫
6: 黄
7: 白
+8表示高亮
*/
void setPrintColor(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}




/*
菜单:
展示选项
开始游戏: 进入游戏界面
设置: 进入设置界面
排行榜: 进入排行榜界面
退出: 退出游戏

选择:
用户可以输入w/s进行选择: 移动光标
确认:
用户输入回车进行确认: 执行对应的操作


游戏界面:
展示:
有蛇, 有地图(食物, 空地,墙)
有操作提示
玩家在里面可以操作蛇
如果蛇撞墙 游戏结束  如果蛇吃到食物xxxxxxx

方向输入:
玩家输入方向后 根据输入的内容修改蛇的方向
如果输入是合法输入 修改
如果是不合法 什么都没有发生
esc: 退出游戏
空格: 暂停游戏

定时执行:
蛇移动一格
空地xxxxxxxx
食物xxxxxxxx
墙xxxxxxxx
*/

// 蛇的长度
int len = 0;

//1墙, 2食物, 0空地
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
第一维度表示蛇的第n个身体
第二维度表示蛇的第n个身体的x轴或y轴

s[0][0] 表示蛇头的x坐标
s[3][1] 表示第4个蛇身的y坐标

#define X 0
#define Y 0
*/
int s[20 * 20][2] = { 0 };

//方向 wasd
char dir = 'wsw';



//------------------service------------------------


/*
功能: 蛇, 地图, 食物, 方向, 长度
1. 初始化地图
一圈1，中间0

2. 蛇
长度: 3
方向: d
坐标: 头的位置 上面, 下面, 左边距离相等

3. 食物
随机生成食物  注意: 避免生成到蛇的坐标上
*/
void init();


/*
负责人: 李四
功能:
判断 用户的输入和蛇原本的方向 是否有冲突
如果有冲突 不修改 返回0
如果没有 修改成用户输入的方向  返回1

参数:
input: 用户的输入
返回值:
0: 表示方向修改失败
1: 表示方向修改成功
*/
int updateDir(char input);

/*
* 游戏结束
*/
void over();


/*
负责人: 李四
功能:
蛇移动一格

判断: 判断蛇的下一步 是什么东西
如果是墙/蛇的身体: return 2;
如果是食物:
长度+1
随机生成新的食物
如果是空地:
void

数据修改: 蛇身的坐标 往前挪一格

如果有吃到食物: return 1;
如果没有吃到: return 0;


参数: void
返回值:
死亡: 2
吃到食物: 返回1
空地: 0

*/
int moveToNext(void);

//-------------view-----------------------------

/*
*	负责人: 张三
功能:
1. 初始化数据       service        初始化数据函数
2. 打印界面: 蛇, 地图, 食物, 提示信息等等     view
while(1){
3. 判断有无输入       view
有输入:
接收并判断输入类型:   view
方向:
修改方向() service      修改方向函数
暂停: getch();   view
退出: return;	view
非法输入: 无视
没有输入:
4. 暂停500毫秒后result = 移动()  service   移动函数
5. 判断移动后的结果      view
墙/咬到尾巴:
打印游戏结束	view
return;
食物:
播放音效		view

长度+1			service
随机生成食物	service

空地:
什么都没有发生.

6. 打印界面				view
}
参数: void
返回值: void
*/
void gameView();

/*
负责人: 张三
功能:
菜单:
while(1){
打印选项
开始游戏
设置
排行榜
退出
用户输入:
选择:
用户可以输入w/s进行选择: 移动光标
确认:
进入对应的界面
开始游戏: gameView();
设置: 进入设置界面
排行榜: 进入排行榜界面
退出: 退出游戏
}
参数: void
返回值: void
*/
void menu();



int main() {
	srand((unsigned)time(NULL));
	menu();
	return 0;
}
// 果子的位置
static void randFruitLocation(int *x, int *y)
{
	while (true)
	{
		*x = rand() % 20;
		*y = rand() % 20;
		// 位置合理
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

// 果子、蛇、空地、边界的颜色设置
static void printColor(int x)
{
	// 空地
	if (x == 0)
	{
		setPrintColor(0x00);
	}
	// 边界
	else if (x == 1)
	{
		setPrintColor(0x6f);
	}
	// 果实
	else if (x == 2)
	{
		setPrintColor(0x4f);
	}
	// 蛇
	else
	{
		setPrintColor(0x2f);
	}
	printf("%d", x);
}
// 蛇的位置赋值
static void changeSnakePos(int len)
{
	// 蛇的坐标数字设置为8
	for (int i = 0; i < len; i++)
	{
		map[s[i][0]][s[i][1]] = 8;
	}
}
// 初始化蛇,最开始有3段身体+1个脑袋
static void randSnakeLocation(int a, int b)//参数是果实的位置
{
	len = 4;
	// 随机生成位置, 19和0的位置不能占
	int x = 1, y = 1;
	while (true)
	{
		x = rand() % 20;
		y = rand() % 20;
		// 头位置合理
		if (x > 0 && x < 19 && y > 0 && y < 19 && x != a && y != b)
		{
			// 未超出边界
			if (x + LEN < 19 && y + LEN < 19)
			{
				break;
			}
		}
	}
	s[0][0] = x; s[0][1] = y;
	// 横着还是竖着
	if (rand() % 2)
	{
		// 横着
		for (int i = 0; i <= 3; i++)
		{
			s[i][0] = x + i; s[i][1] = y;
		}
	}
	else
	{
		// 竖着
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
	// 初始化地图
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

// 判断用户输入是否冲突
int updateDir(char input)
{
	int headX = s[0][0];
	int headY = s[0][1];
	// 头的下一个位置
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
	changeSnakePos(len);	// 改变蛇的位置
	int size = sizeof(map) / sizeof(map[0]);
	// 初始化地图
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
	changeSnakePos(len);	// 改变蛇的位置
	randFruitLocation(&x, &y);
	map[x][y] = 2;
	int size = sizeof(map) / sizeof(map[0]);
	// 初始化地图
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
// 判断下一步
int moveToNext(void)
{
	int headX = s[0][0];
	int headY = s[0][1];
	// 头的下一个位置
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
	case 1:		// 墙
	case 8:		// 咬到自己
		over();
		break;
	case 2:		// 吃到了果实
		len++;	// 长度变长
		// 改变身体位置
		for (int i = len - 1; i >= 0; --i)
		{
			s[i + 1][0] = s[i][0], s[i + 1][1] = s[i][1]; // 身体移动
		}
		s[0][0] = headX, s[0][1] = headY;	// 改变头位置
		runLenAdd();
		break;
	default:
		for (int i = len - 1; i > 0; --i)
		{
			map[s[i][0]][s[i][1]] = 0;
			s[i][0] = s[i - 1][0],s[i][1] = s[i - 1][1]; // 身体移动
		}
		s[0][0] = headX, s[0][1] = headY;	// 改变头位置
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
	// 初始化
	init();
	/*
	* 		while(1){
	3. 判断有无输入       view
	有输入:
	接收并判断输入类型:   view
	方向:
	修改方向() service      修改方向函数
	暂停: getch();   view
	退出: return;	view
	非法输入: 无视
	没有输入:
	4. 暂停500毫秒后result = 移动()  service   移动函数
	5. 判断移动后的结果      view
	墙/咬到尾巴:
	打印游戏结束	view
	return;
	食物:
	播放音效		view

	长度+1			service
	随机生成食物	service

	空地:
	什么都没有发生.

	6. 打印界面				view
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
			if (updateDir(input))	// 移动合理
			{
				dir = input; // 改变方向
			}
		default:
			// 按照之前的方向继续移动
			move();
		}
	}
}

void menu() {
	int userChoose = 0;
	while (1) {
		gotoXY(60, 3);
		printf("贪     吃     蛇");
		if (userChoose == 0) setPrintColor(0x6f);
		gotoXY(64, 6);
		printf("开始游戏");
		if (userChoose == 0) setPrintColor(0x0f);

		if (userChoose == 1) setPrintColor(0x6f);
		gotoXY(65, 9);
		printf("排行榜");
		if (userChoose == 1) setPrintColor(0x0f);

		if (userChoose == 2) setPrintColor(0x6f);
		gotoXY(64, 12);
		printf("游戏设置");
		if (userChoose == 2) setPrintColor(0x0f);

		if (userChoose == 3) setPrintColor(0x6f);
		gotoXY(64, 15);
		printf("退出游戏");
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








