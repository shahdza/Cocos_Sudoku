#ifndef __RankScene_H__
#define __RankScene_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "cocos-ext.h"
using namespace cocos2d;
using namespace cocos2d::extension;

#include "string"
using namespace std;


class RankScene : public cocos2d::Layer, public TableViewDataSource, public TableViewDelegate
{
public:
	// 这个是用来初始化函数的
	virtual bool init();
	// 设置一个静态的场景函数
	static cocos2d::Scene* createScene();
	// 设置一个菜单的回调函数。
	void menuCloseCallback(Ref* pSender);
	// 这个是一个创建对象的代码，他会自动创建对象，
	// 如果失败会自动回收内存，如果回收内存也失败的话，他会自动的删除对象。
	CREATE_FUNC(RankScene);

	int selected;
	void update(float tmd);

	//菜单回调
	void backToMenu(Ref* pSender, Control::EventType controlEvent);

	//显示排名
	string opt;
	void showRank(Ref* pSender, Control::EventType controlEvent);

	void scrollViewDidScroll(ScrollView* view);
	void scrollViewDidZoom(ScrollView* view);

	//一共多少项
	ssize_t numberOfCellsInTableView(TableView *table);

	//生成列表每一项的内容
	TableViewCell * tableCellAtIndex(TableView *table, ssize_t idx);

	//每一项的宽度和高度
	Size cellSizeForTable(TableView *table);

	Size tableCellSizeForIndex(TableView *table, ssize_t idx);

	//处理触摸事件，可以计算点击的是哪一个子项
	void tableCellTouched(TableView* table, TableViewCell* cell);

	//生命周期
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
};

#endif // __RankScene_H__
