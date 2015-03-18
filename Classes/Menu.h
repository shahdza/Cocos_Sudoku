#ifndef __MenuScene_H__
#define __MenuScene_H__

#include "cocos2d.h"

#include "Box2D/Box2D.h"

#include "SimpleAudioEngine.h"

#include "cocos-ext.h"

using namespace cocos2d;
using namespace cocos2d::extension;


class MenuScene : public cocos2d::Layer
{
public:
	// 这个是用来初始化函数的
	virtual bool init();
	// 设置一个静态的场景函数
	static cocos2d::Scene* createScene();
	// 这个是一个创建对象的代码，他会自动创建对象，
	// 如果失败会自动回收内存，如果回收内存也失败的话，他会自动的删除对象。
	CREATE_FUNC(MenuScene);


	bool isPause;

	//启动游戏
	void enterGameMenu(Ref* pSender);
	//关于游戏
	void enterAboutGame(Ref* pSender);
	//退出游戏
	void menuCloseCallback(Ref* pSender);


	//生命周期
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();

};

#endif // __MenuScene_H__
