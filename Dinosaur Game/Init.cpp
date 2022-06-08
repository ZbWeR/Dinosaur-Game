#include "StdHeader.h"
#include "Init.h"
#include "Function.h"
#include"Global.h"
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
