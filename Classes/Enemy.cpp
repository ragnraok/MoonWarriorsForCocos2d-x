/*
 * Enemy.cpp
 *
 *  Created on: 2013-1-25
 *      Author: ragnarok
 */

#include "Enemy.h"
#include "Bullet.h"
#include "Explosion.h"
#include "Loger.h"
#include <stdio.h>

bool Enemy::init() {
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Enemy.plist", "Enemy.png");

	int type = int(CCRANDOM_0_1() * 5) % 5;
	char name[50];
	sprintf(name, "E%d.png", type);
	//LOGD(LOG_TAG, "name is %s", name);
	this->initWithSpriteFrameName(name);

	this->moveType = (CCRANDOM_0_1() + 0.3) > 1 ? 1 : 0;
	//LOGD(LOG_TAG, "moveType is %d", moveType);
	//LOGD(LOG_TAG, "created enemy");

	this->schedule(schedule_selector(Enemy::shoot), this->delayTime);

	return true;
}

void Enemy::update(float dt) {
	if (this->HP <= 0) {
		this->active = false;
	}
	this->_timetick += dt;
	if (this->_timetick > 0.1) {
		this->_timetick = 0;
		if (this->_hurtColorLife > 0) {
			this->_hurtColorLife--;
		}
		if (this->_hurtColorLife == 1) {
			this->setColor(ccWHITE);
		}
	}
}

void Enemy::destroy() {
	//SCORE += this->scoreValue;
	//Explosion *explosion = Explosion::create();
	//this->getParent()->addChild(explosion);
	//explosion->setPosition(this->getPosition());
	//LOGD(LOG_TAG, "finished addChild");
	//explosion->startRun();
	//GV::getInstance()->enemies->removeObject(this);
	this->removeFromParentAndCleanup(true);
}

void Enemy::shoot() {
	CCPoint pos = this->getPositionLua();
	Bullet *bullet = new Bullet(this->bulletSpeed, "W2.png");
	GV::getInstance()->enemy_bullets->addObject(bullet);
	this->getParent()->addChild(bullet, Enemy::zOrder, ENEMY_BULLET_TAG);
	bullet->setPosition(ccp(pos.x, pos.y - this->getContentSize().height * 0.2));
	bullet->setScale(SCALE_FACTOR);
}

void Enemy::hurt() {
	this->_hurtColorLife = 2;
	this->HP--;
	this->setColor(ccRED);
}

CCRect Enemy::collideRect() {
	CCSize contentSize = this->getContentSize();
	CCPoint pos = this->getPosition();
	return CCRectMake(pos.x - contentSize.width / 2 * SCALE_FACTOR, pos.y - contentSize.height / 2 * SCALE_FACTOR,
			contentSize.width * SCALE_FACTOR, contentSize.height * SCALE_FACTOR);
}



