#include "StdHeader.h"
#include "Init.h"
#include "Global.h"
//�������[x,y]�ڵ������
int rand_range(int x, int y)
{
	return rand() % (y + 1) + x;
}

//���͸��������ͼƬ
void PutPng(int x, int y, IMAGE* im_show1, IMAGE* im_show2)
{
	putimage(x, y, im_show1, SRCAND);
	putimage(x, y, im_show2, SRCPAINT);
}


//�ı���������
void change_location()
{
	//С����λ�ñ��
	dino_vy = dino_vy + gravity;
	dino_Topy = dino_Topy + dino_vy;
	dino_Lfetx = dino_Lfetx + dino_vx;
	//�ϰ���1λ�ñ��
	rec1_Leftx = rec1_Leftx + rec1_vx;
	//�ϰ���2λ�ñ��
	rec2_Leftx = rec2_Leftx + rec2_vx;
	//�ƶ�λ�ñ��
	cloud_x -= 0.5;
	cloud_x2 -= 0.5;
	ani = (ani + 1) % 9;
}


//��ü�������
void input_game()
{
	if (_kbhit())
	{
		char input = _getch();
		if ((int)(input) == -32)
		{
			input = _getch();
			//����� �� ������Ծ ȷ���ڵ��ϲ�������
			if ((int)input == 72 && ground_flag >= 1) {
				dino_vy = -5;
				ground_flag -= 1;
				skill1_flag = 0;
			}
			//����� �� �������������
			if ((int)input == 80) {
				dino_vy = 5;
				dino_vx = 0;
			}
			//����� �� ������ǰ����
			if ((int)input == 77) {
				dino_vx = 1;
				if (score >= tmpscore1 && ground_flag >= 0 && skill1_flag == 0) {
					dino_Lfetx += 10, skill1_flag = 1;
				}
			}
			//����� �� ���Ƽ���
			if ((int)input == 75) {
				dino_vx = -1;
			}
		}
	}
}



//����ѭ������
void recircle()
{
	//�ϰ����ܵ���ͷ
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
	//�ƶ�ѭ��
	if (cloud_x <= 0)   cloud_x = width / 4 + 27;
	if (cloud_x2 <= 0)  cloud_x2 = width / 4 + 63;
}



//���ܻ���ж�
void skill_require()
{
	if (score >= tmpscore1 && skill1 == 0) {
		skill1 = 1;
		settextstyle(14, 0, _T("����"));
		TCHAR Skill[] = _T("����¼��ܣ��������ҿ�˲��");
		outtextxy(width / 8 - textwidth(Skill) / 2, height / 16, Skill);
		Sleep(1500);
		settextstyle(7, 0, _T("����"));
	}
	if (score >= tmpscore2 && skill2 == 0) {
		skill2 = 1;
		settextstyle(14, 0, _T("����"));
		TCHAR Skill[] = _T("����¼��ܣ����пɶ�����");
		outtextxy(width / 8 - textwidth(Skill) / 2, height / 16, Skill);
		Sleep(1500);
		settextstyle(7, 0, _T("����"));
	}
}



//��������ж�
void ground_dino()
{
	if (dino_Topy >= bottom - dino_height) {
		dino_vy = 0;//��ֱ�ٶ�Ϊ0
		dino_Topy = bottom - dino_height;//��ֱ������ذ���ͬ
		ground_flag = 1;//λ�ڵ���������Ծһ��
		skill1_flag = 1;//���ܷ�������1
		if (score >= tmpscore2)//�����ü���2
			ground_flag = 2;//λ�ڵ������ܶ�����
	}
	else {
		ani = 3;
	}
}




//������ײ�ж�
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