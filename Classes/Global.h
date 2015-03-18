#ifndef __Global_H__
#define __Global_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "cocos-ext.h"
#include "DancingLinks.h"

using namespace cocos2d;
using namespace cocos2d::extension;


class Global : public cocos2d::Layer
{
private:
	Global();
	~Global();

	struct Grid  {
		int num;
		bool issysnum;
		bool isSysNum() { return issysnum; }
	};

	struct RankSet  {
		int t;
		int num;
		int score;
		void init() { t = 0; num = 0; score = 0; }
		friend bool operator<(const RankSet &a, const RankSet &b) {
			if (a.score != b.score) return a.score>b.score;
			if (b.t != b.t) return a.t < b.t;
			return a.num < b.num;
		}
	}rk[1000];

public:
	//创建一个全局访问点
	static Global* shareGlobal();


	//数独相关
	int degree;			//选择的难度系数
	int selected;		//被选中的格子
	Grid grid[9][9];	//数独盘面
	int ans[9][9];		//解数组
	DLX dlx;			//dancinglinks类
	//生成数独盘面
	void createAnswer(); //随机化,生成数独终盘
	void createQuestion(); //生成唯一解的数独盘局
	void createSudoku(); //创建数独

	//游戏中的背景图片
	Sprite* bg;
	//游戏相关数据
	bool isWin;		//是否胜利
	int mult_penny; //金币倍数
	int mult_star;	//积分倍数
	int rest_time;	//剩余时间
	int past_time;	//已用时间
	int count;		//操作步数

	//金币道具
	int money; //金币
	int addtime; //时限加长
	int hint; //提示
	int star; //积分加倍
	int penny; //金币加倍
	string getMoney();
	string getAddTime();
	string getHint();
	string getStar();
	string getPenny();
	void setMoney();
	void setAddTime();
	void setHint();
	void setStar();
	void setPenny();

	//整形转字符串
	string iToS(int x, int len);
	//整形转字符串
	int sToI(string str);
	//更新排行榜
	int updateRank(string info, string opt);
};

#endif // __Global_H__
