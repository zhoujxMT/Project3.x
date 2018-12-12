#ifndef __Game__LotteryKindScrollView__
#define __Game__LotteryKindScrollView__
#include "CocosUnits.h"
#include "ConfigMgr.h"
#include "AnsString.h"
#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"

# ifndef DELTA
# define DELTA 10
# endif
#define LOTTERY_KIND_SPRITE_TAG			0
#define GAME_KIND_SPRITE_TAG			100
#define PHY_KIND_SPRITE_TAG				200
#define INVALID_TAG					-100

USING_NS_CC;
USING_NS_CC_EXT;

class LotteryKindScrollView : public Layer,TableViewDataSource,TableViewDelegate 
{
    
public:
    LotteryKindScrollView();
    ~LotteryKindScrollView();
    virtual bool init();
    static Scene* scene();
    void pressKindButton(int tag);
    CREATE_FUNC(LotteryKindScrollView);

	virtual void scrollViewDidScroll(ScrollView* view);
	virtual void scrollViewDidZoom(ScrollView* view);

	//�����¼� ������ǵ�������Ǹ���ҳ
	virtual void tableCellTouched(TableView* table, TableViewCell* cell);
	//ÿһ��ĸ߶ȺͿ���
	virtual cocos2d::Size cellSizeForTable(TableView *table);
	//�����б���ÿһ������
	virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);
	//һ��������
	virtual ssize_t numberOfCellsInTableView(TableView *table);

	//ˢ��
	void refreshLayer();
public:
    void onEnter();
    void onExit();
    bool onTouchBegan(Touch *pTouch, Event *pEvent);
    void onTouchMoved(Touch *pTouch, Event *pEvent);
    void onTouchEnded(Touch *pTouch, Event *pEvent);
    void onTouchCancelled(Touch *pTouch, Event *pEvent);
   
	//itype 0Ϊ��Ϸ 1Ϊ��Ʊ 2Ϊ����
	void resetTable(const char* preName,const int count,const int iType);

private:
	int selectedSpriteTag;
	std::vector<int> m_Data;
	int m_Count;
	string m_name;
	TableView* m_table;
	TableViewCell* pCell;
	Vec2 start_pos;
};
#endif