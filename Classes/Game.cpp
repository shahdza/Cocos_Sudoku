//5000

#include "Game.h"

#include "GameMenu.h"
#include "Global.h"
#include "GamePause.h"
#include "GameOver.h"

#include "string"
#include "string.h"

using namespace std;

//宏定义 using namespace cocos2d;
USING_NS_CC;
using namespace CocosDenshion;


#define music_game	"music/game.wav"
#define music_harry "music/harry.wav"
#define music_click "music/click.wav"
#define music_time "music/time.wav"
#define music_error "music/error.wav"
#define music_props "music/props.wav"

//系统数字
#define sysgrid "box_gray.png"
//普通数字
#define normalgrid "box_blue.png"
//选中数字
#define sltgrid "box_purple.png"
//冲突数字
#define cfgrid "box_red.png"

#define fillgrid "box_green"



// 设置一个静态的场景函数
Scene* GameScene::createScene()
{
	// 给scene创建内容
	Scene *myscene = Scene::create();

	// 创建一个layer
	GameScene *mylayer = GameScene::create();

	// 把这个layer加入到scene中
	myscene->addChild(mylayer, 1, 1);

	// 返回scene
	return myscene;
}

// 初始化
bool GameScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	// 加载音效
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic(music_game);
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(1);
	SimpleAudioEngine::getInstance()->playBackgroundMusic(music_game, true);

	//普通游戏音乐
	musicslt = 1;

	Size mysize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	//背景图片 tag = 5600
	Sprite *pbg = Sprite::create("1.png");
	pbg->setPosition(Vec2(origin.x + mysize.width / 2, origin.y + mysize.height / 2));
	this->addChild(pbg, -1, 5600);
	Global::shareGlobal()->bg = pbg;

	//暂停按钮 tag = 5601
	Scale9Sprite *sppause = Scale9Sprite::create("pause.png");
	ControlButton *pbtpause = ControlButton::create(sppause);
	pbtpause->setPosition(Vec2(origin.x + mysize.width - 20, origin.y + mysize.height - 20));
	pbtpause->setPreferredSize(Size(36, 36));
	pbtpause->addTargetWithActionForControlEvents(
		this,
		cccontrol_selector(GameScene::gamePause),
		Control::EventType::TOUCH_UP_INSIDE);
	this->addChild(pbtpause, 1, 5601);

	//显示难度系数
	string degree = "";
	if (Global::shareGlobal()->degree == 1) degree = "easy.png";
	else if (Global::shareGlobal()->degree == 2) degree = "normal.png";
	else if (Global::shareGlobal()->degree == 3) degree = "hard.png";
	Sprite *pdeg = Sprite::create(degree.c_str());
	pdeg->setScale(0.6f);
	pdeg->setPosition(Vec2(origin.x + mysize.width - 30, origin.y + mysize.height - 60));
	this->addChild(pdeg);

	//金币倍数
	//各个难度的金币倍数不同
	mult_penny = 1;
	//若有双倍金币道具,直接使用.
	if (Global::shareGlobal()->penny > 0) {
		mult_penny *= 2;
		Global::shareGlobal()->penny--;
		Global::shareGlobal()->setPenny();
	}

	Label *penny = Label::createWithCharMap("digit.png", 20, 20, '0');
	penny->setString(Global::shareGlobal()->iToS(mult_penny, 1).c_str());
	penny->setPosition(Vec2(origin.x + mysize.width - 135, origin.y + mysize.height - 18));
	penny->setAnchorPoint(Vec2(0, 0));
	penny->setScale(0.7f);
	this->addChild(penny);

	//积分倍数
	mult_star = 1;
	//若有双倍积分道具,直接使用.
	if (Global::shareGlobal()->star > 0) {
		mult_star *= 2;
		Global::shareGlobal()->star--;
		Global::shareGlobal()->setStar();
	}
	Label *star = Label::createWithCharMap("digit.png", 20, 20, '0');
	star->setString(Global::shareGlobal()->iToS(mult_star, 1).c_str());
	star->setPosition(Vec2(origin.x + mysize.width - 60, origin.y + mysize.height - 18));
	star->setAnchorPoint(Vec2(0, 0));
	star->setScale(0.7f);
	this->addChild(star);

	//倒计时 tag = 5501
	//简单500 , 普通1000 , 困难1500
	rest_time = 500 * Global::shareGlobal()->degree;
	past_time = 0;
	Label *gametime = Label::createWithCharMap("digit.png", 20, 20, '0');
	gametime->setString(Global::shareGlobal()->iToS(rest_time, 4).c_str());
	gametime->setPosition(Vec2(origin.x + mysize.width - 130, origin.y + mysize.height - 45));
	gametime->setAnchorPoint(Vec2(0, 0));
	gametime->setScale(0.7f);
	this->addChild(gametime, 1, 5501);

	//步数 tag = 5502
	count = 0;
	Label *gamecount = Label::createWithCharMap("digit.png", 20, 20, '0');
	gamecount->setString(Global::shareGlobal()->iToS(count, 4).c_str());
	gamecount->setPosition(Vec2(origin.x + mysize.width - 130, origin.y + mysize.height - 70));
	gamecount->setAnchorPoint(Vec2(0, 0));
	gamecount->setScale(0.7f);
	this->addChild(gamecount, 1, 5502);


	//道具
	//addtime tag = 5503
	//道具个数
	cnt_addtime = Global::shareGlobal()->addtime; //道具个数
	Label *lbcntadd = Label::createWithCharMap("digit.png", 20, 20, '0');
	lbcntadd->setString(Global::shareGlobal()->iToS(cnt_addtime, 0).c_str());
	lbcntadd->setPosition(Vec2(origin.x + mysize.width - 85, origin.y + mysize.height / 2 + 5));
	lbcntadd->setAnchorPoint(Vec2(0, 0));
	lbcntadd->setScale(0.6f);
	this->addChild(lbcntadd, 2, 5503);
	//道具图片
	Scale9Sprite *spadd = Scale9Sprite::create("props_addtime.png");
	ControlButton *pbtadd = ControlButton::create(spadd);
	pbtadd->setPosition(Vec2(origin.x + mysize.width - 100, origin.y + mysize.height / 2 + 25));
	pbtadd->setPreferredSize(Size(40, 40));
	pbtadd->addTargetWithActionForControlEvents(
		this,
		cccontrol_selector(GameScene::useAddTime),
		Control::EventType::TOUCH_UP_INSIDE);
	this->addChild(pbtadd, 1);


	//hint tag = 5504
	//道具个数
	cnt_hint = min(Global::shareGlobal()->hint, 5); //每局最多用5个
	Label *lbcnthint = Label::createWithCharMap("digit.png", 20, 20, '0');
	lbcnthint->setString(Global::shareGlobal()->iToS(cnt_hint, 0).c_str());
	lbcnthint->setPosition(Vec2(origin.x + mysize.width - 25, origin.y + mysize.height / 2 + 5));
	lbcnthint->setAnchorPoint(Vec2(0, 0));
	lbcnthint->setScale(0.6f);
	this->addChild(lbcnthint, 2, 5504);
	//道具图片
	Scale9Sprite *sphint = Scale9Sprite::create("props_hint.png");
	ControlButton *pbthint = ControlButton::create(sphint);
	pbthint->setPosition(Vec2(origin.x + mysize.width - 40, origin.y + mysize.height / 2 + 25));
	pbthint->setPreferredSize(Size(40, 40));
	pbthint->addTargetWithActionForControlEvents(
		this,
		cccontrol_selector(GameScene::useHint),
		Control::EventType::TOUCH_UP_INSIDE);
	this->addChild(pbthint, 1);



	//填数1~9 + 清空
	//清空, tag = 5200
	//1~9 , tag = 5201~5209
	for (int i = 0; i <= 9; i++)
	{
		string fgrid = fillgrid;
		fgrid += (i + '0');  fgrid += ".png";

		Scale9Sprite *spgrid = Scale9Sprite::create(fgrid.c_str());
		ControlButton *pbtgrid = ControlButton::create(spgrid);
		if (i == 0) //清空按钮
		{
			pbtgrid->setPosition(Vec2(origin.x + mysize.width - 145, origin.y + 22));
			pbtgrid->setPreferredSize(Size(60, 30));
		}
		else //数字按钮
		{
			pbtgrid->setPosition(Vec2(origin.x + mysize.width - 90 + ((i - 1) % 3) * 35, origin.y + 90 - ((i - 1) / 3) * 35));
			pbtgrid->setPreferredSize(Size(28, 28));
		}
		this->addChild(pbtgrid, 1, 5200 + i);
		//绑定事件
		pbtgrid->addTargetWithActionForControlEvents(
			this,
			cccontrol_selector(GameScene::clickNum),
			Control::EventType::TOUCH_UP_INSIDE);
	}


	//数独

	//生成数独盘面
	Global::shareGlobal()->createSudoku();

	for (int i = 0; i < 9; i++)  {
		for (int j = 0; j < 9; j++)  {

			int num = Global::shareGlobal()->grid[i][j].num;

			Sprite* grid; //格子
			Label *lbnum; //数字
			if (Global::shareGlobal()->grid[i][j].isSysNum()) { //是否是系统数字
				grid = Sprite::create(sysgrid);
				lbnum = Label::createWithTTF(Global::shareGlobal()->iToS(num, 1).c_str(), "fonts/arial.ttf", 18);
			}
			else { //空格
				grid = Sprite::create(normalgrid);
				lbnum = Label::createWithTTF("", "fonts/arial.ttf", 18);
				Global::shareGlobal()->selected = i * 9 + j;
			}

			int dx = (i / 3) * 11; int dy = (j / 3) * 11;
			grid->setPosition(Vec2(origin.x + 20 + i * 26 + dx, origin.y + 20 + j * 26 + dy));
			lbnum->setPosition(Vec2(origin.x + 20 + i * 26 + dx, origin.y + 20 + j * 26 + dy));
			lbnum->setColor(Color3B(0, 0, 0));

			this->addChild(grid, 1, 5001 + (i * 9 + j));
			this->addChild(lbnum, 2, 5101 + (i * 9 + j));
		}
	}
	Sprite* grid = (Sprite*)this->getChildByTag(5001 + Global::shareGlobal()->selected);
	Texture2D *text2d = Director::getInstance()->getTextureCache()->addImage(sltgrid);
	grid->setTexture(text2d);

	//更新游戏
	schedule(schedule_selector(GameScene::updateGame), 1.0f);


	//注册触摸事件
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
	dispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	return true;
}


//更新时间
void GameScene::updateGame(float tmd)
{
	rest_time--;
	past_time++;

	updateMusic();

	//倒计时10秒的音效
	if (rest_time <= 10) {
		SimpleAudioEngine::getInstance()->playEffect(music_time);
	}

	//修改时间 tag = 5501
	Label *lbtime = (Label*)this->getChildByTag(5501);
	lbtime->setString(Global::shareGlobal()->iToS(rest_time, 4).c_str());

	//游戏结束 , 失败
	if (rest_time == 0)
	{
		gameEnd(0);
	}
}

//更新游戏音乐
void GameScene::updateMusic()
{
	if (rest_time <= 100) //紧张音乐
	{
		if (musicslt != 2)
		{
			musicslt = 2;
			SimpleAudioEngine::getInstance()->playBackgroundMusic(music_harry);
		}
	}
	else //普通音乐
	{
		if (musicslt != 1)
		{
			musicslt = 1;
			SimpleAudioEngine::getInstance()->playBackgroundMusic(music_game);
		}
	}

}


//游戏结束 , 0表示失败, 1表示胜利
void GameScene::gameEnd(int state)
{
	//将游戏信息记录到全局类Global中
	//isWin;		//是否胜利
	//mult_penny;	//金币倍数
	//mult_star;	//积分倍数
	//rest_time;	//剩余时间
	//past_time;	//已用时间
	//count;		//操作步数

	Global::shareGlobal()->mult_penny = mult_penny;
	Global::shareGlobal()->mult_star = mult_star;
	Global::shareGlobal()->rest_time = rest_time;
	Global::shareGlobal()->past_time = past_time;
	Global::shareGlobal()->count = count;

	if (state == 0) { //失败
		Global::shareGlobal()->isWin = false;
	}
	else { //胜利
		Global::shareGlobal()->isWin = true;
	}

	//切换到游戏结束画面
	Scene *gameover = GameOverScene::createScene();
	auto *tt = TransitionFade::create(1.0f, gameover);
	Director::getInstance()->replaceScene(tt);
}


//暂停游戏
void GameScene::gamePause(Ref * sender, Control::EventType controlEvent)
{
	SimpleAudioEngine::getInstance()->playEffect(music_click);

	//暂停音乐 和 动作
	Director::getInstance()->pause();
	SimpleAudioEngine::getInstance()->pauseBackgroundMusic();

	RenderTexture *renderTexture = RenderTexture::create(480, 270);
	renderTexture->begin();
	this->getParent()->visit();
	renderTexture->end();  //这里实际是通过RenderTexture保存当前界面（相当于截屏），然后传递给暂停界面，当成背景精灵  
	Director::getInstance()->pushScene(GamePauseScene::createScene(renderTexture));
}


//使用延时道具
void GameScene::useAddTime(Ref * sender, Control::EventType controlEvent)
{
	if (cnt_addtime == 0) { //道具已用完
		SimpleAudioEngine::getInstance()->playEffect(music_error);
	}
	else {
		SimpleAudioEngine::getInstance()->playEffect(music_props);
		cnt_addtime--;
		Global::shareGlobal()->addtime--;
		Global::shareGlobal()->setAddTime();

		//道具数目减1 , tag = 5503
		Label *lb = (Label*)this->getChildByTag(5503);
		lb->setString(Global::shareGlobal()->iToS(cnt_addtime, 0).c_str());

		//时限加长 , tag = 5501
		rest_time += 100;
		Label *lbtime = (Label*)this->getChildByTag(5501);
		lbtime->setString(Global::shareGlobal()->iToS(rest_time, 4).c_str());
		updateMusic();
	}
}

//使用提示道具
void GameScene::useHint(Ref * sender, Control::EventType controlEvent)
{
	if (cnt_hint == 0) { //道具已用完
		SimpleAudioEngine::getInstance()->playEffect(music_error);
	}
	else {
		SimpleAudioEngine::getInstance()->playEffect(music_props);
		cnt_hint--;
		Global::shareGlobal()->hint--;
		Global::shareGlobal()->setHint();

		//道具数目减1 , tag = 5504
		Label *lb = (Label*)this->getChildByTag(5504);
		lb->setString(Global::shareGlobal()->iToS(cnt_hint, 0).c_str());

		//被选中的格子显示正确的数字
		int idx = Global::shareGlobal()->selected;
		fillGrid(Global::shareGlobal()->ans[idx / 9][idx % 9]);
	}
}


//是否完成数独棋盘
void GameScene::isFinish()
{
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			int num = Global::shareGlobal()->grid[i][j].num;
			int num2 = Global::shareGlobal()->ans[i][j];
			if (num != num2) return; //若不是正确的解 , 游戏继续
		}
	}
	//否则,完成数独游戏.胜利
	gameEnd(1);
}

//在选中的格子中填上num
void GameScene::fillGrid(int num)
{
	int idx = Global::shareGlobal()->selected; //被选中的是哪个格子
	int x = idx / 9;
	int y = idx % 9;

	//填数特效
	Sprite* grid = (Sprite*)this->getChildByTag(5001 + idx);
	Label *lbnum = (Label*)this->getChildByTag(5101 + idx);
	//放大
	auto *ac1 = ScaleTo::create(0.1f, 1.3f);
	auto *acdelay1 = DelayTime::create(0.1f);
	auto *ac2 = ScaleTo::create(0.2f, 1.0f);
	auto *ac3 = ScaleTo::create(0.1f, 1.3f);
	auto *acdelay2 = DelayTime::create(0.1f);
	auto *ac4 = ScaleTo::create(0.2f, 1.0f);
	auto *cq1 = Sequence::create(ac1, acdelay1, ac2, NULL);
	auto *cq2 = Sequence::create(ac3, acdelay2, ac4, NULL);
	grid->runAction(cq1);
	lbnum->runAction(cq2);

	if (num == 0) //清空
	{
		lbnum->setString("");
		Global::shareGlobal()->grid[x][y].num = 0;
	}
	else //填数
	{
		lbnum->setString(Global::shareGlobal()->iToS(num, 1).c_str());
		Global::shareGlobal()->grid[x][y].num = num;
	}

	checkGrid(); //是否冲突

	isFinish(); //是否结束
}


//填数 5200
void GameScene::clickNum(Ref *sender, Control::EventType controlEvent)
{
	SimpleAudioEngine::getInstance()->playEffect(music_click);

	//修改步数 tag = 5502
	count++;
	Label *lbcnt = (Label*)this->getChildByTag(5502);
	lbcnt->setString(Global::shareGlobal()->iToS(count, 4).c_str());

	int num; //填了什么数字
	for (num = 0; num <= 9; num++)
	{
		ControlButton *bt = (ControlButton*)this->getChildByTag(5200 + num);
		if (sender == bt) break;
	}

	fillGrid(num);
}


//检查格子[x,y]是否冲突
bool GameScene::isIllegal(int x, int y)
{
	int num = Global::shareGlobal()->grid[x][y].num;

	if (num == 0) return false; //是个空格

	//检查行
	for (int i = 0; i < 9; i++) {
		int num2 = Global::shareGlobal()->grid[x][i].num;
		if ((i == y) || (num2 == 0)) continue;
		if (num2 == num) return true; //冲突
	}
	//检查列
	for (int i = 0; i < 9; i++) {
		int num2 = Global::shareGlobal()->grid[i][y].num;
		if ((i == x) || (num2 == 0)) continue;
		if (num2 == num) return true; //冲突
	}
	//检查宫格
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			int xx = (x / 3) * 3 + i;
			int yy = (y / 3) * 3 + j;
			int num2 = Global::shareGlobal()->grid[xx][yy].num;
			if ((xx == x && yy == y) || (num2 == 0)) continue;
			if (num2 == num) return true; //冲突
		}
	}
	return false;
}

//检查是否有冲突,若有将格子变成红色
void GameScene::checkGrid()
{
	for (int i = 0; i < 9; i++)  {
		for (int j = 0; j < 9; j++)  {
			Sprite* grid = (Sprite*)this->getChildByTag(5001 + (i * 9) + j);

			int num = Global::shareGlobal()->grid[i][j].num;

			if (Global::shareGlobal()->grid[i][j].isSysNum()) { //是否是系统数字
				Texture2D *text2d = Director::getInstance()->getTextureCache()->addImage(sysgrid);
				grid->setTexture(text2d);
			}
			else { //空格
				Texture2D *text2d2 = Director::getInstance()->getTextureCache()->addImage(normalgrid);
				grid->setTexture(text2d2);
			}

			if (isIllegal(i, j)) { //如果数字非法,格子变成红色
				Texture2D *text2d3 = Director::getInstance()->getTextureCache()->addImage(cfgrid);
				grid->setTexture(text2d3);
			}
		}
	}
	Sprite* grid = (Sprite*)this->getChildByTag(5001 + Global::shareGlobal()->selected);
	Texture2D *text2d4 = Director::getInstance()->getTextureCache()->addImage(sltgrid);
	grid->setTexture(text2d4);
}

//被选中的位置是不是格子 , 且不能为系统数字
int GameScene::get_tag(Touch *ctouch)
{
	int idx = -1; //不是格子为-1
	Vec2 pt = ctouch->getLocation();

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {

			if (Global::shareGlobal()->grid[i][j].isSysNum()) continue; //不能选择系统数字

			Sprite* grid = (Sprite*)this->getChildByTag(5001 + (i * 9 + j));
			Label *num = (Label*)this->getChildByTag(5101 + (i * 9 + j));
			grid->setScale(1.0f);
			num->setScale(1.0f);
			int minx = grid->getPositionX() - 13;
			int maxx = grid->getPositionX() + 13;
			int miny = grid->getPositionY() - 13;
			int maxy = grid->getPositionY() + 13;
			if ((pt.x > minx&&pt.x<maxx) && (pt.y>miny&&pt.y < maxy)) {
				idx = i * 9 + j;
			}
		}
	}
	return idx; //哪个格子
}

//开始触屏
bool GameScene::onTouchBegan(Touch * ctouch, Event * event)
{
	int idx = get_tag(ctouch);

	if (idx == -1) return false;

	Sprite* grid = (Sprite*)this->getChildByTag(5001 + idx);
	Label *num = (Label*)this->getChildByTag(5101 + idx);
	grid->setScale(1.2f);
	num->setScale(1.2f);

	return true;
}
//移动触屏
void GameScene::onTouchMoved(Touch * ctouch, Event * event)
{
	int idx = get_tag(ctouch);

	if (idx == -1) return;

	Sprite* grid = (Sprite*)this->getChildByTag(5001 + idx);
	Label *num = (Label*)this->getChildByTag(5101 + idx);
	grid->setScale(1.2f);
	num->setScale(1.2f);
}
//结束触屏
void GameScene::onTouchEnded(Touch * ctouch, Event * event)
{
	int idx = get_tag(ctouch);

	if (idx == -1) return;

	SimpleAudioEngine::getInstance()->playEffect(music_click);

	//选中的格子
	Global::shareGlobal()->selected = idx;
	checkGrid();
}


//生命周期
void GameScene::onEnter()
{
	Layer::onEnter();
}
void GameScene::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();
}
void GameScene::onExit()
{
	Layer::onExit();
}

void GameScene::menuCloseCallback(Ref* pSender)
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
