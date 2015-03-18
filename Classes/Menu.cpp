// 0000
#include "Menu.h"

#include "GameMenu.h"
#include "About.h"

using namespace cocos2d;
using namespace CocosDenshion;

#define music_game	"music/maplestory.wav"
#define music_click "music/click.wav"


// 设置一个静态的场景函数
Scene* MenuScene::createScene()
{
	// 给scene创建内容
	Scene *myscene = Scene::create();

	// 创建一个layer
	MenuScene *mylayer = MenuScene::create();

	// 把这个layer加入到scene中
	myscene->addChild(mylayer);

	// 返回scene
	return myscene;
}

// 初始化
bool MenuScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size mysize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//加载音乐音效
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(1);
	SimpleAudioEngine::getInstance()->playBackgroundMusic(music_game, true);


	//设置背景
	Sprite *pbg = Sprite::create("menu_bg.png");
	pbg->setPosition(Vec2(mysize.width / 2, mysize.height / 2));
	this->addChild(pbg, -1);

	//草
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("c.plist");
	Sprite *pcao1 = Sprite::createWithSpriteFrameName("c1.png");
	Sprite *pcao2 = Sprite::createWithSpriteFrameName("c2.png");
	Sprite *pcao3 = Sprite::createWithSpriteFrameName("c3.png");

	pcao1->setPosition(Vec2(origin.x + mysize.width / 2 - 150, origin.y + 40));
	pcao2->setPosition(Vec2(origin.x + mysize.width / 2 + 100, origin.y + 40));
	pcao3->setPosition(Vec2(origin.x + mysize.width / 2 + 300, origin.y + 40));

	this->addChild(pcao1, 100);
	this->addChild(pcao2, 101);
	this->addChild(pcao3, 100);

	//云彩
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("yun.plist");
	Sprite *pyc1 = Sprite::createWithSpriteFrameName("y1.png");
	Sprite *pyc2 = Sprite::createWithSpriteFrameName("y2.png");
	Sprite *pyc3 = Sprite::createWithSpriteFrameName("y3.png");
	Sprite *pyc4 = Sprite::createWithSpriteFrameName("y4.png");

	pyc1->setPosition(Vec2(origin.x + mysize.width / 2 - 150, origin.y + mysize.height - 20));
	pyc2->setPosition(Vec2(origin.x + mysize.width / 2 + 150, origin.y + mysize.height - 30));
	pyc3->setPosition(Vec2(origin.x + mysize.width / 2, origin.y + mysize.height - 40));
	pyc4->setPosition(Vec2(origin.x + mysize.width / 2 + 200, origin.y + mysize.height - 50));

	pyc1->setScale(0.5f);
	pyc2->setScale(0.4f);
	pyc3->setScale(0.6f);
	pyc4->setScale(0.7f);

	this->addChild(pyc1, 100);
	this->addChild(pyc2, 100);
	this->addChild(pyc3, 100);
	this->addChild(pyc4, 100);

	auto *acyunle1 = MoveTo::create(30.0f, Vec2(origin.x - 200, origin.y + mysize.height - 20));
	auto *acyunle2 = MoveTo::create(19.0f, Vec2(origin.x - 200, origin.y + mysize.height - 50));
	auto *acyunle3 = MoveTo::create(34.0f, Vec2(origin.x - 200, origin.y + mysize.height - 30));
	auto *acyunle4 = MoveTo::create(24.0f, Vec2(origin.x - 200, origin.y + mysize.height - 40));

	auto *acyunri1 = MoveTo::create(25.0f, Vec2(mysize.width + 200, origin.y + mysize.height - 40));
	auto *acyunri2 = MoveTo::create(40.0f, Vec2(mysize.width + 200, origin.y + mysize.height - 50));
	auto *acyunri3 = MoveTo::create(28.0f, Vec2(mysize.width + 200, origin.y + mysize.height - 10));
	auto *acyunri4 = MoveTo::create(32.0f, Vec2(mysize.width + 200, origin.y + mysize.height - 20));

	auto *acyun1 = Sequence::create(acyunle1, acyunri1, NULL);
	auto *acyun2 = Sequence::create(acyunri2, acyunle2, NULL);
	auto *acyun3 = Sequence::create(acyunle3, acyunri3, NULL);
	auto *acyun4 = Sequence::create(acyunri4, acyunle4, NULL);

	auto *doyun1 = RepeatForever::create(acyun1);
	auto *doyun2 = RepeatForever::create(acyun2);
	auto *doyun3 = RepeatForever::create(acyun3);
	auto *doyun4 = RepeatForever::create(acyun4);

	pyc1->runAction(doyun1);
	pyc2->runAction(doyun2);
	pyc3->runAction(doyun3);
	pyc4->runAction(doyun4);

	//菜单
	auto *button1 = MenuItemImage::create("bt_entergame_small.png", "bt_entergame_big.png", this, menu_selector(MenuScene::enterGameMenu));
	auto *button2 = MenuItemImage::create("bt_aboutgame_small.png", "bt_aboutgame_big.png", this, menu_selector(MenuScene::enterAboutGame));
	auto *button3 = MenuItemImage::create("bt_closegame_small.png", "bt_closegame_big.png", this, menu_selector(MenuScene::menuCloseCallback));

	button1->setPosition(Vec2(origin.x + mysize.width / 2, origin.y + mysize.height / 2 + 40));
	button2->setPosition(Vec2(origin.x + mysize.width / 2, origin.y + mysize.height / 2 - 5));
	button3->setPosition(Vec2(origin.x + mysize.width / 2, origin.y + mysize.height / 2 - 50));

	auto *pmenu = Menu::create(button1, button2, button3, NULL);
	pmenu->setPosition(Vec2::ZERO);
	this->addChild(pmenu);
	//从小到大
	pmenu->setScale(0);
	auto *ac1 = ScaleTo::create(0.4f, 1.2f);
	auto *acdelay = DelayTime::create(0.1f);
	auto *ac2 = ScaleTo::create(0.2f, 1.0f);
	auto *cq = Sequence::create(ac1, acdelay, ac2, NULL);
	pmenu->runAction(cq);


	this->setKeypadEnabled(true);
	isPause = false;

	return true;
}



//进入游戏,进入GameMenu场景
void MenuScene::enterGameMenu(Ref* pSender)
{
	SimpleAudioEngine::getInstance()->playEffect(music_click);

	Scene *gamemenu = GameMenuScene::createScene();
	auto *tt = TransitionFade::create(1.0f, gamemenu);
	Director::getInstance()->replaceScene(tt);
}


//关于游戏
void MenuScene::enterAboutGame(Ref* pSender)
{
	SimpleAudioEngine::getInstance()->playEffect(music_click);
	//切换场景,翻页
	Scene *aboutscene = AboutScene::createScene();
	auto *tt = CCTransitionPageTurn::create(1.0f, aboutscene, false);
	Director::getInstance()->replaceScene(tt);
}


//生命周期 onEnter / onEnterTransitionDidFinish / onExit
void MenuScene::onEnter()
{
	Layer::onEnter();
}
void MenuScene::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();
}
void MenuScene::onExit()
{
	Layer::onExit();
}


//退出游戏
void MenuScene::menuCloseCallback(Ref* pSender)
{
	SimpleAudioEngine::getInstance()->playEffect(music_click);

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