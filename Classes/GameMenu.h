#ifndef __GameMenuScene_H__
#define __GameMenuScene_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "cocos-ext.h"

using namespace cocos2d;
using namespace cocos2d::extension;
using namespace std;


class GameMenuScene : public cocos2d::Layer
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
	CREATE_FUNC(GameMenuScene);


	int selected; //选择难度
	int money; //金币数量


	//返回菜单
	void backToMenu(Ref * sender, Control::EventType controlEvent);
	//开始游戏
	void startGame(Ref * sender, Control::EventType controlEvent);
	//进入商店
	void enterShop(Ref * sender, Control::EventType controlEvent);
	//进入排行榜
	void enterRank(Ref * sender, Control::EventType controlEvent);


	//触屏事件
	virtual bool onTouchBegan(Touch * touch, Event * event);
	virtual void onTouchMoved(Touch * touch, Event * event);
	virtual void onTouchEnded(Touch * touch, Event * event);
	//被选中的难度编号
	int get_tag(Touch *ctouch);
	//获得要修改的图片
	string get_pic(int tag, int state);


	//生命周期
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
};

#endif // __GameMenuScene_H__
