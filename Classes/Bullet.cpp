/*
 * Bullet.cpp
 *
 *  Created on: 2013-1-25
 *      Author: ragnarok
 */

#include "Bullet.h"

Bullet::Bullet(float bulletSpeed, char* weaponType):
active(true),
xVelocity(0),
yVelocity(200),
power(1),
HP(1)
{
	this->yVelocity = -bulletSpeed;
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("bullet.plist", "bullet.png");
	this->initWithSpriteFrameName(weaponType);
	ccBlendFunc cbl = {GL_SRC_ALPHA, GL_ONE};
	this->setBlendFunc(cbl);
	this->scheduleUpdate();
}

void Bullet::update(float dt) {
	CCPoint pos = this->getPosition();
	pos.x -= this->xVelocity * dt;
	pos.y -= this->yVelocity * dt;
	this->setPosition(pos);
	if (this->HP <= 0) {
		this->active = false;
	}
}

void Bullet::destroy() {
	CCSprite *explode = CCSprite::create("hit.jpg");
	ccBlendFunc cbl = {GL_SRC_ALPHA, GL_ONE};
	explode->setBlendFunc(cbl);
	explode->setPosition(this->getPosition());
	explode->setRotation(CCRANDOM_0_1() * 360);
	explode->setScale(0.75 * SCALE_FACTOR);
	this->getParent()->addChild(explode, 9999);
	this->removeFromParentAndCleanup(true);

	CCCallFunc *removeExplode = CCCallFunc::create(explode, callfunc_selector(CCSprite::removeFromParentAndCleanup));
	explode->runAction(CCScaleBy::create(0.3, 2, 2));
	explode->runAction(CCSequence::create(CCFadeOut::create(0.3), removeExplode));
}

void Bullet::hurt() {
	this->HP--;
}

CCRect Bullet::collideRect() {
	CCPoint pos = this->getPosition();
	return CCRectMake(pos.x - this->getContentSize().width / 2 * SCALE_FACTOR, pos.y - this->getContentSize().height / 2 * SCALE_FACTOR,
			this->getContentSize().width * SCALE_FACTOR, this->getContentSize().height * SCALE_FACTOR);
}

const bool Bullet::isActive() const {
	return this->active;
}
