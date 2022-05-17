<h1 align="center">🏆  Dinosaur-Game 🐋</h1>

## 💡 游戏介绍 

本游戏全程使用 Visual Stuido 2022 编写与封装,主要采用 C++ 的 EasyX 库文件.

游戏灵感来源于Chrome 的 Dino , 该项目仅作为本人第一次游戏编程练习所用.

## 🎯 玩法介绍

方向键上下左右控制 小恐龙 在游戏界面进行移动, 跳过迎面而来的障碍物以获得分数,分数达到一定程度可获得新技能,随着游戏的进行,障碍物的速度将越来越快。

该游戏没有设置胜利条件,游戏目标是尽可能获得更高的分数.

## 📚 实现思路

+ 物体的运动利用牛顿力学规律模拟,即<img src="http://latex.codecogs.com/gif.latex?\\x=x+v*\Delta t,vx=vx+a*\Delta t" style="border:none;">,取25毫秒为一个时间单位.游戏中小恐龙与障碍物的运动都是采用类似的写法实现.

+ EasyX 本身无法显示透明图片, 在导入图片素材时,采用源码图和掩码图叠加做 或运算 的方法即可.

+ 详细代码实现请见博客 [My Blog](https://zbwer.github.io/)(暂未更新)

## 📖 参考资料

1.  Easy X官方文档:https://docs.easyx.cn/zh-cn/intro
2.  童晶 《C和C++趣味游戏编程》
