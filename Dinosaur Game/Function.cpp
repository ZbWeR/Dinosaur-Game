#include "StdHeader.h"
#include "Init.h"
#include "Global.h"
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