/*
 * Bullet.h
 *
 *  Created on: 2013-1-25
 *      Author: ragnarok
 */

#ifndef BULLET_H_
#define BULLET_H_

#include "cocos2d.h"
#include "Global.h"

using namespace cocos2d;

class Bullet : public CCSprite
{
public:
	Bullet(float bulletSpeed, char* weaponType);

	void update(float dis);
	void destroy();
	void hurt();
	CCRect collideRect();

	const bool isActive() const;

	const static int zOrder = 3000;
private:
	bool active;
	float xVelocity;
	float yVelocity;
	float power;
	float HP;
	//int moveType;
};

//int Bullet::zOrder = 3000;

#endif /* BULLET_H_ */
