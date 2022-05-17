#pragma once
#include"StdHeader.h"
////////////////////////////////
//定义图片素材

//logo素材
extern IMAGE im_logo1, im_logo2;

//背景,树,地板,云
extern IMAGE im_ground, im_Tree, im_bg, im_cloud;

//恐龙动作素材
extern IMAGE im_dino21, im_dino22, im_dino31, im_dino32, im_dino41, im_dino42, im_fly1, im_fly2;

//游戏画面长宽以及底部设置
extern double width, height, bottom;

//恐龙矩形四个点坐标
extern double dino_width, dino_height, dino_Lfetx, dino_Topy;

//恐龙水平数值速度,重力加速度
extern double dino_vy, dino_vx, gravity;

//障碍物1相关参数
extern double rec1_width, rec1_height, rec1_Leftx, rec1_Topy, rec1_vx, rec_distance, rec1_flag;

//障碍物2相关参数
extern double rec2_width, rec2_height, rec2_Leftx, rec2_Topy, rec2_vx, rec2_flag;

//游戏分数,,进入下一阶段的分数,技能开启是否开启,恐龙是否位于地面
extern int score, tmpscore1, tmpscore2, ground_flag, skill1_flag, ani;

//背景云朵的参数
extern double cloud_x, cloud_x2;

//是否获得技能1与技能2,是否播放飞翔动画
extern int randwid[5], skill1, skill2;


