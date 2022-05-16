#include<graphics.h>
#include<conio.h>
#include<cstdio>
#include<math.h>
#include<ctime>

//����


//����ͼƬ�ز�
IMAGE im_logo1, im_logo2;//logo�ز�
IMAGE im_ground, im_Tree, im_bg, im_cloud;//����,��,�ذ�,��
IMAGE im_dino21, im_dino22, im_dino31, im_dino32, im_dino41, im_dino42, im_fly1, im_fly2;//���������ز�

double width, height, bottom;//��Ϸ���泤���Լ��ײ�����
double dino_width, dino_height, dino_Lfetx, dino_Topy;//���������ĸ�������
double dino_vy, dino_vx, gravity;//����ˮƽ��ֵ�ٶ�,�������ٶ�
double rec1_width, rec1_height, rec1_Leftx, rec1_Topy, rec1_vx, rec_distance, rec1_flag;//�ϰ���1��ز���
double rec2_width, rec2_height, rec2_Leftx, rec2_Topy, rec2_vx, rec2_flag;//�ϰ���2��ز���
//��Ϸ����,,������һ�׶εķ���,���ܿ����Ƿ���,�����Ƿ�λ�ڵ���
int score, tmpscore1 = 10, tmpscore2 = 25, ground_flag, skill1_flag, ani;
double cloud_x = 220, cloud_x2 = 220 + 70;//�����ƶ�Ĳ���
int randwid[5] = { 80,32,48,16,64 }, skill1, skill2;//�Ƿ��ü���1�뼼��2,�Ƿ񲥷ŷ��趯��

void input_key();//��ǰ��������

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

//��ʼ����Ϸ����
void Init()
{
	//����ͼƬ
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

	//��Ϸ��������
	width = 1000;//��
	height = 400;//��
	bottom = (height - 46) / 4;//�ذ�߶�����
	initgraph(width, height);//��ʼ������
	setaspectratio(4.0, 4.0);//���÷Ŵ����
	settextcolor(RGB(0, 0, 0));//�����������Ϊ��ɫ
	setbkcolor(RGB(177, 236, 240));//���û���������ɫ ǳ��

	//С����
	dino_width = 14;//��
	dino_height = 16;//��
	dino_Lfetx = width / 20;//ˮƽ���꣨���ң�
	dino_Topy = bottom - dino_height;//��ֱ����(����)
	dino_vx = 0;//ˮƽ�ٶ�
	dino_vy = 0;//��ֱ�ٶ�
	gravity = 0.25;//�������ٶ�
	ground_flag = 1;//��ʼλ�ڵ���
	ani = 0;

	//�ϰ���
	rec1_width = rec2_width = 16;//���
	rec1_height = rec2_height = 21;//�߶�
	rec1_Leftx = width / 4 - 25;//1����������
	rec_distance = 100;//���ϰ����ʼ����
	rec2_Leftx = rec1_Leftx + rec_distance;//2����������
	rec1_Topy = rec2_Topy = bottom - rec1_height;//��ֱ����(����)
	rec1_vx = rec2_vx = -2.5;//ˮƽ�ٶ�
	rec1_flag = rec2_flag = 0;//flag1>flag2˵��1��2֮��

	score = 0;//��ʼ����
	skill1 = 0; skill2 = 0;//�Ƿ��ü���1��2
	skill1_flag = 1;//�Ƿ����ʹ�ü���1
}

//���Ƴ�ʼҳ��
void pre_print()
{
	//��Ϸ��ʼ����
	putimage(0, 0, &im_bg);//���ر���ͼƬ
	settextstyle(15, 0, _T("Consolas"));//��������
	settextcolor(RGB(253, 138, 101));//����������ɫ

	//���logo����Ϸ����
	TCHAR Intro[30];
	wcscpy_s(Intro, _T("New Dinosaur"));
	int Intro_wid = width / 8 - textwidth(Intro) / 2;
	int Intro_hei = height / 8 - textheight(Intro);
	outtextxy(Intro_wid + 10, Intro_hei, Intro);
	PutPng(Intro_wid - dino_width * 2 + 10, Intro_hei - 1, &im_logo1, &im_logo2);//logo
	Sleep(1500);

	cleardevice();
	putimage(0, 0, &im_bg);//���ر���ͼƬ
	putimage(0, 0, &im_bg);//���Ʊ���
	putimage(cloud_x, 10, &im_cloud);//�����ƶ�1
	putimage(cloud_x2, 10 + 5, &im_cloud);//�����ƶ�2
	PutPng(dino_Lfetx, dino_Topy, &im_logo1, &im_logo2);//���ƿ���
	//���Ƶذ�
	for (int i = 0; i < width / 4 * 46; i++)
		putimage(i * 46, bottom, &im_ground);

	settextcolor(RGB(0, 0, 0));//����������ɫ
	settextstyle(8, 0, _T("����"));//��������
	//������ʾ����
	wcscpy_s(Intro, _T("��ʼ -   �ո�"));
	Intro_wid = width / 8 - textwidth(Intro) / 2;
	Intro_hei = height / 8 - textheight(Intro) * 2;
	outtextxy(Intro_wid, Intro_hei, Intro);
	wcscpy_s(Intro, _T("�̳� - press A"));
	Intro_hei = Intro_hei + textheight(Intro);
	outtextxy(Intro_wid, Intro_hei + 5, Intro);
	wcscpy_s(Intro, _T("�˳� - press B"));
	outtextxy(Intro_wid, Intro_hei + textheight(Intro) + 10, Intro);
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

//������Ϸ����
void End_game(int score)
{
	TCHAR tmp[20];
	swprintf_s(tmp, _T("Score:%d"), score);
	settextstyle(14, 0, _T("����"));
	outtextxy(width / 8 - textwidth(tmp) / 2, height / 8 - textheight(tmp), tmp);
	settextstyle(7, 0, _T("����"));
	wcscpy_s(tmp, _T("�ո�-���¿�ʼ��Ϸ"));
	outtextxy(width / 8 - textwidth(tmp) / 2, height / 8 + 0.5 * textheight(tmp), tmp);

	settextstyle(15, 0, _T("Consolas"));
	wcscpy_s(tmp, _T("made by zbwer"));
	settextstyle(7, 0, _T("����"));
	outtextxy(width / 8 - textwidth(tmp) / 2, height / 8 + 2 * textheight(tmp), tmp);
	settextstyle(15, 0, _T("Consolas"));
	input_key();
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
//������Ϸ����
void print_game()
{

	//���Ʊ���
	putimage(0, 0, &im_bg);
	putimage(cloud_x, 10, &im_cloud);
	putimage(cloud_x2, 10 + 5, &im_cloud);

	//���ƿ���
	if (ani <= 3) PutPng(dino_Lfetx, dino_Topy, &im_dino21, &im_dino22);
	else if (ani > 3 && ani <= 5) PutPng(dino_Lfetx, dino_Topy, &im_dino31, &im_dino32);
	else PutPng(dino_Lfetx, dino_Topy, &im_dino41, &im_dino42);

	//���Ƶذ�
	for (int i = 0; i < width / 46; i++)
		putimage(i * 46, bottom, &im_ground);

	//�����ϰ���
	putimage(rec1_Leftx, rec1_Topy, &im_Tree);
	putimage(rec2_Leftx, rec2_Topy, &im_Tree);
	//���Ʒ���
	TCHAR s[20];
	swprintf_s(s, _T("%d"), score);
	settextstyle(14, 0, _T("Consolas"));
	outtextxy(50 / 4, 30 / 4, s);
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
//�̳�
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
				//����� �� ������Ծ ȷ���ڵ��ϲ�������
				if ((int)input == 72 && ground_flag >= 1) {
					dino_vy = -5;
					ground_flag -= 1;
					skill1_flag = 0;
					flag1 = 0;
				}
				//����� �� �������������
				if ((int)input == 80) {
					dino_vy = 5;
					dino_vx = 0;
					flag2 = 0;
				}

				//����� �� ������ǰ����
				if ((int)input == 77) {
					dino_vx = 1;
					flag3 = 0;
					if (ground_flag >= 0 && skill1_flag == 0)
						dino_Lfetx += 10, skill1_flag = 1, flag5 = 0;
				}
				//����� �� ���Ƽ���
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
		print_game();//�����Ϸ����

		settextstyle(7, 0, _T("����"));
		if (flag1 == 1)	wcscpy_s(tmp, _T("�������  ������Ծ"));
		else if (flag2 == 1)	wcscpy_s(tmp, _T("��  ��������,����ˮƽ�ٶ�Ϊ0"));
		else if (flag3 == 1)	wcscpy_s(tmp, _T("�������  ����ˮƽ���Ҽ���,�¿�ֹͣ"));
		else if (flag4 == 1)	wcscpy_s(tmp, _T("�������  ����ˮƽ�������")), skill1 = 1;
		else if (flag5 == 1)	wcscpy_s(tmp, _T("�������  ����:���п�˲��"));
		else wcscpy_s(tmp, _T("�ո���ʽ��ʼ��Ϸ"));

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
	Init();//��ʼ������
	pre_print();//��ʼ����Ϸ����
	input_key();//�ȴ���������
	srand((int)time(0));
	closegraph();
	return 0;
}