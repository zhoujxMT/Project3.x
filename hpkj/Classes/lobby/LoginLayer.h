#ifndef __LOGINLAYER_H__
#define __LOGINLAYER_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include"cocostudio/CocoStudio.h"
#include "BaseObject.h"
using namespace cocos2d::extension;

USING_NS_CC;
#define P_SCREEN								(CCDirector::sharedDirector()->getWinSize())
#define FRAME_CENTER_X       (P_SCREEN.width/2)
#define FRAME_CENTER_Y       (P_SCREEN.height/2)

#define GAP_X					30
#define GAP_Y					30

#define NOTICE_CENTER_X       (143+GAP_X)
#define NOTICE_CENTER_Y       (201+GAP_Y)
#define NOTICE_TEXT_CENTER_X       (50)
#define NOTICE_TEXT_UP       (340)

#define LOGIN_CENTER_X       (P_SCREEN.width-192-50)
#define LOGIN_CENTER_Y       (145+110)

#define REMEMBER_CENTER_X       (LOGIN_CENTER_X-90)
#define REMEMBER_CENTER_Y       (LOGIN_CENTER_Y-10)
#define AUTOMATIC_CENTER_X       (REMEMBER_CENTER_X+186)
#define AUTOMATIC_CENTER_Y       (REMEMBER_CENTER_Y)

// 帐号
#define ACCOUNT_CENTER_X        (LOGIN_CENTER_X-180)
#define ACCOUNT_CENTER_Y        (LOGIN_CENTER_Y+105)
#define ACCOUNT_TEXT_CENTER_X   (ACCOUNT_CENTER_X+80)
#define ACCOUNT_TEXT_CENTER_Y   (ACCOUNT_CENTER_Y)
#define TABLE_CENTER_X          (ACCOUNT_CENTER_X-60)
#define TABLE_CENTER_Y          (ACCOUNT_CENTER_Y)

// list button
#define LIST_CENTER_X           (FRAME_CENTER_X+150)
#define LIST_CENTER_Y           (FRAME_CENTER_Y-33)
// 密码
#define PASSWORD_CENTER_X       (ACCOUNT_CENTER_X)
#define PASSWORD_CENTER_Y       (289)
#define PASSWORD_TEXT_CENTER_X  (ACCOUNT_TEXT_CENTER_X)
#define PASSWORD_TEXT_CENTER_Y  (PASSWORD_CENTER_Y)

#define LOGON_CENTER_X          (LOGIN_CENTER_X)
#define LOGON_CENTER_Y          (LOGIN_CENTER_Y-75)
#define REGISTER_CENTER_X       (LOGON_CENTER_X+100)
#define REGISTER_CENTER_Y       (65)
#define GUEST_CENTER_X          (LOGON_CENTER_X-100)
#define GUEST_CENTER_Y          (REGISTER_CENTER_Y)

typedef enum
{
	//主
	FLTAG_Zero				= 0,				//default
	FLTAG_AccountsTex		= 1,				//帐号框
	FLTAG_PassWordTex		= 2,				//密码框
	FLTAG_TableView			= 3,				//帐号列表table
	FLTAG_ClearAccountsBtn	= 4,				//帐号按钮x
	FLTAG_ClearPassWordBtn	= 5,				//密码按钮x
	FLTAG_ListBtn			= 6,				//列表按钮
	FLTAG_LogonBtn			= 7,				//登录按钮
	FLTAG_RememberPW		= 8,				//记住密码按钮
	FLTAG_RememberLogon		= 9,				//自动登录按钮
	FLTAG_ACPWFont			= 10,				//记住密码字体
	FLTAG_AUTOFont			= 11,				//自动登录字体
	FLTAG_RememberPWYES		= 12,				//记住密码yes
	FLTAG_RememberLogonYES	= 13,				//自动登录yes
	
	//子
	FLTAG_Viewbg			= 20,				//当前背景
	FLTAG_Loadbg			= 21,				//登录背景

	TAG_USERLOGIN_LAYER=100,
}FLTAG;

class LoginLayer : public CCLayer, public cocos2d::ui::EditBoxDelegate//CCEditBoxDelegate
{
public:
    
    LoginLayer();
    ~LoginLayer();
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init(bool bLogin);

    //virtual void onEnter();

    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    
    virtual void onEnter();
    virtual void onExit();
    
    cocos2d::extension::EditBox * userInput;
    cocos2d::extension::EditBox * passwordInput;
    cocos2d::ui::EditBox   *m_pAccountEdit;
    cocos2d::ui::EditBox   *m_pPasswordEdit;
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    //CREATE_FUNC(LoginLayer);
    void onLogin(CCObject* obj);								//登陆
    void onRegist(CCObject * obj);								//注册
    void GuestLogon(CCObject * obj);							//找回密码
	void changePassWord(CCObject* obj);							//修改密码
    void back(CCObject * obj);									//返回
    void setIsfaildLogin(bool mIsFaildLogin);					//登陆失败
    void onAnsLoginFinish(CCObject* obj);						//登陆完成
    void onLoginFaild(CCObject* obj);							//登陆失败
    void onFindPassword(CCObject* obj);							//密码找回
	void setLogin(bool loginBool);
	void toFreeLayer(CCObject* obj);
    //void setLogin(bool bLogin) { m_bLogin = bLogin; }  //设置是否直接登陆
    std::string createAccount();
	std::string createPassword();
    static LoginLayer* create(bool bLogin = true)
    {
        LoginLayer *pRet = new LoginLayer(); 
        if (pRet && pRet->init(bLogin)) 
        { 
            pRet->autorelease();
            return pRet; 
        } 
        else
        { 
            delete pRet;
            pRet = NULL;
            return NULL;
        }
    }
	//virtual void keyBackClicked(void);					//手机返回按钮
	void setBoolFrom(bool b);

	void buttonEventWithUserLogin(Ref* target,cocos2d::ui::Widget::TouchEventType type);
    void buttonEventWithUserLoginClose(Ref* target,cocos2d::ui::Widget::TouchEventType type);
	void buttonEventWithLogin(Ref* target,cocos2d::ui::Widget::TouchEventType type);
    void buttonEventWithVisitor(Ref* target,cocos2d::ui::Widget::TouchEventType type);
    void buttonEventWithThirdPlatformLogin(Ref *ref,cocos2d::ui::Widget::TouchEventType type);

    virtual void editBoxEditingDidBegin(EditBox* editBox) {};
    virtual void editBoxEditingDidEnd(EditBox* editBox) {};
    virtual void editBoxTextChanged(EditBox* editBox, const std::string& text) {};
	virtual void editBoxReturn(EditBox* editBox){};
private:
    CCMenu* m_pLoginMenu;       //登陆
    CCMenu* m_pRegisterMenu;    //注册
	CCSize winSize;
	bool m_bLogin;
	bool m_from; //判断是从哪个界面进入到的登陆界面，如果是从设置里的切换进入，则返回到设置界面，如果是从菜单界面进入，则返回到大厅，默认为FALSE，从设置进
	CCMenuItemSprite * m_pDengluItemSprite;
};

#endif // __HELLOWORLD_SCENE_H__
