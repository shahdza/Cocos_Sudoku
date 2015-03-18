#ifndef __AboutScene_H__
#define __AboutScene_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "cocos-ext.h"

using namespace cocos2d;
using namespace cocos2d::extension;


class AboutScene : public cocos2d::Layer
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
	CREATE_FUNC(AboutScene);

	//切换到主菜单
	void backToMenu(Ref* pSender, Control::EventType controlEvent);

	//切换内容
	void tbchange(Node * node, void * a);
	//按钮无效化
	void disable();
	//恢复按钮
	void enable();

	//点击事件
	void downaction(Ref * sender, Control::EventType controlEvent);
	void upinsideaction(Ref * sender, Control::EventType controlEvent);

	//生命周期
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
};

#endif // __AboutScene_H__
