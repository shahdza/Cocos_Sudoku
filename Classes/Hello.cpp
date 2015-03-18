#include "Hello.h"

#include "Menu.h"

using namespace cocos2d;
using namespace CocosDenshion;

#define music_logo "music/logo.wav"

#define music_bg	"music/game.wav"
#define music_game	"music/maplestory.wav"

#define music_click "music/click.wav"
#define music_start "music/start.wav"

#define music_harry "music/harry.wav"
#define music_time "music/time.wav"
#define music_error "music/error.wav"
#define music_props "music/props.wav"

#define music_win "music/win.wav"
#define music_lose "music/lose.wav"


// 设置一个静态的场景函数
Scene* HelloScene::createScene()
{
	// 给scene创建内容
	Scene *myscene = Scene::create();

	// 创建一个layer
	HelloScene *mylayer = HelloScene::create();

	// 把这个layer加入到scene中
	myscene->addChild(mylayer);

	// 返回scene
	return myscene;
}

// 初始化
bool HelloScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size mysize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//开场字幕
	Sprite *plogo = Sprite::create("hello.png");
	plogo->setPosition(Vec2(origin.x + mysize.width / 2, origin.y + mysize.height / 2));
	this->addChild(plogo, -1);

	//加载音乐音效
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic(music_logo);
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic(music_bg);
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic(music_game);
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic(music_harry);

	SimpleAudioEngine::getInstance()->preloadEffect(music_click);
	SimpleAudioEngine::getInstance()->preloadEffect(music_start);
	SimpleAudioEngine::getInstance()->preloadEffect(music_time);
	SimpleAudioEngine::getInstance()->preloadEffect(music_error);
	SimpleAudioEngine::getInstance()->preloadEffect(music_props);

	SimpleAudioEngine::getInstance()->preloadEffect(music_win);
	SimpleAudioEngine::getInstance()->preloadEffect(music_lose);

	SimpleAudioEngine::getInstance()->playBackgroundMusic(music_logo, false);


	//动画效果 / 渐显渐消
	auto *ain = CCFadeIn::create(0.5f);
	auto *aout = CCFadeOut::create(0.5f);
	auto *at = DelayTime::create(0.3f);
	auto *at2 = DelayTime::create(0.3f);
	CallFunc *into_menu = CallFunc::create(this, callfunc_selector(HelloScene::turnScene));
	auto *ac = Sequence::create(ain, at2, aout, at, into_menu, NULL);
	//auto *ac = Sequence::create(into_menu,NULL);

	plogo->runAction(ac);

	return true;
}


void HelloScene::menuCloseCallback(Ref* pSender)
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


//切换到主菜单
void HelloScene::turnScene()
{
	Scene *menuscene = MenuScene::createScene();
	auto *tt = TransitionCrossFade::create(0.2f, menuscene);
	Director::getInstance()->replaceScene(tt);
}


//生命周期 onEnter / onEnterTransitionDidFinish / onExit
void HelloScene::onEnter()
{
	Layer::onEnter();
}

void HelloScene::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();
}

void HelloScene::onExit()
{
	Layer::onExit();
	this->removeAllChildrenWithCleanup(true);
}
