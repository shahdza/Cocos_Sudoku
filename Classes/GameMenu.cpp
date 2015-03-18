//4000

#include "GameMenu.h"

#include "Menu.h"
#include "Shop.h"
#include "Rank.h"
#include "Game.h"
#include "Global.h"

using namespace std;

//宏定义 using namespace cocos2d;
USING_NS_CC;
using namespace CocosDenshion;

#define music_game	"music/maplestory.wav"
#define music_click "music/click.wav"
#define music_start "music/start.wav"


// 设置一个静态的场景函数
Scene* GameMenuScene::createScene()
{
	// 给scene创建内容
	Scene *myscene = Scene::create();

	// 创建一个layer
	GameMenuScene *mylayer = GameMenuScene::create();

	// 把这个layer加入到scene中
	myscene->addChild(mylayer);

	// 返回scene
	return myscene;
}

// 初始化
bool GameMenuScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	SimpleAudioEngine::getInstance()->playBackgroundMusic(music_game);

	Size mysize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//背景图片
	Sprite *pbg = Sprite::create("war.png");
	pbg->setPosition(Vec2(origin.x + mysize.width / 2, origin.y + mysize.height / 2));
	this->addChild(pbg, -1);
	//卷轴背景
	Sprite *pbk = Sprite::create("game_back.png");
	pbk->setPosition(Vec2(origin.x + mysize.width / 2, origin.y + mysize.height / 2));
	this->addChild(pbk, 0);

	//从小到大打开卷轴
	pbk->setScaleX(0);
	auto *ac1 = ScaleTo::create(1.0f, 1.0f);
	auto *cq = Sequence::create(ac1, NULL);
	pbk->runAction(cq);

	//难度选择 4001 , 4002 , 4003 
	Sprite *pbt1 = Sprite::create("game_easy2.png");
	Sprite *pbt2 = Sprite::create("game_normal1.png");
	Sprite *pbt3 = Sprite::create("game_hard1.png");
	pbt1->setPosition(Vec2(origin.x + mysize.width / 2 - 120, origin.y + mysize.height / 2));
	pbt2->setPosition(Vec2(origin.x + mysize.width / 2, origin.y + mysize.height / 2));
	pbt3->setPosition(Vec2(origin.x + mysize.width / 2 + 120, origin.y + mysize.height / 2));
	this->addChild(pbt1, 2, 4001);
	this->addChild(pbt2, 2, 4002);
	this->addChild(pbt3, 2, 4003);
	selected = 4001;

	//渐显效果
	auto *acout1 = CCFadeOut::create(0.0f);
	auto *acout2 = CCFadeOut::create(0.0f);
	auto *acout3 = CCFadeOut::create(0.0f);
	auto *acin1 = CCFadeIn::create(1.0f);
	auto *acin2 = CCFadeIn::create(1.0f);
	auto *acin3 = CCFadeIn::create(1.0f);
	auto *acdy1 = DelayTime::create(0.6f);
	auto *acdy2 = DelayTime::create(0.8f);
	auto *acdy3 = DelayTime::create(1.0f);
	auto *cq1 = Sequence::create(acout1, acdy1, acin1, NULL);
	auto *cq2 = Sequence::create(acout2, acdy2, acin2, NULL);
	auto *cq3 = Sequence::create(acout3, acdy3, acin3, NULL);

	pbt1->runAction(cq1);
	pbt2->runAction(cq2);
	pbt3->runAction(cq3);


	//进入游戏
	Scale9Sprite *spet = Scale9Sprite::create("bt_startgame.png");
	ControlButton *pbtet = ControlButton::create(spet);
	pbtet->setPosition(Vec2(origin.x + mysize.width / 2, origin.y + 25));
	pbtet->setPreferredSize(Size(130, 35));
	pbtet->addTargetWithActionForControlEvents(
		this,
		cccontrol_selector(GameMenuScene::startGame),
		Control::EventType::TOUCH_UP_INSIDE);
	this->addChild(pbtet);
	//从小到大
	pbtet->setScale(0);
	auto *acenter1 = ScaleTo::create(0.5f, 1.2f);
	auto *acenterdy = DelayTime::create(0.1f);
	auto *acenter2 = ScaleTo::create(0.3f, 1.0f);
	auto *cqenter = Sequence::create(acenter1, acenterdy, acenter2, NULL);
	pbtet->runAction(cqenter);

	//返回按钮
	Scale9Sprite *spback = Scale9Sprite::create("return.png");
	ControlButton *pbtbk = ControlButton::create(spback);
	pbtbk->setPosition(Vec2(origin.x + mysize.width - 20, origin.y + mysize.height - 25));
	pbtbk->setPreferredSize(Size(36, 36));
	pbtbk->addTargetWithActionForControlEvents(
		this,
		cccontrol_selector(GameMenuScene::backToMenu),
		Control::EventType::TOUCH_UP_INSIDE);
	this->addChild(pbtbk);

	//购物车
	Scale9Sprite *spcart = Scale9Sprite::create("cart.png");
	ControlButton *pbtcart = ControlButton::create(spcart);
	pbtcart->setPosition(Vec2(origin.x + 30, origin.y + mysize.height - 25));
	pbtcart->setPreferredSize(Size(36, 36));
	pbtcart->addTargetWithActionForControlEvents(
		this,
		cccontrol_selector(GameMenuScene::enterShop),
		Control::EventType::TOUCH_UP_INSIDE);
	this->addChild(pbtcart);

	//金币
	Sprite *spmoney = Sprite::create("money.png");
	spmoney->setPosition(Vec2(origin.x + 72, origin.y + mysize.height - 25));
	this->addChild(spmoney);
	//金币数量
	Label *money = Label::createWithCharMap("digit.png", 20, 20, '0');
	money->setString(Global::shareGlobal()->getMoney().c_str());
	money->setPosition(Vec2(origin.x + 90, origin.y + mysize.height - 35));
	money->setAnchorPoint(Vec2(0, 0));
	money->setScale(0.9f);
	this->addChild(money);

	//排行榜
	Scale9Sprite *spward = Scale9Sprite::create("ward.png");
	ControlButton *pbtward = ControlButton::create(spward);
	pbtward->setPosition(Vec2(origin.x + mysize.width / 2, origin.y + mysize.height - 25));
	pbtward->setPreferredSize(Size(40, 40));
	pbtward->addTargetWithActionForControlEvents(
		this,
		cccontrol_selector(GameMenuScene::enterRank),
		Control::EventType::TOUCH_UP_INSIDE);
	this->addChild(pbtward);


	//注册触摸事件
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(GameMenuScene::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(GameMenuScene::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(GameMenuScene::onTouchEnded, this);
	dispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	return true;
}


//进入游戏
void GameMenuScene::startGame(Ref* sender, Control::EventType controlEvent)
{
	SimpleAudioEngine::getInstance()->playEffect(music_start);

	//记录数独的难度
	Global::shareGlobal()->degree = (selected - 4000);

	//进入游戏
	Scene *gamescene = GameScene::createScene();
	auto *tt = TransitionFade::create(2.0f, gamescene);
	Director::getInstance()->replaceScene(tt);
}

//进入商城
void GameMenuScene::enterShop(Ref* sender, Control::EventType controlEvent)
{
	SimpleAudioEngine::getInstance()->playEffect(music_click);

	Scene *shopscene = ShopScene::createScene();
	auto *tt = TransitionFade::create(1.0f, shopscene);
	Director::getInstance()->replaceScene(tt);
}

//进入排行榜
void GameMenuScene::enterRank(Ref* sender, Control::EventType controlEvent)
{
	SimpleAudioEngine::getInstance()->playEffect(music_click);

	Scene *rankscene = RankScene::createScene();
	auto *tt = TransitionFade::create(1.0f, rankscene);
	Director::getInstance()->replaceScene(tt);
}

//菜单回调
void GameMenuScene::backToMenu(Ref* sender, Control::EventType controlEvent)
{
	SimpleAudioEngine::getInstance()->playEffect(music_click);

	Scene *menuscene = MenuScene::createScene();
	auto *tt = TransitionFade::create(1.0f, menuscene);
	Director::getInstance()->replaceScene(tt);
}

//返回被选中的关卡
int GameMenuScene::get_tag(Touch *ctouch)
{
	int ch = -1;
	Vec2 ptouch = ctouch->getLocation();
	for (int i = 4001; i <= 4003; i++) {
		Sprite *sp = (Sprite *)this->getChildByTag(i);
		int maxx = sp->getPositionX() + 50;
		int minx = sp->getPositionX() - 50;
		int maxy = sp->getPositionY() + 75;
		int miny = sp->getPositionY() - 75;
		if ((ptouch.x > minx&&ptouch.x<maxx) && (ptouch.y>miny&&ptouch.y < maxy))
		{
			ch = i;
			break;
		}
	}
	return ch;
}

//返回难度对于的图片
string GameMenuScene::get_pic(int tag, int state)
{
	string pic = "";
	if (tag == 4001)
	{
		pic = "game_easy";
	}
	else if (tag == 4002)
	{
		pic = "game_normal";
	}
	else if (tag == 4003)
	{
		pic = "game_hard";
	}
	pic += (state + '0');
	pic += ".png";
	return pic;
}



//开始触屏
bool GameMenuScene::onTouchBegan(Touch * ctouch, Event * event)
{
	int ch = get_tag(ctouch);

	if (ch == -1) return false;
	//放大
	Sprite *sp = (Sprite *)this->getChildByTag(ch);
	sp->setScale(1.1f);

	return true;
}
//移动触屏
void GameMenuScene::onTouchMoved(Touch * ctouch, Event * event)
{
	int ch = get_tag(ctouch);
	for (int i = 4001; i <= 4003; i++)
	{
		Sprite *sp = (Sprite *)this->getChildByTag(i);
		sp->setScale(1.0f);
	}

	if (ch == -1) return;

	//放大
	Sprite *sp = (Sprite *)this->getChildByTag(ch);
	sp->setScale(1.1f);
}
//结束触屏
void GameMenuScene::onTouchEnded(Touch * ctouch, Event * event)
{

	SimpleAudioEngine::getInstance()->playEffect(music_click);

	int ch = get_tag(ctouch);
	for (int i = 4001; i <= 4003; i++)
	{
		Sprite *sp = (Sprite *)this->getChildByTag(i);
		sp->setScale(1.0f);
	}

	if (ch == -1) return;


	//将之前选中的变暗
	Sprite *sp1 = (Sprite *)this->getChildByTag(selected);
	Texture2D *text2d = Director::getInstance()->getTextureCache()->addImage(get_pic(selected, 1).c_str());
	sp1->setTexture(text2d);

	//将现在选中的变亮
	Sprite *sp2 = (Sprite *)this->getChildByTag(ch);
	Texture2D *text2d2 = Director::getInstance()->getTextureCache()->addImage(get_pic(ch, 2).c_str());
	sp2->setTexture(text2d2);

	selected = ch;
}

//生命周期
void GameMenuScene::onEnter()
{
	Layer::onEnter();
}
void GameMenuScene::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();
}
void GameMenuScene::onExit()
{
	Layer::onExit();
}

//结束游戏
void GameMenuScene::menuCloseCallback(Ref* pSender)
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
