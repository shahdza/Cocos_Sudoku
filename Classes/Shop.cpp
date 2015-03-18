// 2000

#include "Shop.h"
#include "GameMenu.h"
#include "Global.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;


#define music_click "music/click.wav"
#define music_error "music/error.wav"
#define music_buy "music/buyitem.wav"


// 设置一个静态的场景函数
Scene* ShopScene::createScene()
{
	// 给scene创建内容
	Scene *myscene = Scene::create();

	// 创建一个layer
	ShopScene *mylayer = ShopScene::create();

	// 把这个layer加入到scene中
	myscene->addChild(mylayer);

	// 返回scene
	return myscene;
}

// 初始化
bool ShopScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size mysize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//背景图片
	Sprite *pbg = Sprite::create("shop_bg.png");
	pbg->setPosition(Vec2(origin.x + mysize.width / 2, origin.y + mysize.height / 2));
	this->addChild(pbg, -1);

	//返回按钮
	Scale9Sprite *spback = Scale9Sprite::create("close.png");
	ControlButton *pbtbk = ControlButton::create(spback);
	pbtbk->setPosition(Vec2(origin.x + mysize.width - 20, origin.y + mysize.height - 25));
	pbtbk->setPreferredSize(Size(36, 36));
	pbtbk->addTargetWithActionForControlEvents(
		this,
		cccontrol_selector(ShopScene::backToMenu),
		Control::EventType::TOUCH_UP_INSIDE);
	this->addChild(pbtbk);


	//金币 , tag=3001
	Sprite *spmoney = Sprite::create("money.png");
	spmoney->setPosition(Vec2(origin.x + 30, origin.y + mysize.height - 25));
	this->addChild(spmoney);
	//金币数量
	Label *money = Label::createWithCharMap("digit.png", 20, 20, '0');
	money->setString(Global::shareGlobal()->getMoney().c_str());
	money->setPosition(Vec2(origin.x + 48, origin.y + mysize.height - 35));
	money->setAnchorPoint(Vec2(0, 0));
	money->setScale(0.9f);
	this->addChild(money, 1, 3001);


	//时限加长卡 800 , tag=3002
	Sprite *spadtm = Sprite::create("props_addtime.png");
	spadtm->setPosition(Vec2(origin.x + mysize.width / 2 - 100, origin.y + mysize.height / 2 + 50));
	this->addChild(spadtm);
	//数量
	Label *adtmcnt = Label::createWithCharMap("digit.png", 20, 20, '0');
	adtmcnt->setString(Global::shareGlobal()->getAddTime().c_str());
	adtmcnt->setPosition(Vec2(origin.x + mysize.width / 2 - 115, origin.y + mysize.height / 2 - 15));
	adtmcnt->setAnchorPoint(Vec2(0, 0));
	adtmcnt->setScale(0.9f);
	this->addChild(adtmcnt, 1, 3002);
	//购买按钮
	Scale9Sprite *spbuy1 = Scale9Sprite::create("800.png");
	ControlButton *pbtbuy1 = ControlButton::create(spbuy1);
	pbtbuy1->setPosition(Vec2(origin.x + mysize.width / 2 - 100, origin.y + mysize.height / 2 - 65));
	pbtbuy1->setPreferredSize(Size(80, 40));
	pbtbuy1->addTargetWithActionForControlEvents(
		this,
		cccontrol_selector(ShopScene::propsAddTime),
		Control::EventType::TOUCH_UP_INSIDE);
	this->addChild(pbtbuy1);

	//提示道具 500 , tag=3003
	Sprite *sphint = Sprite::create("props_hint.png");
	sphint->setPosition(Vec2(origin.x + mysize.width / 2 - 20, origin.y + mysize.height / 2 + 50));
	this->addChild(sphint);
	//数量
	Label *hintcnt = Label::createWithCharMap("digit.png", 20, 20, '0');
	hintcnt->setString(Global::shareGlobal()->getHint().c_str());
	hintcnt->setPosition(Vec2(origin.x + mysize.width / 2 - 35, origin.y + mysize.height / 2 - 15));
	hintcnt->setAnchorPoint(Vec2(0, 0));
	hintcnt->setScale(0.9f);
	this->addChild(hintcnt, 1, 3003);
	//购买按钮
	Scale9Sprite *spbuy2 = Scale9Sprite::create("500.png");
	ControlButton *pbtbuy2 = ControlButton::create(spbuy2);
	pbtbuy2->setPosition(Vec2(origin.x + mysize.width / 2 - 20, origin.y + mysize.height / 2 - 65));
	pbtbuy2->setPreferredSize(Size(80, 40));
	pbtbuy2->addTargetWithActionForControlEvents(
		this,
		cccontrol_selector(ShopScene::propsHint),
		Control::EventType::TOUCH_UP_INSIDE);
	this->addChild(pbtbuy2);
	//
	//双倍积分 1000 , tag=3004
	Sprite *spstar = Sprite::create("props_star.png");
	spstar->setPosition(Vec2(origin.x + mysize.width / 2 + 60, origin.y + mysize.height / 2 + 50));
	this->addChild(spstar);
	//数量
	Label *starcnt = Label::createWithCharMap("digit.png", 20, 20, '0');
	starcnt->setString(Global::shareGlobal()->getStar().c_str());
	starcnt->setPosition(Vec2(origin.x + mysize.width / 2 + 45, origin.y + mysize.height / 2 - 15));
	starcnt->setAnchorPoint(Vec2(0, 0));
	starcnt->setScale(0.9f);
	this->addChild(starcnt, 1, 3004);
	//购买按钮
	Scale9Sprite *spbuy3 = Scale9Sprite::create("1000.png");
	ControlButton *pbtbuy3 = ControlButton::create(spbuy3);
	pbtbuy3->setPosition(Vec2(origin.x + mysize.width / 2 + 60, origin.y + mysize.height / 2 - 65));
	pbtbuy3->setPreferredSize(Size(80, 40));
	pbtbuy3->addTargetWithActionForControlEvents(
		this,
		cccontrol_selector(ShopScene::propsStar),
		Control::EventType::TOUCH_UP_INSIDE);
	this->addChild(pbtbuy3);

	//双倍金币 200 , tag=3005
	Sprite *sppenny = Sprite::create("props_penny.png");
	sppenny->setPosition(Vec2(origin.x + mysize.width / 2 + 140, origin.y + mysize.height / 2 + 50));
	this->addChild(sppenny);
	//数量
	Label *pennycnt = Label::createWithCharMap("digit.png", 20, 20, '0');
	pennycnt->setString(Global::shareGlobal()->getPenny().c_str());
	pennycnt->setPosition(Vec2(origin.x + mysize.width / 2 + 125, origin.y + mysize.height / 2 - 15));
	pennycnt->setAnchorPoint(Vec2(0, 0));
	pennycnt->setScale(0.9f);
	this->addChild(pennycnt, 1, 3005);
	//购买按钮
	Scale9Sprite *spbuy4 = Scale9Sprite::create("200.png");
	ControlButton *pbtbuy4 = ControlButton::create(spbuy4);
	pbtbuy4->setPosition(Vec2(origin.x + mysize.width / 2 + 140, origin.y + mysize.height / 2 - 65));
	pbtbuy4->setPreferredSize(Size(80, 40));
	pbtbuy4->addTargetWithActionForControlEvents(
		this,
		cccontrol_selector(ShopScene::propsPenny),
		Control::EventType::TOUCH_UP_INSIDE);
	this->addChild(pbtbuy4);

	return true;
}



//菜单回调
void ShopScene::backToMenu(Ref* pSender, Control::EventType controlEvent)
{
	SimpleAudioEngine::getInstance()->playEffect(music_click);

	Scene *menuscene = GameMenuScene::createScene();
	auto *tt = TransitionFade::create(1.0f, menuscene);
	Director::getInstance()->replaceScene(tt);
}


//购买时限加长 800 , tag = 3002;
void ShopScene::propsAddTime(Ref* pSender, Control::EventType controlEvent)
{
	//道具已满
	if (Global::shareGlobal()->addtime == 99)
	{
		SimpleAudioEngine::getInstance()->playEffect(music_error);
		return;
	}

	if (Global::shareGlobal()->money >= 800)
	{
		SimpleAudioEngine::getInstance()->playEffect(music_buy);

		Global::shareGlobal()->money -= 800;
		Global::shareGlobal()->addtime++;
		Global::shareGlobal()->setMoney();
		Global::shareGlobal()->setAddTime();
		Label *lb1 = (Label *)this->getChildByTag(3001);
		Label *lb2 = (Label *)this->getChildByTag(3002);
		lb1->setString(Global::shareGlobal()->getMoney().c_str());
		lb2->setString(Global::shareGlobal()->getAddTime().c_str());
	}
	else
	{
		SimpleAudioEngine::getInstance()->playEffect(music_error);
		cocos2d::MessageBox("金币不足,请通过游戏获得!", "温馨提醒");
	}
}
//购买提示 500 , tag = 3002;
void ShopScene::propsHint(Ref* pSender, Control::EventType controlEvent)
{
	//道具已满
	if (Global::shareGlobal()->hint == 99)
	{
		SimpleAudioEngine::getInstance()->playEffect(music_error);
		return;
	}

	if (Global::shareGlobal()->money >= 500)
	{

		SimpleAudioEngine::getInstance()->playEffect(music_buy);

		Global::shareGlobal()->money -= 500;
		Global::shareGlobal()->hint++;
		Global::shareGlobal()->setMoney();
		Global::shareGlobal()->setHint();
		Label *lb1 = (Label *)this->getChildByTag(3001);
		Label *lb2 = (Label *)this->getChildByTag(3003);
		lb1->setString(Global::shareGlobal()->getMoney().c_str());
		lb2->setString(Global::shareGlobal()->getHint().c_str());
	}
	else
	{
		SimpleAudioEngine::getInstance()->playEffect(music_error);
		cocos2d::MessageBox("金币不足,请通过游戏获得!", "温馨提醒");
	}
}
//购买积分加倍 1000 , tag = 3004;
void ShopScene::propsStar(Ref* pSender, Control::EventType controlEvent)
{
	//道具已满
	if (Global::shareGlobal()->star == 99)
	{
		SimpleAudioEngine::getInstance()->playEffect(music_error);
		return;
	}

	if (Global::shareGlobal()->money >= 1000)
	{

		SimpleAudioEngine::getInstance()->playEffect(music_buy);

		Global::shareGlobal()->money -= 1000;
		Global::shareGlobal()->star++;
		Global::shareGlobal()->setMoney();
		Global::shareGlobal()->setStar();
		Label *lb1 = (Label *)this->getChildByTag(3001);
		Label *lb2 = (Label *)this->getChildByTag(3004);
		lb1->setString(Global::shareGlobal()->getMoney().c_str());
		lb2->setString(Global::shareGlobal()->getStar().c_str());
	}
	else
	{
		SimpleAudioEngine::getInstance()->playEffect(music_error);
		cocos2d::MessageBox("金币不足,请通过游戏获得!", "温馨提醒");
	}
}
//购买金币加倍 200 , tag = 3005;
void ShopScene::propsPenny(Ref* pSender, Control::EventType controlEvent)
{
	//道具已满
	if (Global::shareGlobal()->penny == 99)
	{
		SimpleAudioEngine::getInstance()->playEffect(music_error);
		return;
	}

	if (Global::shareGlobal()->money >= 200)
	{
		SimpleAudioEngine::getInstance()->playEffect(music_buy);

		Global::shareGlobal()->money -= 200;
		Global::shareGlobal()->penny++;
		Global::shareGlobal()->setMoney();
		Global::shareGlobal()->setPenny();
		Label *lb1 = (Label *)this->getChildByTag(3001);
		Label *lb2 = (Label *)this->getChildByTag(3005);
		lb1->setString(Global::shareGlobal()->getMoney().c_str());
		lb2->setString(Global::shareGlobal()->getPenny().c_str());
	}
	else
	{
		SimpleAudioEngine::getInstance()->playEffect(music_error);
		cocos2d::MessageBox("金币不足,请通过游戏获得!", "温馨提醒");
	}
}


//生命周期
void ShopScene::onEnter()
{
	Layer::onEnter();
}
void ShopScene::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();
}
void ShopScene::onExit()
{
	Layer::onExit();
}

void ShopScene::menuCloseCallback(Ref* pSender)
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

