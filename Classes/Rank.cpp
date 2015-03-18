// 3000

#include "Rank.h"

#include "GameMenu.h"
#include "Global.h"

using namespace std;

using namespace cocos2d;
using namespace CocosDenshion;

#define music_click "music/click.wav"


// 设置一个静态的场景函数
Scene* RankScene::createScene()
{
	// 给scene创建内容
	Scene *myscene = Scene::create();

	// 创建一个layer
	RankScene *mylayer = RankScene::create();

	// 把这个layer加入到scene中
	myscene->addChild(mylayer);

	// 返回scene
	return myscene;
}

// 初始化
bool RankScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	selected = 3001;
	opt = "easy";
	scheduleUpdate();

	Size mysize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//背景图片
	Sprite *pbg = Sprite::create("rank_bg.png");
	pbg->setPosition(Vec2(origin.x + mysize.width / 2, origin.y + mysize.height / 2));
	this->addChild(pbg, -1);

	//返回按钮
	Scale9Sprite *spback = Scale9Sprite::create("close.png");
	ControlButton *pbtbk = ControlButton::create(spback);
	pbtbk->setPosition(Vec2(origin.x + mysize.width - 20, origin.y + mysize.height - 25));
	pbtbk->setPreferredSize(Size(36, 36));
	pbtbk->addTargetWithActionForControlEvents(
		this,
		cccontrol_selector(RankScene::backToMenu),
		Control::EventType::TOUCH_UP_INSIDE);
	this->addChild(pbtbk);

	//rank_easy , tag = 3001
	Scale9Sprite *speasy = Scale9Sprite::create("easy.png");
	ControlButton *rkeasy = ControlButton::create(speasy);
	rkeasy->setPosition(Vec2(origin.x + 40, origin.y + mysize.height / 2 + 50));
	rkeasy->setPreferredSize(Size(75, 50));
	rkeasy->addTargetWithActionForControlEvents(
		this,
		cccontrol_selector(RankScene::showRank),
		Control::EventType::TOUCH_UP_INSIDE);
	this->addChild(rkeasy, 1, 3001);

	//rank_normal , tag = 3002
	Scale9Sprite *spnormal = Scale9Sprite::create("normal.png");
	ControlButton *rknormal = ControlButton::create(spnormal);
	rknormal->setPosition(Vec2(origin.x + 40, origin.y + mysize.height / 2 - 20));
	rknormal->setPreferredSize(Size(75, 50));
	rknormal->addTargetWithActionForControlEvents(
		this,
		cccontrol_selector(RankScene::showRank),
		Control::EventType::TOUCH_UP_INSIDE);
	this->addChild(rknormal, 1, 3002);

	//rank_hard tag = 3003
	Scale9Sprite *sphard = Scale9Sprite::create("hard.png");
	ControlButton *rkhard = ControlButton::create(sphard);
	rkhard->setPosition(Vec2(origin.x + 40, origin.y + mysize.height / 2 - 90));
	rkhard->setPreferredSize(Size(75, 50));
	rkhard->addTargetWithActionForControlEvents(
		this,
		cccontrol_selector(RankScene::showRank),
		Control::EventType::TOUCH_UP_INSIDE);
	this->addChild(rkhard, 1, 3003);

	TableView * tbeasy = TableView::create(this, Size(360, 200));
	tbeasy->setDirection(ScrollView::Direction::VERTICAL);
	tbeasy->setPosition(Vec2(origin.x + 90, origin.y + 15));
	tbeasy->setDelegate(this);
	tbeasy->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
	this->addChild(tbeasy, 1, 3005);

	return true;
}


void RankScene::update(float tmd)
{
	this->getChildByTag(selected)->setScale(1.2f);
}

//显示选中的难度相对应的排名
void RankScene::showRank(Ref* pSender, Control::EventType controlEvent)
{

	SimpleAudioEngine::getInstance()->playEffect(music_click);

	int news = 3001;
	ControlButton* bt;
	for (int i = 3001; i <= 3003; i++)
	{
		bt = (ControlButton *)this->getChildByTag(i);
		if (bt == pSender)
		{
			news = i;
			break;
		}
	}
	if (news == selected) return;

	//放大选择难度
	this->getChildByTag(selected)->setScale(1.0f);
	this->getChildByTag(news)->setScale(1.1f);
	selected = news;

	//选择难度
	if (selected == 3001)		opt = "easy"; //简单
	else if (selected == 3002)	opt = "normal"; //普通
	else if (selected == 3003)	opt = "hard"; //困难

	//获取排名 CCTbaleView , tag = 3005
	TableView *tb = (TableView *)this->getChildByTag(3005);
	tb->reloadData();
}

//一共多少项
ssize_t RankScene::numberOfCellsInTableView(TableView *table)
{
	int cnt = CCUserDefault::sharedUserDefault()->getIntegerForKey(opt.c_str(), 0);
	return max(cnt + 1, 6);
}
//生成列表每一项的内容
TableViewCell* RankScene::tableCellAtIndex(TableView *table, ssize_t idx)
{
	Size mysize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//读取数据
	string str = opt + "_" + Global::shareGlobal()->iToS(idx + 1, 0);

	TableViewCell* cell = table->cellAtIndex(idx);
	if (!cell)
	{
		cell = new TableViewCell();
		cell->autorelease();

		Sprite *item = Sprite::create("tb.png");
		item->setPosition(Vec2(origin.x + 180, 15));
		cell->addChild(item);

		string data = CCUserDefault::sharedUserDefault()->getStringForKey(str.c_str(), "");

		//cocos2d::CCMessageBox(t.c_str(),num.c_str());
		//return cell;

		if (data != "")
		{
			string t = "";
			string num = "";
			string score = "";
			int i = 0;
			while (data[i] != ' ') t += data[i++]; i++; //时间
			while (data[i] != ' ') num += data[i++]; i++; //步数
			while (i < (int)data.length()) score += data[i++]; //分数


			Label *item1 = Label::createWithTTF(Global::shareGlobal()->iToS(idx + 1, 0).c_str(), "fonts/arial.ttf", 18);
			Label *item2 = Label::createWithTTF(t.c_str(), "fonts/arial.ttf", 18);
			Label *item3 = Label::createWithTTF(num.c_str(), "fonts/arial.ttf", 18);
			Label *item4 = Label::createWithTTF(score.c_str(), "fonts/arial.ttf", 18);

			item1->setPosition(Vec2(origin.x + 30, 15));
			item2->setPosition(Vec2(origin.x + 120, 15));
			item3->setPosition(Vec2(origin.x + 210, 15));
			item4->setPosition(Vec2(origin.x + 300, 15));

			cell->addChild(item1);
			cell->addChild(item2);
			cell->addChild(item3);
			cell->addChild(item4);
		}
	}
	return cell;
}

//每一项的宽度和高度
Size RankScene::cellSizeForTable(TableView *table)
{
	return Size(360, 30);
}

Size RankScene::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
	return Size(360, 35);
}

//处理触摸事件，可以计算点击的是哪一个子项
void RankScene::tableCellTouched(TableView* table, TableViewCell* cell)
{

}

void RankScene::scrollViewDidScroll(ScrollView* view)
{

}

void RankScene::scrollViewDidZoom(ScrollView* view)
{

}


//菜单回调
void RankScene::backToMenu(Ref* pSender, Control::EventType controlEvent)
{
	SimpleAudioEngine::getInstance()->playEffect(music_click);

	Scene *menuscene = GameMenuScene::createScene();
	auto *tt = TransitionFade::create(1.0f, menuscene);
	Director::getInstance()->replaceScene(tt);
}


//生命周期
void RankScene::onEnter()
{
	Layer::onEnter();
}
void RankScene::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();
}
void RankScene::onExit()
{
	Layer::onExit();
}

void RankScene::menuCloseCallback(Ref* pSender)
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
