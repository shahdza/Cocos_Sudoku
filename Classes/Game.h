#ifndef __GameScene_H__
#define __GameScene_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "cocos-ext.h"

using namespace cocos2d;
using namespace cocos2d::extension;


class GameScene : public cocos2d::Layer
{
public:
	// 这个是用来初始化函数的
	virtual bool init();
	// 设置一个静态的场景函数
	static cocos2d::Scene* createScene();
	// 设置一个菜单的回调函数。
	void menuCloseCallback(Ref* pSender);
	// 这个是一个创建对象的代码，他会自动创建对象，
	// 如果失败会自动回收内存，如果回收内存也失败的话，他会自动的删除对象。
	CREATE_FUNC(GameScene);

	int mult_penny; //金币倍数
	int mult_star;	//积分倍数
	int rest_time;	//剩余时间
	int past_time;	//已用时间
	int count;		//操作步数

	int cnt_addtime; //时间加长卡个数
	int cnt_hint; //提示道具个数

	//游戏音乐
	int musicslt; //1表示普通音乐 , 2表示时间快到时候的音乐
	void updateMusic();


	//使用道具
	void useAddTime(Ref * sender, Control::EventType controlEvent);
	void useHint(Ref * sender, Control::EventType controlEvent);

	//填数
	void clickNum(Ref * sender, Control::EventType controlEvent);
	void fillGrid(int num);
	//是否完成数独
	void isFinish();

	//检查九宫格状态是否合法
	void checkGrid();
	bool isIllegal(int x, int y); //格子[x,y]是否冲突

	//游戏暂停
	void gamePause(Ref * sender, Control::EventType controlEvent);

	//游戏结束 , 0表示失败 , 1表示胜利
	void gameEnd(int state);

	//计时器
	void updateGame(float tmd);

	//触屏事件
	virtual bool onTouchBegan(Touch * touch, Event * event);
	virtual void onTouchMoved(Touch * touch, Event * event);
	virtual void onTouchEnded(Touch * touch, Event * event);
	//获得触屏的位置是不是格子, 不是返回-1
	int get_tag(Touch *ctouch);


	//生命周期
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
};

#endif // __GameScene_H__
