//7000

#include "GameOver.h"

#include "GameMenu.h"
#include "Global.h"
#include "Game.h"

#include "string"
#include "string.h"

using namespace std;

using namespace cocos2d;
using namespace CocosDenshion;

#define music_win "music/win.wav"
#define music_lose "music/lose.wav"
#define music_click "music/click.wav"
#define music_bg "maplestory.wav"


// 设置一个静态的场景函数
Scene* GameOverScene::createScene()
{
	// 给scene创建内容
	Scene *myscene = Scene::create();

	// 创建一个layer
	GameOverScene *mylayer = GameOverScene::create();

	// 把这个layer加入到scene中
	myscene->addChild(mylayer);

	// 返回scene
	return myscene;
}

// 初始化
bool GameOverScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	SimpleAudioEngine::getInstance()->preloadEffect(music_win);
	SimpleAudioEngine::getInstance()->preloadEffect(music_lose);

	Size mysize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//
	Sprite *bg = Sprite::create("muban.png");
	bg->setPosition(Vec2(origin.x + mysize.width / 2, origin.y + mysize.height / 2));
	this->addChild(bg, -1);

	//返回按钮
	Scale9Sprite *spbk = Scale9Sprite::create("bt_back.png");
	ControlButton *pbtbk = ControlButton::create(spbk);
	pbtbk->setPosition(Vec2(origin.x + mysize.width / 2 + 80, origin.y + 25));
	pbtbk->setPreferredSize(Size(130, 35));
	pbtbk->addTargetWithActionForControlEvents(
		this,
		cccontrol_selector(GameOverScene::backToMenu),
		Control::EventType::TOUCH_UP_INSIDE);
	this->addChild(pbtbk);

	//再次挑战
	Scale9Sprite *spplay = Scale9Sprite::create("bt_playagain.png");
	ControlButton *pbtplay = ControlButton::create(spplay);
	pbtplay->setPosition(Vec2(origin.x + mysize.width / 2 - 80, origin.y + 25));
	pbtplay->setPreferredSize(Size(130, 35));
	pbtplay->addTargetWithActionForControlEvents(
		this,
		cccontrol_selector(GameOverScene::playAgain),
		Control::EventType::TOUCH_UP_INSIDE);
	this->addChild(pbtplay);

	//绘制结束画面, 胜利 or 失败
	if (Global::shareGlobal()->isWin == true) {
		drawWin(); //胜利
	}
	else {
		drawWin(); //胜利
		// drawLose(); //失败
	}

	return true;
}

void GameOverScene::drawWin()
{
	SimpleAudioEngine::getInstance()->playEffect(music_win);

	Size mysize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Sprite *sp = Sprite::create("win.png");
	sp->setPosition(Vec2(origin.x + mysize.width / 2, origin.y + mysize.height / 2 + 25));
	this->addChild(sp, 2);


	//计算得分以及排名
	int mult_penny = Global::shareGlobal()->mult_penny; //金币倍数
	int mult_star = Global::shareGlobal()->mult_star;	//积分倍数
	int rest_time = Global::shareGlobal()->rest_time;	//剩余时间
	int past_time = Global::shareGlobal()->past_time;	//已用时间
	int count = Global::shareGlobal()->count;			//操作步数


	int t = past_time; //时间
	int num = count; //步数
	int score = (rest_time / 0.618) * mult_star; //得分
	int money = (rest_time / 3.82) * mult_penny; //获得金币
	Global::shareGlobal()->money += money;
	Global::shareGlobal()->setMoney(); //保存数据


	string info = ""; //本次游戏的信息, 时间/步数/得分
	string opt = ""; //难度分类, easy/normal/hard
	if (Global::shareGlobal()->degree == 1) opt = "easy";
	else if (Global::shareGlobal()->degree == 2) opt = "normal";
	else opt = "hard";
	info += Global::shareGlobal()->iToS(t, 0); info += " ";
	info += Global::shareGlobal()->iToS(num, 0); info += " ";
	info += Global::shareGlobal()->iToS(score, 0);
	int rank = Global::shareGlobal()->updateRank(info, opt); //插入排行榜 , 并获得历史排名

	//本次用时
	Label *gametime = Label::createWithCharMap("digit.png", 20, 20, '0');
	gametime->setString(Global::shareGlobal()->iToS(past_time, 0).c_str());
	gametime->setPosition(Vec2(origin.x + mysize.width / 2 + 20, origin.y + mysize.height / 2 + 65));
	gametime->setAnchorPoint(Vec2(0, 0));
	this->addChild(gametime, 10);

	//操作步数
	Label *gamenum = Label::createWithCharMap("digit.png", 20, 20, '0');
	gamenum->setString(Global::shareGlobal()->iToS(num, 0).c_str());
	gamenum->setPosition(Vec2(origin.x + mysize.width / 2 + 20, origin.y + mysize.height / 2 + 40));
	gamenum->setAnchorPoint(Vec2(0, 0));
	this->addChild(gamenum, 10);

	//最终得分
	Label *gamescore = Label::createWithCharMap("digit.png", 20, 20, '0');
	gamescore->setString(Global::shareGlobal()->iToS(score, 0).c_str());
	gamescore->setPosition(Vec2(origin.x + mysize.width / 2 + 20, origin.y + mysize.height / 2 + 5));
	gamescore->setAnchorPoint(Vec2(0, 0));
	this->addChild(gamescore, 10);

	//获得金币
	Label *gamemoney = Label::createWithCharMap("digit.png", 20, 20, '0');
	gamemoney->setString(Global::shareGlobal()->iToS(money, 0).c_str());
	gamemoney->setPosition(Vec2(origin.x + mysize.width / 2 + 20, origin.y + mysize.height / 2 - 25));
	gamemoney->setAnchorPoint(Vec2(0, 0));
	this->addChild(gamemoney, 10);

	//历史排名
	Label *gamerank = Label::createWithCharMap("digit.png", 20, 20, '0');
	gamerank->setString(Global::shareGlobal()->iToS(rank, 0).c_str());
	gamerank->setPosition(Vec2(origin.x + mysize.width / 2 + 20, origin.y + mysize.height / 2 - 58));
	gamerank->setAnchorPoint(Vec2(0, 0));
	this->addChild(gamerank, 10);


	//排行榜按钮



}

void GameOverScene::drawLose()
{
	SimpleAudioEngine::getInstance()->playEffect(music_lose);

	Size mysize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Sprite *sp = Sprite::create("lose.png");
	sp->setPosition(Vec2(origin.x + mysize.width / 2, origin.y + mysize.height / 2 + 25));
	this->addChild(sp, 2);
}


//重新游戏
void GameOverScene::playAgain(Ref * sender, Control::EventType controlEvent)
{
	SimpleAudioEngine::getInstance()->playEffect(music_click);

	Scene *game = GameScene::createScene();
	auto *tt = TransitionFade::create(1.0f, game);
	Director::getInstance()->replaceScene(tt);
}
//返回游戏菜单
void GameOverScene::backToMenu(Ref * sender, Control::EventType controlEvent)
{
	SimpleAudioEngine::getInstance()->playEffect(music_click);

	Scene *menuscene = GameMenuScene::createScene();
	auto *tt = TransitionFade::create(1.0f, menuscene);
	Director::getInstance()->replaceScene(tt);
}

//生命周期
void GameOverScene::onEnter()
{
	Layer::onEnter();
}
void GameOverScene::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();
}
void GameOverScene::onExit()
{
	Layer::onExit();
}

void GameOverScene::menuCloseCallback(Ref* pSender)
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

