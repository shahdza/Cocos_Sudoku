#ifndef __GameOverScene_H__
#define __GameOverScene_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "cocos-ext.h"

using namespace cocos2d;
using namespace cocos2d::extension;


class GameOverScene : public cocos2d::Layer
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
	CREATE_FUNC(GameOverScene);


	//绘制胜利画面
	void drawWin();
	//绘制失败画面
	void drawLose();

	//再玩一次
	void playAgain(Ref * sender, Control::EventType controlEvent);
	//返回游戏菜单
	void backToMenu(Ref * sender, Control::EventType controlEvent);

	//生命周期
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
};

#endif // __GameOverScene_H__
