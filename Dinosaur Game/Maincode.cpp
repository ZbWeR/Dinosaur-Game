#include<graphics.h>
#include<conio.h>
#include<cstdio>
#include<math.h>
#include<ctime>

//定义


//定义图片素材
IMAGE im_logo1, im_logo2;//logo素材
IMAGE im_ground, im_Tree, im_bg, im_cloud;//背景,树,地板,云
IMAGE im_dino21, im_dino22, im_dino31, im_dino32, im_dino41, im_dino42, im_fly1, im_fly2;//恐龙动作素材

double width, height, bottom;//游戏画面长宽以及底部设置
double dino_width, dino_height, dino_Lfetx, dino_Topy;//恐龙矩形四个点坐标
double dino_vy, dino_vx, gravity;//恐龙水平数值速度,重力加速度
double rec1_width, rec1_height, rec1_Leftx, rec1_Topy, rec1_vx, rec_distance, rec1_flag;//障碍物1相关参数
double rec2_width, rec2_height, rec2_Leftx, rec2_Topy, rec2_vx, rec2_flag;//障碍物2相关参数
//游戏分数,,进入下一阶段的分数,技能开启是否开启,恐龙是否位于地面
int score, tmpscore1 = 10, tmpscore2 = 25, ground_flag, skill1_flag, ani;
double cloud_x = 220, cloud_x2 = 220 + 70;//背景云朵的参数
int randwid[5] = { 80,32,48,16,64 }, skill1, skill2;//是否获得技能1与技能2,是否播放飞翔动画

void input_key();//提前声明函数

//获得区间[x,y]内的随机数
int rand_range(int x, int y)
{
	return rand() % (y + 1) + x;
}

//输出透明背景的图片
void PutPng(int x, int y, IMAGE* im_show1, IMAGE* im_show2)
{
	putimage(x, y, im_show1, SRCAND);
	putimage(x, y, im_show2, SRCPAINT);
}

//初始化游戏设置
void Init()
{
	//加载图片
	loadimage(&im_bg, _T("./src/background.png"));
	loadimage(&im_logo1, _T("./src/logo1.png"));
	loadimage(&im_logo2, _T("./src/logo2.png"));

	loadimage(&im_dino21, _T("./src/move2_1.png"));
	loadimage(&im_dino22, _T("./src/move2_2.png"));
	loadimage(&im_dino31, _T("./src/move3_1.png"));
	loadimage(&im_dino32, _T("./src/move3_2.png"));
	loadimage(&im_dino41, _T("./src/move4_1.png"));
	loadimage(&im_dino42, _T("./src/move4_2.png"));
	loadimage(&im_fly1, _T("./src/fly_1.png"));
	loadimage(&im_fly2, _T("./src/fly_2.png"));

	loadimage(&im_ground, _T("./src/1.png"));
	loadimage(&im_Tree, _T("./src/Tree.png"));
	loadimage(&im_cloud, _T("./src/cloud.png"));

	//游戏画面设置
	width = 1000;//长
	height = 400;//高
	bottom = (height - 46) / 4;//地板高度坐标
	initgraph(width, height);//初始化画布
	setaspectratio(4.0, 4.0);//设置放大比率
	settextcolor(RGB(0, 0, 0));//设置输出字体为黑色
	setbkcolor(RGB(177, 236, 240));//设置画布背景颜色 浅蓝

	//小恐龙
	dino_width = 14;//宽
	dino_height = 16;//高
	dino_Lfetx = width / 20;//水平坐标（靠右）
	dino_Topy = bottom - dino_height;//竖直坐标(靠上)
	dino_vx = 0;//水平速度
	dino_vy = 0;//竖直速度
	gravity = 0.25;//重力加速度
	ground_flag = 1;//初始位于地面
	ani = 0;

	//障碍物
	rec1_width = rec2_width = 16;//宽度
	rec1_height = rec2_height = 21;//高度
	rec1_Leftx = width / 4 - 25;//1的右上坐标
	rec_distance = 100;//两障碍物初始距离
	rec2_Leftx = rec1_Leftx + rec_distance;//2的右上坐标
	rec1_Topy = rec2_Topy = bottom - rec1_height;//竖直坐标(靠上)
	rec1_vx = rec2_vx = -2.5;//水平速度
	rec1_flag = rec2_flag = 0;//flag1>flag2说明1在2之后

	score = 0;//初始分数
	skill1 = 0; skill2 = 0;//是否获得技能1，2
	skill1_flag = 1;//是否可以使用技能1
}

//绘制初始页面
void pre_print()
{
	//游戏开始界面
	putimage(0, 0, &im_bg);//加载背景图片
	settextstyle(15, 0, _T("Consolas"));//设置字体
	settextcolor(RGB(253, 138, 101));//设置字体颜色

	//输出logo与游戏名称
	TCHAR Intro[30];
	wcscpy_s(Intro, _T("New Dinosaur"));
	int Intro_wid = width / 8 - textwidth(Intro) / 2;
	int Intro_hei = height / 8 - textheight(Intro);
	outtextxy(Intro_wid + 10, Intro_hei, Intro);
	PutPng(Intro_wid - dino_width * 2 + 10, Intro_hei - 1, &im_logo1, &im_logo2);//logo
	Sleep(1500);

	cleardevice();
	putimage(0, 0, &im_bg);//加载背景图片
	putimage(0, 0, &im_bg);//绘制背景
	putimage(cloud_x, 10, &im_cloud);//绘制云朵1
	putimage(cloud_x2, 10 + 5, &im_cloud);//绘制云朵2
	PutPng(dino_Lfetx, dino_Topy, &im_logo1, &im_logo2);//绘制恐龙
	//绘制地板
	for (int i = 0; i < width / 4 * 46; i++)
		putimage(i * 46, bottom, &im_ground);

	settextcolor(RGB(0, 0, 0));//设置字体颜色
	settextstyle(8, 0, _T("宋体"));//设置字体
	//绘制提示字体
	wcscpy_s(Intro, _T("开始 -   空格"));
	Intro_wid = width / 8 - textwidth(Intro) / 2;
	Intro_hei = height / 8 - textheight(Intro) * 2;
	outtextxy(Intro_wid, Intro_hei, Intro);
	wcscpy_s(Intro, _T("教程 - press A"));
	Intro_hei = Intro_hei + textheight(Intro);
	outtextxy(Intro_wid, Intro_hei + 5, Intro);
	wcscpy_s(Intro, _T("退出 - press B"));
	outtextxy(Intro_wid, Intro_hei + textheight(Intro) + 10, Intro);
}

//改变物体坐标
void change_location()
{
	//小恐龙位置变更
	dino_vy = dino_vy + gravity;
	dino_Topy = dino_Topy + dino_vy;
	dino_Lfetx = dino_Lfetx + dino_vx;
	//障碍物1位置变更
	rec1_Leftx = rec1_Leftx + rec1_vx;
	//障碍物2位置变更
	rec2_Leftx = rec2_Leftx + rec2_vx;
	//云朵位置变更
	cloud_x -= 0.5;
	cloud_x2 -= 0.5;
	ani = (ani + 1) % 9;
}

//获得键盘输入
void input_game()
{
	if (_kbhit())
	{
		char input = _getch();
		if ((int)(input) == -32)
		{
			input = _getch();
			//方向键 上 控制跳跃 确保在地上才能起跳
			if ((int)input == 72 && ground_flag >= 1) {
				dino_vy = -5;
				ground_flag -= 1;
				skill1_flag = 0;
			}
			//方向键 下 控制下落与减速
			if ((int)input == 80) {
				dino_vy = 5;
				dino_vx = 0;
			}
			//方向键 左 控制向前加速
			if ((int)input == 77) {
				dino_vx = 1;
				if (score >= tmpscore1 && ground_flag >= 0 && skill1_flag == 0) {
					dino_Lfetx += 10, skill1_flag = 1;
				}
			}
			//方向键 右 控制减速
			if ((int)input == 75) {
				dino_vx = -1;
			}
		}
	}
}

//结束游戏画面
void End_game(int score)
{
	TCHAR tmp[20];
	swprintf_s(tmp, _T("Score:%d"), score);
	settextstyle(14, 0, _T("宋体"));
	outtextxy(width / 8 - textwidth(tmp) / 2, height / 8 - textheight(tmp), tmp);
	settextstyle(7, 0, _T("宋体"));
	wcscpy_s(tmp, _T("空格-重新开始游戏"));
	outtextxy(width / 8 - textwidth(tmp) / 2, height / 8 + 0.5 * textheight(tmp), tmp);

	settextstyle(15, 0, _T("Consolas"));
	wcscpy_s(tmp, _T("made by zbwer"));
	settextstyle(7, 0, _T("宋体"));
	outtextxy(width / 8 - textwidth(tmp) / 2, height / 8 + 2 * textheight(tmp), tmp);
	settextstyle(15, 0, _T("Consolas"));
	input_key();
}
//物体循环播放
void recircle()
{
	//障碍物跑到尽头
	if (rec1_Leftx <= 0) {
		rec1_flag++;
		rec1_Leftx = width / 4;
		if (rec2_Leftx + rec1_width >= width / 4) rec1_Leftx = rec2_Leftx + rand_range(2, 4) * 50;
		score++;
		if (score >= 10)
			rec1_vx -= 0.1, rec2_vx -= 0.1;
	}
	else if (rec2_Leftx <= 0)
	{
		rec2_flag++;
		rec_distance = randwid[rand() % 5];
		if (rec1_flag > rec2_flag) rec_distance = width / 4 - rec1_Leftx;
		rec2_Leftx = width / 4 + rec_distance + randwid[rand() % 5];
		score++;

	}
	//云朵循环
	if (cloud_x <= 0)   cloud_x = width / 4 + 27;
	if (cloud_x2 <= 0)  cloud_x2 = width / 4 + 63;
}
//绘制游戏界面
void print_game()
{

	//绘制背景
	putimage(0, 0, &im_bg);
	putimage(cloud_x, 10, &im_cloud);
	putimage(cloud_x2, 10 + 5, &im_cloud);

	//绘制恐龙
	if (ani <= 3) PutPng(dino_Lfetx, dino_Topy, &im_dino21, &im_dino22);
	else if (ani > 3 && ani <= 5) PutPng(dino_Lfetx, dino_Topy, &im_dino31, &im_dino32);
	else PutPng(dino_Lfetx, dino_Topy, &im_dino41, &im_dino42);

	//绘制地板
	for (int i = 0; i < width / 46; i++)
		putimage(i * 46, bottom, &im_ground);

	//绘制障碍物
	putimage(rec1_Leftx, rec1_Topy, &im_Tree);
	putimage(rec2_Leftx, rec2_Topy, &im_Tree);
	//绘制分数
	TCHAR s[20];
	swprintf_s(s, _T("%d"), score);
	settextstyle(14, 0, _T("Consolas"));
	outtextxy(50 / 4, 30 / 4, s);
}
//技能获得判定
void skill_require()
{
	if (score >= tmpscore1 && skill1 == 0) {
		skill1 = 1;
		settextstyle(14, 0, _T("宋体"));
		TCHAR Skill[] = _T("获得新技能：空中向右可瞬移");
		outtextxy(width / 8 - textwidth(Skill) / 2, height / 16, Skill);
		Sleep(1500);
		settextstyle(7, 0, _T("宋体"));
	}
	if (score >= tmpscore2 && skill2 == 0) {
		skill2 = 1;
		settextstyle(14, 0, _T("宋体"));
		TCHAR Skill[] = _T("获得新技能：空中可二段跳");
		outtextxy(width / 8 - textwidth(Skill) / 2, height / 16, Skill);
		Sleep(1500);
		settextstyle(7, 0, _T("宋体"));
	}
}
//恐龙落地判断
void ground_dino()
{
	if (dino_Topy >= bottom - dino_height) {
		dino_vy = 0;//竖直速度为0
		dino_Topy = bottom - dino_height;//竖直坐标与地板相同
		ground_flag = 1;//位于地面且能跳跃一次
		skill1_flag = 1;//不能发动技能1
		if (score >= tmpscore2)//如果获得技能2
			ground_flag = 2;//位于地面且能二段跳
	}
	else {
		ani = 3;
	}
}

//恐龙碰撞判定
bool dino_collision()
{
	if ((rec1_Leftx < dino_Lfetx + dino_width && rec1_Topy + 1 < dino_Topy + dino_height && dino_Lfetx < rec1_Leftx + rec1_width) ||
		((rec2_Leftx < dino_Lfetx + dino_width && rec2_Topy + 1 < dino_Topy + dino_height && dino_Lfetx < rec2_Leftx + rec2_width)) ||
		(dino_Lfetx <= 0 || dino_Lfetx + dino_width >= width / 4))
		return 1;
	return 0;
}
//游戏主体
void Startgame()
{
	Init();//初始化变量
	while (1) {
		input_game();//读入键盘数据
		change_location();//改变物体坐标
		ground_dino();//恐龙落地判断
		dino_collision();
		//小球与障碍物碰撞判断 以及 小球出界判断
		if (dino_collision())
			break;
		recircle();//物体循环出现
		cleardevice();//清屏
		BeginBatchDraw();
		print_game();//输出游戏画面
		EndBatchDraw();
		skill_require();//技能获得判定
		Sleep(24);
	}
	End_game(score);
}
//教程
void Start_intgame()
{
	Init();
	TCHAR tmp[30];
	int flag1 = 1, flag2 = 1, flag3 = 1, flag4 = 1, flag5 = 1;
	while (1)
	{

		if (_kbhit())
		{
			char input = _getch();
			if ((int)(input) == -32)
			{
				input = _getch();
				//方向键 上 控制跳跃 确保在地上才能起跳
				if ((int)input == 72 && ground_flag >= 1) {
					dino_vy = -5;
					ground_flag -= 1;
					skill1_flag = 0;
					flag1 = 0;
				}
				//方向键 下 控制下落与减速
				if ((int)input == 80) {
					dino_vy = 5;
					dino_vx = 0;
					flag2 = 0;
				}

				//方向键 左 控制向前加速
				if ((int)input == 77) {
					dino_vx = 1;
					flag3 = 0;
					if (ground_flag >= 0 && skill1_flag == 0)
						dino_Lfetx += 10, skill1_flag = 1, flag5 = 0;
				}
				//方向键 右 控制减速
				if ((int)input == 75) {
					dino_vx = -1;
					flag4 = 0;
				}
			}
			if (input == ' ') {
				Startgame();
			}
		}
		cleardevice();
		change_location();
		ground_dino();
		BeginBatchDraw();
		print_game();//输出游戏画面

		settextstyle(7, 0, _T("宋体"));
		if (flag1 == 1)	wcscpy_s(tmp, _T("方向键上  控制跳跃"));
		else if (flag2 == 1)	wcscpy_s(tmp, _T("下  控制下落,并让水平速度为0"));
		else if (flag3 == 1)	wcscpy_s(tmp, _T("方向键右  控制水平向右加速,下可停止"));
		else if (flag4 == 1)	wcscpy_s(tmp, _T("方向键左  控制水平向左加速")), skill1 = 1;
		else if (flag5 == 1)	wcscpy_s(tmp, _T("方向键右  技能:空中可瞬移"));
		else wcscpy_s(tmp, _T("空格正式开始游戏"));

		outtextxy(width / 8 - textwidth(tmp) / 2, height / 8, tmp);
		EndBatchDraw();
		Sleep(24);
	}
}

void input_key()
{
	while (1)
	{
		char input = _getch();
		if (input == ' ')
		{
			Startgame();
			break;
		}
		else if (input == 'B') exit(0);
		else if (input == 'A')
		{
			Start_intgame();
			break;
		}
	}
}

int main()
{
	Init();//初始化变量
	pre_print();//初始化游戏界面
	input_key();//等待键盘输入
	srand((int)time(0));
	closegraph();
	return 0;
}