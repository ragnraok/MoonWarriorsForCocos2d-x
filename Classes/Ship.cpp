/*
 * Ship.cpp
 *
 *  Created on: 2013-1-25
 *      Author: ragnarok
 */

#include "Ship.h"
#include "Loger.h"
#include "Bullet.h"
#include "Explosion.h"

Ship::Ship():
speed(220),
bulletSpeed(900),
HP(5),
bulletTypeValue(1),
bulletPowerValue(1),
throwBombing(false),
canBeAttack(true),
isThrowingBomb(false),
maxBulletPowerValue(4),
appearPosition(ccp(160 * SCALE_FACTOR, 60 * SCALE_FACTOR)),
hurtColorLife(0),
active(true),
timetick(0)
{}

bool Ship::init() {

	if (!CCSprite::init()) {
		return false;
	}

	bool bRet = false;

	do {
		// basically init
		CCTexture2D *shipTexture = CCTextureCache::sharedTextureCache()->addImage("ship01.png");
		this->initWithTexture(shipTexture, CCRectMake(0, 0, 60, 38));
		this->setTag(Ship::zOrder);
		this->setScale(SCALE_FACTOR);
		this->setPosition(this->appearPosition);


		// frames
		CCSpriteFrame *frame0 = CCSpriteFrame::createWithTexture(shipTexture, CCRectMake(0, 0, 60, 38));
		CCSpriteFrame *frame1 = CCSpriteFrame::createWithTexture(shipTexture, CCRectMake(60, 0, 60, 38));

		// ship animation
		CCArray *animFrames = new CCArray();
		animFrames->addObject(frame0);
		animFrames->addObject(frame1);
		//LOGD(LOG_TAG, "add all frames");
		CCAnimation *animation = CCAnimation::animationWithSpriteFrames(animFrames, 0.1f);
		//LOGD(LOG_TAG, "create animation");
		CCAnimate *animate = CCAnimate::actionWithAnimation(animation);
		//LOGD(LOG_TAG, "create animate");
		this->runAction(CCRepeatForever::create(animate));
		this->schedule(schedule_selector(Ship::shoot), 1 / 6.0);

		// revive effect
		this->canBeAttack = false;
		ghostSprite = CCSprite::createWithTexture(shipTexture, CCRectMake(0, 45, 60, 38));
		ghostSprite->setScale(SCALE_FACTOR * 8);
		ccBlendFunc cbl = {GL_SRC_ALPHA, GL_ONE};
		ghostSprite->setPosition(ccp(this->getContentSize().width / 2 * SCALE_FACTOR, 12 * SCALE_FACTOR));
		//LOGD(LOG_TAG, "created ghostSprite");
		this->addChild(ghostSprite, 3000, 99999);
		//LOGD(LOG_TAG, "added child");
		ghostSprite->runAction(CCScaleTo::create(0.5, SCALE_FACTOR, SCALE_FACTOR));
		//LOGD(LOG_TAG, "ghostSprite ran scale action");
		CCBlink *blinks = CCBlink::create(3.0, 9);
		CCCallFunc *makeBeAttack = CCCallFunc::create(this, callfunc_selector(Ship::setCanBeAttack));
		//LOGD(LOG_TAG, "created callback function");
		//this->runAction(CCSequence::create(CCDelayTime::create(0.5), makeBeAttack));
		this->runAction(CCDelayTime::create(0.5));
		this->runAction(blinks);
		//LOGD(LOG_TAG, "ran blinks");
		this->runAction(makeBeAttack);
		//LOGD(LOG_TAG, "ran call back");

		bRet = true;
	} while (0);

	return bRet;
}

void Ship::update(float dt) {
	// shit!

	// other sucks
	if (this->HP <= 0) {
		this->active = false;
	}
	this->timetick += dt;
	if (this->timetick > 0.1) {
		this->timetick = 0;
		if (this->hurtColorLife > 0) {
			this->hurtColorLife--;
		}
		if (this->hurtColorLife == 1) {
			this->setColor(ccWHITE);
		}
	}
}

void Ship::shoot(float dt) {
	int offset = 13 * SCALE_FACTOR;
	CCPoint pos = this->getPosition();
	CCSize contentSize = this->getContentSize();
	Bullet *bullet = new Bullet(this->bulletSpeed, "W1.png");
	bullet->setPosition(ccp(pos.x + offset, pos.y + 3 + contentSize.height * 0.3));
	GV::getInstance()->player_bullets->addObject(bullet);
	this->getParent()->addChild(bullet, Bullet::zOrder, PLAYER_BULLET_TAG);
	//bullet->runAction(CCRepeatForever::create(CCMoveBy::create(0.5, ccp(0, 30))));


	Bullet *bullet2 = new Bullet(this->bulletSpeed, "W1.png");
	bullet2->setPosition(ccp(pos.x - offset, pos.y + 3 + contentSize.height * 0.3));
	GV::getInstance()->player_bullets->addObject(bullet2);
	this->getParent()->addChild(bullet2, Bullet::zOrder, PLAYER_BULLET_TAG);
	//bullet2->runAction(CCRepeatForever::create(CCMoveBy::create(0.5, ccp(0, 30))));

}

void Ship::destroy() {
	LIFE--;
	CCPoint pos = this->getPosition();
	//this->getParent()->addChild(Explosion::create());
	this->getParent()->removeChild(this, true);
}

void Ship::hurt() {
	if (this->canBeAttack) {
		this->hurtColorLife = 2;
		this->HP--;
		this->setColor(ccRED);
	}
}

CCRect Ship::collideRect() {
	CCPoint pos = this->getPosition();
	CCSize contentSize = this->getContentSize();
	CCRect rect = CCRectMake(pos.x - contentSize.width / 2 * SCALE_FACTOR, pos.y - contentSize.height / 2 * SCALE_FACTOR,
			contentSize.width * SCALE_FACTOR, contentSize.height * SCALE_FACTOR);
	return rect;
}

void Ship::setCanBeAttack() {
	this->canBeAttack = true;
	this->setVisible(true);
	this->removeChild(this->ghostSprite, true);
}
