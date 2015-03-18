#include "Global.h"

//宏定义 using namespace cocos2d;
USING_NS_CC;
using namespace CocosDenshion;


//
static Global* m_global = NULL;

Global* Global::shareGlobal()
{
	if (m_global == NULL)
	{
		m_global = new Global();
	}
	return m_global;
}

//构造函数
Global::Global()
{
	money = CCUserDefault::sharedUserDefault()->getIntegerForKey("money", 0);
	addtime = CCUserDefault::sharedUserDefault()->getIntegerForKey("addtime", 0);
	hint = CCUserDefault::sharedUserDefault()->getIntegerForKey("hint", 0);
	star = CCUserDefault::sharedUserDefault()->getIntegerForKey("star", 0);
	penny = CCUserDefault::sharedUserDefault()->getIntegerForKey("penny", 0);
	setMoney();
	setAddTime();
	setHint();
	setPenny();
	CCUserDefault::sharedUserDefault()->flush();
}
//析构函数
Global::~Global()
{

}

//整形转字符串
string Global::iToS(int x, int len)
{
	string str = "";
	if (x == 0) str = "0";
	while (x)
	{
		str += (x % 10 + '0');
		x /= 10;
	}
	if (len > (int)str.length())
	{
		for (int i = len - str.length(); i > 0; i--) str += "0";
	}
	reverse(str.begin(), str.end());
	return str;
}
//整形转字符串
int Global::sToI(string str)
{
	int x = 0;
	for (int i = 0; str[i]; i++)
	{
		x = x * 10 + (str[i] - '0');
	}
	return x;
}

//金币
string Global::getMoney()
{
	string str = "000000";
	int x = money, i = 5;
	while (x)
	{
		str[i--] = (x % 10 + '0');
		x /= 10;
	}
	return str;
}
void Global::setMoney()
{
	CCUserDefault::sharedUserDefault()->setIntegerForKey("money", money);
	CCUserDefault::sharedUserDefault()->flush();
}

//时限加长
string Global::getAddTime()
{
	string str = "00";
	int x = addtime, i = 1;
	while (x)
	{
		str[i--] = (x % 10 + '0');
		x /= 10;
	}
	return str;
}
void Global::setAddTime()
{
	CCUserDefault::sharedUserDefault()->setIntegerForKey("addtime", addtime);
	CCUserDefault::sharedUserDefault()->flush();
}

//提示
string Global::getHint()
{
	string str = "00";
	int x = hint, i = 1;
	while (x)
	{
		str[i--] = (x % 10 + '0');
		x /= 10;
	}
	return str;
}
void Global::setHint()
{
	CCUserDefault::sharedUserDefault()->setIntegerForKey("hint", hint);
	CCUserDefault::sharedUserDefault()->flush();
}

//积分加倍
string Global::getStar()
{
	string str = "00";
	int x = star, i = 1;
	while (x)
	{
		str[i--] = (x % 10 + '0');
		x /= 10;
	}
	return str;
}

void Global::setStar()
{
	CCUserDefault::sharedUserDefault()->setIntegerForKey("star", star);
	CCUserDefault::sharedUserDefault()->flush();
}

//金币加倍
string Global::getPenny()
{
	string str = "00";
	int x = penny, i = 1;
	while (x)
	{
		str[i--] = (x % 10 + '0');
		x /= 10;
	}
	return str;
}
void Global::setPenny()
{
	CCUserDefault::sharedUserDefault()->setIntegerForKey("penny", penny);
	CCUserDefault::sharedUserDefault()->flush();
}


//更新排行榜
//info 为通关信息: 时间,步数,得分
//opt 为难度分类
int Global::updateRank(string info, string opt)
{
	int i, j = 0, rank = 1;
	int t = 0;
	int num = 0;
	int score = 0;
	int cnt = CCUserDefault::sharedUserDefault()->getIntegerForKey(opt.c_str(), 0);

	while (info[j] != ' ') t = t * 10 + (info[j++] - '0'); j++;		//获得时间
	while (info[j] != ' ') num = num * 10 + (info[j++] - '0'); j++;	//获得步数
	while (j < (int)info.length()) score = score * 10 + (info[j++] - '0');//获得分数

	for (i = 0; i < cnt; i++)
	{
		string id = opt + "_" + Global::iToS(i + 1, 0);
		string str = CCUserDefault::sharedUserDefault()->getStringForKey(id.c_str(), "0 0 0");

		j = 0;
		rk[i].init();
		while (str[j] != ' ') rk[i].t = rk[i].t * 10 + (str[j++] - '0'); j++;		//获得时间
		while (str[j] != ' ') rk[i].num = rk[i].num * 10 + (str[j++] - '0'); j++;	//获得步数
		while (j<(int)str.length()) rk[i].score = rk[i].score * 10 + (str[j++] - '0');//获得分数

		if (score<rk[i].score) rank++;
		else if (score == rk[i].score && t>rk[i].t) rank++;
		else if (score == rk[i].score && t == rk[i].t && num>rk[i].num) rank++;
	}

	//插入本场游戏的数据
	rk[cnt].t = t;
	rk[cnt].num = num;
	rk[cnt].score = score;
	cnt++;
	//排序
	sort(rk, rk + cnt);

	CCUserDefault::sharedUserDefault()->setIntegerForKey(opt.c_str(), cnt);
	for (int i = 0; i < cnt; i++)
	{
		string id = opt + "_" + Global::iToS(i + 1, 0);
		string val = Global::iToS(rk[i].t, 0) + " " + Global::iToS(rk[i].num, 0) + " " + Global::iToS(rk[i].score, 0);
		CCUserDefault::sharedUserDefault()->setStringForKey(id.c_str(), val);
	}
	CCUserDefault::sharedUserDefault()->flush();

	return rank;
}

//随机化,生成数独终盘
void Global::createAnswer()
{
	int g[10][10];
	do {
		memset(g, 0, sizeof(g));
		for (int i = 1; i <= 9; i++) { //随机生成种子数
			int j = rand() % 9 + 1;
			g[i][j] = rand() % 9 + 1;
		}
		dlx.solve(g); //利用DLX找到一个终盘
	} while (dlx.cnt == 0); //若找到解,则退出循环

	//保存数独的解,即终盘
	for (int i = 1; i <= 9; i++) {
		for (int j = 1; j <= 9; j++) {
			ans[i - 1][j - 1] = dlx.ans[i][j];
		}
	}
}

//生成唯一解的数独盘局
void Global::createQuestion()
{
	int hole;
	int g[10][10];
	int d[90];
	for (int i = 1; i <= 81; i++) d[i] = i; //9*9的格子,随机挖洞种子

	if (degree == 1) { //简单 , 25~30个空
		hole = 27 + rand() % 5;
	}
	else if (degree == 2) { //普通 , 38~42个空
		hole = 40 + rand() % 3;
	}
	else { //困难 , 50~55个空
		hole = 50 + rand() % 3;
	}

	do {
		random_shuffle(d + 1, d + 1 + 81); //随机打乱顺序
		for (int i = 1; i <= 9; i++)
		for (int j = 1; j <= 9; j++) g[i][j] = ans[i - 1][j - 1];

		for (int i = 1; i <= hole; i++) { //随机挖洞
			int x = (d[i] - 1) / 9;
			int y = (d[i] - 1) % 9;
			g[x + 1][y + 1] = 0; //0表示挖空
		}
		dlx.solve(g); //dlx求解数独
	} while (dlx.cnt != 1); //解是否唯一

	//保存唯一解的数独盘面
	for (int i = 1; i <= 9; i++) {
		for (int j = 1; j <= 9; j++) {
			grid[i - 1][j - 1].num = g[i][j];
			if (g[i][j] == 0) { //待填数字 , 空
				grid[i - 1][j - 1].issysnum = false;
			}
			else { //系统数字
				grid[i - 1][j - 1].issysnum = true;
			}
		}
	}
}


//根据难度生成数独盘面
void Global::createSudoku()
{
	createAnswer();
	createQuestion();
}
