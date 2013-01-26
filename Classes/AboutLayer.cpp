/*
 * AboutLayer.cpp
 *
 *  Created on: 2013-1-24
 *      Author: ragnarok
 */

#include "AboutLayer.h"
#include "StartMenu.h"
#include "Loger.h"

AboutLayer::~AboutLayer() {
	if (this->label) {
		this->label->release();
		this->label = NULL;
	}
}

bool AboutLayer::init() {

	if ( CCLayer::init() )
	{
		//LOGE("Ragnarok", "123123123");
		CCSprite *background = CCSprite::create("loading.png");
		background->setAnchorPoint(ccp(0, 0));
		background->setScale(2.0);
		this->addChild(background);
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		this->label = CCLabelTTF::create("Game For Me\nGame For You","Artial", 50);
		label->retain();
		label->setColor(ccc3(255, 255, 255));
		label->setPosition( ccp(winSize.width/2, winSize.height/2) );
		this->addChild(this->label);

		CCLabelTTF *backLabel = CCLabelTTF::create("Back", "Artial", 45);
		backLabel->setColor(ccc3(255, 255, 255));
		CCMenuItemLabel *backMenuItemLabel = CCMenuItemLabel::create(backLabel, this, menu_selector(AboutLayer::backcallback));
		CCMenu *menu = CCMenu::create(backMenuItemLabel, NULL);
		menu->setPosition(ccp(winSize.width / 2, 40));
		this->addChild(menu);

		return true;
	}
	else
	{
		return false;
	}
}

void AboutLayer::backcallback(CCNode* pSender) {
	//CCScene *scene = CCScene::create();
	//scene->addChild(StartMenu::create());
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.2, StartMenu::scene()));
}

AboutScene::~AboutScene() {
	if (this->layer) {
		this->layer->release();
		this->layer = NULL;
	}
}

bool AboutScene::init() {
	if (CCScene::init()) {

		this->layer = AboutLayer::create();
		this->layer->retain();
		this->addChild(layer);
		return true;
	}
	else {
		return false;
	}
}



