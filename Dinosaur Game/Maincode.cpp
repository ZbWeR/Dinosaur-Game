#include"Function.h"
#include"Init.h"
#include"Global.h"

//��Ϸ����
void Startgame()
{
	Init();//��ʼ������
	while (1) {
		input_game();//�����������
		change_location();//�ı���������
		ground_dino();//��������ж�
		dino_collision();
		//С�����ϰ�����ײ�ж� �Լ� С������ж�
		if (dino_collision())
			break;
		recircle();//����ѭ������
		cleardevice();//����
		BeginBatchDraw();
		print_game();//�����Ϸ����
		EndBatchDraw();
		skill_require();//���ܻ���ж�
		Sleep(24);
	}
	End_game(score);
}

int main()
{
	Init();//��ʼ������
	pre_print();//��ʼ����Ϸ����
	input_key();//�ȴ���������
	srand((int)time(0));
	closegraph();
	return 0;
}