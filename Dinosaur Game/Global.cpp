#include"StdHeader.h"
////////////////////////////////
//����ͼƬ�ز�

//logo�ز�
IMAGE im_logo1, im_logo2;

//����,��,�ذ�,��
IMAGE im_ground, im_Tree, im_bg, im_cloud;

//���������ز�
IMAGE im_dino21, im_dino22, im_dino31, im_dino32, im_dino41, im_dino42, im_fly1, im_fly2;

//��Ϸ���泤���Լ��ײ�����
double width, height, bottom;

//���������ĸ�������
double dino_width, dino_height, dino_Lfetx, dino_Topy;

//����ˮƽ��ֵ�ٶ�,�������ٶ�
double dino_vy, dino_vx, gravity;

//�ϰ���1��ز���
double rec1_width, rec1_height, rec1_Leftx, rec1_Topy, rec1_vx, rec_distance, rec1_flag;

//�ϰ���2��ز���
double rec2_width, rec2_height, rec2_Leftx, rec2_Topy, rec2_vx, rec2_flag;

//��Ϸ����,,������һ�׶εķ���,���ܿ����Ƿ���,�����Ƿ�λ�ڵ���
int score, tmpscore1 = 10, tmpscore2 = 25, ground_flag, skill1_flag, ani;

//�����ƶ�Ĳ���
double cloud_x = 220, cloud_x2 = 220 + 70;

//�Ƿ��ü���1�뼼��2,�Ƿ񲥷ŷ��趯��
int randwid[5] = { 80,32,48,16,64 }, skill1, skill2;


