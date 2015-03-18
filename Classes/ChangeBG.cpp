//6000

#include "ChangeBG.h"

#include "Game.h"
#include "Global.h"

#include "string"
#include "string.h"

using namespace std;

using namespace cocos2d;
using namespace CocosDenshion;


// 设置一个静态的场景函数
Scene* ChangeBGScene::createScene()
{
	// 给scene创建内容
	Scene *myscene = Scene::create();

	// 创建一个layer
	ChangeBGScene *mylayer = ChangeBGScene::create();

	// 把这个layer加入到scene中
	myscene->addChild(mylayer);

	// 返回scene
	return myscene;
}
Scene* ChangeBGScene::createScene(RenderTexture* sqr)
{
	Scene *myscene = Scene::create();

	Sprite *_spr = Sprite::createWithTexture(sqr->getSprite()->getTexture());
	_spr->setPosition(Vec2(240, 135));
	_spr->setFlippedY(true);
	_spr->setColor(Color3B::GRAY);
	myscene->addChild(_spr);

	ChangeBGScene* mylayer = ChangeBGScene::create();

	myscene->addChild(mylayer);

	return myscene;
}

// 初始化
bool ChangeBGScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Size mysize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//文字提示
	Sprite *lb = Sprite::create("changbg.png");
	lb->setPosition(Vec2(origin.x + mysize.width / 2, origin.y + mysize.height - 30));
	this->addChild(lb, 2);

	//四张背景图
	//1
	Scale9Sprite *sp1 = Scale9Sprite::create("11.png");
	ControlButton *pbt1 = ControlButton::create(sp1);
	pbt1->setPosition(Vec2(origin.x + mysize.width / 2 - 80, origin.y + mysize.height / 2 + 20));
	pbt1->setPreferredSize(Size(150, 84));
	this->addChild(pbt1, 2, 6001);
	//绑定事件
	pbt1->addTargetWithActionForControlEvents(
		this,
		cccontrol_selector(ChangeBGScene::changeBG),
		Control::EventType::TOUCH_UP_INSIDE);
	//2
	Scale9Sprite *sp2 = Scale9Sprite::create("22.png");
	ControlButton *pbt2 = ControlButton::create(sp2);
	pbt2->setPosition(Vec2(origin.x + mysize.width / 2 + 80, origin.y + mysize.height / 2 + 20));
	pbt2->setPreferredSize(Size(150, 84));
	this->addChild(pbt2, 2, 6002);
	//绑定事件
	pbt2->addTargetWithActionForControlEvents(
		this,
		cccontrol_selector(ChangeBGScene::changeBG),
		Control::EventType::TOUCH_UP_INSIDE);
	//3
	Scale9Sprite *sp3 = Scale9Sprite::create("33.png");
	ControlButton *pbt3 = ControlButton::create(sp3);
	pbt3->setPosition(Vec2(origin.x + mysize.width / 2 - 80, origin.y + mysize.height / 2 - 80));
	pbt3->setPreferredSize(Size(150, 84));
	this->addChild(pbt3, 2, 6003);
	//绑定事件
	pbt3->addTargetWithActionForControlEvents(
		this,
		cccontrol_selector(ChangeBGScene::changeBG),
		Control::EventType::TOUCH_UP_INSIDE);
	//4
	Scale9Sprite *sp4 = Scale9Sprite::create("44.png");
	ControlButton *pbt4 = ControlButton::create(sp4);
	pbt4->setPosition(Vec2(origin.x + mysize.width / 2 + 80, origin.y + mysize.height / 2 - 80));
	pbt4->setPreferredSize(Size(150, 84));
	this->addChild(pbt4, 2, 6004);
	//绑定事件
	pbt4->addTargetWithActionForControlEvents(
		this,
		cccontrol_selector(ChangeBGScene::changeBG),
		Control::EventType::TOUCH_UP_INSIDE);

	//返回菜单
	Scale9Sprite *spbk = Scale9Sprite::create("return.png");
	ControlButton *pbtbk = ControlButton::create(spbk);
	pbtbk->setPosition(Vec2(origin.x + mysize.width - 20, origin.y + mysize.height - 20));
	pbtbk->setPreferredSize(Size(36, 36));
	this->addChild(pbtbk, 2);
	//绑定事件
	pbtbk->addTargetWithActionForControlEvents(
		this,
		cccontrol_selector(ChangeBGScene::backToMenu),
		Control::EventType::TOUCH_UP_INSIDE);

	return true;
}

//更换背景
void ChangeBGScene::changeBG(Ref * sender, Control::EventType controlEvent)
{
	int i;
	Sprite* bg = Global::shareGlobal()->bg;

	for (i = 1; i <= 4; i++) {
		if (sender == this->getChildByTag(6000 + i)) break;
	}

	string s = "";
	s += (i + '0'); s += ".png";
	Texture2D *text2d = Director::getInstance()->getTextureCache()->addImage(s.c_str());
	bg->setTexture(text2d);

	Director::getInstance()->popScene();
	Director::getInstance()->popScene();

	Director::getInstance()->resume();
	SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}

//返回游戏菜单
void ChangeBGScene::backToMenu(Ref * sender, Control::EventType controlEvent)
{
	Director::getInstance()->popScene();
}


//生命周期
void ChangeBGScene::onEnter()
{
	Layer::onEnter();
}
void ChangeBGScene::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();
}
void ChangeBGScene::onExit()
{
	Layer::onExit();
}


void ChangeBGScene::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
#else
	//退出程序
	Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
#endif
}

