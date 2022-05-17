#include"Function.h"
#include"Init.h"
#include"Global.h"

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

int main()
{
	Init();//初始化变量
	pre_print();//初始化游戏界面
	input_key();//等待键盘输入
	srand((int)time(0));
	closegraph();
	return 0;
}