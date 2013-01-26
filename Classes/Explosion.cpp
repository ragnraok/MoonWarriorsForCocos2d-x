/*
 * Explosion.cpp
 *
 *  Created on: 2013-1-25
 *      Author: ragnarok
 */

#include "Explosion.h"
#include "Loger.h"
#include "Global.h"
#include <stdio.h>

Explosion::Explosion():
destroyAnim(NULL)
{

}

bool Explosion::init() {

	if (!CCSprite::init()) {
		return false;
	}

	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("explosion.plist");
	CCArray *animFrames = new CCArray();
	char filename[80];
	for (int i = 1; i < 35; i++) {
		if (i < 10) {
			sprintf(filename, "explosion_0%d.png", i);
		}
		else {
			sprintf(filename, "explosion_%d.png", i);
		}
		CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(filename);
		animFrames->addObject(frame);
	}
	CCAnimation *animation = CCAnimation::animationWithSpriteFrames(animFrames, 0.04);
	CCSpriteFrame *firstFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("explosion_01.png");
	this->initWithSpriteFrame(firstFrame);
	ccBlendFunc cbl = {GL_SRC_ALPHA, GL_ONE};
	this->setBlendFunc(cbl);

	CCSize contentSize = this->getContentSize();
	this->tmpHeight = contentSize.height;
	this->tmpWidth = contentSize.width;
	this->destroyAnim = CCAnimate::actionWithAnimation(animation);

	return true;
}

void Explosion::destroy() {
	this->getParent()->removeChild(this, true);
}

void Explosion::startRun() {
	//this->runAction(this->ccSequence);
	this->runAction(CCSequence::create(this->destroyAnim,
			CCCallFunc::create(this, callfunc_selector(Explosion::destroy))));
}




