#include "StartMenu.h"
#include "SimpleAudioEngine.h"
#include "Effect.h"
#include "AboutLayer.h"
#include "GameScene.h"

using namespace cocos2d;
using namespace CocosDenshion;

/*
CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback) );
    pCloseItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20) );

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Thonburi", 34);

    // ask director the window size
    CCSize size = CCDirector::sharedDirector()->getWinSize();

    // position the label on the center of the screen
    pLabel->setPosition( ccp(size.width / 2, size.height - 20) );

    // add the label as a child to this layer
    this->addChild(pLabel, 1);

    // add "HelloWorld" splash screen"
    CCSprite* pSprite = CCSprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    pSprite->setPosition( ccp(size.width/2, size.height/2) );

    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);
    
    return true;
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
 }*/

bool StartMenu::init() {

	if (!CCLayer::init()) {
		return false;
	}

	this->winSize = CCDirector::sharedDirector()->getWinSize();
	CCSprite *background = CCSprite::create("loading.png");
	background->setScale(SCALE_FACTOR);
	background->setAnchorPoint(ccp(0, 0));
	this->addChild(background, 0, 1); // zOrder=0, tag=1

	CCSprite *logo = CCSprite::create("logo.png");
	logo->setPosition(ccp(winSize.width / 2, winSize.height / 2 + 80));
	this->addChild(logo,10, 1); // zOrder=10, tag=1

	CCSprite *newGameNormal = CCSprite::create("menu.png", CCRectMake(0, 0, 126, 33));
	CCSprite* newGameSelected = CCSprite::create("menu.png", CCRectMake(0, 33, 126, 33));
	CCSprite* newGameDisabled = CCSprite::create("menu.png", CCRectMake(0, 33 * 2, 126, 33));
	CCMenuItemSprite *newGame = CCMenuItemSprite::create(newGameNormal, newGameSelected, newGameDisabled,
			this, menu_selector(StartMenu::flareEffect));

	CCSprite *gameSettingNormal = CCSprite::create("menu.png", CCRectMake(126, 0, 126, 33));
	CCSprite *gameSettingSelected = CCSprite::create("menu.png", CCRectMake(126, 33, 126, 33));
	CCSprite *gameSettingDisabled = CCSprite::create("menu.png", CCRectMake(126, 33 * 2, 126, 33));
	CCMenuItemSprite *gameSetting = CCMenuItemSprite::create(gameSettingNormal, gameSettingSelected, gameSettingDisabled,
			this, menu_selector(StartMenu::onSettings));

	CCSprite *aboutNormal = CCSprite::create("menu.png", CCRectMake(252, 0, 126, 33));
	CCSprite *aboutSelected = CCSprite::create("menu.png", CCRectMake(252, 33, 126, 33));
	CCSprite *aboutDisabled = CCSprite::create("menu.png", CCRectMake(252, 33 * 2, 126, 33));
	CCMenuItemSprite *about = CCMenuItemSprite::create(aboutNormal, aboutSelected, aboutDisabled,
			this, menu_selector(StartMenu::onAbout));


	CCMenu *menu = CCMenu::create(newGame, gameSetting, about, NULL);
	menu->alignItemsVerticallyWithPadding(10);
	menu->setScale(SCALE_FACTOR);
	this->addChild(menu, 1, 2); // zOrder=1, tag=2
	menu->setPosition(ccp(winSize.width / 2 * 2, (winSize.height / 2 - 80) * 2));

	// create ship
	CCTexture2D *textCache = CCTextureCache::sharedTextureCache()->addImage("ship01.png");
	this->m_ship = CCSprite::createWithTexture(textCache, CCRectMake(0, 45, 60, 38));
	this->m_ship->setScale(SCALE_FACTOR);
	this->addChild(m_ship);

	CCPoint point = ccp(CCRANDOM_0_1() * winSize.width, 0);
	this->m_ship->setPosition(point);
	this->m_ship->runAction(CCMoveBy::create(2, ccp(CCRANDOM_0_1() * winSize.width, point.y + winSize.height  + 100)));
	this->schedule(schedule_selector(StartMenu::update), 0.1);

	return true;
}

CCScene* StartMenu::scene() {
	CCScene *scene = CCScene::create();

	StartMenu *startMenu = StartMenu::create();
	scene->addChild(startMenu);

	return scene;
}

void StartMenu::menuCallback(CCObject* pSender) {
}

void StartMenu::onButtonEffect() {
}

void StartMenu::flareEffect(CCNode* node) {
	Effect *effect = Effect::create();
	CCCallFunc *callback = CCCallFunc::create(this, callfunc_selector(StartMenu::newGame));
	effect->flareEffect(this, callback);
}

void StartMenu::update(float dt) {
	if (this->m_ship->getPosition().y > 480 * 2) {
		CCPoint pos = ccp(CCRANDOM_0_1() * winSize.width, 10);
		m_ship->setPosition(pos);
		m_ship->runAction(CCMoveBy::create(floor(5 * CCRANDOM_0_1()), ccp(CCRANDOM_0_1() * winSize.width, pos.y + 480 * 2)));
	}
}

void StartMenu::onSettings(CCNode* pSender) {
}

void StartMenu::onAbout(CCNode* pSender) {

	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(2, AboutScene::create()));
}

void StartMenu::newGame() {
	//CCDirector::sharedDirector()->end();
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(2, GameScene::create()));
}
