#ifndef __STARTMENU_H__
#define __STARTMENU_H__

#include "cocos2d.h"

using namespace cocos2d;

class StartMenu : public cocos2d::CCLayer
{
public:
	/*
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);

    // implement the "static node()" method manually
    CREATE_FUNC(StartMenu);*/

private:
	CCSprite *m_ship;
	CCSize winSize;

public:
	virtual bool init();

	static CCScene* scene();

	void menuCallback(CCObject *pSender);

	void onSettings(CCNode *pSender);
	void onAbout(CCNode *pSender);

	// button effect
	void onButtonEffect();

	void flareEffect(CCNode *node);

	// draw ship
	virtual void update(float dt);

	// new game
	void newGame();

	// create 'create' function
	CREATE_FUNC(StartMenu);
};

#endif // __STARTMENU_H__





