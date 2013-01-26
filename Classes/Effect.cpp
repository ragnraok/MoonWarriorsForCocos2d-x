/*
 * Effect.cpp
 *
 *  Created on: 2013-1-24
 *      Author: ragnarok
 */

#include "Effect.h"

void Effect::flareEffect(CCNode* parent, CCCallFunc* callback) {
	CCSprite *flareSprite = CCSprite::create("flare.jpg");
	flareSprite->setScale(2);
	parent->addChild(flareSprite, 10);

	ccBlendFunc cbl = {GL_SRC_ALPHA, GL_ONE};
	flareSprite->setBlendFunc(cbl);
	flareSprite->setOpacity(0);
	flareSprite->setPosition(ccp(-30, 297 * 2));
	flareSprite->setRotation(-120);
	flareSprite->setScale(0.2);

	CCActionInterval *opacityAnim = CCFadeTo::create(0.5, 255);
	CCActionInterval *opacityDim = CCFadeTo::create(1, 0);

	CCActionInterval *bigAnim = CCScaleBy::create(0.7, 1.2, 1.2);

	CCEaseSineOut *biggerEase = CCEaseSineOut::create(bigAnim);
	CCActionInterval *moveAnim = CCMoveBy::create(0.5, ccp(328 * 1.6, 0));
	CCEaseSineInOut *moveEase = CCEaseSineInOut::create(moveAnim);

	CCActionInterval *rotateAnim = CCRotateBy::create(2.5, 90);

	CCEaseExponentialInOut *rotateEase = CCEaseExponentialInOut::create(rotateAnim);

	CCScaleTo *bigger = CCScaleTo::create(0.5, 1);

	flareSprite->runAction(CCSequence::create(opacityAnim, biggerEase, opacityAnim, callback, NULL));
	flareSprite->runAction(moveEase);
	flareSprite->runAction(rotateEase);
	flareSprite->runAction(bigger);
}

bool Effect::init() {

}



