//1000

#include "About.h"

#include "Menu.h"

using namespace cocos2d;
using namespace CocosDenshion;

#define music_click "music/click.wav"


// 设置一个静态的场景函数
Scene* AboutScene::createScene()
{
	// 给scene创建内容
	Scene *myscene = Scene::create();

	// 创建一个layer
	AboutScene *mylayer = AboutScene::create();

	// 把这个layer加入到scene中
	myscene->addChild(mylayer);

	// 返回scene
	return myscene;
}


// 初始化
bool AboutScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size mysize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//背景图片
	Sprite *pbg = Sprite::create("about_bg.png");
	pbg->setPosition(Vec2(origin.x + mysize.width / 2, origin.y + mysize.height / 2));
	this->addChild(pbg, 0);

	//显示内容的精灵 tag = 1005
	Sprite *ptb = Sprite::create("about_sudoku.png");
	ptb->setPosition(Vec2(origin.x + mysize.width / 2 + 20, origin.y + mysize.height / 2));
	this->addChild(ptb, 2, 1005);


	//数独介绍 tag = 1001
	Scale9Sprite *sp1 = Scale9Sprite::create("bt_sudoku.png");
	ControlButton *pbt1 = ControlButton::create(sp1);
	pbt1->setPosition(Vec2(origin.x + 40, origin.y + mysize.height - 45));
	pbt1->setPreferredSize(Size(70, 40));
	//游戏规则 tag = 1002
	Scale9Sprite *sp2 = Scale9Sprite::create("bt_rule.png");
	ControlButton *pbt2 = ControlButton::create(sp2);
	pbt2->setPosition(Vec2(origin.x + 40, origin.y + mysize.height - 105));
	pbt2->setPreferredSize(Size(70, 40));
	//道具介绍 tag = 1003
	Scale9Sprite *sp3 = Scale9Sprite::create("bt_props.png");
	ControlButton *pbt3 = ControlButton::create(sp3);
	pbt3->setPosition(Vec2(origin.x + 40, origin.y + mysize.height - 165));
	pbt3->setPreferredSize(Size(70, 40));
	//关于 tag = 1004
	Scale9Sprite *sp4 = Scale9Sprite::create("bt_me.png");
	ControlButton *pbt4 = ControlButton::create(sp4);
	pbt4->setPosition(Vec2(origin.x + 40, origin.y + mysize.height - 225));
	pbt4->setPreferredSize(Size(70, 40));

	//绑定事件
	pbt1->addTargetWithActionForControlEvents(
		this,
		cccontrol_selector(AboutScene::upinsideaction),
		Control::EventType::TOUCH_UP_INSIDE);
	pbt2->addTargetWithActionForControlEvents(
		this,
		cccontrol_selector(AboutScene::upinsideaction),
		Control::EventType::TOUCH_UP_INSIDE);
	pbt3->addTargetWithActionForControlEvents(
		this,
		cccontrol_selector(AboutScene::upinsideaction),
		Control::EventType::TOUCH_UP_INSIDE);
	pbt4->addTargetWithActionForControlEvents(
		this,
		cccontrol_selector(AboutScene::upinsideaction),
		Control::EventType::TOUCH_UP_INSIDE);

	this->addChild(pbt1, 2, 1001);
	this->addChild(pbt2, 2, 1002);
	this->addChild(pbt3, 2, 1003);
	this->addChild(pbt4, 2, 1004);


	//返回按钮
	Scale9Sprite *spback = Scale9Sprite::create("return.png");
	ControlButton *pbtbk = ControlButton::create(spback);
	pbtbk->setPosition(Vec2(origin.x + mysize.width - 20, origin.y + mysize.height - 25));
	pbtbk->setPreferredSize(Size(36, 36));
	pbtbk->addTargetWithActionForControlEvents(
		this,
		cccontrol_selector(AboutScene::backToMenu),
		Control::EventType::TOUCH_UP_INSIDE);
	this->addChild(pbtbk, 3);


	//云彩
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("yun.plist");
	Sprite *pyc1 = Sprite::createWithSpriteFrameName("y1.png");
	Sprite *pyc2 = Sprite::createWithSpriteFrameName("y2.png");
	Sprite *pyc3 = Sprite::createWithSpriteFrameName("y3.png");
	Sprite *pyc4 = Sprite::createWithSpriteFrameName("y4.png");

	pyc1->setPosition(Vec2(origin.x + mysize.width / 2 - 150, origin.y + mysize.height - 70));
	pyc2->setPosition(Vec2(origin.x + mysize.width / 2 - 400, origin.y + mysize.height - 75));
	pyc3->setPosition(Vec2(origin.x + mysize.width / 2 + 50, origin.y + mysize.height - 80));
	pyc4->setPosition(Vec2(origin.x + mysize.width / 2 + 150, origin.y + mysize.height - 60));

	pyc1->setScale(0.2f);
	pyc2->setScale(0.35f);
	pyc3->setScale(0.3f);
	pyc4->setScale(0.5f);

	this->addChild(pyc1, 1);
	this->addChild(pyc2, 1);
	this->addChild(pyc3, 1);
	this->addChild(pyc4, 1);

	auto *acyunle1 = MoveTo::create(0.0f, Vec2(origin.x - 100, origin.y + mysize.height - 70));
	auto *acyunle2 = MoveTo::create(0.0f, Vec2(origin.x - 100, origin.y + mysize.height - 75));
	auto *acyunle3 = MoveTo::create(0.0f, Vec2(origin.x - 100, origin.y + mysize.height - 80));
	auto *acyunle4 = MoveTo::create(0.0f, Vec2(origin.x - 100, origin.y + mysize.height - 60));

	auto *acyunri1 = MoveTo::create(25.0f, Vec2(origin.x + mysize.width + 100, origin.y + mysize.height - 70));
	auto *acyunri2 = MoveTo::create(53.0f, Vec2(origin.x + mysize.width + 100, origin.y + mysize.height - 75));
	auto *acyunri3 = MoveTo::create(37.0f, Vec2(origin.x + mysize.width + 100, origin.y + mysize.height - 80));
	auto *acyunri4 = MoveTo::create(33.0f, Vec2(origin.x + mysize.width + 100, origin.y + mysize.height - 60));

	auto *acyun1 = Sequence::create(acyunri1, acyunle1, NULL);
	auto *acyun2 = Sequence::create(acyunri2, acyunle2, NULL);
	auto *acyun3 = Sequence::create(acyunri3, acyunle3, NULL);
	auto *acyun4 = Sequence::create(acyunri4, acyunle4, NULL);

	auto *doyun1 = RepeatForever::create(acyun1);
	auto *doyun2 = RepeatForever::create(acyun2);
	auto *doyun3 = RepeatForever::create(acyun3);
	auto *doyun4 = RepeatForever::create(acyun4);

	pyc1->runAction(doyun1);
	pyc2->runAction(doyun2);
	pyc3->runAction(doyun3);
	pyc4->runAction(doyun4);

	//创建下雨特效, CCParticleRain
	auto *p1 = ParticleRain::create();
	p1->setAutoRemoveOnFinish(true);
	p1->setSpeed(1.0f);
	p1->setPositionType(ParticleSystem::PositionType::FREE);
	p1->setPosition(Vec2(mysize.width / 2 - 50, mysize.height - 80));
	this->addChild(p1);


	return true;
}


void AboutScene::menuCloseCallback(Ref* pSender)
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


//返回主菜单
void AboutScene::backToMenu(Ref* pSender, Control::EventType controlEvent)
{
	SimpleAudioEngine::getInstance()->playEffect(music_click);
	//翻页切换
	Scene *menuscene = MenuScene::createScene();
	auto *tt = CCTransitionPageTurn::create(0.5f, menuscene, true);
	Director::getInstance()->replaceScene(tt);
}


void AboutScene::downaction(Ref * sender, Control::EventType controlEvent)
{

}
void AboutScene::upinsideaction(Ref * sender, Control::EventType controlEvent)
{
	SimpleAudioEngine::getInstance()->playEffect(music_click);

	Size mysize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	int tb = 1001;
	if (sender == this->getChildByTag(1001))  //数独介绍
	{
		tb = 1001;
	}
	else if (sender == this->getChildByTag(1002))  //游戏规则
	{
		tb = 1002;
	}
	else if (sender == this->getChildByTag(1003)) //游戏道具
	{
		tb = 1003;
	}
	else if (sender == this->getChildByTag(1004)) //关于
	{
		tb = 1004;
	}

	Sprite *ptb = (Sprite *)this->getChildByTag(1005);

	//淡出
	auto *ac1 = FadeOut::create(0.5f);
	auto *ac2 = MoveTo::create(0.5f, Vec2(origin.x + mysize.width / 2 + 30, origin.y + mysize.height / 2));
	auto *act1 = Spawn::create(ac1, ac2, NULL);

	//切换, 无效化/恢复按钮
	auto * change = CallFuncN::create(CC_CALLBACK_1(AboutScene::tbchange, this, (void *)tb));
	CallFunc * no = CallFunc::create(CC_CALLBACK_0(AboutScene::disable, this));
	CallFunc * yes = CallFunc::create(CC_CALLBACK_0(AboutScene::enable, this));

	//淡入
	auto *ac3 = FadeIn::create(0.5f);
	auto *ac4 = MoveTo::create(0.5f, Vec2(origin.x + mysize.width / 2 + 20, origin.y + mysize.height / 2));
	auto *act2 = Spawn::create(ac4, ac3, NULL);

	//淡入淡出的动作
	auto *act3 = Sequence::create(no, act1, change, act2, yes, NULL);
	ptb->runAction(act3);
}

//切换内容
void AboutScene::tbchange(Node * node, void *a)
{
	int op = (int)a;
	char tb[111];
	Sprite *ptb = (Sprite *)node;
	if (op == 1001) //数独介绍
	{
		strcpy(tb, "about_sudoku.png");
	}
	else if (op == 1002) //游戏规则
	{
		strcpy(tb, "about_rule.png");
	}
	else if (op == 1003) //游戏道具
	{
		strcpy(tb, "about_props.png");
	}
	else if (op == 1004) //关于
	{
		strcpy(tb, "about_me.png");
	}
	// 切换
	Texture2D *text2d = Director::getInstance()->getTextureCache()->addImage(tb);
	ptb->setTexture(text2d);
}

//使按钮无效化
void AboutScene::disable()
{
	for (int i = 1001; i <= 1004; i++)
	{
		ControlButton *bt = (ControlButton *)this->getChildByTag(i);
		bt->setEnabled(false);
	}
}

//恢复按钮
void AboutScene::enable()
{
	for (int i = 1001; i <= 1004; i++)
	{
		ControlButton *bt = (ControlButton *)this->getChildByTag(i);
		bt->setEnabled(true);
	}
}



//生命周期 onEnter / onEnterTransitionDidFinish / onExit
void AboutScene::onEnter()
{
	Layer::onEnter();
}

void AboutScene::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();
}

void AboutScene::onExit()
{
	Layer::onExit();
	this->removeAllChildrenWithCleanup(true);
}
