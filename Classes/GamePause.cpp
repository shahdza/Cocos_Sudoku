#include "GamePause.h"


#include "GameMenu.h"
#include "Game.h"
#include "Global.h"
#include "ChangeBG.h"

#include "string"
#include "string.h"

using namespace std;

using namespace cocos2d;
using namespace CocosDenshion;


// 设置一个静态的场景函数
Scene* GamePauseScene::createScene()
{
	// 给scene创建内容
	Scene *myscene = Scene::create();

	// 创建一个layer
	GamePauseScene *mylayer = GamePauseScene::create();

	// 把这个layer加入到scene中
	myscene->addChild(mylayer);

	// 返回scene
	return myscene;
}
Scene* GamePauseScene::createScene(RenderTexture* sqr)
{
	Scene *myscene = Scene::create();

	Sprite *_spr = Sprite::createWithTexture(sqr->getSprite()->getTexture());
	_spr->setPosition(Vec2(240, 135));
	_spr->setFlippedY(true);
	_spr->setColor(Color3B::GRAY);
	myscene->addChild(_spr);

	GamePauseScene* mylayer = GamePauseScene::create();

	myscene->addChild(mylayer);

	return myscene;
}

// 初始化
bool GamePauseScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Size mysize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//背景
	Sprite *bg = Sprite::create("bt_pause.png");
	bg->setPosition(Vec2(origin.x + 50, origin.y + mysize.height - 25));
	this->addChild(bg);

	//更换背景
	Scale9Sprite *sp1 = Scale9Sprite::create("bt_changebg.png");
	ControlButton *pbt1 = ControlButton::create(sp1);
	pbt1->setPosition(Vec2(origin.x + mysize.width / 2, origin.y + mysize.height / 2 + 50));
	pbt1->setPreferredSize(Size(130, 35));
	this->addChild(pbt1, 2);
	//绑定事件
	pbt1->addTargetWithActionForControlEvents(
		this,
		cccontrol_selector(GamePauseScene::changeBG),
		Control::EventType::TOUCH_UP_INSIDE);

	//继续游戏
	Scale9Sprite *sp2 = Scale9Sprite::create("bt_continue.png");
	ControlButton *pbt2 = ControlButton::create(sp2);
	pbt2->setPosition(Vec2(origin.x + mysize.width / 2, origin.y + mysize.height / 2));
	pbt2->setPreferredSize(Size(130, 35));
	this->addChild(pbt2, 2);
	//绑定事件
	pbt2->addTargetWithActionForControlEvents(
		this,
		cccontrol_selector(GamePauseScene::backToRun),
		Control::EventType::TOUCH_UP_INSIDE);

	//返回菜单
	Scale9Sprite *sp3 = Scale9Sprite::create("bt_back.png");
	ControlButton *pbt3 = ControlButton::create(sp3);
	pbt3->setPosition(Vec2(origin.x + mysize.width / 2, origin.y + mysize.height / 2 - 50));
	pbt3->setPreferredSize(Size(130, 35));
	this->addChild(pbt3, 2);
	//绑定事件
	pbt3->addTargetWithActionForControlEvents(
		this,
		cccontrol_selector(GamePauseScene::backToMenu),
		Control::EventType::TOUCH_UP_INSIDE);

	return true;
}

//更换背景
void GamePauseScene::changeBG(Ref * sender, Control::EventType controlEvent)
{
	RenderTexture *renderTexture = RenderTexture::create(480, 270);
	renderTexture->begin();
	this->getParent()->visit();
	renderTexture->end();
	Director::getInstance()->pushScene(ChangeBGScene::createScene(renderTexture));
}

//继续游戏
void GamePauseScene::backToRun(Ref * sender, Control::EventType controlEvent)
{
	Director::getInstance()->popScene();
	Director::getInstance()->resume();
	SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}

//返回游戏菜单
void GamePauseScene::backToMenu(Ref * sender, Control::EventType controlEvent)
{
	Director::getInstance()->popScene();
	Director::getInstance()->resume();
	SimpleAudioEngine::getInstance()->resumeBackgroundMusic();

	Scene *gamemenu = GameMenuScene::createScene();
	auto *tt = TransitionFade::create(1.0f, gamemenu);
	Director::getInstance()->replaceScene(tt);
}


//生命周期
void GamePauseScene::onEnter()
{
	Layer::onEnter();
}
void GamePauseScene::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();
}
void GamePauseScene::onExit()
{
	Layer::onExit();
}


void GamePauseScene::menuCloseCallback(Ref* pSender)
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

